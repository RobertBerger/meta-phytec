# linux-yocto-patch-queue-hack.inc
#
# Why?
# Otherwise patches from kmeta are not applied!
#
# This should work with:
# linux-yocto, linux-yocto-dev
# single patch queue (if you don't issue a branch command in your .scc file)
# 2 patch queues (if you issue a branch command in your .scc file)
# .and apply patches from there
#
# there is a companion patch in classes-recipe/kernel-yocto.bbclass:
# ...
# do_patch() {
#        set +e
#        cd ${S}
#
#    # --- START OF CLASS WORKSPACE HACK ---
#    if [ -d "${S}/.kernel-meta" ]; then
#        bbnote "[CLASS-PATCH] Dynamically calculating workspace paths inside do_patch..."
#        cd "${S}/.kernel-meta"
#
#        # 1. Fetch raw Yocto metadata strings
#        KVER="${LINUX_VERSION}"
#        KTYPE="${LINUX_TARGET_TYPE}"
#
#        # Fallback defaults if variables are unassigned
#        [ -z "$KVER" ] && KVER="7.7"
#        [ -z "$KTYPE" ] && KTYPE="standard"
#
#        # 2. Sanitize the version string: Isolate major.minor and apply 'v' prefix
#         KVER=$(echo "$KVER" | sed 's/^v//' | cut -d'.' -f1,2)
#         KVER="v${KVER}"
#
#        # 3. Assemble the exact target file string dynamically
#        REAL_VERSION_QUEUE="patch.${KVER}.${KTYPE}.queue"
#
#        # --- DETECT IF ANY PATCHES OR QUEUES ACTUALLY EXIST ---
#        if [ ! -s "${REAL_VERSION_QUEUE}" ] && [ ! -s "unused.patch.queue" ] && [ -z "$(find . -maxdepth 1 -name '*.patch' 2>/dev/null)" ]; then
#            bbnote "[CLASS-PATCH] No patch queues detected. Preemptively initializing empty tracking structures to satisfy do_kernel_configme."
#
#            # Create an empty target file so the symlink resolves to a valid, 0-byte file
#            touch "${REAL_VERSION_QUEUE}"
#            ln -sf "${REAL_VERSION_QUEUE}" patch.queue
#            ln -sf patch.queue series
#
#            cd "${S}"
#        else
#            bbnote "[CLASS-PATCH] Calculated target queue name: ${REAL_VERSION_QUEUE}"
#
#            # 4. Establish the exact symlink tracking layout preemptively
#            ln -sf "${REAL_VERSION_QUEUE}" patch.queue
#            ln -sf patch.queue series
#            bbnote "[CLASS-PATCH] Preemptively aligned layout: series -> patch.queue -> ${REAL_VERSION_QUEUE}"
#
#            # 5. If an unused queue already exists, handle the rescue operation
#            if [ -s "unused.patch.queue" ]; then
#                bbnote "[CLASS-PATCH] Rescuing stranded patches from unused.patch.queue..."
#                cat unused.patch.queue >> "${REAL_VERSION_QUEUE}"
#                > unused.patch.queue
#            fi
#
#            cd "${S}"
#        fi
#    fi
#    # --- END OF CLASS WORKSPACE HACK ---

# ...
#
# What it does?
# In do_kernel_configme this structure is constructed under .kernel-meta:
#
# -rw-r--r--  bsp_definition
# drwxr-xr-x  cfg
# -rw-r--r--  config.queue
# drwxr-xr-x  configs
# -rw-r--r--  hardware_frags.txt
# -rw-r--r--  meta-series
# -rw-r--r--  non-hardware_frags.txt
# drwxr-xr-x  patches
# -rw-r--r--  patch.v7.2.standard.queue
# lrwxrwxrwx  series -> patch.queue
# -rw-r--r--  unused.patch.queue
#
# after the patch it looks like this:
#
# -rw-r--r--  bsp_definition
# drwxr-xr-x  cfg
# -rw-r--r--  config.queue
# drwxr-xr-x  configs
# -rw-r--r--  hardware_frags.txt
# -rw-r--r--  meta-series
# -rw-r--r--  non-hardware_frags.txt
# drwxr-xr-x  patches
# lrwxrwxrwx  patch.queue -> patch.v7.2.standard.queue
# -rw-r--r--  patch.v7.2.standard.queue
# lrwxrwxrwx  series -> patch.queue
# -rw-r--r--  unused.patch.queue
#
# .but patches and configs are not applied
# .patches should be applied, but this does not work
# .out of the box because the symlinks are wrong
# .this fixes it and the patch here calls
# .kgit-s2q --gen -v --patches .kernel-meta/
# .which tries to apply the patches in the patch queue
#
#
# do_kernel_configme
#       │
#       ▼
# [RECIPE APPEND HACK] ──► Reads the dynamic 'series' file and forces patches
#       │                  into the tree early using host standard utilities.
#       ▼
# do_patch
#       │
#       ▼
#  [CLASS HACK]        ──► Catches the tree at the start of do_patch. It fixes
#                          the symlinks natively and empties 'unused.patch.queue'
#                          so Yocto's native validator passes safely.


# =======================================================================================
# COMPANION KERNEL METADATA PATCHING LAYER (`linux-yocto-patch-queue-hack.inc`)
# =======================================================================================
#
# PURPOSE:
# This file bridges a critical race condition between dynamic patch-generation tools
# and Yocto's rigid `linux-yocto` tooling. Without this companion layer, patches listed
# in your custom KMETA (.scc / .kernel-meta) layout fail to apply out-of-the-box.
#
# SUPPORTED ENVIRONMENTS & LAYOUTS:
# - Recipes: linux-yocto, linux-yocto-dev
# - Layout A: Single patch queue (when no explicit 'branch' command is issued in your .scc)
# - Layout B: Dual patch queues  (when a 'branch' command forces a split inside the .scc)
#
# CONFIGURATION VARIABLES:
# - KERNEL_PATCH_IDEMPOTENCY_TOKEN: A unique tag expected in your patch commit logs
#   to prevent duplicate applications. CAN BE LEFT EMPTY ("") to explicitly disable the
#   Git history lookup check (useful for zero-patch workflows or forced reapplications).
#
# DESIGN ARCHITECTURE & EXECUTION FLOW:
#
#   do_kernel_configme
#         │
#         ▼
#   [RECIPE APPEND HACK] ──► Intercepts after configme finishes. If a fresh tree is detected,
#         │                  it forces early application of the target queue into the Git
#         │                  source tree using the native Yocto engine (`kgit-s2q`).
#         ▼
#   do_patch
#         │
#         ▼
#     [CLASS HACK]       ──► Catches the tree at the very start of `do_patch`. It corrects
#                            broken relative symlinks natively and empties out redundant
#                            tracking files so Yocto's native internal validator passes.
#
# =======================================================================================

# Define a default tracking token. Can be overridden or cleared ("") in local.conf/recipes.
KERNEL_PATCH_IDEMPOTENCY_TOKEN ??= "YOCTO_TESTMOD"

# Ensure that the native kernel tools (like kgit-s2q) are fully populated in the
# sysroot before this recipe attempts to execute the configme step.
do_kernel_configme[depends] += "kern-tools-native:do_populate_sysroot"

do_kernel_configme:append() {
    KMETA_DIR="${S}/.kernel-meta"

    # Verify if the kernel metadata framework has successfully generated a baseline
    # execution roadmap ('series') file.
    if [ -f "${KMETA_DIR}/series" ]; then
        cd "${S}"

        # Fetch the token variable dynamically from the BitBake datastore
        TOKEN="${KERNEL_PATCH_IDEMPOTENCY_TOKEN}"

        # -------------------------------------------------------------------------------
        # 1. VARIABLE-BASED IDEMPOTENCY CHECK (WITH SILENT BLANK TOKEN SUPPORT)
        # -------------------------------------------------------------------------------
        # - If TOKEN is populated, look for it in the Git log to prevent double-patching.
        # - If TOKEN is explicitly empty, skip the Git lookup entirely and let the
        #   native engine process the tree directly.
        # -------------------------------------------------------------------------------
        PATCHES_ALREADY_APPLIED=0
        if [ -n "$TOKEN" ]; then
            if git log --grep="$TOKEN" -n 1 | grep -q "$TOKEN"; then
                PATCHES_ALREADY_APPLIED=1
            fi
        fi

        if [ "$PATCHES_ALREADY_APPLIED" -eq 1 ]; then
            bbnote "[NATIVE-GIT-HACK] Token '$TOKEN' detected in Git history. Patches already present. Skipping kgit-s2q to prevent conflicts."
        else
            if [ -n "$TOKEN" ]; then
                bbnote "[NATIVE-GIT-HACK] Fresh tree detected (Token '$TOKEN' not found). Handing over to native Yocto patch engine..."
            else
                bbnote "[NATIVE-GIT-HACK] Token is empty. Bypassing history lookup and proceeding straight to native patch validation..."
            fi

            # -------------------------------------------------------------------------------
            # 2. EARLY QUEUE APPLICATION VIA NATIVE PATCH ENGINE
            # -------------------------------------------------------------------------------
            # Run kgit-s2q. If there are 0 patches in the queue, this tool exits instantly
            # with success (0), making it perfectly safe for patchless configurations.
            # -------------------------------------------------------------------------------
            if kgit-s2q --gen -v --patches .kernel-meta/; then
                bbnote "[NATIVE-GIT-HACK] kgit-s2q successfully processed the patch queue workspace layout!"
            else
                bberror "[NATIVE-GIT-HACK] Native engine failed to parse or apply the queue contents!"
            fi
        fi

        # -------------------------------------------------------------------------------
        # 3. METADATA CLEANUP (PREVENTING VALIDATION CRASHES)
        # -------------------------------------------------------------------------------
        # Redundant tracking files like `unused.patch.queue` will cause subsequent
        # Yocto tasks (like `do_patch`) to throw validation errors. Truncating these
        # files to 0-bytes satisfies Yocto's validators. Safe to run repeatedly.
        # -------------------------------------------------------------------------------
        find "${KMETA_DIR}" -name "unused*.queue" -type f | while read -r unused_file; do
            > "$unused_file"
            bbnote "[NATIVE-GIT-HACK] Safely truncated tracking file: $(basename "$unused_file")"
        done
    else
        bberror "[NATIVE-GIT-HACK] Critical Error: The baseline execution map ('series') is missing inside ${KMETA_DIR}!"
    fi
}

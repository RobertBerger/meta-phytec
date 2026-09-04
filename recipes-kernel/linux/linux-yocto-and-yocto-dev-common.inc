# linux-yocto-and-yocto-dev-common.inc
# all this should be dynamic and not hardcoded

# SRC_URI:

# IN-PLACE REPLACEMENT: Swap the base server URI without wiping out other layers
#SRC_URI := "${@d.getVar('SRC_URI').replace('git://git.yoctoproject.org', 'git://github.com/RobertBerger')}"

inherit kernel-deploy-oftree res-instead-of-yocto-git shallow-recovery

COMPATIBLE_MACHINE  = "^("
COMPATIBLE_MACHINE .=  "phyboard-polis-imx8mm-5"
COMPATIBLE_MACHINE .= "|phyboard-pollux-imx8mp-3"
COMPATIBLE_MACHINE .= "|phygate-tauri-l-imx8mm-2"
COMPATIBLE_MACHINE .= "|imx8mp-libra-fpsc-1"
COMPATIBLE_MACHINE .= "|phyboard-segin-imx93-2"
COMPATIBLE_MACHINE .= "|phyboard-nash-imx93-1"
COMPATIBLE_MACHINE .= ")$"

ARCH = "arm64"

KBUILD_DEFCONFIG = "defconfig"
KCONFIG_MODE = "alldefconfig"

KCONF_BSP_AUDIT_LEVEL = "2"
KCONF_AUDIT_LEVEL = "2"

# Dynamically extract major.minor version from PV (e.g., 7.2+git... -> 7.2)
KBRANCH_VERSION = "${@'.'.join(d.getVar('PV').split('+')[0].split('.')[0:2])}"

# Match your metadata branch tracking (yocto-kernel-cache)
KMETA_BRANCH = "yocto-${KBRANCH_VERSION}"

# Define the branch name your build tree will use and patch
KBRANCH = "v${KBRANCH_VERSION}/${LINUX_KERNEL_TYPE}/${MACHINE}"
KBRANCH_DEFAULT = "${KBRANCH}"

# Set default overridable revisions for both tracking streams across ALL compatible machines
#SRCREV_machine ?= "${AUTOREV}"
#SRCREV_meta ?= "${AUTOREV}"

KMACHINE = "${MACHINE}"
KTYPE = "${LINUX_KERNEL_TYPE}"
KARCH = "arm64"

KERNEL_IMAGETYPES += "Image.lzma"
DEPENDS = "lzop-native"

#
# Image.xz: not supported by u-boot
# 12M Jan  3 18:08 Image.xz--6.17.6+git0+b4e4cfd96a_19af2117bc-r0-phyboard-pollux-imx8mp-3-20260103180414.bin
# 13M Jan  3 18:08 Image.lzma--6.17.6+git0+b4e4cfd96a_19af2117bc-r0-phyboard-pollux-imx8mp-3-20260103180414.bin
# 15M Jan  3 18:08 Image.zst--6.17.6+git0+b4e4cfd96a_19af2117bc-r0-phyboard-pollux-imx8mp-3-20260103180414.bin
# 17M Jan  3 18:08 Image.bz2--6.17.6+git0+b4e4cfd96a_19af2117bc-r0-phyboard-pollux-imx8mp-3-20260103180414.bin
# 18M Jan  3 18:08 Image.gz--6.17.6+git0+b4e4cfd96a_19af2117bc-r0-phyboard-pollux-imx8mp-3-20260103180414.bin
# 20M Jan  3 18:08 Image.lzo--6.17.6+git0+b4e4cfd96a_19af2117bc-r0-phyboard-pollux-imx8mp-3-20260103180414.bin
# 22M Jan  3 18:08 Image.lz4--6.17.6+git0+b4e4cfd96a_19af2117bc-r0-phyboard-pollux-imx8mp-3-20260103180414.bin

# U-Boot:
# -*- Enable LZ4 decompression support
# -*- Enable LZMA decompression support
# -*- Enable LZO decompression support
# -*- Enable gzip decompression support
# [ ] Enables zlib's uncompress() functionality (NEW)
# -*- Enable bzip2 decompression support
# [ ] Enable Zstandard decompression support
# [*] Enable LZMA decompression support for VPL build (NEW)
# [ ] Enable gzip decompression support for SPL build (NEW)
# [ ] Enable gzip decompression support for SPL build (NEW)

# -------------------------------------------------------------------------------
# DYNAMIC IDEMPOTENCY TOKEN MAPPING (BASED ON YOCTO KERNEL BRANCHES)
# -------------------------------------------------------------------------------
# This block inspects KMETA_BRANCH to dynamically change the validation token.
# It matches the official Yocto release kernel branches (e.g., yocto-6.18, yocto-7.2).
# -------------------------------------------------------------------------------

KERNEL_PATCH_IDEMPOTENCY_TOKEN:phyboard-pollux-imx8mp-3 = "${@ \
    'freescale: additional imx8mp-phyboard-pollux dtso files' if 'yocto-6.18' in (d.getVar('KMETA_BRANCH') or '') else \
    '' if 'yocto-7.2' in (d.getVar('KMETA_BRANCH') or '') or not d.getVar('KMETA_BRANCH') or d.getVar('KMETA_BRANCH') == 'master' else \
    'YOCTO_TESTMOD' \
}"


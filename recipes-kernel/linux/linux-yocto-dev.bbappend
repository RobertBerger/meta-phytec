# !!! Note !!!
# The default linux-yocto-dev uses:
# SRCREV_meta (yocto-kernel-cache) AUTOREV with branch hardcoded to master
# SRCREV_machine (linux-yocto-dev) AUTOREV with branch v7.2/standard/base
# !!! We change this behavior !!!
#
# via this class:
#   res-instead-of-yocto-git 
# and this config for the class:
#   RES_URI_AND_BRANCH_MAP = " \
#    git.yoctoproject.org/yocto-kernel-cache:master->git://github.com/RobertBerger/yocto-kernel-cache|${KMETA_BRANCH} \
#    git.yoctoproject.org/yocto-kernel-cache->git://github.com/RobertBerger/yocto-kernel-cache \
#
# we use as the branch for the yocto-kernel-cache the ${KMETA_BRANCH} instead of master
#
# and by using the configuration fragment preferred-provider-linux-yocto-dev-pinned.conf
# we pin the commit ids for both branches

inherit kernel-deploy-oftree
require linux-yocto-patch-queue-hack.inc
require linux-yocto-and-yocto-dev-common.inc

# check this comment the code afterwards in linux-yocto-and-yocto-dev-common.inc
# for the KERNEL_PATCH_IDEMPOTENCY_TOKEN:
#
# -------------------------------------------------------------------------------
# DYNAMIC IDEMPOTENCY TOKEN MAPPING (BASED ON YOCTO KERNEL BRANCHES)
# -------------------------------------------------------------------------------

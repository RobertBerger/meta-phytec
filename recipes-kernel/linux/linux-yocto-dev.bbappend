inherit kernel-deploy-oftree

FILESEXTRAPATHS:prepend := "${THISDIR}/linux-yocto-dev:"
#SRC_URI:append = " \
#  file://audit-disable.scc \
#"
#
#KERNEL_FEATURES += "audit-disable.scc"

# --> this is a special case
# we want this to be applied at the very end
# to overwrite everything else before
KERNEL_FEATURES:append = " cfg/nfs-boot-enable.scc"
# <-- this is a special case

COMPATIBLE_MACHINE  = "^("
COMPATIBLE_MACHINE .=  "phyboard-polis-imx8mm-5"
COMPATIBLE_MACHINE .= "|phyboard-pollux-imx8mp-3"
COMPATIBLE_MACHINE .= "|phygate-tauri-l-imx8mm-2"
COMPATIBLE_MACHINE .= "|imx8mp-phyflex-libra-rdk-2"
COMPATIBLE_MACHINE .= "|phyboard-segin-imx91-1"
COMPATIBLE_MACHINE .= "|phyboard-segin-imx93-2"
COMPATIBLE_MACHINE .= "|phyboard-nash-imx93-1"
COMPATIBLE_MACHINE .= ")$"

ARCH = "arm64"

KBUILD_DEFCONFIG = "defconfig"
KCONFIG_MODE = "alldefconfig"

#require linux-yocto-docker.inc

# -------

KCONF_BSP_AUDIT_LEVEL = "2"
KCONF_AUDIT_LEVEL = "2"

SRC_URI += "file://phyboard-pollux-imx8mp-3-kmeta;type=kmeta;destsuffix=phyboard-pollux-imx8mp-3-kmeta"

KMACHINE:phyboard-pollux-imx8mp-3 = "phyboard-pollux-imx8mp-3"

KERNEL_IMAGETYPES += "Image.lzma"

# KERNEL_IMAGETYPES += "Image.gz Image.bz2 Image.lz4 Image.lzma Image.lzo Image.zst Image.xz"
DEPENDS = "lzop-native"


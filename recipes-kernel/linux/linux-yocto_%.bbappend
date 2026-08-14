inherit kernel-deploy-oftree

FILESEXTRAPATHS:prepend := "${THISDIR}/linux-yocto:"
#SRC_URI:append = " \
#  file://audit-disable.scc \
#"

#KERNEL_FEATURES += "audit-disable.scc"

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

SRC_URI += "file://phyboard-pollux-imx8mp-3-kmeta;type=kmeta;destsuffix=phyboard-pollux-imx8mp-3-kmeta"

KMACHINE:phyboard-pollux-imx8mp-3 = "phyboard-pollux-imx8mp-3"

require linux-yocto-docker.inc

#LINUX_VERSION_EXTENSION:append:meson-gx = "-meson64"

# Add HDMI output support if display output is required
#KERNEL_FEATURES:append = "${@bb.utils.contains_any('DISTRO_FEATURES', 'x11 wayland', \
#    ' cfg/meson-hdmi.scc', '', d)}"

#KERNEL_FEATURES:append = "${@bb.utils.contains('DISTRO_FEATURES', 'pci', \
#    ' cfg/meson-pci.scc', '', d)}"

#KERNEL_IMAGETYPES += "Image.zst"

KERNEL_IMAGETYPES += "Image.lzma"

# KERNEL_IMAGETYPES += "Image.gz Image.bz2 Image.lz4 Image.lzma Image.lzo Image.zst Image.xz"
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

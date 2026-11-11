# aarch64 specifics

ARCH = "arm64"


# probably not needed
KARCH = "arm64"

KERNEL_IMAGETYPES += "Image.lzma"
#KERNEL_IMAGETYPES:append:aarch64 = " Image.lzma"
DEPENDS += "lzop-native"

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


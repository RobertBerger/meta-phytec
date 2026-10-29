require phytec-machine-common.inc

# Common settings for PHYTEC's i.MX8 boards

PREFERRED_PROVIDER_virtual/bootloader ?= "u-boot-master"
PREFERRED_PROVIDER_virtual/bootloader:mx8-nxp-bsp ?= "u-boot-phytec-imx"
PREFERRED_PROVIDER_virtual/kernel ?= "linux-yocto-dev"
PREFERRED_PROVIDER_virtual/kernel:mx8-nxp-bsp ?= "linux-phytec-imx"
PREFERRED_PROVIDER_imx-boot = "imx-boot-phytec"
PREFERRED_PROVIDER_opencl-headers:imxgpu = "imx-gpu-viv"
PREFERRED_PROVIDER_linux-imx-mfgtool:mx8-nxp-bsp = "linux-imx-mfgtool"
PREFERRED_PROVIDER_virtual/libgles3:mx8-nxp-bsp = "imx-gpu-viv"

# dont install kernelimage to rootfs
RRECOMMENDS:${KERNEL_PACKAGE_NAME}-base = ""

# remove ath10k firmware to save space
MACHINE_FIRMWARE:remove:mx8-nxp-bsp = "linux-firmware-ath10k"

KERNEL_MODULE_AUTOLOAD += " cryptodev"

# Wic
IMAGE_CLASSES += "wic-helper wic-imx8-helper"
EXTERNAL_KERNEL_DEVICETREE ??= ""
IMAGE_BOOT_FILES += "oftree ${EXTERNAL_KERNEL_DEVICETREE}"

# wks -> wks.in since we want variables to be replaced in it
WKS_FILE = "imx8m-sdimage.wks.in"

WKS_FILES:mx8m-generic-bsp ?= "imx8m-sdimage.wks.in"
WKS_FILES:mx8x-nxp-bsp ?= "imx8x-sdimage.wks.in"
WKS_BOOTIMAGESIZE ?= "50"

IMX_DEFAULT_ATF_PROVIDER:use-mainline-bsp ?= "trusted-firmware-a"
# MMC user area bootloader image offset
BOOTLOADER_SEEK:mx8m-generic-bsp ?= "33"
BOOTLOADER_SEEK:mx8mn-generic-bsp ?= "32"
BOOTLOADER_SEEK:mx8mp-generic-bsp ?= "32"
BOOTLOADER_SEEK:mx8x-generic-bsp ?= "32"
# eMMC boot partition bootloader image offset
BOOTLOADER_SEEK_EMMC:mx8m-generic-bsp ?= "33"
BOOTLOADER_SEEK_EMMC:mx8mn-generic-bsp ?= "0"
BOOTLOADER_SEEK_EMMC:mx8mp-generic-bsp ?= "0"

UBOOT_ARCH = "arm64"
UBOOT_BINARY = "flash.bin"

# Device information used by RAUC and some of its dependencies
EMMC_DEV:mx8mq-generic-bsp ?= "0"
EMMC_DEV:mx8mm-generic-bsp ?= "2"
EMMC_DEV:mx8mn-generic-bsp ?= "2"
EMMC_DEV:mx8mp-generic-bsp ?= "2"
# SD card support:
SD_DEV:mx8mp-generic-bsp ?= "1"

# this is needed for
# Bootloader
# [slot.bootloader.0]
# device=/dev/mmcblk@SD_DEV@
# type=boot-raw-fallback
# region-start=@SD_BOOT_REG_START@
# region-size=@SD_BOOT_REG_SIZE@
#
# How this works on the i.MX8MP
#
# • region-start=32K:
# On the i.MX8M Plus, the System-on-Chip (SoC) internal ROM bootloader
# is hardcoded to look for the primary bootloader vector offset starting
# exactly at 32 KB (sector 64) on an SD card.
# • region-size=8M:
# This tells RAUC to reserve an 8 MB block on the disk. RAUC will internally
# split this into two equal 4 MB halves:
#       • First Half (32 KB offset): Where our active imx-boot file is written.
#       • Second Half (4.032 MB offset): Where the fallback redundancy imx-boot file is safely staged.

SD_DEV:mx8mp-generic-bsp ?= "1"
SD_BOOT_REG_START:mx8mp-generic-bsp ?= "32K"
SD_BOOT_REG_SIZE:mx8mp-generic-bsp = "8M"

# • Raw Fallback Bootloader ends at: 8,421,376 bytes (~8.03 MiB).
# • Partition 1 (boot.0) starts at: 16,777,216 bytes (16 MiB).
# • Safe Buffer Window: ~7.96 MiB.
# Since the compiled bootloader.img is only 2.56 MiB, this provides absolute
# separation and prevents raw flashing loops from bleeding into Partition 1.
BOOT_PART_OFFSET:mx8mp-generic-bsp = "16MiB"

# partup
IMAGE_CLASSES += "image-types-partup"
require partup-layout-config.inc

# kernel
KERNEL_ALT_IMAGETYPE =+ " vmlinux "

# Default images to build
IMAGE_FSTYPES = " \
    ${@bb.utils.contains('DISTRO_FEATURES', 'rauc', '', 'wic.xz wic.bmap', d)} \
    tar.bz2 partup \
"

# use append if we don't want it easily to be overwritten by others:
# IMAGE_FSTYPES:append = " ${@bb.utils.contains('DISTRO_FEATURES', 'rauc', '', 'wic.xz wic.bmap', d)} tar.bz2 partup"

MACHINE_FEATURES:append:use-nxp-bsp = " caam optee"
MACHINE_FEATURES:remove:mx8x-nxp-bsp = " optee"

QEMUVERSION = "8.2%"

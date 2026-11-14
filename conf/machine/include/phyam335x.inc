require phytec-machine-common.inc

#Taken from TI yocto BSP Layer Version 05-2014, original name:ti33xx.inc
SOC_FAMILY = "ti-soc:ti33x"
require conf/machine/include/soc-family.inc
DEFAULTTUNE ?= "cortexa8thf-neon"
require conf/machine/include/arm/armv7a/tune-cortexa8.inc
# List common SoC features
MACHINE_FEATURES = "usbgadget usbhost vfat ext2 screen alsa ethernet can"

# Sub-architecture support adapted fom fsl-arm
MACHINE_SOCARCH = "${TUNE_PKGARCH}-ti33x"
PACKAGE_EXTRA_ARCHS:append = " ${MACHINE_SOCARCH}"

# Bootloader
# Barebox replaced by U-Boot:
#PREFERRED_PROVIDER_virtual/bootloader ?= "barebox"
#PREFERRED_PROVIDER_virtual/prebootloader ?= "barebox-ipl"
#BAREBOX_IPL_IMAGE_NAME = "MLO-${MACHINE}-${PKGV}-${PKGR}${IMAGE_VERSION_SUFFIX}"
#BAREBOX_IPL_BIN_LINK_NAME = "MLO"

# U-Boot:
UBOOT_IMAGE_NAME = "u-boot-${MACHINE}-${PKGV}-${PKGR}${IMAGE_VERSION_SUFFIX}"
UBOOT_BINARY = "u-boot.img"
SPL_BINARY = "MLO"

# Kernel 
PREFERRED_PROVIDER_virtual/kernel ?= "linux-phytec"
PREFERRED_PROVIDER_amx3-cm3 ?= "amx3-cm3-phy"
KERNEL_IMAGETYPE ?= "zImage"
KERNEL_IMAGETYPES ?= "zImage Image"

# --> fitimage 
# Enables the additional files (such as linux.bin) required by the new FIT image recipe
KERNEL_CLASSES += "kernel-fit-extra-artifacts"

# Prevents the bare kernel package from being installed by default (since we are using the FIT image)
RRECOMMENDS:${KERNEL_PACKAGE_NAME}-base = ""

# Sets the FIT image as a dependency for the rootfs build.
MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "linux-yocto-fitimage"
KERNEL_DEPLOY_DEPEND = "linux-yocto-fitimage:do_deploy"
# <-- fitImage

# Install modules in initramfs and rootfs
MACHINE_EXTRA_RRECOMMENDS += "kernel-modules"
KERNEL_MODULE_AUTOLOAD += " cryptodev"

SERIAL_CONSOLES ?= "115200;ttyS0"
# dont install kernelimage to rootfs
RRECOMMENDS:${KERNEL_PACKAGE_NAME}-base = ""

# rootfs images
# Use the expected value of the ubifs filesystem's volume name in the kernel
UBI_VOLNAME = "root"
# The biggest NANDs on current modules are 1GB. With current partition layout,
# this sums up to 7943 LEBs available for the ubifs
MKUBIFS_ARGS = "--min-io-size 2048 --leb-size 129024 --max-leb-cnt 7943 --space-fixup"
UBINIZE_ARGS = "--min-io-size 2048 --peb-size 128KiB --sub-page-size 512"

# xserver
PREFERRED_PROVIDER_virtual/xserver ?= "xserver-xorg"
# For built-in LCD, add xf86-input-tslib
XSERVER = "xserver-xorg \
           xf86-input-evdev \
           xf86-video-fbdev \
           xf86-input-keyboard"

# OpenGLES support for AM335x SGX Core
PREFERRED_PROVIDER_virtual/mesa ?= "mesa-pvr"
PREFERRED_PROVIDER_virtual/egl ?= "mesa-pvr"
PREFERRED_PROVIDER_virtual/libgles1 ?= "mesa-pvr"
PREFERRED_PROVIDER_virtual/libgles2 ?= "mesa-pvr"
PREFERRED_PROVIDER_virtual/libgles3 ?= "mesa-pvr"
PREFERRED_PROVIDER_virtual/libgbm ?= "mesa-pvr"
PREFERRED_PROVIDER_virtual/libglx ?= "mesa-pvr"
PREFERRED_PROVIDER_virtual/libgl ?= "mesa-pvr"

PREFERRED_PROVIDER_virtual/gpudriver ?= "ti-sgx-ddk-km"

QT_QPA_DEFAULT_PLATFORM ?= "${@bb.utils.contains('MACHINE_FEATURES', 'gpu', 'eglfs', 'linuxfb', d)}"

#WIC
IMAGE_CLASSES += "wic-helper"
IMAGE_CLASSES += "wic-am335x-helper"
EXTERNAL_KERNEL_DEVICETREE ??= ""

# --> fitimage stuff with extlinux (not used here)
#KERNEL_IMAGETYPE = "zImage"
## Deploy files to the FAT partition
#IMAGE_BOOT_FILES = "u-boot.img MLO fitImage uEnv.txt"
## Enable the automated extlinux configuration generation
#UBOOT_EXTLINUX = "1"
#UBOOT_EXTLINUX_LABELS = "default"
## cosmetic changes:
#UBOOT_EXTLINUX_FDT = ""
#UBOOT_EXTLINUX_FDTDIR = ""
## Define the configuration file contents (Added the missing mandatory variable)
#UBOOT_EXTLINUX_ROOT = "root=/dev/mmcblk0p2"
#UBOOT_EXTLINUX_KERNEL_IMAGE = "../fitImage"
#UBOOT_EXTLINUX_MENU_DESCRIPTION = "FIT-Local"
#UBOOT_EXTLINUX_BOOTARGS = "rootwait rw earlycon"
#UBOOT_EXTLINUX_CONSOLE = "console=ttyS0,115200n8"
## Instruct the WIC image builder to map the generated layout to your boot partition
#IMAGE_BOOT_FILES:append = " extlinux.conf;extlinux/extlinux.conf"
# <-- fitimage stuff witch extlinux (not used here)

# --> fitimage stuff without extlinux
# Keep the standard raw kernel image type required by modern Yocto
KERNEL_IMAGETYPE = "zImage"

# Deploy only the bootloader, standalone FIT image, and U-Boot RAUC script
# MLO need to written first - we use raw since partup
# does not support mkfs-extraopts like wic --mkfs-extraopts "-g 255/63 -a -s 8"
# which means it will not boot from a FAT partition without raw
IMAGE_BOOT_FILES = "MLO u-boot.img fitImage uEnv.txt"
# ?
BOOTLOADER_FILE:ti33x = ""
UBOOT_LOADADDRESS = "0x82000000"
UBOOT_ENTRYPOINT = "0x82000000"
# <-- fitimage stuff without extlinux

#do_image_wic[depends] += "\
#    virtual/prebootloader:do_deploy \
#"
# WKS_FILES:ti33x ?= "am335x-sdimage.wks"
WKS_FILES:ti33x ?= "am335x-sdimage.wks.in"
WKS_BOOTIMAGESIZE ?= "20"

# Device information used by RAUC and some of its dependencies
SD_DEV:ti33x ?= "0"
EMMC_DEV:ti33x ?= "1"
NAND_DEV:ti33x ?= "0"

# default images to build
IMAGE_FSTYPES ?= "tar.gz wic wic.bmap ext4 \
    ${@bb.utils.contains('MACHINE_FEATURES', 'emmc', 'emmc', 'ubifs', d)}"

# Default images to build
IMAGE_FSTYPES += " \
    ${@bb.utils.contains('DISTRO_FEATURES', 'rauc', '', 'wic.xz wic.bmap', d)} \
    tar.bz2 partup \
"

# partup
IMAGE_CLASSES += "image-types-partup"
require partup-layout-config.inc

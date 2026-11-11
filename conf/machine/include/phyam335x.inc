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
#PREFERRED_PROVIDER_virtual/bootloader ?= "barebox"
#PREFERRED_PROVIDER_virtual/prebootloader ?= "barebox-ipl"
#BAREBOX_IPL_IMAGE_NAME = "MLO-${MACHINE}-${PKGV}-${PKGR}${IMAGE_VERSION_SUFFIX}"
#BAREBOX_IPL_BIN_LINK_NAME = "MLO"

UBOOT_IMAGE_NAME = "u-boot-${MACHINE}-${PKGV}-${PKGR}${IMAGE_VERSION_SUFFIX}"
UBOOT_BINARY = "u-boot.img"
SPL_BINARY = "MLO"

# Kernel 
PREFERRED_PROVIDER_virtual/kernel ?= "linux-phytec"
PREFERRED_PROVIDER_amx3-cm3 ?= "amx3-cm3-phy"
KERNEL_IMAGETYPE ?= "zImage"
KERNEL_IMAGETYPES ?= "zImage Image"

#EERNEL_IMAGETYPE = "fitImage"
#KERNEL_IMAGETYPES = "fitImage"

#KERNEL_IMAGETYPE = "zImage"
#KERNEL_IMAGETYPES = "Image zImage"

# --> fitimage 

# Der Kernel baut das unkomprimierte Image
#KERNEL_IMAGETYPE = "Image"
#KERNEL_IMAGETYPES = "Image zImage"

# Aktiviert die vom neuen FIT-Image-Rezept benötigten Zusatzdateien (wie linux.bin)
KERNEL_CLASSES += "kernel-fit-extra-artifacts"

# Verhindert, dass das nackte Kernel-Paket standardmäßig installiert wird (da du das FIT-Image nutzt)
RRECOMMENDS:${KERNEL_PACKAGE_NAME}-base = ""

# Setzt das FIT-Image als Abhängigkeit für den Rootfs-Bau
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

# --> fitimage stuff

#IMAGE_BOOT_FILES = "barebox.bin MLO ${KERNEL_IMAGETYPE} oftree ${EXTERNAL_KERNEL_DEVICETREE}"
#IMAGE_BOOT_FILES = "u-boot.img MLO ${KERNEL_IMAGETYPE} oftree ${EXTERNAL_KERNEL_DEVICETREE} uEnv.txt"
#IMAGE_BOOT_FILES = "u-boot.img MLO ${KERNEL_IMAGETYPE} oftree ${EXTERNAL_KERNEL_DEVICETREE} uEnv.txt fitImage"

# 1. Enable the automated extlinux configuration generation
#UBOOT_EXTLINUX = "1"
#UBOOT_EXTLINUX_LABELS = "default"

# 2. Define the configuration file contents
#UBOOT_EXTLINUX_KERNEL:default = "../fitImage"
#UBOOT_EXTLINUX_MENU_DESCRIPTION:default = "FIT-Local"
#UBOOT_EXTLINUX_BOOTARGS:default = "console=ttyS0,115200n8 earlycon root=/dev/mmcblk0p2 rootwait rw"

# 3. Ensure the generated file gets added to your boot partition image
#IMAGE_BOOT_FILES:append = " extlinux.conf;extlinux/extlinux.conf"

# Set the primary kernel target to FIT
#KERNEL_IMAGETYPE = "fitImage"
KERNEL_IMAGETYPE = "zImage"
# Deploy files to the FAT partition
#IMAGE_BOOT_FILES = "u-boot.img MLO ${KERNEL_IMAGETYPE} oftree ${EXTERNAL_KERNEL_DEVICETREE} uEnv.txt"
#IMAGE_BOOT_FILES = "u-boot.img MLO fitImage oftree ${EXTERNAL_KERNEL_DEVICETREE} uEnv.txt"
IMAGE_BOOT_FILES = "u-boot.img MLO fitImage uEnv.txt"

# 1. Enable the automated extlinux configuration generation
UBOOT_EXTLINUX = "1"
UBOOT_EXTLINUX_LABELS = "default"
# cosmetic changes:
UBOOT_EXTLINUX_FDT = ""
UBOOT_EXTLINUX_FDTDIR = ""

# 2. Define the configuration file contents (Added the missing mandatory variable)
#UBOOT_EXTLINUX_ROOT = "/dev/mmcblk0p2"
UBOOT_EXTLINUX_ROOT = "root=/dev/mmcblk0p2"
UBOOT_EXTLINUX_KERNEL_IMAGE = "../fitImage"
UBOOT_EXTLINUX_MENU_DESCRIPTION = "FIT-Local"
#UBOOT_EXTLINUX_KERNEL_ARGS = "console=ttyS0,115200n8 earlycon root=/dev/mmcblk0p2 rootwait rw"
#BOOT_EXTLINUX_BOOTARGS = "console=ttyS0,115200n8 earlycon root=/dev/mmcblk0p2 rootwait rw"
#UBOOT_EXTLINUX_BOOTARGS = "rootwait rw console=ttyS0,115200n8 earlycon"
#UBOOT_EXTLINUX_CONSOLE = "console=ttyS0,115200n8"
UBOOT_EXTLINUX_BOOTARGS = "rootwait rw earlycon"
UBOOT_EXTLINUX_CONSOLE = "console=ttyS0,115200n8"




# 6. Instruct the WIC image builder to map the generated layout to your boot partition
IMAGE_BOOT_FILES:append = " extlinux.conf;extlinux/extlinux.conf"

# <-- fitimage stuff

#do_image_wic[depends] += "\
#    virtual/prebootloader:do_deploy \
#"
WKS_FILES:ti33x ?= "am335x-sdimage.wks"
WKS_BOOTIMAGESIZE ?= "20"

# Device information used by RAUC and some of its dependencies
EMMC_DEV:ti33x ?= "1"
NAND_DEV:ti33x ?= "0"

# default images to build
IMAGE_FSTYPES ?= "tar.gz wic wic.bmap ext4 \
    ${@bb.utils.contains('MACHINE_FEATURES', 'emmc', 'emmc', 'ubifs', d)}"

# partup
IMAGE_CLASSES += "image-types-partup"
require partup-layout-config.inc


IMAGE_CMD:emmc:append () {
        if [ -e ${EMMCIMG} ]; then
                # Target U-Boot's MLO instead of Barebox IPL
                # Use "MLO" directly or UBOOT_SPL_IMAGE if mapped to a link name
                UBOOT_SPL_BIN="MLO"

                if [ ! -e ${DEPLOY_DIR_IMAGE}/${UBOOT_SPL_BIN} ]; then
                        bberror "U-Boot SPL binary (${UBOOT_SPL_BIN}) not found in ${DEPLOY_DIR_IMAGE}!"
                fi

                # copy the MLO to address 0x0 and keep the partition table
                dd if=${DEPLOY_DIR_IMAGE}/${UBOOT_SPL_BIN} of=${EMMCIMG} bs=446 count=1 conv=notrunc
                dd if=${DEPLOY_DIR_IMAGE}/${UBOOT_SPL_BIN} of=${EMMCIMG} skip=1 seek=1 conv=notrunc
                # copy the MLO to address 0x20000, 0x40000, 0x60000
                dd if=${DEPLOY_DIR_IMAGE}/${UBOOT_SPL_BIN} of=${EMMCIMG} seek=768 bs=512 conv=notrunc
                dd if=${DEPLOY_DIR_IMAGE}/${UBOOT_SPL_BIN} of=${EMMCIMG} seek=512 bs=512 conv=notrunc
                dd if=${DEPLOY_DIR_IMAGE}/${UBOOT_SPL_BIN} of=${EMMCIMG} seek=256 bs=512 conv=notrunc
        fi
}

IMAGE_CMD:emmc () {
        EMMCIMG=${IMAGE_NAME}.emmc
        WICIMG=${IMAGE_NAME}.wic
        cp ${IMGDEPLOYDIR}/${WICIMG} ${IMGDEPLOYDIR}/${EMMCIMG}

        ln -sf ${EMMCIMG} ${IMGDEPLOYDIR}/${IMAGE_LINK_NAME}.emmc
}

IMAGE_TYPEDEP:emmc = "wic"

# Dropped virtual/prebootloader requirement entirely
do_image_emmc[depends] += " \
    parted-native:do_populate_sysroot \
    mtools-native:do_populate_sysroot \
    dosfstools-native:do_populate_sysroot \
    e2fsprogs-native:do_populate_sysroot \
    virtual/kernel:do_deploy \
    virtual/bootloader:do_deploy \
"

#IMAGE_CMD:emmc:append () {
#	if [ -e ${EMMCIMG} ]; then
#		# copy the MLO to address 0x0 and keep the partition table
#		dd if=${DEPLOY_DIR_IMAGE}/${BAREBOX_IPL_BIN_LINK_NAME} of=${EMMCIMG} bs=446 count=1 conv=notrunc
#		dd if=${DEPLOY_DIR_IMAGE}/${BAREBOX_IPL_BIN_LINK_NAME} of=${EMMCIMG} skip=1 seek=1 conv=notrunc
#		# copy the MLO to address 0x20000, 0x40000, 0x60000
#		dd if=${DEPLOY_DIR_IMAGE}/${BAREBOX_IPL_BIN_LINK_NAME} of=${EMMCIMG} seek=768 bs=512 conv=notrunc
#		dd if=${DEPLOY_DIR_IMAGE}/${BAREBOX_IPL_BIN_LINK_NAME} of=${EMMCIMG} seek=512 bs=512 conv=notrunc
#		dd if=${DEPLOY_DIR_IMAGE}/${BAREBOX_IPL_BIN_LINK_NAME} of=${EMMCIMG} seek=256 bs=512 conv=notrunc
#	fi
#}

#IMAGE_CMD:emmc () {
#	EMMCIMG=${IMAGE_NAME}.emmc
#	WICIMG=${IMAGE_NAME}.wic
#	cp ${IMGDEPLOYDIR}/${WICIMG} ${IMGDEPLOYDIR}/${EMMCIMG}
#
#	ln -sf ${EMMCIMG} ${IMGDEPLOYDIR}/${IMAGE_LINK_NAME}.emmc
#}

#IMAGE_TYPEDEP:emmc = "wic"

#do_image_emmc[depends] += " \
#    parted-native:do_populate_sysroot \
#    mtools-native:do_populate_sysroot \
#    dosfstools-native:do_populate_sysroot \
#    e2fsprogs-native:do_populate_sysroot \
#    virtual/kernel:do_deploy \
#    virtual/bootloader:do_deploy \
#    virtual/prebootloader:do_deploy \
#"

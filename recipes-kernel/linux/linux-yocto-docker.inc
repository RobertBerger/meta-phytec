#include cfg/enable-legacy-ip-tables.scc
#include cfg/docker-overlayfs.scc
#include cfg/kubernetes.scc

# only for 6.17 kernel needed for docker?
KERNEL_FEATURES:append = "${@bb.utils.contains('DISTRO_FEATURES', 'virtualization', ' cfg/enable-legacy-ip-tables.scc', '', d)}"

# - "overlay":
#    - CONFIG_OVERLAY_FS: enabled
KERNEL_FEATURES:append = "${@bb.utils.contains('DISTRO_FEATURES', 'virtualization', ' cfg/docker-overlayfs.scc', '', d)}"

KERNEL_FEATURES:append = "${@bb.utils.contains('DISTRO_FEATURES', 'virtualization', ' cfg/kubernetes.scc', '', d)}"

#KERNEL_FEATURES:append = "${@bb.utils.contains('DISTRO_FEATURES', 'virtualization', ' features/nf_tables/nf_tables.scc', '', d)}"
# extra nft stuff:
KERNEL_FEATURES:append = "${@bb.utils.contains('DISTRO_FEATURES', 'virtualization', ' features/nf_tables/nft_test.scc', '', d)}"

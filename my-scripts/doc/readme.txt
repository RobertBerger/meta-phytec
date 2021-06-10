1) create a new repo on github

2) add my-scripts dir

cd meta-phytec

echo "# meta-phytec fork" >> README.md

git init

git add .

git commit -m "first commit"

git remote add origin git@github.com:RobertBerger/meta-phytec.git

git push -u origin master

3) use my repo

mv meta-phytec meta-phytec.ori
git clone git@github.com:RobertBerger/meta-phytec.git

4) add upstream

cd meta-phytec

git remote add official-upstream git://github.com/phytec/meta-phytec

$ git fetch official-upstream

warning: no common commits
remote: Enumerating objects: 19497, done.
remote: Counting objects: 100% (19497/19497), done.
remote: Compressing objects: 100% (4931/4931), done.
remote: Total 19497 (delta 14128), reused 18843 (delta 13474), pack-reused 0
Receiving objects: 100% (19497/19497), 2.86 MiB | 6.63 MiB/s, done.
Resolving deltas: 100% (14128/14128), done.
From git://github.com/phytec/meta-phytec
 * [new branch]        1.8.1-phy2-fix  -> official-upstream/1.8.1-phy2-fix
 * [new branch]        1.8.1-phy6-fix  -> official-upstream/1.8.1-phy6-fix
 * [new branch]        dizzy           -> official-upstream/dizzy
 * [new branch]        dunfell         -> official-upstream/dunfell
 * [new branch]        fido            -> official-upstream/fido
 * [new branch]        gatesgarth      -> official-upstream/gatesgarth
 * [new branch]        hardknott       -> official-upstream/hardknott
 * [new branch]        jethro          -> official-upstream/jethro
 * [new branch]        krogoth         -> official-upstream/krogoth
 * [new branch]        master          -> official-upstream/master
 * [new branch]        morty           -> official-upstream/morty
 * [new branch]        pyro            -> official-upstream/pyro
 * [new branch]        rocko           -> official-upstream/rocko
 * [new branch]        sumo            -> official-upstream/sumo
 * [new branch]        thud            -> official-upstream/thud
 * [new branch]        warrior         -> official-upstream/warrior
 * [new branch]        zeus            -> official-upstream/zeus
 * [new tag]           1.7.3-phy1      -> 1.7.3-phy1
 * [new tag]           1.8.1-phy2-fix1 -> 1.8.1-phy2-fix1
 * [new tag]           1.8.1-phy6-fix1 -> 1.8.1-phy6-fix1
 * [new tag]           1.7.0-phy1      -> 1.7.0-phy1
 * [new tag]           1.7.0-phy2      -> 1.7.0-phy2
 * [new tag]           1.7.0-phy3      -> 1.7.0-phy3
 * [new tag]           1.7.2-phy1      -> 1.7.2-phy1
 * [new tag]           1.7.2-phy2      -> 1.7.2-phy2
 * [new tag]           1.8.1-phy1      -> 1.8.1-phy1
 * [new tag]           1.8.1-phy2      -> 1.8.1-phy2
 * [new tag]           1.8.1-phy3      -> 1.8.1-phy3
 * [new tag]           1.8.1-phy4      -> 1.8.1-phy4
 * [new tag]           1.8.1-phy5      -> 1.8.1-phy5
 * [new tag]           1.8.1-phy6      -> 1.8.1-phy6
 * [new tag]           1.8.1-phy7      -> 1.8.1-phy7
 * [new tag]           1.8.1-phy8      -> 1.8.1-phy8
 * [new tag]           2.0.1-phy1      -> 2.0.1-phy1
 * [new tag]           2.0.1-phy2      -> 2.0.1-phy2
 * [new tag]           2.0.1-phy3      -> 2.0.1-phy3
 * [new tag]           2.1.1-phy1      -> 2.1.1-phy1
 * [new tag]           2.1.1-phy2      -> 2.1.1-phy2
 * [new tag]           2.1.2-phy1      -> 2.1.2-phy1
...

$ git branch -a

* master
  remotes/official-upstream/1.8.1-phy2-fix
  remotes/official-upstream/1.8.1-phy6-fix
  remotes/official-upstream/dizzy
  remotes/official-upstream/dunfell
  remotes/official-upstream/fido
  remotes/official-upstream/gatesgarth
  remotes/official-upstream/hardknott
  remotes/official-upstream/jethro
  remotes/official-upstream/krogoth
  remotes/official-upstream/master
  remotes/official-upstream/morty
  remotes/official-upstream/pyro
  remotes/official-upstream/rocko
  remotes/official-upstream/sumo
  remotes/official-upstream/thud
  remotes/official-upstream/warrior
  remotes/official-upstream/zeus
  remotes/origin/HEAD -> origin/master
  remotes/origin/master

$ git tag -l

1.7.0-phy1
1.7.0-phy2
1.7.0-phy3
1.7.2-phy1
1.7.2-phy2
1.7.3-phy1
1.8.1-phy1
1.8.1-phy2
1.8.1-phy2-fix1
1.8.1-phy3
1.8.1-phy4
1.8.1-phy5
1.8.1-phy6
1.8.1-phy6-fix1
1.8.1-phy7
1.8.1-phy8
2.0.1-phy1
2.0.1-phy2
2.0.1-phy3
2.1.1-phy1
2.1.1-phy2
2.1.2-phy1
2.1.2-phy2
2.1.2-phy3
2.1.2-phy4
2.1.2-phy5
2.1.3-phy1
2.1.3-phy2
2.1.3-phy3
2.1.3-phy4
2.1.3-phy5
2.1.3-phy6
2.1.3-phy7
2.1.3-phy8
2.2.1-phy1
2.2.1-phy2
2.2.1-phy3
2.2.1-phy4
2.2.1-phy5
2.2.1-phy6
2.2.1-phy7
2.2.1-phy8
2.2.1-phy9
2.2.2-phy1
2.2.2-phy2
2.2.2-phy3

Phytec uses this commit 3ba7567532bcda55d9d73deff80a350877b68d07 for the pd21.1.0-stm release

$ git show 3ba7567532bcda55d9d73deff80a350877b68d07
commit 3ba7567532bcda55d9d73deff80a350877b68d07
Author: Christian Hemp <c.hemp@phytec.de>
Date:   Fri Feb 19 16:51:04 2021 +0100

    fix phygate tauri machine name
    
    Update kernel and u-boot recipe to new phygate-tauri machine name.
    
    Signed-off-by: Christian Hemp <c.hemp@phytec.de>
    Signed-off-by: Stefan Müller-Klieser <s.mueller-klieser@phytec.de>

diff --git a/dynamic-layers/freescale-layer/recipes-kernel/linux/linux-imx_5.4.70_2.3.0-phy3.bb b/dynamic-layers/freescale-layer/recipes-kernel/linux/linux-imx_5.4.70_2.3.0-phy3.bb
index ea1fdbea..439f2a74 100644
--- a/dynamic-layers/freescale-layer/recipes-kernel/linux/linux-imx_5.4.70_2.3.0-phy3.bb
+++ b/dynamic-layers/freescale-layer/recipes-kernel/linux/linux-imx_5.4.70_2.3.0-phy3.bb
@@ -25,6 +25,6 @@ COMPATIBLE_MACHINE .= "|phyboard-polis-imx8mm-3"
 COMPATIBLE_MACHINE .= "|phyboard-polis-imx8mm-4"
 COMPATIBLE_MACHINE .= "|phyboard-polis-imx8mn-1"
 COMPATIBLE_MACHINE .= "|phyboard-pollux-imx8mp-1"
-COMPATIBLE_MACHINE .= "|phygate-tauri-imx8mm-1"
-COMPATIBLE_MACHINE .= "|phygate-tauri-imx8mm-2"
+COMPATIBLE_MACHINE .= "|phygate-tauri-l-imx8mm-1"
+COMPATIBLE_MACHINE .= "|phygate-tauri-l-imx8mm-2"
 COMPATIBLE_MACHINE .= ")$"
diff --git a/recipes-bsp/u-boot/u-boot-imx_2020.04_2.3.0-phy2.bb b/recipes-bsp/u-boot/u-boot-imx_2020.04_2.3.0-phy2.bb
index aae54cc5..0e33781e 100644
--- a/recipes-bsp/u-boot/u-boot-imx_2020.04_2.3.0-phy2.bb
+++ b/recipes-bsp/u-boot/u-boot-imx_2020.04_2.3.0-phy2.bb
@@ -51,8 +51,8 @@ COMPATIBLE_MACHINE .= "|phyboard-polis-imx8mm-3"
 COMPATIBLE_MACHINE .= "|phyboard-polis-imx8mm-4"
 COMPATIBLE_MACHINE .= "|phyboard-polis-imx8mn-1"
 COMPATIBLE_MACHINE .= "|phyboard-pollux-imx8mp-1"
-COMPATIBLE_MACHINE .= "|phygate-tauri-imx8mm-1"
-COMPATIBLE_MACHINE .= "|phygate-tauri-imx8mm-2"
+COMPATIBLE_MACHINE .= "|phygate-tauri-l-imx8mm-1"
+COMPATIBLE_MACHINE .= "|phygate-tauri-l-imx8mm-2"
 COMPATIBLE_MACHINE .= ")$"
 
 UBOOT_NAME_mx8 = "u-boot-${MACHINE}.bin-${UBOOT_CONFIG}"

5) use specific tag/commit and make own branch

git co 3ba7567532bcda55d9d73deff80a350877b68d07

$ git co 955b1d9a5f706013d718687b1afa6e3022c68fac
Note: checking out '955b1d9a5f706013d718687b1afa6e3022c68fac'.

You are in 'detached HEAD' state. You can look around, make experimental
changes and commit them, and you can discard any commits you make in this
state without impacting any branches by performing another checkout.

If you want to create a new branch to retain commits you create, you may
do so (now or later) by using -b with the checkout command again. Example:

  git checkout -b <new-branch-name>

HEAD is now at 955b1d9 M4PROJECTS: Update to v1.3.0

make branch out of it

$ git checkout -b 2021-06-08-955b1d9a5f706013d718687b1afa6e3022c68fac-pd21.1.0-dunfell
Switched to a new branch '2021-06-08-955b1d9a5f706013d718687b1afa6e3022c68fac-pd21.1.0-dunfell'

$ git branch
* 2021-06-08-955b1d9a5f706013d718687b1afa6e3022c68fac-pd21.1.0-dunfell
  master

our hacked version of this branch (subset and modifications)

$ git branch 2021-06-09-pd21.1.0-subset-dunfell-as-hardknott
$ git co 2021-06-09-pd21.1.0-subset-dunfell-as-hardknott
Switched to branch '2021-06-09-pd21.1.0-subset-dunfell-as-hardknott'
$ git branch
  2021-06-08-955b1d9a5f706013d718687b1afa6e3022c68fac-pd21.1.0-dunfell
* 2021-06-09-pd21.1.0-subset-dunfell-as-hardknott
  master

#5) use specific upstream branch/commit and make own branch
#
#syntax: git fetch url-to-repo branchname:refs/remotes/origin/branchname
#
#$ git fetch git://github.com/STMicroelectronics/meta-st-stm32mp dunfell:refs/remotes/origin/dunfell
#
#From git://github.com/Freescale/meta-freescale
# * [new branch]        dunfell    -> origin/dunfell
#

#6) Update from upstream:
#git co master
#>> git remote -v
#
#official-upstream       git://github.com/Freescale/meta-freescale (fetch)
#official-upstream       git://github.com/Freescale/meta-freescale (push)
#origin  git@github.com:RobertBerger/meta-freescale.git (fetch)
#origin  git@github.com:RobertBerger/meta-freescale.git (push)
#
#>> git fetch official-upstream
#remote: Counting objects: 4043, done.
#remote: Compressing objects: 100% (1273/1273), done.
#remote: Total 4043 (delta 3130), reused 3632 (delta 2727)
#Receiving objects: 100% (4043/4043), 721.50 KiB | 402.00 KiB/s, done.
#Resolving deltas: 100% (3130/3130), completed with 502 local objects.
#From git://git://github.com/Freescale/meta-freescale
#   62591d9..e758547  master     -> official-upstream/master
# + 2942327...a382678 master-next -> official-upstream/master-next  (forced update)
#   a3fa5ce..6a1f33c  morty      -> official-upstream/morty
#---
#

6) hack the branch and update

6.1) hack it

6.2) add/commit

6.3) What was changed?

$ git diff 2021-06-08-955b1d9a5f706013d718687b1afa6e3022c68fac-pd21.1.0-dunfell --stat
 conf/layer.conf                                                                                       |   2 +-
 recipes-connectivity/bluetooth/bluetooth-suspend.bb                                                   |  28 ------------
 recipes-connectivity/bluetooth/bluetooth-suspend/bluetooth-brcmfmac-sleep.service                     |  13 ------
 recipes-connectivity/bluetooth/bluetooth-suspend/bluetooth_brcmfmac_driver.sh                         |  44 -------------------
 recipes-connectivity/wifi/wifi-suspend.bb                                                             |  28 ------------
 recipes-connectivity/wifi/wifi-suspend/wifi-brcmfmac-sleep.service                                    |  13 ------
 recipes-connectivity/wifi/wifi-suspend/wifi_brcmfmac_driver.sh                                        |  54 -----------------------
 recipes-core/base-files/base-files/fstab                                                              |  11 -----
 recipes-core/base-files/base-files_%.bbappend                                                         |   1 -
 recipes-core/busybox/busybox/0001-miscutils-watchdog-Add-gettimeleft.patch                            |  38 ----------------
 recipes-core/busybox/busybox/busybox-stm32mp.cfg                                                      |  13 ------
 recipes-core/busybox/busybox/ifplugd.action                                                           |  20 ---------
 recipes-core/busybox/busybox/ifplugd.conf                                                             |   2 -
 recipes-core/busybox/busybox/ifplugd.sh                                                               |   5 ---
 recipes-core/busybox/busybox_%.bbappend                                                               |  33 --------------
 recipes-core/dropbear/dropbear_%.bbappend                                                             |   2 -
 recipes-core/meta/target-sdk-provides-dummy.bbappend                                                  |   1 -
 recipes-core/systemd/systemd-conf_%.bbappend                                                          |   9 ----
 recipes-devtools/sdcard-raw-tools/sdcard-raw-tools.bb                                                 |   2 +-
 recipes-graphics/drm/libdrm/0001-tests-modetest-automatic-configuration.patch                         | 125 ----------------------------------------------------
 recipes-graphics/drm/libdrm/0002-tests-util-smtpe-increase-alpha-to-middle-band.patch                 |  48 --------------------
 recipes-graphics/drm/libdrm/0003-tests-modetest-set-property-in-atomic-mode.patch                     |  43 ------------------
 recipes-graphics/drm/libdrm/0004-tests-modetest-close-crtc.patch                                      |  42 ------------------
 recipes-graphics/drm/libdrm_2.4.101.bbappend                                                          |  11 -----
 recipes-graphics/gcnano-userland/gcnano-userland-binary.inc                                           | 193 --------------------------------------------------------------------------------
 recipes-graphics/gcnano-userland/gcnano-userland-multi-binary-debug-stm32mp.bb                        |  17 -------
 recipes-graphics/gcnano-userland/gcnano-userland-multi-binary-stm32mp.bb                              |  15 -------
 recipes-graphics/mesa/mesa-gl_%.bbappend                                                              |   3 --
 recipes-graphics/mesa/mesa_%.bbappend                                                                 |  12 -----
 recipes-graphics/wayland/weston-init.bbappend                                                         |   2 -
 recipes-graphics/wayland/weston-init/weston.ini                                                       | 102 ------------------------------------------
 recipes-graphics/wayland/weston/xwayland.weston-start                                                 |   7 ---
 recipes-graphics/wayland/weston_%.bbappend                                                            |   1 -
 recipes-multimedia/pulseaudio/pulseaudio/default.pa                                                   | 137 ---------------------------------------------------------
 recipes-multimedia/pulseaudio/pulseaudio/system.pa                                                    |  76 --------------------------------
 recipes-multimedia/pulseaudio/pulseaudio_%.bbappend                                                   |  23 ----------
 recipes-st/images/st-image-userfs.bb                                                                  |   8 +++-
 recipes-support/hidapi/hidapi-stm32mp/0001-configure.ac-remove-duplicate-AC_CONFIG_MACRO_DIR-22.patch |  27 ++++++++++++
 recipes-support/hidapi/hidapi-stm32mp_0.8.0-rc1.bb                                                    |   4 +-
 39 files changed, 39 insertions(+), 1176 deletions(-)

7) push upstream:
git co master
cd my-scripts
./push-all-to-github.sh

#8) apply patches
#
#cd meta-virtualization
#
#git co 2019-09-09-warrior-2.7+
#
#stg init
#
#stg series
#
#stg import --mail ../meta-virtualization-patches/2019-09-09-warrior-2.7+/0001-use-systemd-as-cgroup-manager-for-docker-While-it-s-.patch
#
#import all patches
#
#...
#
#stg series
#
#stg commit --all
#
#git log
#
#git co master
#
9) push to my upstream

my-scripts/push-all-to-github.sh


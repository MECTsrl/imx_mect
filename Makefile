export LC_ALL := C

# ---------------------------

# MECT Suite version
export MECT_BUILD_MAJOR := 3
export MECT_BUILD_MINOR := 1
export MECT_BUILD_BUILD := 5
export MECT_BUILD_RELEASE = $(MECT_BUILD_MAJOR).$(MECT_BUILD_MINOR).$(MECT_BUILD_BUILD)

# ---------------------------

# imx_mect branch used by ltib_update make target
# If empty it points to 'master'
MECT_BUILD_IMXMECT_BRANCH := mect_suite_3.0
# imx_mect tag used by ltib_update make target
# Set to 0.0 to checkout HEAD
MECT_BUILD_IMXMECT_TAG := v$(MECT_BUILD_RELEASE)

# git branch and tag for the ATCMcontrol_RunTimeSystem project
MECT_BUILD_ATCMCRT_BRANCH := mect_suite_3.0
# Set to 0.0 to checkout HEAD
export MECT_BUILD_ATCMCRT_TAG := v2.013
# svn branch and release for the ATCMcontrol_RunTimeSystem project
MECT_BUILD_ATCMCRT_CAN_BRANCH := mect_suite_3.0
MECT_BUILD_ATCMCRT_CAN_REV := 254
MECT_BUILD_ATCMCRT_CAN_URL := svn://192.168.0.254/4c_runtime/branches

# git branch and tag for the mect_plugins project
MECT_BUILD_PLUGINSCRT_BRANCH := mect_suite_3.0
# Set to 0.0 to checkout HEAD
export MECT_BUILD_PLUGINSCRT_TAG := v$(MECT_BUILD_RELEASE)

# git branch and tag for the mect_apps project
MECT_BUILD_APPSCRT_BRANCH := mect_suite_3.0
# Set to 0.0 to checkout HEAD
export MECT_BUILD_APPSCRT_TAG := v$(MECT_BUILD_RELEASE)

# git branch and tag for the cloner project
MECT_BUILD_CLONERCRT_BRANCH := mect_suite_3.0
# Set to 0.0 to checkout HEAD
export MECT_BUILD_CLONERCRT_TAG := v$(MECT_BUILD_RELEASE)

# Mandatory prefix for all target device names
MECT_TARGET_PREFIX := MECT_
# Release prefix for image files
MECT_REL_PREFIX := _ms

# Name of the default target device image that is part of the default build.
MECT_DEFAULT_IMAGE := TPAC1007_04_AA

# Qt and related versions
MECT_QT_VERSION := 4.8.5
MECT_QWT_VERSION := 6.1-multiaxes

MECT_BUILD_QTVERSION = $(MECT_QT_VERSION)
MECT_BUILD_QWTVERSION = $(MECT_QWT_VERSION)

# Name of the root file system version file
MECT_RFS_VERSION_FILE := rootfs_version

# Target pltform architecture
export MECT_TARGET_ARCH := arm
# UNIX name of the target platform
MECT_TARGET_UNIX_NAME := imx28

# Developer info for git
MECT_USER_NAME := "Embedded developer"
MECT_HOST_NAME := "development.localdomain"

# Download the archives here.
export MECT_FTPDIR := $(CURDIR)/src
# LTIB is installed here.
MECT_LTIBDIR := $(CURDIR)/ltib
# LTIB (config and dist) before MECT patches is saved here.
MECT_LTIBDIR_REF := $(CURDIR)/ltib.reference
# LTIB (config and dist) on which to apply current patches.
MECT_LTIBDIR_PATCH := $(CURDIR)/ltib.patched
# LTIB rootfs is created here.
export MECT_LTIB_RFSDIR = $(MECT_LTIBDIR)/rootfs
# Unpack the archives here.
MECT_TMPDIR := $(CURDIR)/tmp
# Archive repository
MECT_FTPURL := http://www.mect.it/archive
# Hardcoded Freescale directory
MECT_FSDIR := /opt/freescale
# Freescale binaries directory
MECT_FSBINDIR := /opt/freescale/ltib/usr/bin
# LTIB RPM binary
export MECT_RPMBIN = $(MECT_FSBINDIR)/rpm
# RPM archive
export MECT_RPMBASEDIR := $(CURDIR)/ltib/rpm
MECT_RPMBUILDDIR = $(MECT_RPMBASEDIR)/BUILD
export MECT_RPMDIR = $(MECT_RPMBASEDIR)/RPMS/$(MECT_TARGET_ARCH)
# Top-level directory for target image build receipts
MECT_MKIMGDIR := $(CURDIR)/targets
# Top-level directory fo target device images
export MECT_IMGDIR := $(CURDIR)/images
# Projects directory
MECT_PRJDIR := $(CURDIR)/projects
# Utility to compare current target images with a given reference set.
MECT_IMG_TESTER = $(MECT_FTPDIR)/image-tester.sh
# Staging directory for image test
MECT_TESTSHARE := /media/sf_share
# Prefix of staging image directory
MECT_TESTNAME := MectSuite_
# Draft directory for rpmbuild
export MECT_TMPRPMDIR = /tmp/rpm-$(LOGNAME)
# Expand to the name of the kernel RPM built by LTIB.
MECT_LTIB_KERNEL_RPM = $(MECT_RPMDIR)/$(shell if test -x $(MECT_RPMBIN); then $(MECT_RPMBIN) --root $(MECT_LTIB_RFSDIR) --dbpath /var/lib/rpm -q --whatprovides kernel; else echo 'no-package'; fi).$(MECT_TARGET_ARCH).rpm
# Expand to the name of the timestamp when the kernel RPM was built by LTIB.
MECT_LTIB_KERNEL_TS_NAME = last-kernel-build
MECT_LTIB_KERNEL_TS_RPM = $(MECT_RPMDIR)/$(shell if test -x $(MECT_RPMBIN); then $(MECT_RPMBIN) --root $(MECT_LTIB_RFSDIR) --dbpath /var/lib/rpm -q --whatprovides $(MECT_LTIB_KERNEL_TS_NAME); else echo 'no-package'; fi).$(MECT_TARGET_ARCH).rpm
# Kernel configuration file.
MECT_KERNEL_CONF := $(MECT_LTIBDIR)/config/platform/imx/kernel-2.6.35-imx28-tpac.config
# Script to update target file systems
MECT_SYSUPD_IMG_TMPL := $(MECT_FTPDIR)/sysupdate_imx28_img.sh
MECT_SYSUPD_IMG_SH := sysupdate_img_$(MECT_BUILD_RELEASE).sh
# System cloner for all targets
MECT_SYSCLONE_TMPL := $(MECT_PRJDIR)/cloner/sysupdate_cloner.sh
MECT_SYSCLONE_PRE_TMPL := $(MECT_PRJDIR)/cloner/sysupdate_script_pre.sh
MECT_SYSCLONE_POST_TMPL := $(MECT_PRJDIR)/cloner/sysupdate_script_post.sh
MECT_SYSCLONE_SHAR := $(MECT_IMGDIR)/sysupdate_cloner_$(MECT_BUILD_RELEASE).sh
MECT_SYSCLONE_SHDIR := $(MECT_IMGDIR)/cloner_$(MECT_BUILD_RELEASE)
MECT_SYSCLONE_SH = $(MECT_SYSCLONE_SHDIR)/sysupdate_cloner_$(MECT_BUILD_RELEASE).sh
MECT_SYSCLONE_IMG = $(MECT_SYSCLONE_SHDIR)/img_cloner_$(MECT_BUILD_RELEASE).ext2
MECT_SYSCLONE_LOOP = $(MECT_SYSCLONE_SHDIR)/sysupdate_cloner_$(MECT_BUILD_RELEASE).loop
MECT_SYSCLONE_DIR := $(MECT_IMGDIR)/sysupdate_cloner_$(MECT_BUILD_RELEASE)/temp
# Program to update target kernel
MECT_KOBS_TMPL := $(MECT_FTPDIR)/kobs-ng
# sysupdate for MECT Remote Services configuration
MECT_SYSUPD_VPN_PRE := $(MECT_FTPDIR)/sysupdate_vpn_pre.sh
MECT_SYSUPD_VPN = $(MECT_IMGDIR)/sysupdate_vpn_$(MECT_BUILD_RELEASE).sh
MECT_SYSUPD_VPN_POST := $(MECT_FTPDIR)/sysupdate_vpn_post.sh

# Extension of the MD5 checksums for the downloads.
MECT_MD5EXT := md5

# Packages for USB serial kernel modules.
#

MECT_RFSPKG_USBSERIAL_USBSERIAL := kernel-rfs-usbserial-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_AIRCABLE := kernel-rfs-usbserial-aircable-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_ARK3116 := kernel-rfs-usbserial-ark3116-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_BELKIN := kernel-rfs-usbserial-belkin_sa-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_CH341 := kernel-rfs-usbserial-ch341-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_CP210X := kernel-rfs-usbserial-cp210x-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_CYBERJACK := kernel-rfs-usbserial-cyberjack-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_CYPRESS_M8 := kernel-rfs-usbserial-cypress_m8-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_DEBUG := kernel-rfs-usbserial-debug-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_DIGI_ACCELEPORT := kernel-rfs-usbserial-digi_acceleport-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_EMPEG := kernel-rfs-usbserial-empeg-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_FTDI_SIO := kernel-rfs-usbserial-ftdi_sio-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_FUNSOFT := kernel-rfs-usbserial-funsoft-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_GARMIN_GPS := kernel-rfs-usbserial-garmin_gps-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_HP4X := kernel-rfs-usbserial-hp4x-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_IO_EDGEPORT := kernel-rfs-usbserial-io_edgeport-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_IO_TI := kernel-rfs-usbserial-io_ti-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_IPAQ := kernel-rfs-usbserial-ipaq-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_IPW := kernel-rfs-usbserial-ipw-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_IR := kernel-rfs-usbserial-ir-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_IUU_PHOENIX := kernel-rfs-usbserial-iuu_phoenix-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_KEYSPAN := kernel-rfs-usbserial-keyspan-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_KEYSPAN_PDA := kernel-rfs-usbserial-keyspan_pda-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_KL5KUSB105 := kernel-rfs-usbserial-kl5kusb105-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_KOBIL_SCT := kernel-rfs-usbserial-kobil_sct-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_MCT_U232 := kernel-rfs-usbserial-mct_u232-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_MOS7720 := kernel-rfs-usbserial-mos7720-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_MOS7840 := kernel-rfs-usbserial-mos7840-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_MOTO_MODEM := kernel-rfs-usbserial-moto_modem-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_NAVMAN := kernel-rfs-usbserial-navman-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_OMNINET := kernel-rfs-usbserial-omninet-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_OPTICON := kernel-rfs-usbserial-opticon-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_OPTION := kernel-rfs-usbserial-option-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_OTI6858 := kernel-rfs-usbserial-oti6858-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_PL2303 := kernel-rfs-usbserial-pl2303-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_QCAUX := kernel-rfs-usbserial-qcaux-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_QCSERIAL := kernel-rfs-usbserial-qcserial-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_SAFE_SERIAL := kernel-rfs-usbserial-safe_serial-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_SIEMENS_MPI := kernel-rfs-usbserial-siemens_mpi-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_SIERRA := kernel-rfs-usbserial-sierra-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_SPCP8X5 := kernel-rfs-usbserial-spcp8x5-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_SYMBOLSERIAL := kernel-rfs-usbserial-symbolserial-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_TI_03410_5052 := kernel-rfs-usbserial-ti_03410_5052-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_VISOR := kernel-rfs-usbserial-visor-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_VIVOPAY := kernel-rfs-usbserial-vivopay-serial-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_WHITEHEAT := kernel-rfs-usbserial-whiteheat-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_WWAN := kernel-rfs-usbserial-wwan-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm
MECT_RFSPKG_USBSERIAL_ZIO := kernel-rfs-usbserial-zio-2.6.35.3-imx_1.1.0.$(MECT_TARGET_ARCH).rpm

# Package list for creating the root file system for various targets.
#

MECT_COMMON_RFSPKGS := \
	alsa-lib-rfs-1.0.24.1-0.$(MECT_TARGET_ARCH).rpm \
	alsa-utils-rfs-1.0.24.2-0.$(MECT_TARGET_ARCH).rpm \
	base_libs-rfs-1.2-1.$(MECT_TARGET_ARCH).rpm \
	boa-rfs-0.94.14rc21-1.$(MECT_TARGET_ARCH).rpm \
	busybox-rfs-1.15.0-1.$(MECT_TARGET_ARCH).rpm \
	cantest-rfs-1.0-1.$(MECT_TARGET_ARCH).rpm \
	cgic_work-rfs-0.0-1.$(MECT_TARGET_ARCH).rpm \
	dhcp-rfs-3.0.3b1-1.$(MECT_TARGET_ARCH).rpm \
	dropbear-rfs-2016.73-1.$(MECT_TARGET_ARCH).rpm \
	e2fsprogs-rfs-1.41.4-1.$(MECT_TARGET_ARCH).rpm \
	expat-rfs-1.95.8-1.$(MECT_TARGET_ARCH).rpm \
	fontconfig-rfs-2.4.2-1.$(MECT_TARGET_ARCH).rpm \
	freetype-rfs-2.3.9-1.$(MECT_TARGET_ARCH).rpm \
	glib2-rfs-2.18.1-1.$(MECT_TARGET_ARCH).rpm \
	iproute-rfs-2.6.37-1.$(MECT_TARGET_ARCH).rpm \
	iptables-rfs-1.4.2-1.$(MECT_TARGET_ARCH).rpm \
	libmodbus-rfs-3.0.6-1.$(MECT_TARGET_ARCH).rpm \
	libpng-rfs-1.2.8-1.$(MECT_TARGET_ARCH).rpm \
	libqrencode-rfs-3.4.2-1.$(MECT_TARGET_ARCH).rpm \
	libsocketcan-rfs-0.0.8-0.$(MECT_TARGET_ARCH).rpm \
	libtermcap-rfs-2.0.8-31_1.$(MECT_TARGET_ARCH).rpm \
	libusb1-rfs-1.0.20-1.$(MECT_TARGET_ARCH).rpm \
	lrzsz-rfs-0.12.21-1.$(MECT_TARGET_ARCH).rpm \
	lzo-rfs-2.03-0.$(MECT_TARGET_ARCH).rpm \
	mac_sn-rfs-1.0-1.$(MECT_TARGET_ARCH).rpm \
	mect_plugins-rfs-$(MECT_BUILD_PLUGINSCRT_TAG)-1.$(MECT_TARGET_ARCH).rpm \
	merge-rfs-0.1-1.$(MECT_TARGET_ARCH).rpm \
	modeps-rfs-1.0-1.$(MECT_TARGET_ARCH).rpm \
	mtd-utils-rfs-201006-1.$(MECT_TARGET_ARCH).rpm \
	mysql-rfs-4.1.12-0.$(MECT_TARGET_ARCH).rpm \
	nagios-plugins-rfs-1.0-1.$(MECT_TARGET_ARCH).rpm \
	ncurses-rfs-5.3-1.$(MECT_TARGET_ARCH).rpm \
	nrpe-rfs-2.15-1.$(MECT_TARGET_ARCH).rpm \
	openssl-rfs-1.0.1s-1.$(MECT_TARGET_ARCH).rpm \
	openvpn-rfs-2.4.4-1.$(MECT_TARGET_ARCH).rpm \
	ppp-rfs-2.4.4-1.$(MECT_TARGET_ARCH).rpm \
	qt-embedded-rfs-4.8.5-1.$(MECT_TARGET_ARCH).rpm \
	qwt-rfs-6.1-1_multiaxes.$(MECT_TARGET_ARCH).rpm \
	rsync-rfs-2.6.5-1.$(MECT_TARGET_ARCH).rpm \
	SDcard-rfs-1.0-1.$(MECT_TARGET_ARCH).rpm \
	sftp-server-rfs-4.3p2-1.$(MECT_TARGET_ARCH).rpm \
	skell-rfs-1.18-2.$(MECT_TARGET_ARCH).rpm \
	splash-rfs-1.0-1.$(MECT_TARGET_ARCH).rpm \
	sqlite-rfs-3.6.12-1.$(MECT_TARGET_ARCH).rpm \
	sysconfig-rfs-1.2-5.$(MECT_TARGET_ARCH).rpm \
	tcp_wrappers-rfs-7.6-1.$(MECT_TARGET_ARCH).rpm \
	tslib-rfs-1.0-3.$(MECT_TARGET_ARCH).rpm \
	usb-modeswitch-data-rfs-20160112-1.$(MECT_TARGET_ARCH).rpm \
	usb-modeswitch-rfs-2.3.0-1.$(MECT_TARGET_ARCH).rpm \
	wifi-drivers-ath9k_htc-rfs-3.12.8-1.$(MECT_TARGET_ARCH).rpm \
	wifi-drivers-common-rfs-3.12.8-1.$(MECT_TARGET_ARCH).rpm \
	wifi-drivers-rt5370-rfs-3.12.8-1.$(MECT_TARGET_ARCH).rpm \
	wireless_tools-rfs-29-1.$(MECT_TARGET_ARCH).rpm \
	wpa_supplicant-rfs-0.5.9-1.$(MECT_TARGET_ARCH).rpm \
	xenomai-rfs-2.6.0-1.$(MECT_TARGET_ARCH).rpm \
	zip-rfs-3.0.0-0.$(MECT_TARGET_ARCH).rpm \
	zlib-rfs-1.2.3-2.$(MECT_TARGET_ARCH).rpm \

MECT_COMMON_RFSPKGS := $(MECT_COMMON_RFSPKGS:%=$(MECT_RPMDIR)/%)

MECT_COMMON_LFSPKGS := \
	local-1.0-1.$(MECT_TARGET_ARCH).rpm \
	merge-lfs-0.1-1.$(MECT_TARGET_ARCH).rpm \

MECT_COMMON_LFSPKGS := $(MECT_COMMON_LFSPKGS:%=$(MECT_RPMDIR)/%)

MECT_TARGET_LFSPKG_ATCMCONTROL_RUNTIMESYSTEM := $(MECT_RPMDIR)/ATCMcontrol_RunTimeSystem-lfs-$(MECT_BUILD_ATCMCRT_TAG)-1.$(MECT_TARGET_ARCH).rpm
MECT_TARGET_LFSPKG_4C_RUNTIME := $(MECT_RPMDIR)/4c_runtime-lfs-$(MECT_BUILD_ATCMCRT_TAG)-1.$(MECT_TARGET_ARCH).rpm

MECT_TARGET_RFSPKGS := \
	kernel-rfs-2.6.35.3-imx_1.1.0.arm.rpm \
	$(MECT_RFSPKG_USBSERIAL_PL2303) \
	$(MECT_RFSPKG_USBSERIAL_USBSERIAL) \

MECT_TARGET_RFSPKGS := $(MECT_TARGET_RFSPKGS:%=$(MECT_RPMDIR)/%)


# Set archive sources
#

# Toolchain archive
MECT_CSXCPREFIX = arm-2011.03
MECT_CSXCARCH = $(MECT_CSXCPREFIX)-41-arm-none-linux-gnueabi-i686-pc-linux-gnu.tar.bz2
MECT_CSXCUNPACK = $(CURDIR)/$(MECT_CSXCPREFIX)
# Keep this in sync with LTIB config
export MECT_CSXCDIR := /opt/CodeSourcery
export MECT_CC_DIRECTORY = $(MECT_CSXCDIR)
export MECT_CC_VERSION := 
export MECT_CC_RADIX := arm-none-linux-gnueabi

# LTIB archive
MECT_LTIB_EVKARCH = L2.6.35_1.1.0_130130_source.tar.gz
MECT_LTIB_EVKDIR = $(MECT_LTIB_EVKARCH:%.tar.gz=%)

# LTIB pre-configuration for install (MECT patch)
MECT_LTIBINST_TARGETDIR_PATHCH = ltib-install-preset-target-dir.patch

# LTIB fix downloads for Ubuntu 12.04 (MECT patch)
MECT_LTIB_UBUNTU_URL_PATHCH = ltib-ubuntu12.04-url.patch

# LTIB fix /usr/include/sys for i386 architectures for Ubuntu 12.04 (MECT patch)
MECT_LTIB_UBUNTU_INCLUDE_SYS_PATHCH = ltib-ubuntu12.04-include-sys.patch

# LTIB fix configuration and specs (MECT patches)
MECT_LTIB_MECT_CONFIG_PATCH = ltib-mect-config.patch
MECT_LTIB_MECT_SPECS_PATCH = ltib-mect-specs.patch
MECT_LTIB_MECT_BIN_PATCH = ltib-mect-bin.patch

# LTIB set MECT PPP (MECT patch)
MECT_LTIB_MECT_PPP_PATCH = ltib-mect-ppp-url.patch

# LTIB Ubuntu 12.04 patch bundle
MECT_LTIB_UBUNTU_12_04_PATCH = patch-ltib-ubuntu12.04.sh
MECT_URL_LTIB_UBUNTU_12_04_PATCH = $(MECT_FTPURL)/$(MECT_LTIB_UBUNTU_12_04_PATCH)

# LTIB Ubuntu 12.04 patch bundle fix /usr/include/sys for i386 architectures (MECT patch)
MECT_LTIB_UBUNTU_12_04_PATCH_INCLUDE_SYS_PATCH = ubuntu-ltib-patch-include-sys-i386.patch

# LTIB qt spec file (MECT patch)
export MECT_QT_INSTALL_DIR = /opt/Trolltech
MECT_LTIB_QT_ARCH = qt-everywhere-opensource-src-4.8.5.tar.gz
MECT_LTIB_QT_PATCH1 = qt-everywhere-opensource-src-4.8.5-1394522957.patch
MECT_LTIB_QT_PATCH2 = qt-everywhere-opensource-src-4.8.5-1420823826.patch
MECT_LTIB_QT_PATCH3 = qt-everywhere-opensource-src-4.8.5-1420823825.patch


# Extra packages to copy in $(LTIBPKGDIR)
MECT_FSPKG_DL := \
	$(MECT_LTIB_QT_ARCH) \
	$(MECT_LTIB_QT_PATCH2) \

MECT_FSPKG := \
	$(MECT_LTIB_QT_PATCH1) \
	$(MECT_LTIB_QT_PATCH3) \

MECT_FSPKG := $(MECT_FSPKG) $(MECT_FSPKG_DL)


MECT_FSPKGMD5 := $(MECT_FSPKG:%=%.$(MECT_MD5EXT))
MECT_FSPKG := $(MECT_FSPKG) $(MECT_FSPKGMD5)
MECT_FSPKG := $(MECT_FSPKG:%=$(MECT_FTPDIR)/%)


MECT_DOWNLOADS := \
	$(MECT_CSXCARCH) \
	$(MECT_LTIB_EVKARCH) \
	$(MECT_LTIB_UBUNTU_12_04_PATCH) \
	$(MECT_FSPKG_DL) \

MECT_DLMD5 := $(MECT_DOWNLOADS:%=%.$(MECT_MD5EXT))
MECT_DOWNLOADS := $(MECT_DOWNLOADS) $(MECT_DLMD5)
MECT_DOWNLOADS := $(MECT_DOWNLOADS:%=$(MECT_FTPDIR)/%)

MECT_DOWNLOADS := $(MECT_DOWNLOADS)


MECT_UTILS = \
	apt-get \
	sudo \

MECT_PACKAGES = \
	bison \
	ccache \
	coreutils \
	e2fsprogs \
	g++ \
	gcc \
	gzip \
	intltool \
	libdbus-glib-1-dev \
	libglib2.0-dev \
	libgtk2.0-dev \
	liblzo2-dev \
	libncurses5-dev \
	liborbit2-dev \
	libx11-dev \
	m4 \
	make \
	nsis \
	openssl \
	p7zip \
	patch \
	perl \
	pigz \
	qemu \
	qemu-user \
	rpm \
	sed \
	sharutils \
	tar \
	tcl \
	texinfo \
	texlive \
	uuid \
	uuid-dev \
	wget \
	zip \
	zlib1g \
	zlib1g-dev \
	zlibc \

ifeq ($(shell lsb_release -r | cut -f2 | cut -d. -f1),14)
MECT_PACKAGES += \
	zlib-bin
endif
ifeq ($(shell lsb_release -r | cut -f2 | cut -d. -f1),16)
MECT_PACKAGES += \
	minizip
endif


.PHONY: all
all: env downloads setup build image target_dev sysupdate_mrs

# Set up the build environment.
.PHONY: env
env:
	set -e; for p in $(MECT_UTILS); do which $$p; done
	if test "`uname -m`" = x86_64; then \
		sudo apt-get $(MECT_APTGET_AUTOUPDATE) install lib32bz2-1.0 lib32ncurses5 lib32z1 libc6-dev-i386; \
		sudo ln -sf /usr/lib/x86_64-linux-gnu/librt.so /usr/lib/librt.so; \
	fi
	if test -d $(MECT_LTIBDIR); then \
		echo "*** Error: Destination directory $(MECT_LTIBDIR) exists, will not overwrite."; \
		echo "Hint: To continue an interupted installation try running LTIB directly:"; \
		echo "          cd $(MECT_LTIBDIR); ./ltib"; \
		echo "Aborting."; \
		exit 1; \
	fi
	sudo apt-get $(MECT_APTGET_AUTOUPDATE) install $(MECT_PACKAGES)

# Initial downloads (toolchain, LTIB, LTIB patches, spec files patches, ...)
.PHONY: downloads
downloads: $(MECT_FTPDIR) downloads_fc $(MECT_DOWNLOADS)

$(MECT_FTPDIR):
	test -d $@

# Remove the existing MD5s to force the download of the changed archives (if any).
.PHONY: downloads_fc
downloads_fc:
	for f in "" $(MECT_DOWNLOADS); do \
		test -z "$$f" && continue; \
		rm -f $$f.$(MECT_MD5EXT); \
	done; exit 0		# Don't break the build if the download list is empty.

# Set up LTIB and projects
.PHONY: setup
setup: ltib_setup projects_setup spec_setup

# Install and build LTIB.
.PHONY: ltib_setup
ltib_setup: ltib_inst ltib_patch

.PHONY: ltib_inst
ltib_inst: $(MECT_TMPDIR) downloads
	rm -rf $(MECT_TMPDIR)/$(MECT_LTIB_EVKDIR)
	tar xzvf $(MECT_FTPDIR)/$(MECT_LTIB_EVKARCH) -C $(MECT_TMPDIR)
	cd $(MECT_TMPDIR)/$(MECT_LTIB_EVKDIR); patch -p1 < $(MECT_FTPDIR)/$(MECT_LTIBINST_TARGETDIR_PATHCH)
	if test -n "$(MECT_FSPKG)"; then cp -pv $(MECT_FSPKG) $(MECT_TMPDIR)/$(MECT_LTIB_EVKDIR)/pkgs; fi
	cd $(MECT_TMPDIR)/$(MECT_LTIB_EVKDIR); (echo -e "qy\nyes" ) | ./install
	chmod 0775 $(MECT_LTIBDIR)
	rm -rf $(MECT_TMPDIR)/$(MECT_LTIB_EVKDIR)

$(MECT_TMPDIR):
	rm -rf $(MECT_TMPDIR)
	mkdir -p $(MECT_TMPDIR)

.PHONY: ltib_patch
ltib_patch: downloads
	test -d $(MECT_LTIBDIR)
	cd $(MECT_LTIBDIR); cp $(MECT_FTPDIR)/$(MECT_LTIB_UBUNTU_12_04_PATCH) .
	cd $(MECT_LTIBDIR); cp $(MECT_FTPDIR)/$(MECT_LTIB_UBUNTU_12_04_PATCH_INCLUDE_SYS_PATCH) .
	cd $(MECT_LTIBDIR); patch -p1 < $(MECT_FTPDIR)/$(MECT_LTIB_UBUNTU_URL_PATHCH)
	cd $(MECT_LTIBDIR); patch -p1 < $(MECT_FTPDIR)/$(MECT_LTIB_UBUNTU_INCLUDE_SYS_PATHCH)
	cd $(MECT_LTIBDIR); sh ./$(MECT_LTIB_UBUNTU_12_04_PATCH) $(MECT_FTPURL)
	cd $(MECT_LTIBDIR); rm -f $(MECT_LTIB_UBUNTU_12_04_PATCH) $(MECT_LTIB_UBUNTU_12_04_PATCH_INCLUDE_SYS_PATCH)
	rm -rf $(MECT_LTIBDIR_REF)
	mkdir -p $(MECT_LTIBDIR_REF)
	rsync -a $(MECT_LTIBDIR)/config $(MECT_LTIBDIR)/dist $(MECT_LTIBDIR)/bin $(MECT_LTIBDIR)/ltib $(MECT_LTIBDIR_REF)/
	cd $(MECT_LTIBDIR); for p in \
		$(MECT_LTIB_MECT_CONFIG_PATCH) \
		$(MECT_LTIB_MECT_PPP_PATCH) \
		$(MECT_LTIB_MECT_SPECS_PATCH) \
		$(MECT_LTIB_MECT_BIN_PATCH) \
	; do \
		patch -p1 < $(MECT_FTPDIR)/$$p; \
	done
	sed -i "s,^%ldirs$$,\0\n$(MECT_FTPDIR)\n$(MECT_CSXCDIR)/arm-none-linux-gnueabi/libc/usr/bin," $(MECT_LTIBDIR)/.ltibrc

# Build LTIB and projects
.PHONY: build
build: ltib_build projects_build

.PHONY: ltib_build
ltib_build: hosttools
	test -n "$(LOGNAME)"
	sudo rm -rf $(MECT_FSDIR)/rootfs
	sudo rm -rf $(MECT_FSDIR)/rpm/BUILD
	sudo chown -R $(LOGNAME).$(shell groups | awk '{print $$1}') $(MECT_FSDIR)
	mkdir -p $(MECT_FSDIR)/rootfs
	mkdir -p $(MECT_FSDIR)/rpm/BUILD
	cd $(MECT_LTIBDIR); PATH=/usr/lib/ccache:$$PATH GIT_AUTHOR_NAME=$(MECT_USER_NAME) GIT_AUTHOR_EMAIL=$(MECT_TARGET_UNIX_NAME)@$(MECT_HOST_NAME) GIT_COMMITTER_NAME=$(MECT_USER_NAME) GIT_COMMITTER_EMAIL=$(MECT_TARGET_UNIX_NAME)@$(MECT_HOST_NAME) ./ltib

# Set up the host tools.
.PHONY: hosttools
hosttools: downloads toolchain qt

# Set up the toolchain.
.PHONY: toolchain
toolchain:
	sudo rm -rf $(MECT_CSXCUNPACK) $(MECT_CSXCDIR)
	tar xjvf $(MECT_FTPDIR)/$(MECT_CSXCARCH)
	sudo mv $(MECT_CSXCUNPACK) $(MECT_CSXCDIR)
	test -d /usr/lib/ccache
	for f in arm-none-linux-gnueabi-gcc arm-none-linux-gnueabi-c++ arm-none-linux-gnueabi-g++; do \
	       	sudo ln -sf ../../bin/ccache /usr/lib/ccache/$$f; \
	done

# Set up host Qt.
.PHONY: qt
qt:
	test -n "$(LOGNAME)"
	mkdir -p $(MECT_TMPRPMDIR) $(MECT_LTIBDIR)/rpm/SOURCES
	for f in $(MECT_FSPKG); do cp $$f $(MECT_LTIBDIR)/rpm/SOURCES; done
	PATH=/usr/lib/ccache:$(PATH) rpmbuild --define 'toolchain 1' --define 'toolchain_install_dir $(MECT_QT_INSTALL_DIR)' --define '_topdir $(MECT_LTIBDIR)/rpm' --dbpath $(MECT_TMPRPMDIR)/rpmdb --target arm --define '_target_cpu arm' --define '_prefix /opt' --define '_rpmdir $(MECT_TMPRPMDIR)/RPMS' -bb --clean --rmsource $(MECT_LTIBDIR)/dist/lfs-5.1/qt/qt-embedded.spec
	-sudo rpm --force-debian --root / --dbpath $(MECT_TMPRPMDIR)/rpmdb -e --allmatches --nodeps --define '_tmppath $(MECT_LTIBDIR)/tmp' qt-embedded 2>/dev/null
	sudo rpm --force-debian --root / --dbpath $(MECT_TMPRPMDIR)/rpmdb --ignorearch -ivh --force --nodeps --excludedocs --define '_tmppath $(MECT_LTIBDIR)/tmp' $(MECT_TMPRPMDIR)/RPMS/$(MECT_TARGET_ARCH)/qt-embedded-$(MECT_BUILD_QTVERSION)-*.$(MECT_TARGET_ARCH).rpm
	sudo chown -R $(LOGNAME).$(shell groups | awk '{print $$1}') $(MECT_TMPRPMDIR)


# Set up the local projects: ATCMcontrol_RunTimeSystem.
.PHONY: projects_setup_ATCMcontrol_RunTimeSystem
projects_setup_ATCMcontrol_RunTimeSystem:
	test -d $(MECT_PRJDIR)
	test -n '$(MECT_BUILD_ATCMCRT_BRANCH)'
	cd $(MECT_PRJDIR); if test -d ATCMcontrol_RunTimeSystem; then cd ATCMcontrol_RunTimeSystem; git reset --hard origin/master; git fetch; else git clone https://github.com/MECTsrl/ATCMcontrol_RunTimeSystem.git ATCMcontrol_RunTimeSystem; fi
	cd $(MECT_PRJDIR); if test -d ATCMcontrol_RunTimeSystem -a -n '$(MECT_BUILD_ATCMCRT_BRANCH)'; then cd ATCMcontrol_RunTimeSystem; git checkout -f origin/$(MECT_BUILD_ATCMCRT_BRANCH); fi
	cd $(MECT_PRJDIR); if test -d ATCMcontrol_RunTimeSystem -a -n '$(MECT_BUILD_ATCMCRT_TAG)' -a '$(MECT_BUILD_ATCMCRT_TAG)' != '0.0'; then cd ATCMcontrol_RunTimeSystem; git checkout -f tags/$(MECT_BUILD_ATCMCRT_TAG); fi
	ping -W2 -c1 192.168.0.254 || exit 0; \
	test -n "$(MECT_BUILD_ATCMCRT_CAN_URL)" || exit 0; \
	test -n "$(MECT_BUILD_ATCMCRT_CAN_BRANCH)" || exit 0; \
	test -n "$(MECT_BUILD_ATCMCRT_CAN_REV)" || exit 0; \
	svn info $(MECT_BUILD_ATCMCRT_CAN_URL)/$(MECT_BUILD_ATCMCRT_CAN_BRANCH) || exit 0; \
		cd $(MECT_PRJDIR); rm -rf 4c_runtime; svn checkout --revision $(MECT_BUILD_ATCMCRT_CAN_REV) $(MECT_BUILD_ATCMCRT_CAN_URL)/$(MECT_BUILD_ATCMCRT_CAN_BRANCH) 4c_runtime

# Set up the local projects: mect_plugins.
.PHONY: projects_setup_mect_plugins
projects_setup_mect_plugins:
	test -d $(MECT_PRJDIR)
	test -n '$(MECT_BUILD_PLUGINSCRT_BRANCH)'
	cd $(MECT_PRJDIR); if test -d mect_plugins; then cd mect_plugins; git reset --hard origin/master; git fetch; else git clone https://github.com/MECTsrl/mect_plugins.git mect_plugins; fi
	cd $(MECT_PRJDIR); if test -d mect_plugins -a -n '$(MECT_BUILD_PLUGINSCRT_BRANCH)'; then cd mect_plugins; git checkout -f origin/$(MECT_BUILD_PLUGINSCRT_BRANCH); fi
	cd $(MECT_PRJDIR); if test -d mect_plugins -a -n '$(MECT_BUILD_PLUGINSCRT_TAG)' -a '$(MECT_BUILD_PLUGINSCRT_TAG)' != '0.0'; then cd mect_plugins; git checkout -f tags/$(MECT_BUILD_PLUGINSCRT_TAG); fi

# Set up the local projects: mect_apps.
.PHONY: projects_setup_mect_apps
projects_setup_mect_apps:
	test -d projects
	test -n '$(MECT_BUILD_APPSCRT_BRANCH)'
	cd projects; if test -d mect_apps; then cd mect_apps; git reset --hard origin/master; git fetch; else git clone https://github.com/MECTsrl/mect_apps.git mect_apps; fi
	cd projects; if test -d mect_apps -a -n '$(MECT_BUILD_APPSCRT_BRANCH)'; then cd mect_apps; git checkout -f origin/$(MECT_BUILD_APPSCRT_BRANCH); fi
	cd projects; if test -d mect_apps -a -n '$(MECT_BUILD_APPSCRT_TAG)' -a '$(MECT_BUILD_APPSCRT_TAG)' != '0.0'; then cd mect_apps; git checkout -f tags/$(MECT_BUILD_APPSCRT_TAG); fi

# Set up the local projects: cloner.
.PHONY: projects_setup_cloner
projects_setup_cloner:
	test -d $(MECT_PRJDIR)
	test -n '$(MECT_BUILD_PLUGINSCRT_BRANCH)'
	cd $(MECT_PRJDIR); if test -d cloner; then cd cloner; git reset --hard origin/master; git fetch; else git clone https://github.com/MECTsrl/cloner.git cloner; fi
	cd $(MECT_PRJDIR); if test -d cloner -a -n '$(MECT_BUILD_CLONERCRT_BRANCH)'; then cd cloner; git checkout -f origin/$(MECT_BUILD_CLONERCRT_BRANCH); fi
	cd $(MECT_PRJDIR); if test -d cloner -a -n '$(MECT_BUILD_CLONERCRT_TAG)' -a '$(MECT_BUILD_CLONERCRT_TAG)' != '0.0'; then cd cloner; git checkout -f tags/$(MECT_BUILD_CLONERCRT_TAG); fi

# Set up the local projects.
.PHONY: projects_setup
projects_setup: projects_setup_ATCMcontrol_RunTimeSystem projects_setup_mect_plugins projects_setup_mect_apps projects_setup_cloner

# Build the local projects.
.PHONY: projects_build
projects_build:
	test -d $(MECT_PRJDIR)
	$(MAKE) -C projects clean all

# Set up and build the local projects.
.PHONY: projects
projects: projects_setup projects_build


.PHONY: spec_setup
spec_setup: MECT_LTIBSPECDIR := $(MECT_LTIBDIR)/dist/lfs-5.1
spec_setup:
	for s in ATCMcontrol_RunTimeSystem/ATCMcontrol_RunTimeSystem.spec 4c_runtime/4c_runtime.spec; do \
		test -w $(MECT_LTIBSPECDIR)/$$s || continue; \
		sed -i 's|^\s*\(Version\s*:\).*|\1 $(MECT_BUILD_ATCMCRT_TAG)|I' $(MECT_LTIBSPECDIR)/$$s; \
	done
	for s in mect_plugins/mect_plugins.spec; do \
		test -w $(MECT_LTIBSPECDIR)/$$s || continue; \
		sed -i 's|^\s*\(Version\s*:\).*|\1 $(MECT_BUILD_PLUGINSCRT_TAG)|I' $(MECT_LTIBSPECDIR)/$$s; \
	done
	for s in mect_apps/mect_apps.spec; do \
		test -w $(MECT_LTIBSPECDIR)/$$s || continue; \
		sed -i 's|^\s*\(Version\s*:\).*|\1 $(MECT_BUILD_APPSCRT_TAG)|I' $(MECT_LTIBSPECDIR)/$$s; \
	done
	for s in cloner/cloner.spec; do \
		test -w $(MECT_LTIBSPECDIR)/$$s || continue; \
		sed -i 's|^\s*\(Version\s*:\).*|\1 $(MECT_BUILD_RELEASE)|I' $(MECT_LTIBSPECDIR)/$$s; \
	done


# Rules to build target root file systems
#

MECT_IMAGES := \
	TP1043_01_A \
	TP1043_02_A \
	TP1057_01_A \
	TP1070_01_A \
	TP1070_01_C \
	TP1070_02_E \
	TPAC1007_03 \
	TPAC1007_04_AA \
	TPAC1007_04_AB \
	TPAC1007_04_AC \
	TPAC1007_LV \
	TPLC050_01_AA \

ifneq ($(wildcard $(MECT_PRJDIR)/4c_runtime/.*),)

	MECT_IMAGES += \
		TP1043_01_B \
		TP1043_02_B \
		TP1057_01_B \
		TP1070_01_B \
		TPAC1005 \
		TPAC1006 \
		TPAC1008_01 \
		TPAC1008_02_AA \
		TPAC1008_02_AB \
		TPAC1008_02_AD \
		TPAC1008_02_AE \
		TPAC1008_02_AF \
		TPAC1008_03_AC \
		TPAC1008_03_AD \
		TPLC100_01_AA \
		TPLC100_01_AB \

endif

# Image-specific settings and targets
$(foreach img,$(MECT_IMAGES),$(eval include $(MECT_MKIMGDIR)/Makefile-$(img).in))


# Build the default target image.
.PHONY: image
image: cloner_shar $(MECT_DEFAULT_IMAGE)


# Generate all manufacturing images.
#

# Recurse to properly evaluate the targets.
.PHONY: images
images: cloner_shar
	$(MAKE) $@_do

images_do: $(MECT_IMAGES)

# Build the cloner shell archive.
.PHONY: cloner_shar
cloner_shar: CLONER_COMPONENTS := \
    /lib/ld-linux.so.3 \
    /lib/libc.so.6 \
    /lib/libdl.so.2 \
    /lib/libgcc_s.so.1 \
    /lib/libm.so.6 \
    /lib/libpthread.so.0 \
    /lib/librt.so.1 \
    /lib/libstdc++.so.6 \
    /sbin/cloner \
    /usr/bin/flash_eraseall \
    /usr/lib/fonts \
    /usr/lib/libATCMinputdialog.so \
    /usr/lib/libfreetype.so.6 \
    /usr/lib/libglib-2.0.so.0 \
    /usr/lib/libgmodule-2.0.so.0 \
    /usr/lib/libgobject-2.0.so.0 \
    /usr/lib/libgthread-2.0.so.0 \
    /usr/lib/libpng.so.3 \
    /usr/lib/libQtCore.so \
    /usr/lib/libQtGui.so \
    /usr/lib/libQtNetwork.so \
    /usr/lib/libts-1.0.so.0 \
    /usr/lib/libz.so.1 \
    /usr/lib/ts \
    /usr/share/cloner/excludes_localfs.lst \
    /usr/share/cloner/excludes_rootfs.lst \

cloner_shar: CLONER_COMPONENTS := $(CLONER_COMPONENTS:%=$(MECT_LTIB_RFSDIR)%)
cloner_shar:
	test -n '$(CLONER_COMPONENTS)'
	rm -rf $(MECT_SYSCLONE_SHAR) $(MECT_SYSCLONE_DIR) $(MECT_SYSCLONE_SHDIR)
	mkdir -p $(MECT_SYSCLONE_DIR)
	rsync -aLv $(CLONER_COMPONENTS) $(MECT_KOBS_TMPL) $(MECT_SYSCLONE_DIR)/ --exclude \*.la
	#cp $(MECT_SYSCLONE_PRE_TMPL) $(MECT_SYSCLONE_SHAR)
	#cd $(MECT_SYSCLONE_DIR)/..; shar -M -x $(notdir $(MECT_SYSCLONE_DIR))/* >> $(MECT_SYSCLONE_SHAR)
	#tail -1 $(MECT_SYSCLONE_SHAR) | grep -q '^exit 0$$'
	#sed -i '$$ d' $(MECT_SYSCLONE_SHAR)
	#cat $(MECT_SYSCLONE_POST_TMPL) >> $(MECT_SYSCLONE_SHAR)
	mkdir -p $(MECT_SYSCLONE_SHDIR)
	test -d "$(MECT_SYSCLONE_SHDIR)"
	if /sbin/losetup -a | grep -q $(MECT_SYSCLONE_IMG); then \
	    dev=`/sbin/losetup -a | grep $(MECT_SYSCLONE_IMG)\$$ | awk '{ print $$1; }'`; \
	    if test -n "$$dev"; then sudo umount "$$dev"; fi; \
	fi
	sync
	dd if=/dev/zero of=$(MECT_SYSCLONE_IMG) bs=1k count=`du -s $(MECT_SYSCLONE_DIR) | awk '{ print int($$1 * 1.5); }'`
	/sbin/mke2fs -t ext2 -F -m 0 -i 1024 -b 1024 -L cloner $(MECT_SYSCLONE_IMG)
	rm -rf $(MECT_SYSCLONE_LOOP); mkdir -p $(MECT_SYSCLONE_LOOP)
	sudo mount -o loop -t ext2 $(MECT_SYSCLONE_IMG) $(MECT_SYSCLONE_LOOP)
	sudo rsync -av --delete --inplace --exclude lost+found $(MECT_SYSCLONE_DIR)/ $(MECT_SYSCLONE_LOOP)/
	sudo umount $(MECT_SYSCLONE_LOOP)
	rmdir $(MECT_SYSCLONE_LOOP)
	/sbin/e2fsck -fy $(MECT_SYSCLONE_IMG); test $$? -le 3
	/sbin/resize2fs -Mp $(MECT_SYSCLONE_IMG)
	install -m 644 $(MECT_SYSCLONE_TMPL) $(MECT_SYSCLONE_SH)
	sed -i 's/@@CLONER_VERSION@@/$(MECT_BUILD_RELEASE)/' $(MECT_SYSCLONE_SH)
	rm -rf $(dir $(MECT_SYSCLONE_DIR))

# Build the sysupdate for MECT Remote Services configuration.
.PHONY: sysupdate_mrs
sysupdate_mrs:
	rm -f $(MECT_SYSUPD_VPN)
	cat $(MECT_SYSUPD_VPN_PRE) > $(MECT_SYSUPD_VPN)
	if tail -1 $(MECT_SYSUPD_VPN) | grep -q '^exit 0$$'; then sed -i '$$ d' $(MECT_SYSUPD_VPN); fi
	cat $(MECT_SYSUPD_VPN_POST) >> $(MECT_SYSUPD_VPN)


PHONY: wininst
wininst: MECT_DOWNLOADS := \
	    7z.dll \
	    7zG.exe \
	    ActivePerl-5.16.3.1603-MSWin32-x86-296746.msi \
	    arm-2011.03-41-arm-none-linux-gnueabi.exe \
	    ATCM_Common.4cl \
	    ATCM.zip \
	    ATHW119_4CVM.kad \
	    Engineering_Help.zip \
	    Fonts.7z \
	    PLC.zip \
	    Qt485.7z \
	    Qt485_upd_rev$(MECT_BUILD_RELEASE).7z \
	    QtProject.7z \
	    sourcery-g++-lite.7z \
	    unzip.exe
wininst: MECT_DOWNLOADS += $(MECT_DOWNLOADS:%=%.$(MECT_MD5EXT))
wininst: MECT_DOWNLOADS := $(MECT_DOWNLOADS:%=$(MECT_FTPDIR)/%)
wininst:
	make MECT_DOWNLOADS="$(MECT_DOWNLOADS)" downloads
	test -f $(MECT_PRJDIR)/installer/Makefile
	make -C $(MECT_PRJDIR)/installer

# Common target rules
#

# Build the target-specific kernel.
$(subst /kernel-,/kernel-rfs-$(MECT_TARGET_PREFIX)$(MECT_BUILD_TARGET)-,$(MECT_LTIB_KERNEL_RPM)): $(MECT_LTIB_KERNEL_TS_RPM)
	test -n "$(MECT_BUILD_TARGET)" -a -n "$(MECT_KERNEL_TARGET_CONF)"
	touch -r $(MECT_LTIB_KERNEL_TS_RPM) /tmp/$(shell basename $(MECT_LTIB_KERNEL_TS_RPM).ltib-timestamp)
	rm -rf $(MECT_LTIBDIR)/rpm/BUILD/linux-*
	rm -f $(MECT_KERNEL_CONF) $(MECT_KERNEL_CONF).dev
	ln -s $(MECT_KERNEL_TARGET_CONF) $(MECT_KERNEL_CONF)
	cd $(MECT_LTIBDIR); ./ltib -f -p kernel
	touch -r /tmp/$(shell basename $(MECT_LTIB_KERNEL_TS_RPM).ltib-timestamp) $(MECT_LTIB_KERNEL_TS_RPM); rm -f /tmp/$(shell basename $(MECT_LTIB_KERNEL_TS_RPM).ltib-timestamp)
	set -e; cd $(MECT_RPMDIR); for rpm in '' `ls kernel-rfs-*.$(MECT_TARGET_ARCH).rpm imx-bootlets-src-mfg-*.$(MECT_TARGET_ARCH).rpm 2>/dev/null | sed '/-$(MECT_TARGET_PREFIX)/ d;'`; do \
		test -n "$$rpm" || continue; \
		mv $$rpm `echo $$rpm | sed 's/^\(kernel\|imx-bootlets-src\)-\(rfs\|mfg\)-/\1-\2-$(MECT_TARGET_PREFIX)$(MECT_BUILD_TARGET)-/'`; \
	done

$(MECT_LTIB_KERNEL_TS_RPM):
	cd $(MECT_LTIBDIR); ./ltib -f -p $(MECT_LTIB_KERNEL_TS_NAME)

# Build the target-specific boot.
.PHONY: target_boot
target_boot: MECT_KERNELRPM = $(subst /kernel-,/kernel-rfs-$(MECT_TARGET_PREFIX)$(MECT_BUILD_TARGET)-,$(MECT_LTIB_KERNEL_RPM))
target_boot: MECT_BOOTDIR = $(MECT_IMGDIR)/$(MECT_BUILD_TARGET)$(MECT_REL_PREFIX)$(MECT_BUILD_RELEASE)/boot
target_boot: $(MECT_COMMON_RFSPKGS)
	test -n '$(MECT_BUILD_TARGET)' -a -n '$(MECT_KERNEL_TARGET_CONF)'
	$(MAKE) MECT_BUILD_TARGET=$(MECT_BUILD_TARGET) MECT_KERNEL_TARGET_CONF=$(MECT_KERNEL_TARGET_CONF) $(MECT_KERNELRPM)
	sudo rm -rf $(MECT_BOOTDIR)
	mkdir -p $(MECT_BOOTDIR)/var/lib/rpm
	sudo $(MECT_FSDIR)/ltib/usr/bin/rpm --nodeps --root $(MECT_BOOTDIR) --prefix / --define '_tmppath /tmp/ltib' --dbpath /var/lib/rpm --ignorearch -Uvh --excludedocs $(MECT_RPMDIR)/imx-bootlets-src-mfg-$(MECT_TARGET_PREFIX)$(MECT_BUILD_TARGET)-2.6.35.3-1.1.0.$(MECT_TARGET_ARCH).rpm
	sudo rm -f $(MECT_BOOTDIR)/var/lib/rpm/*
	sudo rmdir $(MECT_BOOTDIR)/var/lib/rpm
	sudo rmdir --ignore-fail-on-non-empty $(MECT_BOOTDIR)/var/lib
	sudo rmdir --ignore-fail-on-non-empty $(MECT_BOOTDIR)/var

# Build the target-specific root file system.
.PHONY: target_rfs
target_rfs: MECT_KERNELRPM = $(subst /kernel-,/kernel-rfs-$(MECT_TARGET_PREFIX)$(MECT_BUILD_TARGET)-,$(MECT_LTIB_KERNEL_RPM))
target_rfs: MECT_RFSDIR = $(MECT_IMGDIR)/$(MECT_BUILD_TARGET)$(MECT_REL_PREFIX)$(MECT_BUILD_RELEASE)/rootfs
target_rfs: $(MECT_COMMON_RFSPKGS)
	test -n '$(MECT_BUILD_TARGET)' -a -n '$(MECT_KERNEL_TARGET_CONF)'
	$(MAKE) MECT_BUILD_TARGET=$(MECT_BUILD_TARGET) MECT_KERNEL_TARGET_CONF=$(MECT_KERNEL_TARGET_CONF) $(MECT_KERNELRPM)
	sudo rm -rf $(MECT_RFSDIR)
	mkdir -p $(MECT_RFSDIR)/var/lib/rpm $(MECT_RFSDIR)/tmp/ltib
	sudo $(MECT_FSDIR)/ltib/usr/bin/rpm --nodeps --root $(MECT_RFSDIR) --prefix / --define '_tmppath /tmp/ltib' --dbpath /var/lib/rpm --ignorearch -Uvh --excludedocs $(MECT_COMMON_RFSPKGS) $(subst /kernel-rfs-,/kernel-rfs-$(MECT_TARGET_PREFIX)$(MECT_BUILD_TARGET)-,$(MECT_TARGET_RFSPKGS))
	sudo rm -f $(MECT_RFSDIR)/var/lib/rpm/*
	sudo rmdir $(MECT_RFSDIR)/var/lib/rpm
	sudo rmdir --ignore-fail-on-non-empty $(MECT_RFSDIR)/var/lib
	sudo rmdir --ignore-fail-on-non-empty $(MECT_RFSDIR)/var
	sudo rmdir --ignore-fail-on-non-empty $(MECT_RFSDIR)/tmp/ltib
	sudo qemu-arm $(MECT_CSXCDIR)/arm-none-linux-gnueabi/libc/sbin/ldconfig -r $(MECT_RFSDIR)
	( \
		echo "Release: $(MECT_BUILD_RELEASE)"; \
		echo "Target:  $(MECT_BUILD_TARGET)"; \
		echo "Qt:      $(MECT_BUILD_QTVERSION)"; \
		echo "Qwt:     $(MECT_BUILD_QWTVERSION)"; \
		echo "RunTime: $(MECT_BUILD_ATCMCRT_BRANCH)/$(MECT_BUILD_ATCMCRT_TAG)"; \
		echo "MectPlugin: $(MECT_BUILD_PLUGINSCRT_BRANCH)/$(MECT_BUILD_PLUGINSCRT_TAG)"; \
		echo "MectApps: $(MECT_BUILD_APPSCRT_BRANCH)/$(MECT_BUILD_APPSCRT_TAG)"; \
	) > $(MECT_RFSDIR)/$(MECT_RFS_VERSION_FILE) && sudo chown root:root $(MECT_RFSDIR)/$(MECT_RFS_VERSION_FILE)
	# Target-specific tuning (better build target-specific packages?)
	if test "$(MECT_BUILD_TARGET)" = "TPLC100_01_AA" -o "$(MECT_BUILD_TARGET)" = "TPLC100_01_AB" \
		-o "$(MECT_BUILD_TARGET)" = "TPLC050_01_AA" -o "$(MECT_BUILD_TARGET)" = "TPLC050_01_AB"; then \
		sudo rm -f $(MECT_RFSDIR)/usr/bin/ts_calibrate; \
	fi
	sudo depmod -ae -F $(MECT_LTIBDIR)/rootfs/boot/System.map -b $(MECT_RFSDIR) 2.6.35.3
	sudo du -sh --apparent-size $(MECT_RFSDIR)

# Build the target-specific local file system.
.PHONY: target_lfs
target_lfs: MECT_KERNELRPM = $(subst /kernel-,/kernel-rfs-$(MECT_TARGET_PREFIX)$(MECT_BUILD_TARGET)-,$(MECT_LTIB_KERNEL_RPM))
target_lfs_flash target_lfs: MECT_LFSDIR = $(MECT_IMGDIR)/$(MECT_BUILD_TARGET)$(MECT_REL_PREFIX)$(MECT_BUILD_RELEASE)/localfs
target_lfs: $(MECT_COMMON_LFSPKGS)
	test -n '$(MECT_BUILD_TARGET)'
	sudo rm -rf $(MECT_LFSDIR)
	sudo mkdir -p $(MECT_LFSDIR)/var/lib/rpm $(MECT_LFSDIR)/tmp/ltib
	sudo $(MECT_FSDIR)/ltib/usr/bin/rpm --nodeps --root $(MECT_LFSDIR) --prefix / --define '_tmppath /tmp/ltib' --dbpath /var/lib/rpm --ignorearch -Uvh --excludedocs $(MECT_COMMON_LFSPKGS) $(MECT_LFSPKGS)
	sudo rm -f $(MECT_LFSDIR)/var/lib/rpm/*
	sudo rmdir $(MECT_LFSDIR)/var/lib/rpm
	sudo rmdir --ignore-fail-on-non-empty $(MECT_LFSDIR)/var/lib
	sudo rmdir --ignore-fail-on-non-empty $(MECT_LFSDIR)/var
	sudo rmdir --ignore-fail-on-non-empty $(MECT_LFSDIR)/tmp/ltib
	sudo rmdir --ignore-fail-on-non-empty $(MECT_LFSDIR)/tmp
	$(MAKE) target_lfs_flash
	sudo du -sh --apparent-size $(MECT_LFSDIR)

# Customize local file system layout for switch between FLASH/SD card.
.PHONY: target_lfs_flash
target_lfs_flash:
	test -n '$(MECT_LFSDIR)'
	test -d $(MECT_LFSDIR)
	! test -d $(MECT_LFSDIR)/flash
	sudo mkdir $(MECT_LFSDIR)/flash
	sudo mv $(MECT_LFSDIR)/root $(MECT_LFSDIR)/etc $(MECT_LFSDIR)/control $(MECT_LFSDIR)/data $(MECT_LFSDIR)/flash
	sudo ln -s flash/root $(MECT_LFSDIR)/root
	sudo ln -s flash/etc $(MECT_LFSDIR)/etc
	sudo ln -s flash/control $(MECT_LFSDIR)/control
	sudo ln -s flash/data $(MECT_LFSDIR)/data

# Build the target-specific project for Freescale manufacturing tool.
.PHONY: target_mfg_upd
target_mfg_upd: MECT_TGTDIR = $(MECT_IMGDIR)/$(MECT_BUILD_TARGET)$(MECT_REL_PREFIX)$(MECT_BUILD_RELEASE)
target_mfg_upd: MECT_MFGDIR = $(MECT_TGTDIR)/$(shell basename $(MECT_TGTDIR) | sed 's/\./_/g')
target_mfg_upd: MECT_MFGZIP = $(shell readlink -m $(MECT_MFGDIR)/../../$(notdir $(MECT_MFGDIR)).zip)
target_mfg_upd: MECT_SYSUPD_IMG = $(shell readlink -m $(MECT_MFGDIR)/../../img_sysupdate-$(MECT_BUILD_RELEASE)-$(MECT_BUILD_TARGET).ext2)
target_mfg_upd: MECT_SYSUPD_LOOP = $(shell readlink -m $(MECT_MFGDIR)/../../sysupdate_$(MECT_BUILD_RELEASE)_$(MECT_BUILD_TARGET).loop)
target_mfg_upd: MECT_SYSUPDIR = $(shell readlink -m $(MECT_MFGDIR)/../../$(MECT_BUILD_TARGET))
target_mfg_upd: MECT_BOOTDIR = $(MECT_TGTDIR)/boot
target_mfg_upd: MECT_RFSDIR = $(MECT_TGTDIR)/rootfs
target_mfg_upd: MECT_LFSDIR = $(MECT_TGTDIR)/localfs
target_mfg_upd: MECT_BUILD_VER_MAJ_MIN := $(shell echo $(MECT_BUILD_RELEASE) | sed 's/^\([0-9]\+\.[0-9]\+\).*/\1/; s/\./\\\\\\\\./g')
target_mfg_upd:
	test -n '$(MECT_BUILD_TARGET)' -a -n '$(MECT_FTPDIR)'
	sudo rm -rf $(MECT_MFGDIR)
	mkdir -p $(MECT_MFGDIR)/'OS firmware'/img $(MECT_MFGDIR)/'OS firmware'/sys $(MECT_TGTDIR)
	sed "s/@@PLAYER@@/$(notdir $(MECT_MFGDIR))/" $(MECT_FTPDIR)/player.ini > $(MECT_MFGDIR)/player.ini
	install -m 644 $(MECT_FTPDIR)/fdisk-u.input $(MECT_MFGDIR)/'OS firmware'/sys/fdisk-u.input
	install -m 644 $(MECT_FTPDIR)/ucl.xml $(MECT_MFGDIR)/'OS firmware'/ucl.xml
	sudo tar cf $(MECT_MFGDIR)/'OS firmware'/img/rootfs.tar -C $(MECT_RFSDIR) .
	sudo tar cf $(MECT_MFGDIR)/'OS firmware'/img/localfs.tar -C $(MECT_LFSDIR) .
	install -m 644 $(MECT_BOOTDIR)/boot/imx28_ivt_linux.sb $(MECT_MFGDIR)/'OS firmware'/img
	install -m 644 $(MECT_BOOTDIR)/boot/updater_ivt.sb $(MECT_MFGDIR)/'OS firmware'/sys
	rm -f $(MECT_MFGZIP)
	cd $(MECT_MFGDIR); zip -0r $(MECT_MFGZIP) *
	#
	sudo rm -rf $(MECT_SYSUPDIR)
	mkdir -p $(MECT_SYSUPDIR)
	install -m 644 $(MECT_KOBS_TMPL) $(MECT_SYSUPDIR)/..
	install -m 644 $(MECT_BOOTDIR)/boot/imx28_ivt_linux.sb $(MECT_SYSUPDIR)
	sudo rm -rf $(MECT_RFSDIR)/local/*
	sudo tar cf $(MECT_SYSUPDIR)/rootfs.tar -C $(MECT_RFSDIR) .
	cd $(MECT_LFSDIR); sudo rm -rf \
		flash/etc/sysconfig \
		flash/root/hmi \
		flash/control \
		retentive \
		flash/data \
		var/spool/cron/crontabs/root \
		flash/etc/ppp/chat-usb3g \
		flash/etc/icinga/nrpe.cfg
	sudo tar cf $(MECT_SYSUPDIR)/localfs.tar -C $(MECT_LFSDIR) .
	#
	mkdir -p $(MECT_SYSUPDIR)/fs
	sudo tar xf $(MECT_SYSUPDIR)/rootfs.tar -C $(MECT_SYSUPDIR)/fs
	sudo tar xf $(MECT_SYSUPDIR)/localfs.tar -C $(MECT_SYSUPDIR)/fs/local
	test ! -d $(MECT_SYSUPDIR)/fs/sysupdate
	sudo mkdir -p $(MECT_SYSUPDIR)/fs/sysupdate
	test -d $(MECT_SYSUPDIR)/fs/sysupdate
	sudo cp --reflink=auto $(MECT_SYSUPDIR)/imx28_ivt_linux.sb $(MECT_SYSUPDIR)/fs/sysupdate
	sudo cp --reflink=auto $(MECT_KOBS_TMPL) $(MECT_SYSUPDIR)/fs/sysupdate
	sudo chmod 755 $(MECT_SYSUPDIR)/fs/sysupdate/$(notdir $(MECT_KOBS_TMPL))
	#
	if /sbin/losetup -a | grep -q $(MECT_SYSUPD_IMG); then \
	    dev=`/sbin/losetup -a | grep $(MECT_SYSUPD_IMG)\$$ | awk '{ print $$1; }'`; \
	    if test -n "$$dev"; then sudo umount "$$dev"; fi; \
	fi
	sync
	dd if=/dev/zero of=$(MECT_SYSUPD_IMG) bs=1k count=`du -s $(MECT_SYSUPDIR)/fs | awk '{ print int($$1 * 1.5); }'`
	/sbin/mke2fs -t ext2 -F -m 0 -i 1024 -b 1024 -L sysupdate_$(MECT_BUILD_TARGET) $(MECT_SYSUPD_IMG)
	rm -rf $(MECT_SYSUPD_LOOP); mkdir -p $(MECT_SYSUPD_LOOP)
	sudo mount -o loop -t ext2 $(MECT_SYSUPD_IMG) $(MECT_SYSUPD_LOOP)
	sudo rsync -av --delete --inplace --exclude lost+found $(MECT_SYSUPDIR)/fs/ $(MECT_SYSUPD_LOOP)/
	sudo umount $(MECT_SYSUPD_LOOP)
	rmdir $(MECT_SYSUPD_LOOP)
	/sbin/e2fsck -fy $(MECT_SYSUPD_IMG); test $$? -le 3
	/sbin/resize2fs -Mp $(MECT_SYSUPD_IMG)
	sed 's/@@THIS_VERSION@@/$(MECT_BUILD_RELEASE)/; s/@@THIS_VERSION_MAJ_MIN@@/$(MECT_BUILD_VER_MAJ_MIN)/' $(MECT_SYSUPD_IMG_TMPL) > $(MECT_IMGDIR)/$(MECT_SYSUPD_IMG_SH)
	sudo rm -rf $(MECT_SYSUPDIR)/fs $(MECT_RFSDIR) $(MECT_LFSDIR) $(MECT_BOOTDIR) $(MECT_SYSUPDIR) $(shell readlink -m $(MECT_SYSUPDIR)/../$(notdir $(MECT_KOBS_TMPL))) $(MECT_TGTDIR)

# Build the archive for target-specific development.
.PHONY: target_dev
target_dev:
	test -n '$(MECT_IMGDIR)'
	sudo rm -rf $(MECT_IMGDIR)/dev $(MECT_IMGDIR)/rootfs_dev.zip
	-for d in /usr/include /usr/lib /lib /usr/src/linux/include; do \
		mkdir -p $(MECT_IMGDIR)/dev/rootfs$$d; \
		sudo rsync -avL $(MECT_LTIB_RFSDIR)$$d/ $(MECT_IMGDIR)/dev/rootfs$$d/; \
	done
	cd $(MECT_IMGDIR)/dev; sudo zip -1r $(MECT_IMGDIR)/rootfs_dev.zip rootfs
	sudo rm -rf $(MECT_IMGDIR)/dev

# Handle the patches for LTIB configuration and spec files.
# 

# Create new patches from the current installation.

.PHONY: ltib_genpatch
ltib_genpatch: ltib_genpatch_config ltib_genpatch_specs ltib_genpatch_bin

.PHONY: ltib_genpatch_config
ltib_genpatch_config: $(MECT_LTIBDIR_REF)/config
	cd $(MECT_LTIBDIR)/.. && { diff -aurN --exclude=.config.old --exclude=*.config.dev --exclude=*.bak --exclude=*.swp $(shell basename $(MECT_LTIBDIR_REF))/config $(shell basename $(MECT_LTIBDIR))/config; diff -auN $(shell basename $(MECT_LTIBDIR_REF))/.config $(shell basename $(MECT_LTIBDIR))/.config; diff -auN $(shell basename $(MECT_LTIBDIR_REF))/.config.cmd $(shell basename $(MECT_LTIBDIR))/.config.cmd; diff -auN $(shell basename $(MECT_LTIBDIR_REF))/.tmpconfig.h $(shell basename $(MECT_LTIBDIR))/.tmpconfig.h; } | sed '/^\(---\|\+\+\+\) / s/\t.*//' > $(MECT_FTPDIR)/$(MECT_LTIB_MECT_CONFIG_PATCH); true
	cd $(MECT_FTPDIR); md5sum $(MECT_LTIB_MECT_CONFIG_PATCH) > $(MECT_LTIB_MECT_CONFIG_PATCH).$(MECT_MD5EXT)

.PHONY: ltib_genpatch_specs
ltib_genpatch_specs: $(MECT_LTIBDIR_REF)/dist
	cd $(MECT_LTIBDIR)/.. && diff -aurN --exclude=*-orig.spec --exclude=*.bak --exclude=*.swp $(shell basename $(MECT_LTIBDIR_REF))/dist $(shell basename $(MECT_LTIBDIR))/dist | sed '/^\(---\|\+\+\+\) / s/\t.*//' > $(MECT_FTPDIR)/$(MECT_LTIB_MECT_SPECS_PATCH); true
	cd $(MECT_FTPDIR); md5sum $(MECT_LTIB_MECT_SPECS_PATCH) > $(MECT_LTIB_MECT_SPECS_PATCH).$(MECT_MD5EXT)

.PHONY: ltib_genpatch_bin
ltib_genpatch_bin: $(MECT_LTIBDIR_REF)/bin
	cd $(MECT_LTIBDIR)/.. && { diff -aurN --exclude=*.bak --exclude=*.swp $(shell basename $(MECT_LTIBDIR_REF))/bin $(shell basename $(MECT_LTIBDIR))/bin; diff -auN $(shell basename $(MECT_LTIBDIR_REF))/ltib $(shell basename $(MECT_LTIBDIR))/ltib; } | sed '/^\(---\|\+\+\+\) / s/\t.*//' > $(MECT_FTPDIR)/$(MECT_LTIB_MECT_BIN_PATCH); true
	cd $(MECT_FTPDIR); md5sum $(MECT_LTIB_MECT_BIN_PATCH) > $(MECT_LTIB_MECT_BIN_PATCH).$(MECT_MD5EXT)

# Update an existing LTIB installation from repository.
#

.PHONY: ltib_update
ltib_update:
	git fetch origin
	git reset --hard origin/master
	if test -n '$(MECT_BUILD_IMXMECT_BRANCH)'; then git checkout $(MECT_BUILD_IMXMECT_BRANCH); git pull; fi
	if test -n '$(MECT_BUILD_IMXMECT_TAG)' -a '$(MECT_BUILD_IMXMECT_TAG)' != '0.0'; then git checkout tags/$(MECT_BUILD_IMXMECT_TAG); fi
	if ! test -d $(MECT_LTIBDIR_REF); then \
		mv $(MECT_LTIBDIR) $(MECT_LTIBDIR).precious; \
		$(MAKE) ltib_inst ltib_patch; \
		rm -rf $(MECT_LTIBDIR); \
		mv $(MECT_LTIBDIR).precious $(MECT_LTIBDIR); \
	fi
	rm -rf $(MECT_LTIBDIR_PATCH)
	rsync -a $(MECT_LTIBDIR_REF)/ $(MECT_LTIBDIR_PATCH)/
	cd $(MECT_LTIBDIR_PATCH); patch -p1 < $(MECT_FTPDIR)/$(MECT_LTIB_MECT_CONFIG_PATCH)
	cd $(MECT_LTIBDIR_PATCH); patch -p1 < $(MECT_FTPDIR)/$(MECT_LTIB_MECT_SPECS_PATCH)
	cd $(MECT_LTIBDIR_PATCH); patch -p1 < $(MECT_FTPDIR)/$(MECT_LTIB_MECT_BIN_PATCH)
	rsync -a --delete $(MECT_LTIBDIR_PATCH)/config/ $(MECT_LTIBDIR)/config/
	rsync -a --delete $(MECT_LTIBDIR_PATCH)/dist/ $(MECT_LTIBDIR)/dist/
	rsync -a --delete $(MECT_LTIBDIR_PATCH)/bin/ $(MECT_LTIBDIR)/bin/
	cp $(MECT_LTIBDIR_PATCH)/.config $(MECT_LTIBDIR)/.config
	cp $(MECT_LTIBDIR_PATCH)/.config.cmd $(MECT_LTIBDIR)/.config.cmd
	cp $(MECT_LTIBDIR_PATCH)/.tmpconfig.h $(MECT_LTIBDIR)/.tmpconfig.h
	cp -a $(MECT_LTIBDIR_PATCH)/ltib $(MECT_LTIBDIR)/ltib
	rm -rf $(MECT_LTIBDIR_PATCH)
	$(MAKE) spec_setup


# Create reference images for use to check future builds
#

.PHONY: images_check
images_check: MECT_GOLD_REL = $(shell echo $(MECT_BUILD_RELEASE) | sed 's/\./_/g')
ifeq ($(MECT_REF_IMG),)
images_check: MECT_REF_IMG := $(GI)
endif
images_check:
	if test -z "$(MECT_REF_IMG)" -o ! -d "$(MECT_REF_IMG)"; then \
		echo "ERROR: no image reference directory ($(MECT_REF_IMG))."; \
		exit 1; \
	fi
	test -s '$(MECT_IMG_TESTER)'
	for i in "" $(MECT_IMGDIR)/*$(MECT_REL_PREFIX)$(MECT_GOLD_REL).zip; do \
		test -z "$$i" -o ! -s "$$i" && continue; \
		echo ""; \
		echo "Checking $$i..."; \
		sudo sh $(MECT_IMG_TESTER) "$(MECT_REF_IMG)" "$$i" $(MECT_TMPDIR) $(MECT_REL_PREFIX)$(MECT_GOLD_REL).zip; \
	done


# Stage images for testing.
#

.PHONY: stage_images
stage_images:
	test -d $(MECT_TESTSHARE) -a -w $(MECT_TESTSHARE)
	mount | grep -q ' $(MECT_TESTSHARE) '
	rsync -ahP $(MECT_IMGDIR)/ $(MECT_TESTSHARE)/$(MECT_TESTNAME)$(MECT_BUILD_RELEASE)/


# Utilities
#

.PHONY: clean_projects
clean_projects:
	if test -d $(MECT_PRJDIR); then $(MAKE) -C $(MECT_PRJDIR) clean; fi

.PHONY: clean
clean: clean_projects
	sudo rm -rf $(MECT_LTIBDIR) $(MECT_TMPDIR) $(MECT_CSXCUNPACK) $(MECT_CSXCDIR) $(MECT_FSDIR)/ltib $(MECT_FSDIR)/pkgs $(MECT_FSDIR)/rootfs $(MECT_TMPRPMDIR) $(MECT_QT_INSTALL_DIR)
	if test -d $(MECT_FSDIR); then sudo rmdir --ignore-fail-on-non-empty $(MECT_FSDIR); fi

.PHONY: distclean
distclean: clean
	if which ccache > /dev/null; then ccache -C; fi
	sudo rm -rf $(MECT_IMGDIR) $(MECT_LTIBDIR_REF)


# Downloads
#
# NOTE: Here we assume that each file to download has an MD5
# checksum named <file_name>.$(MECT_MD5EXT) in the same directory.
#

# Generic download rule for MECT site
$(MECT_FTPDIR)/%: $(MECT_FTPDIR)/%.$(MECT_MD5EXT)
	dir=$(shell dirname $@); mkdir -p $$dir; cd $$dir; md5sum -c $@.$(MECT_MD5EXT) 2>/dev/null || { rm -f $@; wget -O $@ --progress=dot:mega "$(MECT_FTPURL)/$(shell basename $@)"; md5sum -c $@.$(MECT_MD5EXT); }

$(MECT_FTPDIR)/%.$(MECT_MD5EXT):
	mkdir -p $(shell dirname $@)
	wget -O $@ "$(MECT_FTPURL)/$(shell basename $@)"
	touch -c $@			# Force the re-check of the downloaded file, if any.
	$(MAKE) $(@:%.$(MECT_MD5EXT)=%)	# Re-check the downloaded file, if any.


# Specific download rules from non-MECT sites
$(MECT_FTPDIR)/$(MECT_LTIB_UBUNTU_12_04_PATCH): $(MECT_FTPDIR)/$(MECT_LTIB_UBUNTU_12_04_PATCH).$(MECT_MD5EXT)
	dir=$(shell dirname $@); mkdir -p $$dir; cd $$dir; md5sum -c $@.$(MECT_MD5EXT) 2>/dev/null || { rm -f $@; wget -O $@ --progress=dot:mega --no-check-certificate "$(MECT_URL_LTIB_UBUNTU_12_04_PATCH)"; md5sum -c $@.$(MECT_MD5EXT); }

$(MECT_FTPDIR)/$(MECT_LTIB_UBUNTU_12_04_PATCH).$(MECT_MD5EXT):
	mkdir -p $(shell dirname $@)
	wget -O $@ "$(MECT_FTPURL)/$(shell basename $@)"
	touch -c $@			# Force the re-check of the downloaded file, if any.
	$(MAKE) $(@:%.$(MECT_MD5EXT)=%)	# Re-check the downloaded file, if any.


# Test targets, if any
#
-include ../tests.in

# vim: set noexpandtab:

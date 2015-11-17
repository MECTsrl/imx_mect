# Default target image.
# NOTE: uncomment only one.
DEFAULT_IMAGE := TPAC1007_480x272
#DEFAULT_IMAGE := TPAC1006_320x240
#DEFAULT_IMAGE := TPAC1006_640x480
#DEFAULT_IMAGE := TPAC1008_800x600

# Build version information.
BUILD_RELEASE := 6.6rc0
BUILD_TARGET_TPAC1006_320x240 := TPAC1006_320x240
BUILD_TARGET_TPAC1006_640x480 := TPAC1006_640x480
BUILD_TARGET_TPAC1007_480x272 := TPAC1007_480x272
BUILD_TARGET_TPAC1008_800x600 := TPAC1008_800x600
BUILD_QTVERSION = $(QT_VERSION)
BUILD_QWTVERSION = $(QWT_VERSION)

QT_VERSION := 4.8.5
QWT_VERSION := 6.1-multiaxes

# Name of the root file system version file
RFS_VERSION_FILE := rootfs_version

# Target pltform architecture
TARGET_ARCH := arm
# UNIX name of the target platform
TARGET_UNIX_NAME := imx28

# Developer info for git
USER_NAME := "Embedded developer"
HOST_NAME := "development.localdomain"

# Download the archives here.
FTPDIR = $(CURDIR)/src
# LTIB is installed here.
LTIBDIR = $(CURDIR)/ltib
# LTIB (config and dist) before MECT patches is saved here.
LTIBDIR_REF = $(CURDIR)/ltib.reference
# LTIB (config and dist) on which to apply current patches.
LTIBDIR_PATCH = $(CURDIR)/ltib.patched
# LTIB rootfs is created here.
LTIB_RFSDIR = $(LTIBDIR)/rootfs
# LTIB specs are installed here.
LTIBSPECDIR = $(LTIBDIR)/dist/lfs-5.1
# Unpack the archives here.
TMPDIR = $(CURDIR)/tmp
# Archive repository
FTPURL := http://www.mect.it/archive
# Hardcoded Freescale directory
FSDIR := /opt/freescale
# LPP location
LPPDIR = $(FSDIR)/pkgs
# RPM archive
RPMDIR = $(CURDIR)/ltib/rpm/RPMS/$(TARGET_ARCH)
# Root file system top-level directory
IMGDIR = $(CURDIR)/images-all
# Draft directory for rpmbuild
TMPRPMDIR = /tmp/rpm-$(USER)
# Expand to the name of the kernel RPM built by LTIB.
LTIB_KERNEL_RPM = $(RPMDIR)/$(shell $(FSDIR)/ltib/usr/bin/rpm --root $(LTIB_RFSDIR) --dbpath /var/lib/rpm -q --whatprovides kernel).$(TARGET_ARCH).rpm
# Expand to the name of the timestamp when the kernel RPM was built by LTIB.
LTIB_KERNEL_TS_NAME = last-kernel-build
LTIB_KERNEL_TS_RPM = $(RPMDIR)/$(shell $(FSDIR)/ltib/usr/bin/rpm --root $(LTIB_RFSDIR) --dbpath /var/lib/rpm -q --whatprovides $(LTIB_KERNEL_TS_NAME)).$(TARGET_ARCH).rpm
# Kernel configuration file.
KERNEL_CONF := $(LTIBDIR)/config/platform/imx/kernel-2.6.35-imx28-tpac.config


# Extension of the MD5 checksums for the downloads.
MD5EXT := md5

# Packages for USB serial kernel modules.
#

RFSPKG_USBSERIAL_USBSERIAL := kernel-dev-usbserial-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_AIRCABLE := kernel-dev-usbserial-aircable-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_ARK3116 := kernel-dev-usbserial-ark3116-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_BELKIN := kernel-dev-usbserial-belkin_sa-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_CH341 := kernel-dev-usbserial-ch341-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_CP210X := kernel-dev-usbserial-cp210x-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_CYBERJACK := kernel-dev-usbserial-cyberjack-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_CYPRESS_M8 := kernel-dev-usbserial-cypress_m8-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_DEBUG := kernel-dev-usbserial-debug-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_DIGI_ACCELEPORT := kernel-dev-usbserial-digi_acceleport-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_EMPEG := kernel-dev-usbserial-empeg-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_FTDI_SIO := kernel-dev-usbserial-ftdi_sio-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_FUNSOFT := kernel-dev-usbserial-funsoft-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_GARMIN_GPS := kernel-dev-usbserial-garmin_gps-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_HP4X := kernel-dev-usbserial-hp4x-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_IO_EDGEPORT := kernel-dev-usbserial-io_edgeport-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_IO_TI := kernel-dev-usbserial-io_ti-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_IPAQ := kernel-dev-usbserial-ipaq-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_IPW := kernel-dev-usbserial-ipw-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_IR := kernel-dev-usbserial-ir-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_IUU_PHOENIX := kernel-dev-usbserial-iuu_phoenix-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_KEYSPAN := kernel-dev-usbserial-keyspan-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_KEYSPAN_PDA := kernel-dev-usbserial-keyspan_pda-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_KL5KUSB105 := kernel-dev-usbserial-kl5kusb105-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_KOBIL_SCT := kernel-dev-usbserial-kobil_sct-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_MCT_U232 := kernel-dev-usbserial-mct_u232-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_MOS7720 := kernel-dev-usbserial-mos7720-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_MOS7840 := kernel-dev-usbserial-mos7840-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_MOTO_MODEM := kernel-dev-usbserial-moto_modem-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_NAVMAN := kernel-dev-usbserial-navman-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_OMNINET := kernel-dev-usbserial-omninet-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_OPTICON := kernel-dev-usbserial-opticon-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_OPTION := kernel-dev-usbserial-option-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_OTI6858 := kernel-dev-usbserial-oti6858-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_PL2303 := kernel-dev-usbserial-pl2303-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_QCAUX := kernel-dev-usbserial-qcaux-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_QCSERIAL := kernel-dev-usbserial-qcserial-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_SAFE_SERIAL := kernel-dev-usbserial-safe_serial-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_SIEMENS_MPI := kernel-dev-usbserial-siemens_mpi-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_SIERRA := kernel-dev-usbserial-sierra-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_SPCP8X5 := kernel-dev-usbserial-spcp8x5-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_SYMBOLSERIAL := kernel-dev-usbserial-symbolserial-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_TI_3410_5052 := kernel-dev-usbserial-ti_3410_5052-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_VISOR := kernel-dev-usbserial-visor-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_VIVOPAY := kernel-dev-usbserial-vivopay-serial-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_WHITEHEAT := kernel-dev-usbserial-whiteheat-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_WWAN := kernel-dev-usbserial-wwan-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm
RFSPKG_USBSERIAL_ZIO := kernel-dev-usbserial-zio-2.6.35.3-imx_1.1.0.$(TARGET_ARCH).rpm

# Packages for USB 3G modems
#

RFSPKG_USB3G_MODESWITCH := usb-modeswitch-rfs-2.2.5-1.$(TARGET_ARCH).rpm
RFSPKG_USB3G_MODESWITCH_DATA := usb-modeswitch-data-rfs-20150627-1.$(TARGET_ARCH).rpm
RFSPKG_USB3G_LIBUSB1 := libusb1-rfs-1.0.20-1.$(TARGET_ARCH).rpm

# Package list for creating the root file system for various targets.
#

COMMON_RFSPKGS := \
	base_libs-rfs-1.2-1.$(TARGET_ARCH).rpm \
	boa-rfs-0.94.14rc21-1.$(TARGET_ARCH).rpm \
	busybox-rfs-1.15.0-1.$(TARGET_ARCH).rpm \
	cantest-rfs-1.0-1.$(TARGET_ARCH).rpm \
	dhcp-rfs-3.0.3b1-1.$(TARGET_ARCH).rpm \
	dropbear-rfs-0.52-1.$(TARGET_ARCH).rpm \
	e2fsprogs-rfs-1.41.4-1.$(TARGET_ARCH).rpm \
	expat-rfs-1.95.8-1.$(TARGET_ARCH).rpm \
	fontconfig-rfs-2.4.2-1.$(TARGET_ARCH).rpm \
	freetype-rfs-2.3.9-1.$(TARGET_ARCH).rpm \
	glib2-rfs-2.18.1-1.$(TARGET_ARCH).rpm \
	hotplug-rfs-2004_03_29-3.$(TARGET_ARCH).rpm \
	iproute-rfs-2.6.37-050330.$(TARGET_ARCH).rpm \
	libsocketcan-rfs-0.0.8-0.$(TARGET_ARCH).rpm \
	libtermcap-rfs-2.0.8-31_1.$(TARGET_ARCH).rpm \
	libusb1-rfs-1.0.20-1.$(TARGET_ARCH).rpm \
	libusb-rfs-0.1.8-1.$(TARGET_ARCH).rpm \
	lzo-rfs-2.03-0.$(TARGET_ARCH).rpm \
	merge-rfs-0.1-1.$(TARGET_ARCH).rpm \
	modeps-rfs-1.0-1.$(TARGET_ARCH).rpm \
	mtd-utils-rfs-201006-1.$(TARGET_ARCH).rpm \
	mysql-rfs-4.1.12-0.$(TARGET_ARCH).rpm \
	ncurses-rfs-5.3-1.$(TARGET_ARCH).rpm \
	ppp-rfs-2.4.4-1.$(TARGET_ARCH).rpm \
	qt-embedded-rfs-4.8.5-1.$(TARGET_ARCH).rpm \
	qwt-rfs-6.1-1_multiaxes.$(TARGET_ARCH).rpm \
	rsync-rfs-2.6.5-1.$(TARGET_ARCH).rpm \
	sftp-server-rfs-4.3p2-1.$(TARGET_ARCH).rpm \
	skell-rfs-1.18-2.$(TARGET_ARCH).rpm \
	sqlite-rfs-3.6.12-1.$(TARGET_ARCH).rpm \
	sysconfig-rfs-1.2-5.$(TARGET_ARCH).rpm \
	tslib-rfs-1.0-3.$(TARGET_ARCH).rpm \
	udev-rfs-117-5.$(TARGET_ARCH).rpm \
	usb-modeswitch-data-rfs-20150627-1.$(TARGET_ARCH).rpm \
	usb-modeswitch-rfs-2.2.5-1.$(TARGET_ARCH).rpm \
	xenomai-rfs-2.6.0-1.$(TARGET_ARCH).rpm \
	zip-rfs-3.0.0-0.$(TARGET_ARCH).rpm \
	zlib-rfs-1.2.3-2.$(TARGET_ARCH).rpm \

COMMON_RFSPKGS := $(COMMON_RFSPKGS:%=$(RPMDIR)/%)

LFSPKGS := \
	local-1.0-1_$(BUILD_RELEASE).$(TARGET_ARCH).rpm \
	local-ATCMControl_runtime_system-1.0-1_$(BUILD_RELEASE).$(TARGET_ARCH).rpm \
	local-cgic_work-1.0-1_$(BUILD_RELEASE).$(TARGET_ARCH).rpm \
	local-factory_data-1.0-1_$(BUILD_RELEASE).$(TARGET_ARCH).rpm \
	local-setup_time-1.0-1_$(BUILD_RELEASE).$(TARGET_ARCH).rpm \
	local-splash-1.0-1_$(BUILD_RELEASE).$(TARGET_ARCH).rpm \

LFSPKGS := $(LFSPKGS:%=$(RPMDIR)/%)

TARGET_RFSPKGS := \
	kernel-rfs-2.6.35.3-imx_1.1.0.arm.rpm \
	$(RFSPKG_USBSERIAL_PL2303) \
	$(RFSPKG_USBSERIAL_USBSERIAL) \
	$(RFSPKG_USB3G_MODESWITCH) \
	$(RFSPKG_USB3G_MODESWITCH_DATA) \
	$(RFSPKG_USB3G_LIBUSB1) \

TARGET_RFSPKGS := $(TARGET_RFSPKGS:%=$(RPMDIR)/%)


# Set archive sources
#

# Toolchain archive
CSXCPREFIX = arm-2011.03
CSXCARCH = $(CSXCPREFIX)-41-arm-none-linux-gnueabi-i686-pc-linux-gnu.tar.bz2
URL_CSXCARCH = $(FTPURL)/$(CSXCARCH)
URL_CSXCARCH_MD5 = $(FTPURL)/$(CSXCARCH).$(MD5EXT)
CSXCUNPACK = $(CURDIR)/$(CSXCPREFIX)
# Keep this in sync with LTIB config
CSXCDIR = /opt/CodeSourcery

# LTIB archive
LTIB_EVKARCH = L2.6.35_1.1.0_130130_source.tar.gz
LTIB_EVKDIR = $(LTIB_EVKARCH:%.tar.gz=%)

# LTIB pre-configuration for install (MECT patch)
LTIBINST_TARGETDIR_PATHCH = ltib-install-preset-target-dir.patch

# LTIB fix downloads for Ubuntu 12.04 (MECT patch)
LTIB_UBUNTU_URL_PATHCH = ltib-ubuntu12.04-url.patch

# LTIB fix /usr/include/sys for i386 architectures for Ubuntu 12.04 (MECT patch)
LTIB_UBUNTU_INCLUDE_SYS_PATHCH = ltib-ubuntu12.04-include-sys.patch

# LTIB fix configuration and specs (MECT patches)
LTIB_MECT_CONFIG_PATCH = ltib-mect-config.patch
LTIB_MECT_SPECS_PATCH = ltib-mect-specs.patch
LTIB_MECT_BIN_PATCH = ltib-mect-bin.patch

# LTIB set MECT PPP (MECT patch)
LTIB_MECT_PPP_PATCH = ltib-mect-ppp-url.patch

# LTIB Ubuntu 12.04 patch bundle
LTIB_UBUNTU_12_04_PATCH = patch-ltib-ubuntu12.04.sh
URL_LTIB_UBUNTU_12_04_PATCH = $(FTPURL)/$(LTIB_UBUNTU_12_04_PATCH)

# LTIB Ubuntu 12.04 patch bundle fix /usr/include/sys for i386 architectures (MECT patch)
LTIB_UBUNTU_12_04_PATCH_INCLUDE_SYS_PATCH = ubuntu-ltib-patch-include-sys-i386.patch

# LTIB qt spec file (MECT patch)
QT_INSTALL_DIR = /opt/Trolltech
LTIB_QT_ARCH = qt-everywhere-opensource-src-4.8.5.tar.gz
LTIB_QT_PATCH1 = qt-everywhere-opensource-src-4.8.5-1394522957.patch
LTIB_QT_PATCH2 = qt-everywhere-opensource-src-4.8.5-1420823826.patch
LTIB_QT_PATCH3 = qt-everywhere-opensource-src-4.8.5-1420823825.patch


# Extra packages to copy in $(LTIBPKGDIR)
FSPKG_DL := \
	$(LTIB_QT_ARCH) \
	$(LTIB_QT_PATCH2) \

FSPKG := \
	$(LTIB_QT_PATCH1) \
	$(LTIB_QT_PATCH3) \

FSPKG := $(FSPKG) $(FSPKG_DL)


FSPKGMD5 := $(FSPKG:%=%.$(MD5EXT))
FSPKG := $(FSPKG) $(FSPKGMD5)
FSPKG := $(FSPKG:%=$(FTPDIR)/%)


DOWNLOADS := \
	$(CSXCARCH) \
	$(LTIB_EVKARCH) \
	$(LTIB_UBUNTU_12_04_PATCH) \
	$(FSPKG_DL) \

DLMD5 := $(DOWNLOADS:%=%.$(MD5EXT))
DOWNLOADS := $(DOWNLOADS) $(DLMD5)
DOWNLOADS := $(DOWNLOADS:%=$(FTPDIR)/%)

DOWNLOADS := $(DOWNLOADS)


UTILS = \
	apt-get \
	sudo \

PACKAGES = \
	bison \
	ccache \
	coreutils \
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
	patch \
	perl \
	qemu \
	rpm \
	sed \
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
	zlib-bin \
	zlibc \


.PHONY: all
all: env downloads ltib projects image

# Set up the build environment.
.PHONY: env
env:
	@for p in $(UTILS); do which $$p; done
	if test -d $(LTIBDIR); then \
		echo "*** Error: Destination directory $(LTIBDIR) exists, will not overwrite."; \
		echo "Hint: To continue an interupted installation try running LTIB directly:"; \
		echo "          cd $(LTIBDIR); ./ltib"; \
		echo "Aborting."; \
		exit 1; \
	fi
	-sudo apt-get update
	sudo apt-get install $(PACKAGES)

# Initial downloads (toolchain, LTIB, LTIB patches, spec files patches, ...)
.PHONY: downloads
downloads: $(FTPDIR) downloads_fc $(DOWNLOADS)

$(FTPDIR):
	test -d $@

# Remove the existing MD5s to force the download of the changed archives (if any).
.PHONY: downloads_fc
downloads_fc:
	for f in "" $(DOWNLOADS); do \
	    test -z "$$f" && continue; \
	    rm -f $$f.$(MD5EXT); \
	done; exit 0		# Don't break the build if the download list is empty.

# Install and build LTIB.
.PHONY: ltib
ltib: ltibinst ltibpatch ltibbuild

.PHONY: ltibinst
ltibinst: $(TMPDIR) downloads
	rm -rf $(TMPDIR)/$(LTIB_EVKDIR)
	tar xzvf $(FTPDIR)/$(LTIB_EVKARCH) -C $(TMPDIR)
	cd $(TMPDIR)/$(LTIB_EVKDIR); patch -p1 < $(FTPDIR)/$(LTIBINST_TARGETDIR_PATHCH)
	-test -n "$(FSPKG)" && cp -pv $(FSPKG) $(TMPDIR)/$(LTIB_EVKDIR)/pkgs
	cd $(TMPDIR)/$(LTIB_EVKDIR); (echo -e "qy\nyes" ) | ./install
	rm -rf $(TMPDIR)/$(LTIB_EVKDIR)

$(TMPDIR):
	rm -rf $(TMPDIR)
	mkdir -p $(TMPDIR)

.PHONY: ltibpatch
ltibpatch: downloads
	test -d $(LTIBDIR)
	cd $(LTIBDIR); cp $(FTPDIR)/$(LTIB_UBUNTU_12_04_PATCH) .
	cd $(LTIBDIR); cp $(FTPDIR)/$(LTIB_UBUNTU_12_04_PATCH_INCLUDE_SYS_PATCH) .
	cd $(LTIBDIR); patch -p1 < $(FTPDIR)/$(LTIB_UBUNTU_URL_PATHCH)
	cd $(LTIBDIR); patch -p1 < $(FTPDIR)/$(LTIB_UBUNTU_INCLUDE_SYS_PATHCH)
	cd $(LTIBDIR); sh ./$(LTIB_UBUNTU_12_04_PATCH) $(FTPURL)
	cd $(LTIBDIR); rm -f $(LTIB_UBUNTU_12_04_PATCH) $(LTIB_UBUNTU_12_04_PATCH_INCLUDE_SYS_PATCH)
	rm -rf $(LTIBDIR_REF)
	mkdir -p $(LTIBDIR_REF)
	rsync -a $(LTIBDIR)/config $(LTIBDIR)/dist $(LTIBDIR)/bin $(LTIBDIR)/ltib $(LTIBDIR_REF)/
	cd $(LTIBDIR); for p in \
		$(LTIB_MECT_CONFIG_PATCH) \
		$(LTIB_MECT_PPP_PATCH) \
		$(LTIB_MECT_SPECS_PATCH) \
		$(LTIB_MECT_BIN_PATCH) \
	; do \
		patch -p1 < $(FTPDIR)/$$p; \
	done

.PHONY: ltibbuild
ltibbuild: hosttools
	sudo rm -rf $(FSDIR)/rootfs
	sudo mkdir -p $(FSDIR)/rootfs
	sudo chown -R $(USER).$(shell groups | awk '{print $$1}') $(FSDIR)
	sed -i "s,^%ldirs$$,\0\n$(FTPDIR)\n$(CSXCDIR)/arm-none-linux-gnueabi/libc/usr/bin," $(LTIBDIR)/.ltibrc
	cd $(LTIBDIR); PATH=/usr/lib/ccache:$$PATH GIT_AUTHOR_NAME=$(USER_NAME) GIT_AUTHOR_EMAIL=$(TARGET_UNIX_NAME)@$(HOST_NAME) GIT_COMMITTER_NAME=$(USER_NAME) GIT_COMMITTER_EMAIL=$(TARGET_UNIX_NAME)@$(HOST_NAME) ./ltib

# Set up the host tools.
.PHONY: hosttools
hosttools: downloads toolchain qt

# Set up the toolchain.
.PHONY: toolchain
toolchain:
	sudo rm -rf $(CSXCUNPACK) $(CSXCDIR)
	tar xjvf $(FTPDIR)/$(CSXCARCH)
	sudo mv $(CSXCUNPACK) $(CSXCDIR)
	test -d /usr/lib/ccache
	for f in arm-none-linux-gnueabi-gcc arm-none-linux-gnueabi-c++ arm-none-linux-gnueabi-g++; do \
	       	sudo ln -sf $(CSXCDIR)/bin/$$f /usr/lib/ccache/; \
	done

# Set up host Qt.
.PHONY: qt
qt:
	mkdir -p /tmp/rpm-$(USER) $(LTIBDIR)/rpm/SOURCES
	for f in $(FSPKG); do cp $$f $(LTIBDIR)/rpm/SOURCES; done
	PATH=/usr/lib/ccache:$(CSXCDIR)/bin:$(PATH) MAKEFLAGS=-j`grep -c ^processor /proc/cpuinfo` rpmbuild --define 'toolchain 1' --define 'toolchain_install_dir $(QT_INSTALL_DIR)' --define '_topdir $(LTIBDIR)/rpm' --dbpath /tmp/rpm-$(USER)/rpmdb --target arm --define '_target_cpu arm' --define '_prefix /opt' --define '_rpmdir /tmp/rpm-$(USER)/RPMS' -bb --clean --rmsource $(LTIBDIR)/dist/lfs-5.1/qt/qt-embedded.spec
	-sudo rpm --force-debian --root / --dbpath /tmp/rpm-$(USER)/rpmdb -e --allmatches --nodeps --define '_tmppath $(LTIBDIR)/tmp' qt-embedded 2>/dev/null
	sudo rpm --force-debian --root / --dbpath /tmp/rpm-$(USER)/rpmdb --ignorearch -ivh --force --nodeps --excludedocs --define '_tmppath $(LTIBDIR)/tmp' /tmp/rpm-$(USER)/RPMS/$(TARGET_ARCH)/qt-embedded-$(QT_VERSION)-*.$(TARGET_ARCH).rpm
	sudo chown -R $(USER).$(shell groups | awk '{print $$1}') /tmp/rpm-$(USER)


# Build the local projects.
.PHONY: projects
projects:
	$(MAKE) -C projects RELEASE=$(BUILD_RELEASE) clean all

# Build the default target image.
.PHONY: image
image: $(DEFAULT_IMAGE)


# Rules to build target root file systems
#

# Generate all manufacturing images.

.PHONY: images
images: TPAC1006_IP112_320x240 TPAC1006_IP118_320x240 TPAC1006_320x240 TPAC1006_IP119_640x480 TPAC1006_640x480 TPAC1007_IP113_480x272 TPAC1007_IP114_480x272 TPAC1007_480x272 TPAC1008_IP208_800x600 TPAC1008_800x600

# Target TPAC 1006, 320x240, IP 192.168.5.112

TPAC1006_IP112_320x240%: SUFFIX := tpac_1006_320x240
TPAC1006_IP112_320x240%: TGTDIR := $(IMGDIR)/TPAC1006_IP112_320x240_r$(BUILD_RELEASE)
TPAC1006_IP112_320x240%: MFGDIR = $(TGTDIR)/$(shell basename $(TGTDIR) | sed 's/\./_/g')
TPAC1006_IP112_320x240%: MFGZIP = $(MFGDIR)/../$(shell basename $(MFGDIR)).zip
TPAC1006_IP112_320x240%: BOOTDIR = $(TGTDIR)/boot
TPAC1006_IP112_320x240%: RFSDIR = $(TGTDIR)/rootfs
TPAC1006_IP112_320x240%: LFSDIR = $(TGTDIR)/localfs
TPAC1006_IP112_320x240%: KERNELRPM = $(subst /kernel-,/kernel-$(SUFFIX)-,$(LTIB_KERNEL_RPM))
TPAC1006_IP112_320x240%: KERNEL_TARGET_CONF := kernel-2.6.35-imx28-tpac1006_320x240.config

.PHONY: TPAC1006_IP112_320x240
TPAC1006_IP112_320x240: TPAC1006_IP112_320x240_mfg

.PHONY: TPAC1006_IP112_320x240_boot
TPAC1006_IP112_320x240_boot:
	$(MAKE) BOOTDIR='$(BOOTDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' target_boot

.PHONY: TPAC1006_IP112_320x240_rfs
TPAC1006_IP112_320x240_rfs:
	$(MAKE) BUILD_TARGET='$(BUILD_TARGET_TPAC1006_320x240)' RFSDIR='$(RFSDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' RFSDIR='$(RFSDIR)' target_rfs

.PHONY: TPAC1006_IP112_320x240_lfs
TPAC1006_IP112_320x240_lfs:
	$(MAKE) LFSDIR='$(LFSDIR)' target_lfs

.PHONY: TPAC1006_IP112_320x240_config
TPAC1006_IP112_320x240_config:
	test -n '$(LFSDIR)'
	sudo sed -i '/^\s*\bIPADDR0\b\s*=/ s/=.*/=192.168.5.112/;'  $(LFSDIR)/flash/etc/sysconfig/net.conf
	sudo sed -i '/^\s*\bMAC0\b\s*=/ s/=.*/=00:11:22:22:51:70/;' $(LFSDIR)/flash/etc/sysconfig/net.conf

.PHONY: TPAC1006_IP112_320x240_mfg
TPAC1006_IP112_320x240_mfg: TPAC1006_IP112_320x240_boot TPAC1006_IP112_320x240_rfs TPAC1006_IP112_320x240_lfs TPAC1006_IP112_320x240_config
	$(MAKE) MFGDIR='$(MFGDIR)' RFSDIR='$(RFSDIR)' LFSDIR='$(LFSDIR)' TGTDIR='$(TGTDIR)' BOOTDIR='$(BOOTDIR)' MFGZIP='$(MFGZIP)' target_mfg

.PHONY: TPAC1006_IP112_320x240_win
TPAC1006_IP112_320x240_win: TGTTMPDIR = $(TGTDIR)/tmp
TPAC1006_IP112_320x240_win: TPAC1006_IP112_320x240_rfs
	$(MAKE) TGTTMPDIR='$(TGTTMPDIR)' TGTDIR='$(TGTDIR)' target_win

# Target TPAC 1006, 320x240, IP 192.168.5.118

TPAC1006_IP118_320x240%: SUFFIX := tpac_1006_320x240
TPAC1006_IP118_320x240%: TGTDIR := $(IMGDIR)/TPAC1006_IP118_320x240_r$(BUILD_RELEASE)
TPAC1006_IP118_320x240%: MFGDIR = $(TGTDIR)/$(shell basename $(TGTDIR) | sed 's/\./_/g')
TPAC1006_IP118_320x240%: MFGZIP = $(MFGDIR)/../$(shell basename $(MFGDIR)).zip
TPAC1006_IP118_320x240%: BOOTDIR = $(TGTDIR)/boot
TPAC1006_IP118_320x240%: RFSDIR = $(TGTDIR)/rootfs
TPAC1006_IP118_320x240%: LFSDIR = $(TGTDIR)/localfs
TPAC1006_IP118_320x240%: KERNELRPM = $(subst /kernel-,/kernel-$(SUFFIX)-,$(LTIB_KERNEL_RPM))
TPAC1006_IP118_320x240%: KERNEL_TARGET_CONF := kernel-2.6.35-imx28-tpac1006_320x240.config

.PHONY: TPAC1006_IP118_320x240
TPAC1006_IP118_320x240: TPAC1006_IP118_320x240_mfg

.PHONY: TPAC1006_IP118_320x240_boot
TPAC1006_IP118_320x240_boot:
	$(MAKE) BOOTDIR='$(BOOTDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' target_boot

.PHONY: TPAC1006_IP118_320x240_rfs
TPAC1006_IP118_320x240_rfs:
	$(MAKE) BUILD_TARGET='$(BUILD_TARGET_TPAC1006_320x240)' RFSDIR='$(RFSDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' RFSDIR='$(RFSDIR)' target_rfs

.PHONY: TPAC1006_IP118_320x240_lfs
TPAC1006_IP118_320x240_lfs:
	$(MAKE) LFSDIR='$(LFSDIR)' target_lfs

.PHONY: TPAC1006_IP118_320x240_config
TPAC1006_IP118_320x240_config:
	test -n '$(LFSDIR)'
	sudo sed -i '/^\s*\bIPADDR0\b\s*=/ s/=.*/=192.168.5.118/;'  $(LFSDIR)/flash/etc/sysconfig/net.conf
	sudo sed -i '/^\s*\bMAC0\b\s*=/ s/=.*/=00:11:22:22:51:76/;' $(LFSDIR)/flash/etc/sysconfig/net.conf

.PHONY: TPAC1006_IP118_320x240_mfg
TPAC1006_IP118_320x240_mfg: TPAC1006_IP118_320x240_boot TPAC1006_IP118_320x240_rfs TPAC1006_IP118_320x240_lfs TPAC1006_IP118_320x240_config
	$(MAKE) MFGDIR='$(MFGDIR)' RFSDIR='$(RFSDIR)' LFSDIR='$(LFSDIR)' TGTDIR='$(TGTDIR)' BOOTDIR='$(BOOTDIR)' MFGZIP='$(MFGZIP)' target_mfg

.PHONY: TPAC1006_IP118_320x240_win
TPAC1006_IP118_320x240_win: TGTTMPDIR = $(TGTDIR)/tmp
TPAC1006_IP118_320x240_win: TPAC1006_IP118_320x240_rfs
	$(MAKE) TGTTMPDIR='$(TGTTMPDIR)' TGTDIR='$(TGTDIR)' target_win

# Target TPAC 1006, 320x240

TPAC1006_320x240%: SUFFIX := tpac_1006_320x240
TPAC1006_320x240%: TGTDIR := $(IMGDIR)/TPAC1006_320x240_r$(BUILD_RELEASE)
TPAC1006_320x240%: MFGDIR = $(TGTDIR)/$(shell basename $(TGTDIR) | sed 's/\./_/g')
TPAC1006_320x240%: MFGZIP = $(MFGDIR)/../$(shell basename $(MFGDIR)).zip
TPAC1006_320x240%: BOOTDIR = $(TGTDIR)/boot
TPAC1006_320x240%: RFSDIR = $(TGTDIR)/rootfs
TPAC1006_320x240%: LFSDIR = $(TGTDIR)/localfs
TPAC1006_320x240%: KERNELRPM = $(subst /kernel-,/kernel-$(SUFFIX)-,$(LTIB_KERNEL_RPM))
TPAC1006_320x240%: KERNEL_TARGET_CONF := kernel-2.6.35-imx28-tpac1006_320x240.config

.PHONY: TPAC1006_320x240
TPAC1006_320x240: TPAC1006_320x240_mfg

.PHONY: TPAC1006_320x240_boot
TPAC1006_320x240_boot:
	$(MAKE) BOOTDIR='$(BOOTDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' target_boot

.PHONY: TPAC1006_320x240_rfs
TPAC1006_320x240_rfs:
	$(MAKE) BUILD_TARGET='$(BUILD_TARGET_TPAC1006_320x240)' RFSDIR='$(RFSDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' RFSDIR='$(RFSDIR)' target_rfs

.PHONY: TPAC1006_320x240_lfs
TPAC1006_320x240_lfs:
	$(MAKE) LFSDIR='$(LFSDIR)' target_lfs

.PHONY: TPAC1006_320x240_mfg
TPAC1006_320x240_mfg: TPAC1006_320x240_boot TPAC1006_320x240_rfs TPAC1006_320x240_lfs
	$(MAKE) MFGDIR='$(MFGDIR)' RFSDIR='$(RFSDIR)' LFSDIR='$(LFSDIR)' TGTDIR='$(TGTDIR)' BOOTDIR='$(BOOTDIR)' MFGZIP='$(MFGZIP)' target_mfg

.PHONY: TPAC1006_320x240_win
TPAC1006_320x240_win: TGTTMPDIR = $(TGTDIR)/tmp
TPAC1006_320x240_win: TPAC1006_320x240_rfs
	$(MAKE) TGTTMPDIR='$(TGTTMPDIR)' TGTDIR='$(TGTDIR)' target_win

# Target TPAC 1006, 640x480, IP 192.168.5.119

TPAC1006_IP119_640x480%: SUFFIX := tpac_1006_640x480
TPAC1006_IP119_640x480%: TGTDIR := $(IMGDIR)/TPAC1006_IP119_640x480_r$(BUILD_RELEASE)
TPAC1006_IP119_640x480%: MFGDIR = $(TGTDIR)/$(shell basename $(TGTDIR) | sed 's/\./_/g')
TPAC1006_IP119_640x480%: MFGZIP = $(MFGDIR)/../$(shell basename $(MFGDIR)).zip
TPAC1006_IP119_640x480%: BOOTDIR = $(TGTDIR)/boot
TPAC1006_IP119_640x480%: RFSDIR = $(TGTDIR)/rootfs
TPAC1006_IP119_640x480%: LFSDIR = $(TGTDIR)/localfs
TPAC1006_IP119_640x480%: KERNELRPM = $(subst /kernel-,/kernel-$(SUFFIX)-,$(LTIB_KERNEL_RPM))
TPAC1006_IP119_640x480%: KERNEL_TARGET_CONF := kernel-2.6.35-imx28-tpac1006_640x480.config

.PHONY: TPAC1006_IP119_640x480
TPAC1006_IP119_640x480: TPAC1006_IP119_640x480_mfg

.PHONY: TPAC1006_IP119_640x480_boot
TPAC1006_IP119_640x480_boot:
	$(MAKE) BOOTDIR='$(BOOTDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' target_boot

.PHONY: TPAC1006_IP119_640x480_rfs
TPAC1006_IP119_640x480_rfs:
	$(MAKE) BUILD_TARGET='$(BUILD_TARGET_TPAC1006_640x480)' RFSDIR='$(RFSDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' RFSDIR='$(RFSDIR)' target_rfs

.PHONY: TPAC1006_IP119_640x480_lfs
TPAC1006_IP119_640x480_lfs:
	$(MAKE) LFSDIR='$(LFSDIR)' target_lfs

.PHONY: TPAC1006_IP119_640x480_config
TPAC1006_IP119_640x480_config:
	test -n '$(LFSDIR)'
	sudo sed -i '/^\s*\bIPADDR0\b\s*=/ s/=.*/=192.168.5.119/;'  $(LFSDIR)/flash/etc/sysconfig/net.conf
	sudo sed -i '/^\s*\bMAC0\b\s*=/ s/=.*/=00:11:22:22:51:77/;' $(LFSDIR)/flash/etc/sysconfig/net.conf

.PHONY: TPAC1006_IP119_640x480_mfg
TPAC1006_IP119_640x480_mfg: TPAC1006_IP119_640x480_boot TPAC1006_IP119_640x480_rfs TPAC1006_IP119_640x480_lfs TPAC1006_IP119_640x480_config
	$(MAKE) MFGDIR='$(MFGDIR)' RFSDIR='$(RFSDIR)' LFSDIR='$(LFSDIR)' TGTDIR='$(TGTDIR)' BOOTDIR='$(BOOTDIR)' MFGZIP='$(MFGZIP)' target_mfg

.PHONY: TPAC1006_IP119_640x480_win
TPAC1006_IP119_640x480_win: TGTTMPDIR = $(TGTDIR)/tmp
TPAC1006_IP119_640x480_win: TPAC1006_640x480_rfs
	$(MAKE) TGTTMPDIR='$(TGTTMPDIR)' TGTDIR='$(TGTDIR)' target_win

# Target TPAC 1006, 640x480

TPAC1006_640x480%: SUFFIX := tpac_1006_640x480
TPAC1006_640x480%: TGTDIR := $(IMGDIR)/TPAC1006_640x480_r$(BUILD_RELEASE)
TPAC1006_640x480%: MFGDIR = $(TGTDIR)/$(shell basename $(TGTDIR) | sed 's/\./_/g')
TPAC1006_640x480%: MFGZIP = $(MFGDIR)/../$(shell basename $(MFGDIR)).zip
TPAC1006_640x480%: BOOTDIR = $(TGTDIR)/boot
TPAC1006_640x480%: RFSDIR = $(TGTDIR)/rootfs
TPAC1006_640x480%: LFSDIR = $(TGTDIR)/localfs
TPAC1006_640x480%: KERNELRPM = $(subst /kernel-,/kernel-$(SUFFIX)-,$(LTIB_KERNEL_RPM))
TPAC1006_640x480%: KERNEL_TARGET_CONF := kernel-2.6.35-imx28-tpac1006_640x480.config

.PHONY: TPAC1006_640x480
TPAC1006_640x480: TPAC1006_640x480_mfg

.PHONY: TPAC1006_640x480_boot
TPAC1006_640x480_boot:
	$(MAKE) BOOTDIR='$(BOOTDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' target_boot

.PHONY: TPAC1006_640x480_rfs
TPAC1006_640x480_rfs:
	$(MAKE) BUILD_TARGET='$(BUILD_TARGET_TPAC1006_640x480)' RFSDIR='$(RFSDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' RFSDIR='$(RFSDIR)' target_rfs

.PHONY: TPAC1006_640x480_lfs
TPAC1006_640x480_lfs:
	$(MAKE) LFSDIR='$(LFSDIR)' target_lfs

.PHONY: TPAC1006_640x480_mfg
TPAC1006_640x480_mfg: TPAC1006_640x480_boot TPAC1006_640x480_rfs TPAC1006_640x480_lfs
	$(MAKE) MFGDIR='$(MFGDIR)' RFSDIR='$(RFSDIR)' LFSDIR='$(LFSDIR)' TGTDIR='$(TGTDIR)' BOOTDIR='$(BOOTDIR)' MFGZIP='$(MFGZIP)' target_mfg

.PHONY: TPAC1006_640x480_win
TPAC1006_640x480_win: TGTTMPDIR = $(TGTDIR)/tmp
TPAC1006_640x480_win: TPAC1006_640x480_rfs
	$(MAKE) TGTTMPDIR='$(TGTTMPDIR)' TGTDIR='$(TGTDIR)' target_win

# Target TPAC 1007, 480x272 pixels, IP 192.168.5.113

TPAC1007_IP113_480x272%: SUFFIX := tpac_1007_480x272
TPAC1007_IP113_480x272%: TGTDIR := $(IMGDIR)/TPAC1007_IP113_480x272_r$(BUILD_RELEASE)
TPAC1007_IP113_480x272%: MFGDIR = $(TGTDIR)/$(shell basename $(TGTDIR) | sed 's/\./_/g')
TPAC1007_IP113_480x272%: MFGZIP = $(MFGDIR)/../$(shell basename $(MFGDIR)).zip
TPAC1007_IP113_480x272%: BOOTDIR = $(TGTDIR)/boot
TPAC1007_IP113_480x272%: RFSDIR = $(TGTDIR)/rootfs
TPAC1007_IP113_480x272%: LFSDIR = $(TGTDIR)/localfs
TPAC1007_IP113_480x272%: KERNELRPM = $(subst /kernel-,/kernel-$(SUFFIX)-,$(LTIB_KERNEL_RPM))
TPAC1007_IP113_480x272%: KERNEL_TARGET_CONF := kernel-2.6.35-imx28-tpac1007_480x272.config

.PHONY: TPAC1007_IP113_480x272
TPAC1007_IP113_480x272: TPAC1007_IP113_480x272_mfg

.PHONY: TPAC1007_IP113_480x272_boot
TPAC1007_IP113_480x272_boot:
	$(MAKE) BOOTDIR='$(BOOTDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' target_boot

.PHONY: TPAC1007_IP113_480x272_rfs
TPAC1007_IP113_480x272_rfs:
	$(MAKE) BUILD_TARGET='$(BUILD_TARGET_TPAC1007_480x272)' RFSDIR='$(RFSDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' RFSDIR='$(RFSDIR)' target_rfs

.PHONY: TPAC1007_IP113_480x272_lfs
TPAC1007_IP113_480x272_lfs:
	$(MAKE) LFSDIR='$(LFSDIR)' target_lfs

.PHONY: TPAC1007_IP113_480x272_config
TPAC1007_IP113_480x272_config:
	test -n '$(LFSDIR)'
	sudo sed -i '/^\s*\bIPADDR0\b\s*=/ s/=.*/=192.168.5.113/;'  $(LFSDIR)/flash/etc/sysconfig/net.conf
	sudo sed -i '/^\s*\bMAC0\b\s*=/ s/=.*/=00:11:22:22:51:71/;' $(LFSDIR)/flash/etc/sysconfig/net.conf

.PHONY: TPAC1007_IP113_480x272_mfg
TPAC1007_IP113_480x272_mfg: TPAC1007_IP113_480x272_boot TPAC1007_IP113_480x272_rfs TPAC1007_IP113_480x272_lfs TPAC1007_IP113_480x272_config
	$(MAKE) MFGDIR='$(MFGDIR)' RFSDIR='$(RFSDIR)' LFSDIR='$(LFSDIR)' TGTDIR='$(TGTDIR)' BOOTDIR='$(BOOTDIR)' MFGZIP='$(MFGZIP)' target_mfg

.PHONY: TPAC1007_IP113_480x272_win
TPAC1007_IP113_480x272_win: TGTTMPDIR = $(TGTDIR)/tmp
TPAC1007_IP113_480x272_win: TPAC1007_IP113_480x272_rfs
	$(MAKE) TGTTMPDIR='$(TGTTMPDIR)' TGTDIR='$(TGTDIR)' target_win

# Target TPAC 1007, 480x272 pixels, IP 192.168.5.114

TPAC1007_IP114_480x272%: SUFFIX := tpac_1007_480x272
TPAC1007_IP114_480x272%: TGTDIR := $(IMGDIR)/TPAC1007_IP114_480x272_r$(BUILD_RELEASE)
TPAC1007_IP114_480x272%: MFGDIR = $(TGTDIR)/$(shell basename $(TGTDIR) | sed 's/\./_/g')
TPAC1007_IP114_480x272%: MFGZIP = $(MFGDIR)/../$(shell basename $(MFGDIR)).zip
TPAC1007_IP114_480x272%: BOOTDIR = $(TGTDIR)/boot
TPAC1007_IP114_480x272%: RFSDIR = $(TGTDIR)/rootfs
TPAC1007_IP114_480x272%: LFSDIR = $(TGTDIR)/localfs
TPAC1007_IP114_480x272%: KERNELRPM = $(subst /kernel-,/kernel-$(SUFFIX)-,$(LTIB_KERNEL_RPM))
TPAC1007_IP114_480x272%: KERNEL_TARGET_CONF := kernel-2.6.35-imx28-tpac1007_480x272.config

.PHONY: TPAC1007_IP114_480x272
TPAC1007_IP114_480x272: TPAC1007_IP114_480x272_mfg

.PHONY: TPAC1007_IP114_480x272_boot
TPAC1007_IP114_480x272_boot:
	$(MAKE) BOOTDIR='$(BOOTDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' target_boot

.PHONY: TPAC1007_IP114_480x272_rfs
TPAC1007_IP114_480x272_rfs:
	$(MAKE) BUILD_TARGET='$(BUILD_TARGET_TPAC1007_480x272)' RFSDIR='$(RFSDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' RFSDIR='$(RFSDIR)' target_rfs

.PHONY: TPAC1007_IP114_480x272_lfs
TPAC1007_IP114_480x272_lfs:
	$(MAKE) LFSDIR='$(LFSDIR)' target_lfs

.PHONY: TPAC1007_IP114_480x272_config
TPAC1007_IP114_480x272_config:
	test -n '$(LFSDIR)'
	sudo sed -i '/^\s*\bIPADDR0\b\s*=/ s/=.*/=192.168.5.114/;'  $(LFSDIR)/flash/etc/sysconfig/net.conf
	sudo sed -i '/^\s*\bMAC0\b\s*=/ s/=.*/=00:11:22:22:51:72/;' $(LFSDIR)/flash/etc/sysconfig/net.conf

.PHONY: TPAC1007_IP114_480x272_mfg
TPAC1007_IP114_480x272_mfg: TPAC1007_IP114_480x272_boot TPAC1007_IP114_480x272_rfs TPAC1007_IP114_480x272_lfs TPAC1007_IP114_480x272_config
	$(MAKE) MFGDIR='$(MFGDIR)' RFSDIR='$(RFSDIR)' LFSDIR='$(LFSDIR)' TGTDIR='$(TGTDIR)' BOOTDIR='$(BOOTDIR)' MFGZIP='$(MFGZIP)' target_mfg

.PHONY: TPAC1007_IP114_480x272_win
TPAC1007_IP114_480x272_win: TGTTMPDIR = $(TGTDIR)/tmp
TPAC1007_IP114_480x272_win: TPAC1007_IP114_480x272_rfs
	$(MAKE) TGTTMPDIR='$(TGTTMPDIR)' TGTDIR='$(TGTDIR)' target_win

# Target TPAC 1007, 480x272 pixels, IP 192.168.5.120

TPAC1007_IP120_480x272%: SUFFIX := tpac_1007_480x272
TPAC1007_IP120_480x272%: TGTDIR := $(IMGDIR)/TPAC1007_IP120_480x272_r$(BUILD_RELEASE)
TPAC1007_IP120_480x272%: MFGDIR = $(TGTDIR)/$(shell basename $(TGTDIR) | sed 's/\./_/g')
TPAC1007_IP120_480x272%: MFGZIP = $(MFGDIR)/../$(shell basename $(MFGDIR)).zip
TPAC1007_IP120_480x272%: BOOTDIR = $(TGTDIR)/boot
TPAC1007_IP120_480x272%: RFSDIR = $(TGTDIR)/rootfs
TPAC1007_IP120_480x272%: LFSDIR = $(TGTDIR)/localfs
TPAC1007_IP120_480x272%: KERNELRPM = $(subst /kernel-,/kernel-$(SUFFIX)-,$(LTIB_KERNEL_RPM))
TPAC1007_IP120_480x272%: KERNEL_TARGET_CONF := kernel-2.6.35-imx28-tpac1007_480x272.config

.PHONY: TPAC1007_IP120_480x272
TPAC1007_IP120_480x272: TPAC1007_IP120_480x272_mfg

.PHONY: TPAC1007_IP120_480x272_boot
TPAC1007_IP120_480x272_boot:
	$(MAKE) BOOTDIR='$(BOOTDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' target_boot

.PHONY: TPAC1007_IP120_480x272_rfs
TPAC1007_IP120_480x272_rfs:
	$(MAKE) BUILD_TARGET='$(BUILD_TARGET_TPAC1007_480x272)' RFSDIR='$(RFSDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' RFSDIR='$(RFSDIR)' target_rfs

.PHONY: TPAC1007_IP120_480x272_lfs
TPAC1007_IP120_480x272_lfs:
	$(MAKE) LFSDIR='$(LFSDIR)' target_lfs

.PHONY: TPAC1007_IP120_480x272_config
TPAC1007_IP120_480x272_config:
	test -n '$(LFSDIR)'
	sudo sed -i '/^\s*\bIPADDR0\b\s*=/ s/=.*/=192.168.5.120/;'  $(LFSDIR)/flash/etc/sysconfig/net.conf
	sudo sed -i '/^\s*\bMAC0\b\s*=/ s/=.*/=00:11:22:22:51:78/;' $(LFSDIR)/flash/etc/sysconfig/net.conf

.PHONY: TPAC1007_IP120_480x272_mfg
TPAC1007_IP120_480x272_mfg: TPAC1007_IP120_480x272_boot TPAC1007_IP120_480x272_rfs TPAC1007_IP120_480x272_lfs TPAC1007_IP120_480x272_config
	$(MAKE) MFGDIR='$(MFGDIR)' RFSDIR='$(RFSDIR)' LFSDIR='$(LFSDIR)' TGTDIR='$(TGTDIR)' BOOTDIR='$(BOOTDIR)' MFGZIP='$(MFGZIP)' target_mfg

.PHONY: TPAC1007_IP120_480x272_win
TPAC1007_IP120_480x272_win: TGTTMPDIR = $(TGTDIR)/tmp
TPAC1007_IP120_480x272_win: TPAC1007_IP120_480x272_rfs
	$(MAKE) TGTTMPDIR='$(TGTTMPDIR)' TGTDIR='$(TGTDIR)' target_win

# Target TPAC 1007, 480x272

TPAC1007_480x272%: SUFFIX := tpac_1007_480x272
TPAC1007_480x272%: TGTDIR := $(IMGDIR)/TPAC1007_480x272_r$(BUILD_RELEASE)
TPAC1007_480x272%: MFGDIR = $(TGTDIR)/$(shell basename $(TGTDIR) | sed 's/\./_/g')
TPAC1007_480x272%: MFGZIP = $(MFGDIR)/../$(shell basename $(MFGDIR)).zip
TPAC1007_480x272%: BOOTDIR = $(TGTDIR)/boot
TPAC1007_480x272%: RFSDIR = $(TGTDIR)/rootfs
TPAC1007_480x272%: LFSDIR = $(TGTDIR)/localfs
TPAC1007_480x272%: KERNELRPM = $(subst /kernel-,/kernel-$(SUFFIX)-,$(LTIB_KERNEL_RPM))
TPAC1007_480x272%: KERNEL_TARGET_CONF := kernel-2.6.35-imx28-tpac1007_480x272.config

.PHONY: TPAC1007_480x272
TPAC1007_480x272: TPAC1007_480x272_mfg

.PHONY: TPAC1007_480x272_boot
TPAC1007_480x272_boot:
	$(MAKE) BOOTDIR='$(BOOTDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' target_boot

.PHONY: TPAC1007_480x272_rfs
TPAC1007_480x272_rfs:
	$(MAKE) BUILD_TARGET='$(BUILD_TARGET_TPAC1007_480x272)' RFSDIR='$(RFSDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' RFSDIR='$(RFSDIR)' target_rfs

.PHONY: TPAC1007_480x272_lfs
TPAC1007_480x272_lfs:
	$(MAKE) LFSDIR='$(LFSDIR)' target_lfs

.PHONY: TPAC1007_480x272_mfg
TPAC1007_480x272_mfg: TPAC1007_480x272_boot TPAC1007_480x272_rfs TPAC1007_480x272_lfs
	$(MAKE) MFGDIR='$(MFGDIR)' RFSDIR='$(RFSDIR)' LFSDIR='$(LFSDIR)' TGTDIR='$(TGTDIR)' BOOTDIR='$(BOOTDIR)' MFGZIP='$(MFGZIP)' target_mfg

.PHONY: TPAC1007_480x272_win
TPAC1007_480x272_win: TGTTMPDIR = $(TGTDIR)/tmp
TPAC1007_480x272_win: TPAC1007_480x272_rfs
	$(MAKE) TGTTMPDIR='$(TGTTMPDIR)' TGTDIR='$(TGTDIR)' target_win

# Target TPAC 1008, 800x600, IP 192.168.5.208

TPAC1008_IP208_800x600%: SUFFIX := tpac_1008_800x600
TPAC1008_IP208_800x600%: TGTDIR := $(IMGDIR)/TPAC1008_IP208_800x600_r$(BUILD_RELEASE)
TPAC1008_IP208_800x600%: MFGDIR = $(TGTDIR)/$(shell basename $(TGTDIR) | sed 's/\./_/g')
TPAC1008_IP208_800x600%: MFGZIP = $(MFGDIR)/../$(shell basename $(MFGDIR)).zip
TPAC1008_IP208_800x600%: BOOTDIR = $(TGTDIR)/boot
TPAC1008_IP208_800x600%: RFSDIR = $(TGTDIR)/rootfs
TPAC1008_IP208_800x600%: LFSDIR = $(TGTDIR)/localfs
TPAC1008_IP208_800x600%: KERNELRPM = $(subst /kernel-,/kernel-$(SUFFIX)-,$(LTIB_KERNEL_RPM))
TPAC1008_IP208_800x600%: KERNEL_TARGET_CONF := kernel-2.6.35-imx28-tpac1008_800x480.config

.PHONY: TPAC1008_IP208_800x600
TPAC1008_IP208_800x600: TPAC1008_IP208_800x600_mfg

.PHONY: TPAC1008_IP208_800x600_boot
TPAC1008_IP208_800x600_boot:
	$(MAKE) BOOTDIR='$(BOOTDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' target_boot

.PHONY: TPAC1008_IP208_800x600_rfs
TPAC1008_IP208_800x600_rfs:
	$(MAKE) BUILD_TARGET='$(BUILD_TARGET_TPAC1008_800x600)' RFSDIR='$(RFSDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' RFSDIR='$(RFSDIR)' target_rfs

.PHONY: TPAC1008_IP208_800x600_lfs
TPAC1008_IP208_800x600_lfs:
	$(MAKE) LFSDIR='$(LFSDIR)' target_lfs

.PHONY: TPAC1008_IP208_800x600_config
TPAC1008_IP208_800x600_config:
	test -n '$(LFSDIR)'
	sudo sed -i '/^\s*\bIPADDR0\b\s*=/ s/=.*/=192.168.5.208/;'  $(LFSDIR)/flash/etc/sysconfig/net.conf
	sudo sed -i '/^\s*\bMAC0\b\s*=/ s/=.*/=00:11:22:22:51:D0/;' $(LFSDIR)/flash/etc/sysconfig/net.conf

.PHONY: TPAC1008_IP208_800x600_mfg
TPAC1008_IP208_800x600_mfg: TPAC1008_IP208_800x600_boot TPAC1008_IP208_800x600_rfs TPAC1008_IP208_800x600_lfs TPAC1008_IP208_800x600_config
	$(MAKE) MFGDIR='$(MFGDIR)' RFSDIR='$(RFSDIR)' LFSDIR='$(LFSDIR)' TGTDIR='$(TGTDIR)' BOOTDIR='$(BOOTDIR)' MFGZIP='$(MFGZIP)' target_mfg

.PHONY: TPAC1008_IP208_800x600_win
TPAC1008_IP208_800x600_win: TGTTMPDIR = $(TGTDIR)/tmp
TPAC1008_IP208_800x600_win: TPAC1008_800x600_rfs
	$(MAKE) TGTTMPDIR='$(TGTTMPDIR)' TGTDIR='$(TGTDIR)' target_win

# Target TPAC 1008, 800x600

TPAC1008_800x600%: SUFFIX := tpac_1008_800x600
TPAC1008_800x600%: TGTDIR := $(IMGDIR)/TPAC1008_800x600_r$(BUILD_RELEASE)
TPAC1008_800x600%: MFGDIR = $(TGTDIR)/$(shell basename $(TGTDIR) | sed 's/\./_/g')
TPAC1008_800x600%: MFGZIP = $(MFGDIR)/../$(shell basename $(MFGDIR)).zip
TPAC1008_800x600%: BOOTDIR = $(TGTDIR)/boot
TPAC1008_800x600%: RFSDIR = $(TGTDIR)/rootfs
TPAC1008_800x600%: LFSDIR = $(TGTDIR)/localfs
TPAC1008_800x600%: KERNELRPM = $(subst /kernel-,/kernel-$(SUFFIX)-,$(LTIB_KERNEL_RPM))
TPAC1008_800x600%: KERNEL_TARGET_CONF := kernel-2.6.35-imx28-tpac1008_800x480.config

.PHONY: TPAC1008_800x600
TPAC1008_800x600: TPAC1008_800x600_mfg

.PHONY: TPAC1008_800x600_boot
TPAC1008_800x600_boot:
	$(MAKE) BOOTDIR='$(BOOTDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' target_boot

.PHONY: TPAC1008_800x600_rfs
TPAC1008_800x600_rfs:
	$(MAKE) BUILD_TARGET='$(BUILD_TARGET_TPAC1008_800x600)' RFSDIR='$(RFSDIR)' SUFFIX='$(SUFFIX)' KERNEL_TARGET_CONF='$(KERNEL_TARGET_CONF)' KERNELRPM='$(KERNELRPM)' RFSDIR='$(RFSDIR)' target_rfs

.PHONY: TPAC1008_800x600_lfs
TPAC1008_800x600_lfs:
	$(MAKE) LFSDIR='$(LFSDIR)' target_lfs

.PHONY: TPAC1008_800x600_mfg
TPAC1008_800x600_mfg: TPAC1008_800x600_boot TPAC1008_800x600_rfs TPAC1008_800x600_lfs
	$(MAKE) MFGDIR='$(MFGDIR)' RFSDIR='$(RFSDIR)' LFSDIR='$(LFSDIR)' TGTDIR='$(TGTDIR)' BOOTDIR='$(BOOTDIR)' MFGZIP='$(MFGZIP)' target_mfg

.PHONY: TPAC1008_800x600_win
TPAC1008_800x600_win: TGTTMPDIR = $(TGTDIR)/tmp
TPAC1008_800x600_win: TPAC1008_800x600_rfs
	$(MAKE) TGTTMPDIR='$(TGTTMPDIR)' TGTDIR='$(TGTDIR)' target_win

# Common target rules
#

# Build the target-specific kernel.
$(subst /kernel-,/kernel-$(SUFFIX)-,$(LTIB_KERNEL_RPM)): $(LTIB_KERNEL_TS_RPM)
	test -n "$(SUFFIX)" -a -n "$(KERNEL_TARGET_CONF)"
	touch -r $(LTIB_KERNEL_TS_RPM) /tmp/$(shell basename $(LTIB_KERNEL_TS_RPM).ltib-timestamp)
	rm -rf $(LTIBDIR)/rpm/BUILD/linux-*
	ln -sf $(KERNEL_TARGET_CONF) $(KERNEL_CONF)
	cd $(LTIBDIR); ./ltib -f -p kernel
	touch -r /tmp/$(shell basename $(LTIB_KERNEL_TS_RPM).ltib-timestamp) $(LTIB_KERNEL_TS_RPM); rm -f /tmp/$(shell basename $(LTIB_KERNEL_TS_RPM).ltib-timestamp)
	set -e; cd $(RPMDIR); for rpm in '' `ls kernel-*.$(TARGET_ARCH).rpm imx-bootlets-src-*.$(TARGET_ARCH).rpm 2>/dev/null | sed '/-tpac_/ d;'`; do \
		test -n "$$rpm" || continue; \
		mv $$rpm `echo $$rpm | sed 's/^kernel-/kernel-$(SUFFIX)-/; s/^imx-bootlets-src-/imx-bootlets-src-$(SUFFIX)-/;'`; \
	done

$(LTIB_KERNEL_TS_RPM):
	cd $(LTIBDIR); ./ltib -f -p $(LTIB_KERNEL_TS_NAME)

# Build the target-specific boot.
.PHONY: target_boot
target_boot: $(COMMON_RFSPKGS)
	test -n '$(BOOTDIR)' -a -n '$(SUFFIX)' -a -n '$(KERNEL_TARGET_CONF)' -a -n '$(KERNELRPM)' -a -n '$(FSDIR)' -a -n '$(RPMDIR)' -a -n '$(TARGET_ARCH)'
	$(MAKE) SUFFIX=$(SUFFIX) KERNEL_TARGET_CONF=$(KERNEL_TARGET_CONF) $(KERNELRPM)
	sudo rm -rf $(BOOTDIR)
	mkdir -p $(BOOTDIR)/var/lib/rpm
	sudo $(FSDIR)/ltib/usr/bin/rpm --nodeps --root $(BOOTDIR) --prefix / --define '_tmppath /tmp/ltib' --dbpath /var/lib/rpm --ignorearch -Uvh --excludedocs $(RPMDIR)/imx-bootlets-src-$(SUFFIX)-mfg-2.6.35.3-1.1.0.$(TARGET_ARCH).rpm
	sudo rm -f $(BOOTDIR)/var/lib/rpm/*
	sudo rmdir $(BOOTDIR)/var/lib/rpm
	sudo rmdir --ignore-fail-on-non-empty $(BOOTDIR)/var/lib
	sudo rmdir --ignore-fail-on-non-empty $(BOOTDIR)/var

# Build the target-specific root file system.
.PHONY: target_rfs
target_rfs: $(COMMON_RFSPKGS)
	test -n '$(BUILD_TARGET)' -a -n '$(RFSDIR)' -a -n '$(SUFFIX)' -a -n '$(KERNEL_TARGET_CONF)' -a -n '$(KERNELRPM)' -a -n '$(RFSDIR)' -a -n '$(FSDIR)' -a -n '$(COMMON_RFSPKGS)' -a -n '$(TARGET_RFSPKGS)' -a -n '$(CSXCDIR)' -a -n '$(RFS_VERSION_FILE)'
	$(MAKE) SUFFIX=$(SUFFIX) KERNEL_TARGET_CONF=$(KERNEL_TARGET_CONF) $(KERNELRPM)
	sudo rm -rf $(RFSDIR)
	mkdir -p $(RFSDIR)/var/lib/rpm $(RFSDIR)/tmp/ltib
	sudo $(FSDIR)/ltib/usr/bin/rpm --nodeps --root $(RFSDIR) --prefix / --define '_tmppath /tmp/ltib' --dbpath /var/lib/rpm --ignorearch -Uvh --excludedocs $(COMMON_RFSPKGS) $(subst /kernel-,/kernel-$(SUFFIX)-,$(TARGET_RFSPKGS))
	sudo rm -f $(RFSDIR)/var/lib/rpm/*
	sudo rmdir $(RFSDIR)/var/lib/rpm
	sudo rmdir --ignore-fail-on-non-empty $(RFSDIR)/var/lib
	sudo rmdir --ignore-fail-on-non-empty $(RFSDIR)/var
	sudo rmdir --ignore-fail-on-non-empty $(RFSDIR)/tmp/ltib
	sudo qemu-arm $(CSXCDIR)/arm-none-linux-gnueabi/libc/sbin/ldconfig -r $(RFSDIR)
	( \
		echo "Release: rel$(BUILD_RELEASE)"; \
		echo "Target:  $(BUILD_TARGET)"; \
		echo "Qt:      $(QT_VERSION)"; \
		echo "Qwt:     $(QWT_VERSION)" \
	) > $(RFSDIR)/$(RFS_VERSION_FILE)
	sudo du -sh --apparent-size $(RFSDIR)

# Build the target-specific local file system.
.PHONY: target_lfs
target_lfs: $(LFSPKGS)
	test -n '$(LFSDIR)' -a -n '$(FSDIR)' -a -n '$(LFSPKGS)'
	sudo rm -rf $(LFSDIR)
	mkdir -p $(LFSDIR)/var/lib/rpm $(LFSDIR)/tmp/ltib
	sudo $(FSDIR)/ltib/usr/bin/rpm --nodeps --root $(LFSDIR) --prefix / --define '_tmppath /tmp/ltib' --dbpath /var/lib/rpm --ignorearch -Uvh --excludedocs $(LFSPKGS)
	sudo rm -f $(LFSDIR)/var/lib/rpm/*
	sudo rmdir $(LFSDIR)/var/lib/rpm
	sudo rmdir --ignore-fail-on-non-empty $(LFSDIR)/var/lib
	sudo rmdir --ignore-fail-on-non-empty $(LFSDIR)/var
	sudo rmdir --ignore-fail-on-non-empty $(LFSDIR)/tmp/ltib
	sudo rmdir --ignore-fail-on-non-empty $(LFSDIR)/tmp
	sudo du -sh --apparent-size $(LFSDIR)

# Build the target-specific project for Freescale manufacturing tool.
.PHONY: target_mfg
target_mfg:
	test -n '$(MFGDIR)' -a -n '$(FTPDIR)' -a -n '$(RFSDIR)' -a -n '$(LFSDIR)' -a -n '$(TGTDIR)' -a -n '$(BOOTDIR)' -a -n '$(MFGZIP)'
	sudo rm -rf $(MFGDIR)
	mkdir -p $(MFGDIR)/'OS firmware'/img $(MFGDIR)/'OS firmware'/sys
	sed "s/@@PLAYER@@/$(shell basename $(MFGDIR))/" $(FTPDIR)/player.ini > $(MFGDIR)/player.ini
	install -m 644 $(FTPDIR)/fdisk-u.input $(MFGDIR)/'OS firmware'/sys/fdisk-u.input
	install -m 644 $(FTPDIR)/ucl.xml $(MFGDIR)/'OS firmware'/ucl.xml
	sudo tar cf $(MFGDIR)/'OS firmware'/img/rootfs.tar -C $(RFSDIR) .
	sudo tar cf $(MFGDIR)/'OS firmware'/img/localfs.tar -C $(LFSDIR) .
	sudo tar cjf $(TGTDIR)/local.tar.bz2 -C $(LFSDIR) .
	install -m 644 $(BOOTDIR)/boot/imx28_ivt_linux.sb $(MFGDIR)/'OS firmware'/img
	install -m 644 $(BOOTDIR)/boot/updater_ivt.sb $(MFGDIR)/'OS firmware'/sys
	sudo rm -f $(MFGZIP)
	cd $(MFGDIR); sudo zip -0r $(MFGZIP) *

# Build the archive for target-specific development on Windows.
.PHONY: target_win
target_win:
	test -n '$(TGTTMPDIR)' -a -n '$(LTIBDIR)' -a -n '$(TGTDIR)'
	sudo rm -rf $(TGTTMPDIR)
	-for d in /usr/include /usr/lib /lib /usr/src/linux/include; do \
		mkdir -p $(TGTTMPDIR)/rootfs$$d; \
		sudo rsync -aL $(LTIBDIR)/rootfs$$d $(TGTTMPDIR)/rootfs$$d; \
	done
	cd $(TGTTMPDIR); sudo zip -qr $(TGTDIR)/rootfs_rsync-L.zip rootfs
	sudo rm -rf $(TGTTMPDIR)

.PHONY: images_check
images_check:
	sudo diff -r --brief images-all-golden images-all 2>&1 | grep -v 'No such file or directory' > images_check.diff
	diff -u images_check-golden.diff images_check.diff && echo "Images OK."

# Handle the patches for LTIB configuration and spec files.
# 

# Create new patches from the current installation.

.PHONY: ltib_genpatch
ltib_genpatch: ltib_genpatch_config ltib_genpatch_specs ltib_genpatch_bin

.PHONY: ltib_genpatch_config
ltib_genpatch_config: $(LTIBDIR_REF)/config
	cd $(LTIBDIR)/.. && { diff -urN --exclude=*.bak --exclude=*.swp $(shell basename $(LTIBDIR_REF))/config $(shell basename $(LTIBDIR))/config; diff -uN $(shell basename $(LTIBDIR_REF))/.config $(shell basename $(LTIBDIR))/.config; diff -uN $(shell basename $(LTIBDIR_REF))/.config.cmd $(shell basename $(LTIBDIR))/.config.cmd; diff -uN $(shell basename $(LTIBDIR_REF))/.tmpconfig.h $(shell basename $(LTIBDIR))/.tmpconfig.h; } > $(FTPDIR)/$(LTIB_MECT_CONFIG_PATCH); true
	cd $(FTPDIR); md5sum $(LTIB_MECT_CONFIG_PATCH) > $(LTIB_MECT_CONFIG_PATCH).$(MD5EXT)

.PHONY: ltib_genpatch_specs
ltib_genpatch_specs: $(LTIBDIR_REF)/dist
	cd $(LTIBDIR)/.. && diff -urN --exclude=*-orig.spec --exclude=*.bak --exclude=*.swp $(shell basename $(LTIBDIR_REF))/dist $(shell basename $(LTIBDIR))/dist > $(FTPDIR)/$(LTIB_MECT_SPECS_PATCH); true
	cd $(FTPDIR); md5sum $(LTIB_MECT_SPECS_PATCH) > $(LTIB_MECT_SPECS_PATCH).$(MD5EXT)

.PHONY: ltib_genpatch_bin
ltib_genpatch_bin: $(LTIBDIR_REF)/bin
	cd $(LTIBDIR)/.. && { diff -urN --exclude=*.bak --exclude=*.swp $(shell basename $(LTIBDIR_REF))/bin $(shell basename $(LTIBDIR))/bin; diff -uN $(shell basename $(LTIBDIR_REF))/ltib $(shell basename $(LTIBDIR))/ltib; } > $(FTPDIR)/$(LTIB_MECT_BIN_PATCH); true
	cd $(FTPDIR); md5sum $(LTIB_MECT_BIN_PATCH) > $(LTIB_MECT_BIN_PATCH).$(MD5EXT)

# Update an existing LTIB installation from repository.

.PHONY: ltib_update
ltib_update:
	git pull
	if ! test -d $(LTIBDIR_REF); then \
		mv $(LTIBDIR) $(LTIBDIR).precious; \
		$(MAKE) ltibinst ltibpatch; \
		rm -rf $(LTIBDIR); \
		mv $(LTIBDIR).precious $(LTIBDIR); \
	fi
	rm -rf $(LTIBDIR_PATCH)
	rsync -a $(LTIBDIR_REF)/ $(LTIBDIR_PATCH)/
	cd $(LTIBDIR_PATCH); patch -p1 < $(FTPDIR)/$(LTIB_MECT_CONFIG_PATCH)
	cd $(LTIBDIR_PATCH); patch -p1 < $(FTPDIR)/$(LTIB_MECT_SPECS_PATCH)
	cd $(LTIBDIR_PATCH); patch -p1 < $(FTPDIR)/$(LTIB_MECT_BIN_PATCH)
	rsync -a --delete $(LTIBDIR_PATCH)/config/ $(LTIBDIR)/config/
	rsync -a --delete $(LTIBDIR_PATCH)/dist/ $(LTIBDIR)/dist/
	rsync -a --delete $(LTIBDIR_PATCH)/bin/ $(LTIBDIR)/bin/
	cp $(LTIBDIR_PATCH)/.config $(LTIBDIR)/.config
	cp $(LTIBDIR_PATCH)/.config.cmd $(LTIBDIR)/.config.cmd
	cp $(LTIBDIR_PATCH)/.tmpconfig.h $(LTIBDIR)/.tmpconfig.h
	cp -a $(LTIBDIR_PATCH)/ltib $(LTIBDIR)/ltib
	rm -rf $(LTIBDIR_PATCH)


# Utilities
#

.PHONY: clean
clean: clean_projects
	sudo rm -rf $(LTIBDIR) $(TMPDIR) $(CSXCUNPACK) $(CSXCDIR) $(FSDIR)/ltib $(FSDIR)/pkgs $(FSDIR)/rootfs $(TMPRPMDIR) $(QT_INSTALL_DIR)
	sudo rmdir --ignore-fail-on-non-empty $(FSDIR)

.PHONY: clean_projects
clean_projects:
	$(MAKE) -C projects RELEASE=$(BUILD_RELEASE) clean

.PHONY: distclean
distclean: clean
	sudo rm -rf $(IMGDIR)


# Downloads
#
# NOTE: Here we assume that each file to download has an MD5
# checksum named <file_name>.$(MD5EXT) in the same directory.
#

# Generic download rule for MECT site
$(FTPDIR)/%: $(FTPDIR)/%.$(MD5EXT)
	dir=$(shell dirname $@); mkdir -p $$dir; cd $$dir; md5sum -c $@.$(MD5EXT) 2>/dev/null || { rm -f $@; wget -O $@ --progress=dot:mega "$(FTPURL)/$(shell basename $@)"; md5sum -c $@.$(MD5EXT); }

$(FTPDIR)/%.$(MD5EXT):
	mkdir -p $(shell dirname $@)
	wget -O $@ "$(FTPURL)/$(shell basename $@)"
	touch -c $@			# Force the re-check of the downloaded file, if any.
	$(MAKE) $(@:%.$(MD5EXT)=%)	# Re-check the downloaded file, if any.


# Specific download rules from non-MECT sites
$(FTPDIR)/$(LTIB_UBUNTU_12_04_PATCH): $(FTPDIR)/$(LTIB_UBUNTU_12_04_PATCH).$(MD5EXT)
	dir=$(shell dirname $@); mkdir -p $$dir; cd $$dir; md5sum -c $@.$(MD5EXT) 2>/dev/null || { rm -f $@; wget -O $@ --progress=dot:mega --no-check-certificate "$(URL_LTIB_UBUNTU_12_04_PATCH)"; md5sum -c $@.$(MD5EXT); }

$(FTPDIR)/$(LTIB_UBUNTU_12_04_PATCH).$(MD5EXT):
	mkdir -p $(shell dirname $@)
	wget -O $@ "$(FTPURL)/$(shell basename $@)"
	touch -c $@			# Force the re-check of the downloaded file, if any.
	$(MAKE) $(@:%.$(MD5EXT)=%)	# Re-check the downloaded file, if any.

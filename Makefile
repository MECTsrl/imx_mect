# Build version information.
BUILD_RELEASE = 6.6rc0
BUILD_TARGET = TPAC1007_480x272
BUILD_QTVERSION = $(QT_VERSION)
BUILD_QWTVERSION = $(QWT_VERSION)
# Name of the root file system version file
RFS_VERSION_FILE = rootfs_version

# UNIX name of the target platform
TARGET_UNIX_NAME = imx28

# Developer info for git
USER_NAME = "Embedded developer"
HOST_NAME = "development.localdomain"

# Download the archives here.
FTPDIR = $(CURDIR)/src
# LTIB is installed here.
LTIBDIR = $(CURDIR)/ltib
# LTIB rootfs is created here.
LTIB_RFSDIR = $(LTIBDIR)/rootfs
# LTIB specs are installed here.
LTIBSPECDIR = $(LTIBDIR)/dist/lfs-5.1
# Unpack the archives here.
TMPDIR = $(CURDIR)/tmp
# Archive repository
FTPURL = http://www.mect.it/archive
# Hardcoded Freescale directory
FSDIR = /opt/freescale
# LPP location
LPPDIR = $(FSDIR)/pkgs
# RPM archive
RPMDIR = $(CURDIR)/ltib/rpm/RPMS/arm
# Root file system top-level directory
IMGDIR = $(CURDIR)/images-all
# Draft directory for rpmbuild
TMPRPMDIR = /tmp/rpm-$(USER)


# Extension of the MD5 checksums for the downloads.
MD5EXT = md5


# Package list for creating the root file system for various targets.
#

RFSPKGS_TPAC1007_480x272 := \
	base_libs-rfs-1.2-1.arm.rpm \
	boa-rfs-0.94.14rc21-1.arm.rpm \
	busybox-rfs-1.15.0-1.arm.rpm \
	cantest-rfs-1.0-1.arm.rpm \
	dhcp-rfs-3.0.3b1-1.arm.rpm \
	dropbear-rfs-0.52-1.arm.rpm \
	e2fsprogs-rfs-1.41.4-1.arm.rpm \
	expat-rfs-1.95.8-1.arm.rpm \
	fontconfig-rfs-2.4.2-1.arm.rpm \
	freetype-rfs-2.3.9-1.arm.rpm \
	glib2-rfs-2.18.1-1.arm.rpm \
	hotplug-rfs-2004_03_29-3.arm.rpm \
	imx-bootlets-src-rfs-2.6.35.3-1.1.0.arm.rpm \
	iproute-rfs-2.6.37-050330.arm.rpm \
	kernel-rfs-2.6.35.3-imx_1.1.0.arm.rpm \
	libsocketcan-rfs-0.0.8-0.arm.rpm \
	libtermcap-rfs-2.0.8-31_1.arm.rpm \
	libusb-rfs-0.1.8-1.arm.rpm \
	lzo-rfs-2.03-0.arm.rpm \
	merge-rfs-0.1-1.arm.rpm \
	modeps-rfs-1.0-1.arm.rpm \
	mtd-utils-rfs-201006-1.arm.rpm \
	mysql-rfs-4.1.12-0.arm.rpm \
	ncurses-rfs-5.3-1.arm.rpm \
	ppp-rfs-2.4.4-1.arm.rpm \
	qt-embedded-rfs-4.8.5-1.arm.rpm \
	qwt-rfs-6.1.0-1.arm.rpm \
	rsync-rfs-2.6.5-1.arm.rpm \
	sftp-server-rfs-4.3p2-1.arm.rpm \
	skell-rfs-1.18-2.arm.rpm \
	sqlite-rfs-3.6.12-1.arm.rpm \
	sysconfig-rfs-1.2-5.arm.rpm \
	tslib-rfs-1.0-3.arm.rpm \
	udev-rfs-117-5.arm.rpm \
	xenomai-rfs-2.6.0-1.arm.rpm \
	zip-rfs-3.0.0-0.arm.rpm \
	zlib-rfs-1.2.3-2.arm.rpm \
	#bzip2-rfs-1.0.2-2.arm.rpm \
	#unzip-rfs-5.52-1.arm.rpm \

RFSPKGS_TPAC1007_480x272 := $(RFSPKGS_TPAC1007_480x272:%=$(RPMDIR)/%)

LFSPKGS_TPAC1007_480x272 := \
	skell-lfs-1.18-2.arm.rpm \
	local-1.0-1_$(BUILD_RELEASE).arm.rpm \
	local-ATCMControl_runtime_system-1.0-1_$(BUILD_RELEASE).arm.rpm \
	local-cgic_work-1.0-1_$(BUILD_RELEASE).arm.rpm \
	local-factory_data-1.0-1_$(BUILD_RELEASE).arm.rpm \
	local-setup_time-1.0-1_$(BUILD_RELEASE).arm.rpm \
	local-splash-1.0-1_$(BUILD_RELEASE).arm.rpm \

LFSPKGS_TPAC1007_480x272 := $(LFSPKGS_TPAC1007_480x272:%=$(RPMDIR)/%)


# Definition of the sources
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

# LTIB set configuration (MECT patch)
LTIB_CONFIG_PATCH = ltib-config.patch

# LTIB fix deprecated warning and missing zlib (MECT patch)
LTIB_DEPR_AND_ZLIB_PATCH = ltib-deprecated+zlib.patch

# LTIB change wget options for download and log (MECT patch)
LTIB_WGET_OPTIONS_PATCH = ltib-wget-retry.patch

# LTIB rpm-fs spec file (MECT patch)
LTIB_RPM_FS_SPEC_PATCH = rpm-fs-mect-spec.patch

# LTIB bison spec file (MECT patch)
LTIB_BISON_SPEC_PATCH = bison-mect-spec.patch

# LTIB texinfo spec file (MECT patch)
LTIB_TEXINFO_SPEC_PATCH = texinfo-mect-spec.patch

# LTIB pkgconfig spec file (MECT patch)
LTIB_PKGCONFIG_SPEC_PATCH = pkgconfig-mect-spec.patch

# LTIB git spec file (MECT patch)
LTIB_GIT_SPEC_PATCH = git-mect-spec.patch

# LTIB fix u-boot build (MECT patch)
LTIB_U_BOOT_SPEC_PATCH = u-boot-spec-patch-link-fix-1418123257.patch
LTIB_U_BOOT_TEMPLATE_SPEC_PATCH = u-boot-2.6.35_1.1.0-spec-template-mect.patch

# LTIB fix configuration merge into root file system (MECT patch)
LTIB_MERGE_PATCH = merge-mect-spec.patch

# LTIB fix kernel spec to include MECT changes and Xenomai (MECT patch)
LTIB_KERNEL_SPEC_PATCH = kernel-2.6.35-spec-mect-xenomai.patch
LTIB_KERNEL_TEMPLATE_SPEC_PATCH = kernel-2.6.35-spec-template-mect.patch

# LTIB set MECT PPP (MECT patch)
LTIB_MECT_PPP_PATCH = ltib-mect-ppp-url.patch

# LTIB Ubuntu 12.04 patch bundle
LTIB_UBUNTU_12_04_PATCH = patch-ltib-ubuntu12.04.sh
URL_LTIB_UBUNTU_12_04_PATCH = $(FTPURL)/$(LTIB_UBUNTU_12_04_PATCH)

# LTIB Ubuntu 12.04 patch bundle fix /usr/include/sys for i386 architectures (MECT patch)
LTIB_UBUNTU_12_04_PATCH_INCLUDE_SYS_PATCH = ubuntu-ltib-patch-include-sys-i386.patch

# LTIB include patch elftosb-missing-lm.patch in elftosb spec file (MECT patch)
LTIB_ELFTOSB_SPEC_PATCH = elftosb-spec-patch1.patch

# SFTP server
LTIB_SFTP_SERVER_SPEC_PATCH = sftp-server-mect-spec.patch

# libsocketcan
LTIB_LIBSOCKETCAN_SPEC_PATCH = libsocketcan-mect-spec.patch

# qwt
QWT_VERSION = 6.1.0
LTIB_QWT_SPEC_PATCH = qwt-mect-6.1.0-spec.patch

# LTIB fix boot_stream spec (MECT patch)
LTIB_BOOT_STREAM_SPEC_PATCH = boot_stream-mect-spec.patch

# LTIB MECT patch to fix linking of base_libs
LTIB_BASE_LIBS_SPEC_PATCH = base_libs-mect-spec.patch

# LTIB boa spec file (MECT patch)
LTIB_BOA_SPEC_PATCH = boa-mect-spec.patch

# LTIB qt spec file (MECT patch)
QT_INSTALL_DIR = /opt/Trolltech
QT_VERSION = 4.8.5
LTIB_QT_SPEC_PATCH = qt-embedded-mect-4.8.5-spec.patch
LTIB_QT_ARCH = qt-everywhere-opensource-src-4.8.5.tar.gz
LTIB_QT_PATCH1 = qt-everywhere-opensource-src-4.8.5-1394522957.patch
LTIB_QT_PATCH2 = qt-everywhere-opensource-src-4.8.5-1420823826.patch
LTIB_QT_PATCH3 = qt-everywhere-opensource-src-4.8.5-1420823825.patch

# LTIB iproute spec file (MECT patch)
LTIB_IPROUTE_SPEC_PATCH = iproute-mect-spec.patch

# LTIB skell spec file (MECT patch)
LTIB_SKELL_SPEC_PATCH = skell-mect-spec.patch

# LTIB sysconfig spec file (MECT patch)
LTIB_SYSCONFIG_SPEC_PATCH = sysconfig-mx-mect-spec.patch

# LTIB xenomai spec file (MECT patch)
LTIB_XENOMAI_SPEC_PATCH = xenomai-mect-spec.patch

# LTIB zip30 spec file (MECT patch)
LTIB_ZIP30_SPEC_PATCH = zip30-mect-spec.patch

# LTIB busybox spec file (MECT patch)
LTIB_BUSYBOX_SPEC_PATCH = busybox-mect-spec.patch

# LTIB bzip2 spec file (MECT patch)
LTIB_BZIP2_SPEC_PATCH = bzip2-mect-spec.patch

# LTIB cantest spec file (MECT patch)
LTIB_CANTEST_SPEC_PATCH = cantest-mect-spec.patch

# LTIB dhcp spec file (MECT patch)
LTIB_DHCP_SPEC_PATCH = dhcp-mect-spec.patch

# LTIB dropbear spec file (MECT patch)
LTIB_DROPBEAR_SPEC_PATCH = dropbear-mect-spec.patch

# LTIB e2fsprogs spec file (MECT patch)
LTIB_E2FSPROGS_SPEC_PATCH = e2fsprogs-mect-spec.patch

# LTIB expat spec file (MECT patch)
LTIB_EXPAT_SPEC_PATCH = expat-mect-spec.patch

# LTIB fake-provides spec file (MECT patch)
LTIB_FAKE_SPEC_PATCH = fake-provides-mect-spec.patch

# LTIB fontconfig spec file (MECT patch)
LTIB_FONTCONFIG_SPEC_PATCH = fontconfig-mect-spec.patch

# LTIB freetype spec file (MECT patch)
LTIB_FREETYPE_SPEC_PATCH = freetype-mect-spec.patch

# LTIB glib2 spec file (MECT patch)
LTIB_GLIB2_SPEC_PATCH = glib2-mect-spec.patch

# LTIB hotplug spec file (MECT patch)
LTIB_HOTPLUG_SPEC_PATCH = hotplug-mect-spec.patch

# LTIB imx spec file (MECT patch)
LTIB_IMX_SPEC_PATCH = imx-test-mect-spec.patch

# LTIB libtermcap spec file (MECT patch)
LTIB_LIBTERMCAP_SPEC_PATCH = libtermcap-mect-spec.patch

# LTIB libusb spec file (MECT patch)
LTIB_LIBUSB_SPEC_PATCH = libusb-mect-spec.patch

# LTIB lzo spec file (MECT patch)
LTIB_LZO_SPEC_PATCH = lzo-mect-spec.patch

# LTIB modeps spec file (MECT patch)
LTIB_MODEPS_SPEC_PATCH = modeps-mect-spec.patch

# LTIB mtd spec file (MECT patch)
LTIB_MTD_SPEC_PATCH = mtd-utils-mect-spec.patch

# LTIB mysql spec file (MECT patch)
LTIB_MYSQL_SPEC_PATCH = mysql-mect-spec.patch

# LTIB ncurses spec file (MECT patch)
LTIB_NCURSES_SPEC_PATCH = ncurses-mect-spec.patch

# LTIB ppp spec file (MECT patch)
LTIB_PPP_SPEC_PATCH = ppp-mect-spec.patch

# LTIB rsync spec file (MECT patch)
LTIB_RSYNC_SPEC_PATCH = rsync-mect-spec.patch

# LTIB sqlite spec file (MECT patch)
LTIB_SQLITE_SPEC_PATCH = sqlite-mect-spec.patch

# LTIB tslib spec file (MECT patch)
LTIB_TSLIB_SPEC_PATCH = tslib-mect-spec.patch

# LTIB udev spec file (MECT patch)
LTIB_UDEV_SPEC_PATCH = udev-mect-spec.patch

# LTIB unzip spec file (MECT patch)
LTIB_UNZIP_SPEC_PATCH = unzip-mect-spec.patch

# LTIB zlib spec file (MECT patch)
LTIB_ZLIB_SPEC_PATCH = zlib-mect-spec.patch


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
all: env downloads ltib projects

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
	cd $(LTIBDIR); for p in \
			$(LTIB_CONFIG_PATCH) \
			$(LTIB_DEPR_AND_ZLIB_PATCH) \
			$(LTIB_WGET_OPTIONS_PATCH) \
			$(LTIB_U_BOOT_SPEC_PATCH) \
			$(LTIB_RPM_FS_SPEC_PATCH) \
			$(LTIB_BISON_SPEC_PATCH) \
			$(LTIB_TEXINFO_SPEC_PATCH) \
			$(LTIB_PKGCONFIG_SPEC_PATCH) \
			$(LTIB_GIT_SPEC_PATCH) \
			$(LTIB_U_BOOT_TEMPLATE_SPEC_PATCH) \
			$(LTIB_MERGE_PATCH) \
			$(LTIB_KERNEL_SPEC_PATCH) \
			$(LTIB_KERNEL_TEMPLATE_SPEC_PATCH) \
			$(LTIB_MECT_PPP_PATCH) \
			$(LTIB_ELFTOSB_SPEC_PATCH) \
			$(LTIB_SFTP_SERVER_SPEC_PATCH) \
			$(LTIB_LIBSOCKETCAN_SPEC_PATCH) \
			$(LTIB_QWT_SPEC_PATCH) \
			$(LTIB_BOOT_STREAM_SPEC_PATCH) \
			$(LTIB_BASE_LIBS_SPEC_PATCH) \
			$(LTIB_BOA_SPEC_PATCH) \
			$(LTIB_QT_SPEC_PATCH) \
			$(LTIB_IPROUTE_SPEC_PATCH) \
			$(LTIB_SKELL_SPEC_PATCH) \
			$(LTIB_SYSCONFIG_SPEC_PATCH) \
			$(LTIB_XENOMAI_SPEC_PATCH) \
			$(LTIB_ZIP30_SPEC_PATCH) \
			$(LTIB_BUSYBOX_SPEC_PATCH) \
			$(LTIB_BZIP2_SPEC_PATCH) \
			$(LTIB_CANTEST_SPEC_PATCH) \
			$(LTIB_DHCP_SPEC_PATCH) \
			$(LTIB_DROPBEAR_SPEC_PATCH) \
			$(LTIB_E2FSPROGS_SPEC_PATCH) \
			$(LTIB_EXPAT_SPEC_PATCH) \
			$(LTIB_FAKE_SPEC_PATCH) \
			$(LTIB_FONTCONFIG_SPEC_PATCH) \
			$(LTIB_FREETYPE_SPEC_PATCH) \
			$(LTIB_GLIB2_SPEC_PATCH) \
			$(LTIB_HOTPLUG_SPEC_PATCH) \
			$(LTIB_IMX_SPEC_PATCH) \
			$(LTIB_LIBTERMCAP_SPEC_PATCH) \
			$(LTIB_LIBUSB_SPEC_PATCH) \
			$(LTIB_LZO_SPEC_PATCH) \
			$(LTIB_MODEPS_SPEC_PATCH) \
			$(LTIB_MTD_SPEC_PATCH) \
			$(LTIB_MYSQL_SPEC_PATCH) \
			$(LTIB_NCURSES_SPEC_PATCH) \
			$(LTIB_PPP_SPEC_PATCH) \
			$(LTIB_RSYNC_SPEC_PATCH) \
			$(LTIB_SQLITE_SPEC_PATCH) \
			$(LTIB_TSLIB_SPEC_PATCH) \
			$(LTIB_UDEV_SPEC_PATCH) \
			$(LTIB_UNZIP_SPEC_PATCH) \
			$(LTIB_ZLIB_SPEC_PATCH) \
	; do \
		patch -p1 < $(FTPDIR)/$$p; \
	done

.PHONY: ltibbuild
ltibbuild: hosttools
	sudo rm -rf $(FSDIR)/rootfs
	sudo mkdir -p $(FSDIR)/rootfs
	sudo chown -R $(USER).$(shell groups | awk '{print $$1}') $(FSDIR)
	sed -i "s,^%ldirs$$,\0\n$(FTPDIR)," $(LTIBDIR)/.ltibrc
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
	sudo rpm --force-debian --root / --dbpath /tmp/rpm-$(USER)/rpmdb --ignorearch -ivh --force --nodeps --excludedocs --define '_tmppath $(LTIBDIR)/tmp' /tmp/rpm-$(USER)/RPMS/arm/qt-embedded-$(QT_VERSION)-*.arm.rpm
	sudo chown -R $(USER).$(shell groups | awk '{print $$1}') /tmp/rpm-$(USER)


# Build the local projects.
.PHONY: projects
projects:
	make -C projects RELEASE=$(BUILD_RELEASE) clean all


# Rules to build target root file systems
#

TPAC1007_480x272%: TGTDIR := $(IMGDIR)/TPAC1007_480x272_r$(BUILD_RELEASE)
TPAC1007_480x272%: TGT_RPMDIR = $(TGTDIR)/rpm
TPAC1007_480x272%: MFGDIR = $(TGTDIR)/$(shell basename $(TGTDIR) | sed 's/\./_/g')
TPAC1007_480x272%: MFGZIP = $(MFGDIR)/../$(shell basename $(MFGDIR)).zip
TPAC1007_480x272%: BOOTDIR = $(TGTDIR)/boot
TPAC1007_480x272%: RFSDIR = $(TGTDIR)/rootfs
TPAC1007_480x272%: LFSDIR = $(TGTDIR)/localfs

.PHONY: TPAC1007_480x272
TPAC1007_480x272: TPAC1007_480x272_boot TPAC1007_480x272_rfs TPAC1007_480x272_lfs TPAC1007_480x272_mfg TPAC1007_480x272_win

.PHONY: TPAC1007_480x272_boot
TPAC1007_480x272_boot: $(RFSPKGS_TPAC1007_480x272)
	test -n '$(BOOTDIR)'
	sudo rm -rf $(BOOTDIR)
	mkdir -p $(BOOTDIR)/var/lib/rpm
	sudo $(FSDIR)/ltib/usr/bin/rpm --nodeps --root $(BOOTDIR) --prefix / --define '_tmppath /tmp/ltib' --dbpath /var/lib/rpm --ignorearch -Uvh --excludedocs $(RPMDIR)/imx-bootlets-src-mfg-2.6.35.3-1.1.0.arm.rpm
	rm -f $(BOOTDIR)/var/lib/rpm/*
	-rmdir $(BOOTDIR)/var/lib/rpm
	-rmdir $(BOOTDIR)/var/lib
	-rmdir $(BOOTDIR)/var
	-rmdir $(BOOTDIR)/tmp/ltib
	-rmdir $(BOOTDIR)/tmp

.PHONY: TPAC1007_480x272_rfs
TPAC1007_480x272_rfs: $(RFSPKGS_TPAC1007_480x272)
	test -n '$(RFSDIR)'
	sudo rm -rf $(RFSDIR)
	mkdir -p $(RFSDIR)/var/lib/rpm $(RFSDIR)/tmp/ltib
	sudo $(FSDIR)/ltib/usr/bin/rpm --nodeps --root $(RFSDIR) --prefix / --define '_tmppath /tmp/ltib' --dbpath /var/lib/rpm --ignorearch -Uvh --excludedocs $(RFSPKGS_TPAC1007_480x272)
	rm -f $(RFSDIR)/var/lib/rpm/*
	-rmdir $(RFSDIR)/var/lib/rpm
	-rmdir $(RFSDIR)/var/lib
	-rmdir $(RFSDIR)/var
	-rmdir $(RFSDIR)/tmp/ltib
	cd $(RFSDIR); sudo ldconfig -r `pwd`
	( \
		echo "Release: rel$(BUILD_RELEASE)"; \
		echo "Target:  $(BUILD_TARGET)"; \
		echo "Qt:      $(QT_VERSION)"; \
		echo "Qwt:     $(QWT_VERSION)" \
	) > $(RFSDIR)/$(RFS_VERSION_FILE)
	#sudo install -D -p $(CSXCDIR)/arm-none-linux-gnueabi/libc/usr/bin/gdbserver $(RFSDIR)/usr/bin/gdbserver
	du -sh --apparent-size $(RFSDIR)

.PHONY: TPAC1007_480x272_lfs
TPAC1007_480x272_lfs: $(LFSPKGS_TPAC1007_480x272)
	test -n '$(LFSDIR)'
	sudo rm -rf $(LFSDIR)
	mkdir -p $(LFSDIR)/var/lib/rpm $(LFSDIR)/tmp/ltib
	sudo $(FSDIR)/ltib/usr/bin/rpm --nodeps --root $(LFSDIR) --prefix / --define '_tmppath /tmp/ltib' --dbpath /var/lib/rpm --ignorearch -Uvh --excludedocs $(LFSPKGS_TPAC1007_480x272)
	rm -f $(LFSDIR)/var/lib/rpm/*
	-rmdir $(LFSDIR)/var/lib/rpm
	-rmdir $(LFSDIR)/var/lib
	-rmdir $(LFSDIR)/var
	-rmdir $(LFSDIR)/tmp/ltib
	-rmdir $(LFSDIR)/tmp
	du -sh --apparent-size $(LFSDIR)

.PHONY: TPAC1007_480x272_mfg
TPAC1007_480x272_mfg: TPAC1007_480x272_boot TPAC1007_480x272_rfs TPAC1007_480x272_lfs
	test -n '$(MFGDIR)' -a -n '$(RFSDIR)' -a -n '$(LFSDIR)' -a -n '$(BOOTDIR)' -a -n '$(MFGDIR)' -a -n '$(MFGZIP)'
	mkdir -p $(MFGDIR)/'OS firmware'/img $(MFGDIR)/'OS firmware'/sys
	sed "s/@@PLAYER@@/$(shell basename $(MFGDIR))/" $(FTPDIR)/player.ini > $(MFGDIR)/player.ini
	install -m 644 $(FTPDIR)/fdisk-u.input $(MFGDIR)/'OS firmware'/sys/fdisk-u.input
	install -m 644 $(FTPDIR)/ucl.xml $(MFGDIR)/'OS firmware'/ucl.xml
	BZIP2=-1 tar cjf $(MFGDIR)/'OS firmware'/img/rootfs.tar.bz2 -C $(RFSDIR) .
	BZIP2=-1 tar cjf $(MFGDIR)/'OS firmware'/img/localfs.tar.bz2 -C $(LFSDIR) .
	install -m 644 $(BOOTDIR)/boot/imx28_ivt_linux.sb $(MFGDIR)/'OS firmware'/img
	install -m 644 $(BOOTDIR)/boot/updater_ivt.sb $(MFGDIR)/'OS firmware'/sys
	rm -f $(MFGZIP)
	cd $(MFGDIR); zip -0r $(MFGZIP) *

.PHONY: TPAC1007_480x272_win
TPAC1007_480x272_win: TPAC1007_480x272_rfs
	-BZIP2=-1 tar cjhf $(TGTDIR)/rootfs_rsync-L.tar.bz2 --hard-dereference --transform=s/^rootfs/rootfs_rsync-L/ -C $(LTIBDIR) rootfs/usr/include rootfs/usr/lib rootfs/lib rootfs/usr/src/linux/include


.PHONY: clean
clean: clean_projects
	sudo rm -rf $(LTIBDIR) $(TMPDIR) $(CSXCUNPACK) $(CSXCDIR) $(FSDIR) $(TMPRPMDIR) $(QT_INSTALL_DIR)

.PHONY: clean_projects
clean_projects:
	make -C projects RELEASE=$(BUILD_RELEASE) clean

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
	touch -c $@		# Force the re-check of the downloaded file, if any.
	make $(@:%.$(MD5EXT)=%)	# Re-check the downloaded file, if any.

# Specific download rules from non-MECT sites
$(FTPDIR)/$(LTIB_UBUNTU_12_04_PATCH): $(FTPDIR)/$(LTIB_UBUNTU_12_04_PATCH).$(MD5EXT)
	dir=$(shell dirname $@); mkdir -p $$dir; cd $$dir; md5sum -c $@.$(MD5EXT) 2>/dev/null || { rm -f $@; wget -O $@ --progress=dot:mega --no-check-certificate "$(URL_LTIB_UBUNTU_12_04_PATCH)"; md5sum -c $@.$(MD5EXT); }

$(FTPDIR)/$(LTIB_UBUNTU_12_04_PATCH).$(MD5EXT):
	mkdir -p $(shell dirname $@)
	wget -O $@ "$(FTPURL)/$(shell basename $@)"
	touch -c $@		# Force the re-check of the downloaded file, if any.
	make $(@:%.$(MD5EXT)=%)	# Re-check the downloaded file, if any.

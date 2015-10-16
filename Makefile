# Build version information.
BUILD_RELEASE = rel5.3rc2
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
FTPDIR = $(CURDIR)/ftp
# LTIB is installed here.
LTIBDIR = $(CURDIR)/ltib
# LTIB rootfs is created here.
LTIB_RFS_DIR = $(LTIBDIR)/rootfs
# LTIB specs are installed here.
LTIBSPECDIR = $(LTIBDIR)/dist/lfs-5.1
# Unpack the archives here.
TMPDIR = $(CURDIR)/tmp
# Archive repository
FTPURL = http://www.mect.it/archive
# Hardcoded Freescale directory
FSDIR = /opt/freescale
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

RFSPKGS_TPAC_1007 := \
	base_libs-rfs-1.2-1.arm.rpm \
	boa-rfs-0.94.14rc21-1.arm.rpm \
	busybox-rfs-1.15.0-1.arm.rpm \
	bzip2-rfs-1.0.2-2.arm.rpm \
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
	unzip-rfs-5.52-1.arm.rpm \
	xenomai-rfs-2.6.0-1.arm.rpm \
	zip-rfs-3.0.0-0.arm.rpm \
	zlib-rfs-1.2.3-2.arm.rpm \

RFSPKGS_TPAC_1007 := $(RFSPKGS_TPAC_1007:%=$(RPMDIR)/%)


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

# LTIB rpm-fs spec file (MECT patch)
LTIB_RPM_FS_SPEC_PATCH = rpm-fs-mect-spec.patch

# LTIB bison spec file (MECT patch)
LTIB_BISON_SPEC_PATCH = bison-mect-spec.patch

# LTIB texinfo spec file (MECT patch)
LTIB_TEXINFO_SPEC_PATCH = texinfo-mect-spec.patch

# LTIB pkgconfig spec file (MECT patch)
LTIB_PKGCONFIG_SPEC_PATCH = pkgconfig-mect-spec.patch

# LTIB sparse spec file (MECT patch)
LTIB_SPARSE_SPEC_PATCH = sparse-mect-spec.patch

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
LTIB_QWT_SPEC_PATCH = qwt-mect-$(QWT_VERSION)-spec.patch

# LTIB fix boot_stream spec (MECT patch)
LTIB_BOOT_STREAM_SPEC_PATCH = boot_stream-mect-spec.patch

# LTIB MECT patch to fix linking of base_libs
LTIB_BASE_LIBS_SPEC_PATCH = base_libs-mect-spec.patch

# LTIB boa spec file (MECT patch)
LTIB_BOA_SPEC_PATCH = boa-mect-spec.patch

# LTIB qt spec file (MECT patch)
QT_INSTALL_DIR = /opt/Trolltech
QT_VERSION = 4.8.5
LTIB_QT_SPEC_PATCH = qt-embedded-mect-$(QT_VERSION)-spec.patch
LTIB_QT_ARCH = qt-everywhere-opensource-src-$(QT_VERSION).tar.gz
LTIB_QT_PATCH1 = qt-everywhere-opensource-src-$(QT_VERSION)-1394522957.patch
LTIB_QT_PATCH2 = qt-everywhere-opensource-src-$(QT_VERSION)-1420823826.patch
LTIB_QT_PATCH3 = qt-everywhere-opensource-src-$(QT_VERSION)-1420823825.patch

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

# MECT dropbear host key
MECT_DROPBEAR_HOST_KEY = dropbear_rsa_host_key
MECT_DROPBEAR_HOST_KEY_DIR = etc/dropbear


# Extra packages to copy in $(LTIBPKGDIR)
FSPKG := \
	$(LTIB_QT_ARCH) \
	$(LTIB_QT_PATCH1) \
	$(LTIB_QT_PATCH2) \
	$(LTIB_QT_PATCH3) \

FSPKGMD5 := $(FSPKG:%=%.$(MD5EXT))
FSPKG := $(FSPKG) $(FSPKGMD5)
FSPKG := $(FSPKG:%=$(FTPDIR)/%)

DOWNLOADS := \
	$(CSXCARCH) \
	$(LTIB_EVKARCH) \
	$(LTIBINST_TARGETDIR_PATHCH) \
	$(LTIB_UBUNTU_URL_PATHCH) \
	$(LTIB_UBUNTU_INCLUDE_SYS_PATHCH) \
	$(LTIB_CONFIG_PATCH) \
	$(LTIB_DEPR_AND_ZLIB_PATCH) \
	$(LTIB_RPM_FS_SPEC_PATCH) \
	$(LTIB_BISON_SPEC_PATCH) \
	$(LTIB_TEXINFO_SPEC_PATCH) \
	$(LTIB_PKGCONFIG_SPEC_PATCH) \
	$(LTIB_SPARSE_SPEC_PATCH) \
	$(LTIB_GIT_SPEC_PATCH) \
	$(LTIB_U_BOOT_SPEC_PATCH) \
	$(LTIB_U_BOOT_TEMPLATE_SPEC_PATCH) \
	$(LTIB_MERGE_PATCH) \
	$(LTIB_KERNEL_SPEC_PATCH) \
	$(LTIB_KERNEL_TEMPLATE_SPEC_PATCH) \
	$(LTIB_MECT_PPP_PATCH) \
	$(LTIB_UBUNTU_12_04_PATCH) \
	$(LTIB_UBUNTU_12_04_PATCH_INCLUDE_SYS_PATCH) \
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
	$(MECT_DROPBEAR_HOST_KEY) \

DLMD5 := $(DOWNLOADS:%=%.$(MD5EXT))
DOWNLOADS := $(DOWNLOADS) $(DLMD5)
DOWNLOADS := $(DOWNLOADS:%=$(FTPDIR)/%)

DOWNLOADS := $(DOWNLOADS) $(FSPKG)


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
	zlib1g \
	zlib1g-dev \
	zlib-bin \
	zlibc \


.PHONY: all
all: env downloads ltib

# Set up the build environment.
.PHONY: env
env:
	@for p in $(UTILS); do which $$p; done
	@sudo -kn which sudo > /dev/null 2>&1 || { echo "*** Error: user \"$$USER\" must be allowed to sudo without password."; exit 1; }
	if test -d $(LTIBDIR); then \
		echo "*** Error: Destination directory $(LTIBDIR) exists. Will not overwrite, aborting."; \
		exit 1; \
	fi
	-sudo apt-get -y update
	sudo apt-get install $(PACKAGES)

# Initial downloads (toolchain, LTIB, LTIB patches, spec files patches, ...)
.PHONY: downloads
downloads: $(FTPDIR) downloads_fc $(DOWNLOADS)

$(FTPDIR):
	mkdir -p $(FTPDIR)

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
			$(LTIB_U_BOOT_SPEC_PATCH) \
			$(LTIB_RPM_FS_SPEC_PATCH) \
			$(LTIB_BISON_SPEC_PATCH) \
			$(LTIB_TEXINFO_SPEC_PATCH) \
			$(LTIB_PKGCONFIG_SPEC_PATCH) \
			$(LTIB_SPARSE_SPEC_PATCH) \
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

# Rules to build target root file systems
#

.PHONY: tpac_1007
tpac_1007: tpac_1007_rfs tpac_1007_lfs

.PHONY: tpac_1007_rfs
tpac_1007_rfs: RFSDIR := tpac_1007/rootfs
tpac_1007_rfs: $(RFSPKGS_TPAC_1007)
	sudo rm -rf $(IMGDIR)/$(RFSDIR)
	mkdir -p $(IMGDIR)/$(RFSDIR)/var/lib/rpm $(IMGDIR)/$(RFSDIR)/tmp/ltib
	sudo $(FSDIR)/ltib/usr/bin/rpm --nodeps --root $(IMGDIR)/$(RFSDIR) --dbpath /var/lib/rpm --prefix / --ignorearch -Uvh --force --excludedocs --define '_tmppath /tmp/ltib' $(RFSPKGS_TPAC_1007)
	cd $(IMGDIR)/$(RFSDIR); sudo ldconfig -r `pwd`
	( \
		echo "Release: $(BUILD_RELEASE)"; \
		echo "Target:  $(BUILD_TARGET)";  \
		echo "Qt:      $(QT_VERSION)";    \
		echo "Qwt:     $(QWT_VERSION)"    \
	) > $(IMGDIR)/$(RFSDIR)/$(RFS_VERSION_FILE)
	sudo install -D -p $(CSXCDIR)/arm-none-linux-gnueabi/libc/usr/bin/gdbserver $(IMGDIR)/$(RFSDIR)/usr/bin/gdbserver
	du -sh --apparent-size $(IMGDIR)/$(RFSDIR)
	cd $(IMGDIR)/$(RFSDIR); BZIP2=-9 tar cjf ../rootfs.tar.bz2 *

.PHONY: tpac_1007_lfs
tpac_1007_lfs: LFSDIR := tpac_1007/localfs
tpac_1007_lfs:
	#sudo rm -rf $(IMGDIR)/$(LFSDIR)
	#mkdir -p $(IMGDIR)/$(LFSDIR)/var/lib/rpm $(IMGDIR)/$(LFSDIR)/tmp/ltib
	#sudo $(FSDIR)/ltib/usr/bin/rpm --nodeps --root $(IMGDIR)/$(LFSDIR) --dbpath /var/lib/rpm --prefix / --ignorearch -Uvh --force --excludedocs --define '_tmppath /tmp/ltib' $(LFSPKGS_TPAC_1007)
	#du -sh --apparent-size $(IMGDIR)/$(LFSDIR)
	#cd $(IMGDIR)/$(LFSDIR); BZIP2=-9 tar cjf ../localfs.tar.bz2 *


.PHONY: clean
clean:
	sudo rm -rf $(LTIBDIR) $(TMPDIR) $(CSXCUNPACK) $(CSXCDIR) $(FSDIR) $(TMPRPMDIR) $(FTPDIR) $(QT_INSTALL_DIR)



# Downloads
#
# NOTE: Here we assume that each downloaded file has an MD5
# checksum in the same directory and named <file_name>.$(MD5EXT)
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

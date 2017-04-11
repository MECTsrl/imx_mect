########################################################################
#
# NOTE: override as needed!
#
QTH_WINE_INSTALL_PREFIX := C:/MECT/Qt-4.8.5
QTH_ARM_WINE_INSTALL_PREFIX := C:/MECT/Qt-4.8.5-arm
#
########################################################################

QTH_DIR := Qt-4.8.5
QTH_ARM_DIR := Qt-4.8.5-arm
QTC_DIR := Qt-Creator-2.8.1
MINGW_DIR := MinGW
EMB_DIR := target
LTIBRFS := ../../../ltib/rootfs
SRCDIR := ../../../src
MECTAPPS_DIR := ../../mect_apps
MECTAPPS_SAVE_DIR := ../../mect_apps.original
MECTAPPS_DESTDIR := MectApps

INSTALLSCR := installer.nsi

INSTALLDST := install-them-all
APPNAME := MECTSuite
VERSIONMAJOR := 2
VERSIONMINOR := 1
VERSIONBUILD := 0
ARCHNAME = $(APPNAME)-$(VERSIONMAJOR).$(VERSIONMINOR).$(VERSIONBUILD).zip
INSTALLPRG = $(APPNAME)-$(VERSIONMAJOR).$(VERSIONMINOR).$(VERSIONBUILD)-installer.exe

QTH_INSTALLSRC := ../wine/drive_c/MECT
QTH_INSTALLSTUFF := \
    $(QTH_DIR)/bin \
    $(QTH_DIR)/changes-4.8.5 \
    $(QTH_DIR)/features \
    $(QTH_DIR)/imports \
    $(QTH_DIR)/include \
    $(QTH_DIR)/LGPL_EXCEPTION.txt \
    $(QTH_DIR)/lib \
    $(QTH_DIR)/.LICENSE-ALLOS \
    $(QTH_DIR)/.LICENSE-ALLOS-US \
    $(QTH_DIR)/.LICENSE-DESKTOP \
    $(QTH_DIR)/.LICENSE-DESKTOP-US \
    $(QTH_DIR)/.LICENSE-EMBEDDED \
    $(QTH_DIR)/.LICENSE-EMBEDDED-US \
    $(QTH_DIR)/.LICENSE-EVALUATION \
    $(QTH_DIR)/.LICENSE-EVALUATION-US \
    $(QTH_DIR)/LICENSE.FDL \
    $(QTH_DIR)/LICENSE.GPL3 \
    $(QTH_DIR)/LICENSE.LGPL \
    $(QTH_DIR)/mkspecs \
    $(QTH_DIR)/plugins \
    $(QTH_DIR)/projects.pro \
    $(QTH_DIR)/qmake \
    $(QTH_DIR)/README \
    $(QTH_DIR)/templates \
    $(QTH_DIR)/tmp \
    $(QTH_DIR)/tools \
    $(QTH_DIR)/translations \
    $(QTH_DIR)/util \
    \
    #\
    $(QTH_DIR)/demos \
    $(QTH_DIR)/doc \
    $(QTH_DIR)/examples \
    $(QTH_DIR)/src \
    \
    $(QTH_DIR)/config.profiles \
    $(QTH_DIR)/config.tests \
    $(QTH_DIR)/configure \
    $(QTH_DIR)/configure.cache \
    $(QTH_DIR)/configure.exe \
    $(QTH_DIR)/INSTALL \
    $(QTH_DIR)/Makefile \
    $(QTH_DIR)/.qmake.cache \
    $(QTH_DIR)/.tag \

# Define MYQTARM to use Qt for ARM compiled by devtools.
#MYQTARM := true
QTH_ARM_INSTALLSRC := ../wine/drive_c/MECT/$(QTH_ARM_DIR)
QTH_ARM_ARCHIVE := Qt-4.8.5-arm.zip
ifndef $(MYQTARM)
    QTH_ARM_WINE_INSTALL_PREFIX := C:/Qt485/imx28/qt-everywhere-opensource-src-4.8.5
endif

QTC_INSTALLSRC := ../wine/drive_c/MECT
QTC_INSTALLSTUFF := \
    $(QTC_DIR)/bin \
    $(QTC_DIR)/doc \
    $(QTC_DIR)/lib \
    $(QTC_DIR)/share \

MINGW_INSTALLSRC := ../wine/drive_c
MINGW_INSTALLSTUFF := \
    $(MINGW_DIR)/bin \
    $(MINGW_DIR)/include \
    $(MINGW_DIR)/lib \
    $(MINGW_DIR)/libexec \
    $(MINGW_DIR)/mingw32 \
    $(MINGW_DIR)/msys/1.0/bin \
    $(MINGW_DIR)/msys/1.0/etc \
    $(MINGW_DIR)/msys/1.0/lib \
    $(MINGW_DIR)/msys/1.0/MECT \
    $(MINGW_DIR)/msys/1.0/postinstall \
    $(MINGW_DIR)/msys/1.0/sbin \
    $(MINGW_DIR)/msys/1.0/share \
    $(MINGW_DIR)/perl-5.24.0 \
    $(MINGW_DIR)/share \

QTT_RPM := ../../../ltib/rpm/RPMS/arm/qt-embedded-4.8.5-1.arm.rpm
QTT_RPMROOT := $(shell pwd)/rpmroot

CSXC_ARC := arm-2011.03-41-arm-none-linux-gnueabi.exe
MECTAPPS_ARCHNAME := MECTAPPS.zip
CAN_ARC := ATCM.zip
PLC_ARC := PLC.zip
PLC_ATHW := ATHW119_4CVM.kad
FONTS_ARC := Fonts.zip

UNZIP_EXE := unzip.exe

ZCF := 9


# Set dummy default version.
ifeq ($(strip $(MECT_BUILD_RELEASE)),)
    MECT_BUILD_RELEASE := 2.1.0
endif

.PHONY: all
all:
	sudo rm -rf $(INSTALLDST)
	mkdir -p $(INSTALLDST)
	#
	# Qt x86
	test -d "$(QTH_INSTALLSRC)"
	for p in $(QTH_INSTALLSTUFF); do \
	    mkdir -p `dirname $(INSTALLDST)/$$p`; \
	    cp -aL --reflink=auto $(QTH_INSTALLSRC)/$$p `dirname $(INSTALLDST)/$$p`; \
	done
	for d in `find $(INSTALLDST)/Qt-4.8.5 -type d -name mkspecs -print`; do \
	    for m in `find $$d -type f -name qmake.conf -print`; do \
		grep -q '^QMAKE_INCDIR += "."$$' $$m || echo 'QMAKE_INCDIR += "."' >> $$m; \
	    done; \
	done
	for d in `find $(INSTALLDST)/Qt-4.8.5 -type d -name lib -print`; do \
	    for m in `find $$d -type f -name \*.prl -print`; do \
		sed -i 's|^\s*QMAKE_PRL_BUILD_DIR\s*=\s*$(QTH_WINE_INSTALL_PREFIX)|QMAKE_PRL_BUILD_DIR = @@_QT_INSTALL_DIR_@@|' $$m; \
	    done; \
	done
	#
	# Qt ARM
ifdef $(MYQTARM)
	test -d "$(QTH_ARM_INSTALLSRC)"
	cp -aL --reflink=auto $(QTH_ARM_INSTALLSRC) $(INSTALLDST)
else
	test -r "$(SRCDIR)/$(QTH_ARM_ARCHIVE)"
	unzip -o -d $(INSTALLDST) $(SRCDIR)/$(QTH_ARM_ARCHIVE)
endif
	for d in `find $(INSTALLDST)/$(QTH_ARM_DIR) -type d -name mkspecs -print`; do \
	    for m in `find $$d -type f -name qmake.conf -print`; do \
		grep -q '^QMAKE_INCDIR += "."$$' $$m || echo 'QMAKE_INCDIR += "."' >> $$m; \
	    done; \
	done
	for d in `find $(INSTALLDST)/$(QTH_ARM_DIR) -type d -name lib -print`; do \
	    for m in `find $$d -type f -name \*.prl -print`; do \
		sed -i 's|^\s*QMAKE_PRL_BUILD_DIR\s*=\s*$(QTH_ARM_WINE_INSTALL_PREFIX)|QMAKE_PRL_BUILD_DIR = @@_QT_INSTALL_DIR_@@|' $$m; \
	    done; \
	done
	find $(INSTALLDST)/$(QTH_ARM_DIR) -type f -name \*.o -print0 | xargs -0 rm -f
	#
	# Qt Creator x86
	test -d "$(QTC_INSTALLSRC)"
	for p in $(QTC_INSTALLSTUFF); do \
	    mkdir -p `dirname $(INSTALLDST)/$$p`; \
	    cp -aL --reflink=auto $(QTC_INSTALLSRC)/$$p `dirname $(INSTALLDST)/$$p`; \
	done
	#
	# MinGW x86
	test -d "$(MINGW_INSTALLSRC)"
	for d in $(MINGW_INSTALLSTUFF); do \
	    mkdir -p $(INSTALLDST)/$$d; \
	    cp -aL --reflink=auto $(MINGW_INSTALLSRC)/$$d `dirname $(INSTALLDST)/$$d`; \
	done
	#
	# ARM root file system
	test -r "$(QTT_RPM)"
	mkdir -p "$(QTT_RPMROOT)/tmprpmdb"
	sudo rm -rf "$(QTT_RPMROOT)"
	sudo rpm --force-debian --root $(QTT_RPMROOT) --dbpath tmprpmdb --ignorearch -ivh --force --nodeps --excludedocs $(QTT_RPM)
	sudo chown -R $(USER) "$(QTT_RPMROOT)"
	mv "$(QTT_RPMROOT)/opt/freescale/rootfs/arm/usr" "$(QTT_RPMROOT)/opt/freescale/rootfs/arm/$(EMB_DIR)"
	cp -aL --reflink=auto "$(QTT_RPMROOT)/opt/freescale/rootfs/arm/$(EMB_DIR)" "$(INSTALLDST)"
	for d in /usr/include /usr/lib /lib /usr/src/linux/include; do \
	    mkdir -p $(INSTALLDST)/$(EMB_DIR)$$d; \
	    cp -aLf --reflink=auto $(LTIBRFS)$$d/* $(INSTALLDST)/$(EMB_DIR)$$d; \
	done
	#
	# Qt Creator configuration template
	cp -aL --reflink=auto QtProject "$(INSTALLDST)"
	#
	# MECT apps
	rm -rf $(MECTAPPS_DESTDIR)
	mkdir -p $(MECTAPPS_DESTDIR)
	cp -a --reflink=auto $(MECTAPPS_DIR)/.git $(MECTAPPS_DESTDIR)
	cd $(MECTAPPS_DESTDIR); git checkout .
	rm -rf $(MECTAPPS_DESTDIR)/.git
	find $(MECTAPPS_DESTDIR) -type f -name systemicons.qrc -exec sed -i 's|>C:/Qt485/desktop|>@@_MECTAPPS_SYSTEMICONS_PREFIX_@@|' {} \;
	for f in `grep -rIl 'ATCM_TEMPLATE_BASE_DIR\s*=\s*C:/Qt485/desktop/share/qtcreator/templates/wizards' $(MECTAPPS_DESTDIR)`; do \
	    sed -i 's|ATCM_TEMPLATE_BASE_DIR\s*=\s*C:/Qt485/desktop/share/qtcreator/templates/wizards|ATCM_TEMPLATE_BASE_DIR = $$$$(MECT_QTC_INSTALL_DIR)/share/qtcreator/templates/wizards|' $$f; \
	done
	#
	# QT_LUPDATE_PATH = C:/Qt485/desktop/bin
	# ./install-them-all/Qt-4.8.5/bin/lupdate.exe
	for f in `grep -rIl 'QT_LUPDATE_PATH\s*=\s*C:/Qt485/desktop/bin' $(MECTAPPS_DESTDIR)`; do \
	    sed -i 's|QT_LUPDATE_PATH\s*=\s*C:/Qt485/desktop|QT_LUPDATE_PATH = $$$$(MECT_QTH_INSTALL_DIR)|' $$f; \
	done
	#
	# QT_LRELEASE_PATH = C:/Qt485/imx28/qt-everywhere-opensource-src-4.8.5/bin
	# ./install-them-all/Qt-4.8.5/bin/lrelease.exe
	for f in `grep -rIl 'QT_LRELEASE_PATH\s*=\s*C:/Qt485/imx28/qt-everywhere-opensource-src-4.8.5/bin' $(MECTAPPS_DESTDIR)`; do \
	    sed -i 's|QT_LRELEASE_PATH\s*=\s*C:/Qt485/imx28/qt-everywhere-opensource-src-4.8.5|QT_LRELEASE_PATH = $$$$(MECT_QTH_INSTALL_DIR)|' $$f; \
	done
	#
	# QT_ROOTFS = C:/Qt485/imx28/rootfs
	for f in `grep -rIl 'QT_ROOTFS\s*=\s*C:/Qt485/imx28/rootfs' $(MECTAPPS_DESTDIR)`; do \
	    sed -i 's|QT_ROOTFS\s*=\s*C:/Qt485/imx28/rootfs|QT_ROOTFS = $$$$(MECT_QTT_INSTALL_DIR)|' $$f; \
	done
ifdef $(MYQTARM)
	#
	#./install-them-all/Qt-4.8.5-arm/mkspecs/qws/linux-g++-mx/qmake.conf:QMAKE_INCDIR                   = ../../ltib/rootfs/usr/include ../../ltib/rootfs/usr/include/glib-2.0 ../../ltib/rootfs/usr/lib/glib-2.0/include
	#./install-them-all/Qt-4.8.5-arm/mkspecs/qws/linux-g++-mx/qmake.conf:QMAKE_LIBDIR                   = ../../ltib/rootfs/usr/lib
	# Sanity checks
	grep -q 'QMAKE_INCDIR\s*=\s*\.\./\.\./ltib/rootfs/' $(INSTALLDST)/Qt-4.8.5-arm/mkspecs/qws/linux-g++-mx/qmake.conf
	grep -q 'QMAKE_LIBDIR\s*=\s*\.\./\.\./ltib/rootfs/' $(INSTALLDST)/Qt-4.8.5-arm/mkspecs/qws/linux-g++-mx/qmake.conf
	sed -i 's|\.\./\.\./ltib/rootfs|@@_MECT_QTTUNIX_INSTALL_DIR_@@|g' $(INSTALLDST)/Qt-4.8.5-arm/mkspecs/qws/linux-g++-mx/qmake.conf
else
	# ./install-them-all/Qt-4.8.5-arm/mkspecs/linux-arm-gnueabi-g++/qmake.conf
	grep -q 'QT_ROOTFS\s*=\s*$$$${QT_CREATOR_PATH}/imx28/rootfs' $(INSTALLDST)/Qt-4.8.5-arm/mkspecs/common/mect.conf
	sed -i 's|QT_ROOTFS\s*=\s*$$$${QT_CREATOR_PATH}/imx28/rootfs|QT_ROOTFS = @@_MECT_QTTUNIX_INSTALL_DIR_@@/../target|' $(INSTALLDST)/Qt-4.8.5-arm/mkspecs/common/mect.conf
endif
	#
	# MECT apps
	rm -f "$(MECTAPPS_ARCHNAME)"
	zip -$(ZCF)r "$(MECTAPPS_ARCHNAME)" $(MECTAPPS_DESTDIR)
	#
	# PLC Engineering
	cp --reflink=auto $(SRCDIR)/$(PLC_ARC) .
	cp --reflink=auto $(SRCDIR)/$(PLC_ATHW) .
	#
	# Code Sourcery ARM cross compiler installer
	cp --reflink=auto $(SRCDIR)/$(CSXC_ARC) .
	#
	# CAN builder
	cp --reflink=auto $(SRCDIR)/$(CAN_ARC) .
	#
	# unzip
	cp --reflink=auto $(SRCDIR)/$(UNZIP_EXE) .
	#
	# NSIS install archive
	rm -f "$(ARCHNAME)"
	archive="`pwd`/$(ARCHNAME)"; cd $(INSTALLDST); sudo zip -$(ZCF)r "$$archive" *; sudo chown $$USER "$$archive"
	#
	# MECT apps archive
	test -d $(MECTAPPS_DIR)
	test ! -d $(MECTAPPS_SAVE_DIR)
	#
	# Fonts
	cp --reflink=auto $(SRCDIR)/$(FONTS_ARC) .
	#
	# NSIS build
	makensis \
	    -DAPPNAME=$(APPNAME) \
	    -DVERSIONMAJOR=$(VERSIONMAJOR) \
	    -DVERSIONMINOR=$(VERSIONMINOR) \
	    -DVERSIONBUILD=$(VERSIONBUILD) \
	    -DARCHNAME=$(ARCHNAME) \
	    -DFONTS_ARC=$(FONTS_ARC) \
	    -DPLC_ATHW=$(PLC_ATHW) \
	    -DINSTALLPRG=$(INSTALLPRG) \
	    -DINSTALLSIZE="`du -s ${INSTALLDST} | awk '{print $$1}'`" \
	    -DQTH_DIR=$(QTH_DIR) \
	    -DQTH_ARM_DIR=$(QTH_ARM_DIR) \
	    -DMINGW_DIR=$(MINGW_DIR) \
	    -DQTC_DIR=$(QTC_DIR) \
	    -DEMB_DIR=$(EMB_DIR) \
	$(INSTALLSCR)


.PHONY: clean
clean:
	test -n "$(INSTALLDST)"
	test -n "$(ARCHNAME)"
	test -n "$(INSTALLPRG)"
	test -n "$(QTT_RPMROOT)"
	test -n "$(CSXC_ARC)"
	sudo rm -rf $(INSTALLDST) $(ARCHNAME) $(INSTALLPRG) $(QTT_RPMROOT) $(CSXC_ARC)

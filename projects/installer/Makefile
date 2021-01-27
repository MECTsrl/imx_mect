QTH_DIR := desktop
QTH_IMX_DIR := imx28
QTH_ARM_DIR := imx28\\qt-everywhere-opensource-src-4.8.5
QTC_DIR := desktop
SRCDIR := ../../src
MECTAPPS_DIR := ../mect_apps
MECTAPPS_DESTDIR := MectApps
MECTAPPS_ARCHNAME := MectApps.zip

INSTALLSCR := installer.nsi

INSTALLDST := install-them-all
APPNAME := MECTSuite
ifeq ($(strip $(MECT_BUILD_MAJOR)),)
    MECT_BUILD_MAJOR := 0
endif
ifeq ($(strip $(MECT_BUILD_MINOR)),)
    MECT_BUILD_MINOR := 0
endif
ifeq ($(strip $(MECT_BUILD_BUILD)),)
    MECT_BUILD_BUILD := 0
endif
ifeq ($(strip $(MECT_BUILD_RELEASE)),)
    MECT_BUILD_RELEASE = $(MECT_BUILD_MAJOR).$(MECT_BUILD_MINOR).$(MECT_BUILD_BUILD)
endif
BULK_ARC_BASE = $(APPNAME)-$(MECT_BUILD_RELEASE)-base.7z
BULK_ARC_UPDATE = $(APPNAME)-$(MECT_BUILD_RELEASE)-update.7z
INSTALLPRG = $(APPNAME)-$(MECT_BUILD_RELEASE)-installer.exe

QT_ARCHIVE_BASE := Qt485.7z
QT_ARCHIVE_UPDATE := Qt485_upd_rev$(MECT_BUILD_RELEASE).7z
QTPROJECT := QtProject

CSXC_ARC := sourcery-g++-lite.7z
CSXC_DIR = $(basename $(CSXC_ARC))
CAN_ARC := ATCM.zip
PLC_ARC := PLC.zip
PLC_ATHW := ATHW119_4CVM.kad
PLC_ATCM_COMMON := ATCM_Common.4cl
FONTS_ARC := Fonts.7z
PLCHELP_ARC := Engineering_Help_3.zip

UNZIP_EXE := unzip.exe
UN7ZIPG_EXE := 7zG.exe
UN7ZIP_DLL := 7z.dll
PERL_INST := ActivePerl-5.16.3.1603-MSWin32-x86-296746.msi


.PHONY: all
all:
	sudo rm -rf $(INSTALLDST)
	mkdir -p $(INSTALLDST)
	#
	# unzip
	cp --reflink=auto $(SRCDIR)/$(UNZIP_EXE) .
	#
	# 7zip
	cp --reflink=auto $(SRCDIR)/$(UN7ZIPG_EXE) .
	cp --reflink=auto $(SRCDIR)/$(UN7ZIP_DLL) .
	#
	# MECT apps
	rm -rf $(MECTAPPS_DESTDIR)
	mkdir -p $(MECTAPPS_DESTDIR)
	cp -a --reflink=auto $(MECTAPPS_DIR)/.git $(MECTAPPS_DESTDIR)
	cd $(MECTAPPS_DESTDIR); git checkout .
	rm -rf $(MECTAPPS_DESTDIR)/.git
	rm -f "$(MECTAPPS_ARCHNAME)"
	zip -r "$(MECTAPPS_ARCHNAME)" $(MECTAPPS_DESTDIR)
	#
	# PLC Engineering
	cp --reflink=auto $(SRCDIR)/$(PLC_ARC) .
	cp --reflink=auto $(SRCDIR)/$(PLC_ATHW) .
	cp --reflink=auto $(SRCDIR)/$(PLC_ATCM_COMMON) .
	cp --reflink=auto $(SRCDIR)/$(PLCHELP_ARC) .
	#
	# Code Sourcery ARM cross compiler installer
	cp --reflink=auto $(SRCDIR)/$(CSXC_ARC) .
	#
	# CAN builder
	cp --reflink=auto $(SRCDIR)/$(CAN_ARC) .
	#
	# ActivePerl 5.16.3.1603-MSWin32-x86-296746
	cp --reflink=auto $(SRCDIR)/$(PERL_INST) .
	#
	# Bulk install archive (Qt x86, Qt ARM, Qt Creator, root FS, ...)
	cp --reflink=auto $(SRCDIR)/$(QT_ARCHIVE_BASE) $(BULK_ARC_BASE)
	cp --reflink=auto $(SRCDIR)/$(QT_ARCHIVE_UPDATE) $(BULK_ARC_UPDATE)
	#
	# QtProject template
	cp --reflink=auto $(SRCDIR)/$(QTPROJECT).7z .
	#
	# Fonts
	cp --reflink=auto $(SRCDIR)/$(FONTS_ARC) .
	#
	# NSIS build
	makensis \
	    -DAPPNAME=$(APPNAME) \
	    -DVERSIONMAJOR=$(MECT_BUILD_MAJOR) \
	    -DVERSIONMINOR=$(MECT_BUILD_MINOR) \
	    -DVERSIONBUILD=$(MECT_BUILD_BUILD) \
	    -DCSXC_ARC=$(CSXC_ARC) \
	    -DBULK_ARC_BASE=$(BULK_ARC_BASE) \
	    -DBULK_ARC_UPDATE=$(BULK_ARC_UPDATE) \
	    -DQTPROJECT=$(QTPROJECT) \
	    -DPLCHELP_ARC=$(PLCHELP_ARC) \
	    -DPERL_INST=$(PERL_INST) \
	    -DFONTS_ARC=$(FONTS_ARC) \
	    -DPLC_ATHW=$(PLC_ATHW) \
	    -DPLC_ATCM_COMMON=$(PLC_ATCM_COMMON) \
	    -DINSTALLPRG=$(INSTALLPRG) \
	    -DQTH_DIR=$(QTH_DIR) \
	    -DCSXC_DIR=$(CSXC_DIR) \
	    -DQTH_IMX_DIR=$(QTH_IMX_DIR) \
	    -DQTH_ARM_DIR=$(QTH_ARM_DIR) \
	    -DQTC_DIR=$(QTC_DIR) \
	    -DINSTALLSIZE="`7zr l $(BULK_ARC_BASE) | tail -1 | awk '{ print int($$1 / 1024); }'`" \
	$(INSTALLSCR)
	#
	# Install the installer (if called from the main Makefile).
	test -n "$(MECT_IMGDIR)"
	test -n "$(MECT_WINDIR)"
	mkdir -p "$(MECT_IMGDIR)/$(MECT_WINDIR)"
	rm -f "$(MECT_IMGDIR)/$(MECT_WINDIR)/$(INSTALLPRG)"
	cp -a --reflink=auto $(INSTALLPRG) "$(MECT_IMGDIR)/$(MECT_WINDIR)"


.PHONY: clean
clean:
	test -n "$(CSXC_ARC)"
	test -n "$(CAN_ARC)"
	test -n "$(PLC_ATHW)"
	test -n "$(PLC_ATCM_COMMON)"
	test -n "$(FONTS_ARC)"
	test -n "$(INSTALLDST)"
	test -n "$(BULK_ARC)"
	test -n "$(INSTALLPRG)"
	test -n "$(MECTAPPS_ARCHNAME)"
	test -n "$(MECTAPPS_DESTDIR)"
	test -n "$(PLC_ARC)"
	test -n "$(UNZIP_EXE)"
	test -n "$(CSXC_ARC)"
	sudo rm -rf $(CSXC_ARC) $(CAN_ARC) $(PLC_ATHW) $(PLC_ATCM_COMMON) $(FONTS_ARC) $(INSTALLDST) $(BULK_ARC) $(INSTALLPRG) $(MECTAPPS_ARCHNAME) $(MECTAPPS_DESTDIR) $(PLC_ARC) $(UNZIP_EXE) $(CSXC_ARC) $(PERL_INST)

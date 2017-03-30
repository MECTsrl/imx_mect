# vim: set noexpandtab:

QTH_DIR := Qt-4.8.5
QTC_DIR := Qt-Creator-2.8.1
MINGW_DIR := MinGW
EMB_DIR := target
LTIBRFS := ../../../../ltib/rootfs
SRCDIR := ../../../../src

INSTALLSCR := installer.nsi

INSTALLDST := install-them-all
APPNAME := MECTSuite
VERSIONMAJOR := 2
VERSIONMINOR := 1
VERSIONBUILD := 0
ARCHNAME = $(APPNAME)-$(VERSIONMAJOR).$(VERSIONMINOR).$(VERSIONBUILD).zip
INSTALLPRG = $(APPNAME)-$(VERSIONMAJOR).$(VERSIONMINOR).$(VERSIONBUILD)-installer.exe

QTH_INSTALLSRC := ../../wine/drive_c/MECT
QTH_INSTALLSTUFF := \
    $(QTH_DIR)/bin \
    $(QTH_DIR)/features \
    $(QTH_DIR)/imports \
    $(QTH_DIR)/include \
    $(QTH_DIR)/lib \
    $(QTH_DIR)/mkspecs \
    $(QTH_DIR)/plugins \
    $(QTH_DIR)/qmake \
    $(QTH_DIR)/templates \
    $(QTH_DIR)/tmp \
    $(QTH_DIR)/tools \
    $(QTH_DIR)/translations \
    $(QTH_DIR)/util \
    $(QTC_DIR)/bin \
    $(QTC_DIR)/lib \
    $(QTC_DIR)/share

MINGW_INSTALLSRC := ../../wine/drive_c
MINGW_INSTALLSTUFF := \
    $(MINGW_DIR)/bin \
    $(MINGW_DIR)/libexec \
    $(MINGW_DIR)/include \
    $(MINGW_DIR)/lib \
    $(MINGW_DIR)/mingw32 \
    $(MINGW_DIR)/share \
    $(MINGW_DIR)/msys/1.0/share \
    $(MINGW_DIR)/msys/1.0/bin \
    $(MINGW_DIR)/msys/1.0/sbin \
    $(MINGW_DIR)/msys/1.0/etc \
    $(MINGW_DIR)/msys/1.0/postinstall \
    $(MINGW_DIR)/msys/1.0/lib \
    $(MINGW_DIR)/msys/1.0/MECT

QTT_RPM := ../../../../ltib/rpm/RPMS/arm/qt-embedded-4.8.5-1.arm.rpm
QTT_RPMROOT := $(shell pwd)/rpmroot

CSXC_ARC := arm-2011.03-41-arm-none-linux-gnueabi.exe


# Set dummy default version.
ifeq ($(strip $(MECT_BUILD_RELEASE)),)
    MECT_BUILD_RELEASE := 2.1.0
endif

.PHONY: all
all:
	sudo rm -rf $(INSTALLDST)
	mkdir -p $(INSTALLDST)
	test -d "$(QTH_INSTALLSRC)"
	for d in $(QTH_INSTALLSTUFF); do \
	    mkdir -p $(INSTALLDST)/$$d; \
	    cp -aL --reflink=auto $(QTH_INSTALLSRC)/$$d `dirname $(INSTALLDST)/$$d`; \
	done
	test -d "$(MINGW_INSTALLSRC)"
	for d in $(MINGW_INSTALLSTUFF); do \
	    mkdir -p $(INSTALLDST)/$$d; \
	    cp -aL --reflink=auto $(MINGW_INSTALLSRC)/$$d `dirname $(INSTALLDST)/$$d`; \
	done
	test -r "$(QTT_RPM)"
	mkdir -p "$(QTT_RPMROOT)/tmprpmdb"
	sudo rm -rf "$(QTT_RPMROOT)"
	sudo rpm --force-debian --root $(QTT_RPMROOT) --dbpath tmprpmdb --ignorearch -ivh --force --nodeps --excludedocs $(QTT_RPM)
	sudo chown -R $(USER) "$(QTT_RPMROOT)/opt/freescale/rootfs/arm"
	mv "$(QTT_RPMROOT)/opt/freescale/rootfs/arm/usr" "$(QTT_RPMROOT)/opt/freescale/rootfs/arm/$(EMB_DIR)"
	cp -aL --reflink=auto "$(QTT_RPMROOT)/opt/freescale/rootfs/arm/$(EMB_DIR)" "$(INSTALLDST)"
	for d in /usr/include /usr/lib /lib /usr/src/linux/include; do \
	    mkdir -p $(INSTALLDST)/$(EMB_DIR)$$d; \
	    sudo cp -aL --reflink=auto $(LTIBRFS)$$d/* $(INSTALLDST)/$(EMB_DIR)$$d; \
	done
	rm -f "$(ARCHNAME)"
	archive="`pwd`/$(ARCHNAME)"; cd $(INSTALLDST); sudo zip -9r "$$archive" *; sudo chown $$USER "$$archive"
	cp --reflink=auto $(SRCDIR)/$(CSXC_ARC) .
	makensis -DAPPNAME=$(APPNAME) -DVERSIONMAJOR=$(VERSIONMAJOR) -DVERSIONMINOR=$(VERSIONMINOR) -DVERSIONBUILD=$(VERSIONBUILD) -DARCHNAME=$(ARCHNAME) -DINSTALLPRG=$(INSTALLPRG) -DINSTALLSIZE="`du -s ${INSTALLDST} | awk '{print $$1}'`" -DQTH_DIR=$(QTH_DIR) -DMINGW_DIR=$(MINGW_DIR) -DQTC_DIR=$(QTC_DIR) -DEMB_DIR=$(EMB_DIR) $(INSTALLSCR)


.PHONY: clean
clean:
	rm -rf $(INSTALLDST) $(ARCHNAME) $(INSTALLPRG)
	sudo rm -rf $(QTT_RPMROOT)

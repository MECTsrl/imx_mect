# Copyright 2011 Mect s.r.l
# build the cgi from c and install all the cgi/css/html file nto the BIN_DIR

QMAKE             =  qmake -spec qws/linux-g++-mx

# Define MECT_CC_DIRECTORY in the include.
include tool_chain_base_dir.inc
MECT_CC_BINDIR    =  $(MECT_CC_DIRECTORY)/bin/
MECT_CC_RADIX     =  arm-none-linux-gnueabi
ifdef MECT_CC_RADIX
AR                =  $(MECT_CC_BINDIR)/$(MECT_CC_RADIX)-ar
AS                =  $(MECT_CC_BINDIR)/$(MECT_CC_RADIX)-gcc
CC                =  $(MECT_CC_BINDIR)/$(MECT_CC_RADIX)-gcc -Wcast-align
LD                =  $(MECT_CC_BINDIR)/$(MECT_CC_RADIX)-gcc
STRIP             =  $(MECT_CC_BINDIR)/$(MECT_CC_RADIX)-strip --strip-unneeded
else
AR                =  $(MECT_CC_BINDIR)/ar
AS                =  $(MECT_CC_BINDIR)/gcc
CC                =  $(MECT_CC_BINDIR)/gcc -Wcast-align
LD                =  $(MECT_CC_BINDIR)/gcc
STRIP             =  $(MECT_CC_BINDIR)/strip --strip-unneeded
endif
RM                =  rm
MD                =  mkdir
SED               =  sed
RM                =  rm

BIN_DIR = $(INSTALL_ROOT)/usr/share/www

ARCH_LIB_PATH     =  -L$(MECT_RFSDIR)/usr/lib
ARCH_INCLUDE      =  -I$(MECT_RFSDIR)/usr/include -I$(MECT_RFSDIR)/usr/src/linux/include
ARCH_DFLAGS       =  -D__arm

CFLAGS            =  -Wall

CGISH_LIST = \
	alarms_manager.cgi \
	changepwd.cgi \
	checkpwd.cgi \
	config_manager.cgi \
	date_time.cgi \
	display.cgi \
	display_csv.cgi \
	display_setup.cgi \
	factory_reset.cgi \
	factory_reset_confirm.cgi \
	filebrowser.cgi \
	filesmanager.cgi \
	formatsdcard.cgi \
	index.cgi \
	info.cgi \
	lan_config.cgi \
	lan_setup.cgi \
	load.cgi \
	login.cgi \
	logout.cgi \
	logs_extractor.cgi \
	logs_filter.cgi \
	logs_manager.cgi \
	managepwd.cgi \
	menu.cgi \
	reboot.cgi \
	recipes_manager.cgi \
	reset_mass_storage.cgi \
	reset_passwords.cgi \
	select \
	style.css \
	trend_manager.cgi \
	underconstruction.cgi \
	updatetime.cgi \
	upload.cgi

DATA_LIST = \
	select-template.html \
	.passwd

CGIC_LIST = upgrade.cgi getdatesinterval extract updateall.cgi

CGI_LIST = $(CGISH_LIST) $(CGIC_LIST)

all: $(CGI_LIST) $(DATA_LIST)
	
alarms_manager.cgi:
changepwd.cgi:
checkpwd.cgi:
config_manager.cgi:
date_time.cgi:
display.cgi:
display_csv.cgi:
display_setup.cgi:
factory_reset.cgi:
factory_reset_confirm.cgi:
filebrowser.cgi:
filesmanager.cgi:
formatsdcard.cgi:
index.cgi:
info.cgi:
lan_config.cgi:
lan_setup.cgi:
load.cgi:
login.cgi:
logout.cgi:
logs_extractor.cgi:
logs_filter.cgi:
logs_manager.cgi:
managepwd.cgi:
menu.cgi:
reboot.cgi:
recipes_manager.cgi:
reset_mass_storage.cgi:
reset_passwords.cgi:
select:
select-template.html:
style.css:
trend_manager.cgi:
underconstruction.cgi:
updatetime.cgi:
upload.cgi:
.passwd:

updateall.cgi: updateall.c common.c common.h cgic.c
	$(CC) $(ARCH_INCLUDE) $(CFLAGS) updateall.c common.c cgic.c -o www/updateall.cgi

upgrade.cgi: upgrade.c common.c common.h cgic.c
	$(CC) $(ARCH_INCLUDE) $(CFLAGS) upgrade.c common.c cgic.c -o www/upgrade.cgi

getdatesinterval: getdatesinterval.c
	$(CC) $(ARCH_INCLUDE) $(CFLAGS) getdatesinterval.c -o www/getdatesinterval

extract: store_extract.c
	$(CC) $(ARCH_INCLUDE) $(CFLAGS) -DSTANDALONE store_extract.c -o www/extract

install:
	@mkdir -p $(BIN_DIR)
	$(foreach file,$(CGI_LIST),install -D -m 0755 www/$(file) $(BIN_DIR)/$(file);)
	$(foreach file,$(DATA_LIST),install -D -m 0644 www/$(file) $(BIN_DIR)/$(file);)

clean:
	@rm -f *.o

distclean: clean
	@$(foreach file,$(CGIC_LIST),rm -f www/$(file);)

clobber: distclean
	@$(foreach file,$(CGI_LIST),rm -f $(BIN_DIR)/$(file);)
	@$(foreach file,$(DATA_LIST),rm -f $(BIN_DIR)/$(file);)



 # Copyright 2011 Mect s.r.l

# ../../Makefile.cfg
#

QMAKE          =  qmake -spec qws/linux-arm-gnueabi-g++

CC_RADIX       =  arm-none-linux-gnueabi-
AR             =  $(CC_DIRECTORY)$(CC_RADIX)ar
AS             =  $(CC_DIRECTORY)$(CC_RADIX)gcc
CC             =  $(CC_DIRECTORY)$(CC_RADIX)gcc -Wcast-align
LD             =  $(CC_DIRECTORY)$(CC_RADIX)gcc
STRIP          =  $(CC_DIRECTORY)$(CC_RADIX)strip --strip-unneeded
RM             =  rm
MD             =  mkdir
SED            =  sed
RM             =  rm

ARCH_LIB_PATH  =  -L$(RFSDIR)/usr/lib
ARCH_INCLUDE   =  -I$(RFSDIR)/usr/include -I$(RFSDIR)/usr/src/linux/include
ARCH_DFLAGS    =  -D__arm

# Makefile
#

CFLAGS = -Wall

BIN_DIR = ../localfs/www

all: upgrade.cgi getdatesinterval extract updateall.cgi
	
updateall.cgi: updateall.c common.c common.h cgic.c
	$(CC) $(ARCH_INCLUDE) $(CFLAGS) updateall.c common.c cgic.c -o updateall.cgi

upgrade.cgi: upgrade.c common.c common.h cgic.c 
	$(CC) $(ARCH_INCLUDE) $(CFLAGS) upgrade.c common.c cgic.c -o upgrade.cgi

getdatesinterval: getdatesinterval.c 
	$(CC) $(ARCH_INCLUDE) $(CFLAGS) getdatesinterval.c -o getdatesinterval

extract: store_extract.c
	$(CC) $(ARCH_INCLUDE) $(CFLAGS) -DSTANDALONE store_extract.c -o extract 

install: all
	install -D -m 0755 updateall.cgi $(BIN_DIR)/updateall.cgi
	install -D -m 0755 upgrade.cgi $(BIN_DIR)/upgrade.cgi
	install -D -m 0755 getdatesinterval $(BIN_DIR)/getdatesinterval
	install -D -m 0755 extract $(BIN_DIR)/extract

clean:
	rm -f *.o

distclean: clean
	rm -f updateall.cgi upgrade.cgi getdatesinterval extract

clobber: distclean
	rm -f $(BIN_DIR)/updateall.cgi $(BIN_DIR)/upgrade.cgi $(BIN_DIR)/getdatesinterval $(BIN_DIR)/extract

 # Copyright 2011 Mect s.r.l

include ../projects-make.cfg

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
	install -D -m 755 updateall.cgi $(BIN_DIR)/updateall.cgi
	install -D -m 755 upgrade.cgi $(BIN_DIR)/upgrade.cgi
	install -D -m 755 getdatesinterval $(BIN_DIR)/getdatesinterval
	install -D -m 755 extract $(BIN_DIR)/extract

clean:
	rm -f *.o

distclean: clean
	rm -f updateall.cgi upgrade.cgi getdatesinterval extract

clobber: distclean
	rm -f $(BIN_DIR)/updateall.cgi $(BIN_DIR)/upgrade.cgi $(BIN_DIR)/getdatesinterval $(BIN_DIR)/extract

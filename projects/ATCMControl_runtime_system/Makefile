MAKE := make
SCP := scp


.PHONY: all p tags clean clobber

all:
	$(MAKE) -f _fcrts.mak TARGET=4CPC DEBUG=1 GDB=1 PRODUCT=USE_CROSSTABLE SOURCERY_GCC=1 $@

p:
	$(SCP) -p bin/fcrts* root@192.168.5.211:


tags:
	ctags -R . /usr/include


clean: clobber

clobber:
	$(MAKE) -f _fcrts.mak TARGET=4CPC DEBUG=1 GDB=1 PRODUCT=USE_CROSSTABLE SOURCERY_GCC=1 $@

.PHONY: all
all: all-linux clean all-windows

.PHONY: all-windows all-linux
all-windows all-linux:
	test -r Makefile.$(@:all-%=%)
	$(MAKE) -f Makefile.$(@:all-%=%) all


.PHONY: clean
clean: clean-windows clean-linux

.PHONY: clean-windows clean-linux
clean-windows clean-linux:
	-if test -r Makefile.$(@:clean-%=%); then $(MAKE) -f Makefile.$(@:clean-%=%) clean; fi


.PHONY: distclean
distclean: distclean-windows distclean-linux

.PHONY: distclean-windows distclean-linux
distclean-windows distclean-linux:
	-if test -r Makefile.$(@:distclean-%=%); then $(MAKE) -f Makefile.$(@:distclean-%=%) distclean; fi

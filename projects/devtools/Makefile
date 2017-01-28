.PHONY: all
all:
	$(MAKE) buildclean-windows
	$(MAKE) buildclean-linux
	$(MAKE) all-windows
	$(MAKE) buildclean-windows
	$(MAKE) all-linux
	$(MAKE) buildclean-linux

.PHONY: all-windows all-linux
all-windows all-linux:
	test -r Makefile.$(@:all-%=%)
	$(MAKE) -f Makefile.$(@:all-%=%) all


.PHONY: clean
clean: clean-windows clean-linux

.PHONY: clean-windows clean-linux
clean-windows clean-linux:
	-if test -r Makefile.$(@:clean-%=%); then $(MAKE) -f Makefile.$(@:clean-%=%) clean; fi


.PHONY: buildclean
buildclean: buildclean-windows buildclean-linux

.PHONY: buildclean-windows buildclean-linux
buildclean-windows buildclean-linux:
	-if test -r Makefile.$(@:buildclean-%=%); then $(MAKE) -f Makefile.$(@:buildclean-%=%) buildclean; fi

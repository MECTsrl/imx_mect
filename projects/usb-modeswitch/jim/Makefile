# Tools
CC ?= ccache gcc
CXX = ccache g++
RANLIB = ranlib
AR = ar
STRIP = strip

# Configuration

SH_CFLAGS ?= -fpic
SH_LDFLAGS ?= -shared
SHOBJ_CFLAGS ?= -fpic
SHOBJ_LDFLAGS ?= -shared
CFLAGS = -Wall
CXXFLAGS = -Wall
LDFLAGS = 
LDLIBS += 
exec_prefix ?= /usr
prefix ?= /usr

CC += -D_GNU_SOURCE -Wall $(OPTIM) -I.
CXX += -D_GNU_SOURCE -Wall $(OPTIM) -I.

LIBJIM := libjim.a

JIMSH_CC := $(CC) $(CFLAGS)

OBJS := _load-static-exts.o jim-subcmd.o jim-interactive.o jim-format.o jim.o utf8.o jimregexp.o \
     jim-aio.o jim-array.o jim-clock.o jim-eventloop.o jim-exec.o jim-file.o jim-package.o jim-readdir.o jim-regexp.o glob.o tclcompat.o

JIMSH := jimsh

all: $(JIMSH) 

# Create C extensions from pure Tcl extensions
.SUFFIXES: .tcl
.tcl.o:
	/usr/bin/tclsh ./make-c-ext.tcl $< >_$*.c || ( rm _$*.c; exit 1)
	$(CC) $(CFLAGS) -c -o $@ _$*.c || ( rm _$*.c; exit 1)
	@rm -f _$*.c

docs: Tcl.html

$(JIMSH): $(LIBJIM) jimsh.o initjimsh.o
	$(JIMSH_CC)  $(LDFLAGS) -o $@ jimsh.o initjimsh.o $(LIBJIM) $(LDLIBS)

install: all docs  install-exec
	mkdir -p $(DESTDIR)$(prefix)/lib/jim
	cp $(LIBJIM) $(DESTDIR)$(prefix)/lib
	cp ./README.extensions   $(DESTDIR)$(prefix)/lib/jim
	mkdir -p $(DESTDIR)$(prefix)/include
	cp ./jim.h ./jim-eventloop.h ./jim-nvp.h ./jim-signal.h \
		./jim-subcmd.h ./jim-win32compat.h $(DESTDIR)$(prefix)/include
	cp jim-config.h $(DESTDIR)$(prefix)/include
	mkdir -p $(DESTDIR)$(prefix)/doc/jim
	cp Tcl.html $(DESTDIR)$(prefix)/doc/jim

install-exec: all
	mkdir -p $(DESTDIR)$(prefix)/bin
	cp $(JIMSH) $(DESTDIR)$(prefix)/bin

uninstall:
	rm -f $(DESTDIR)$(prefix)/bin/$(JIMSH)
	rm -f $(DESTDIR)$(prefix)/lib/$(LIBJIM)
	for i in README.extensions  ; do rm -f $(DESTDIR)$(prefix)/lib/jim/$$i; done
	rm -f $(DESTDIR)$(prefix)/include/jim*.h
	rm -f $(DESTDIR)$(prefix)/doc/jim/Tcl.html

test: $(JIMSH)
	$(DEF_LD_PATH) $(MAKE) -C ./tests jimsh=`pwd`/jimsh

$(OBJS): Makefile


_load-static-exts.c: ./make-load-static-exts.tcl Makefile
	/usr/bin/tclsh ./make-load-static-exts.tcl aio array clock eventloop exec file package readdir regexp glob tclcompat >$@ || ( rm $@; exit 1)

$(LIBJIM): $(OBJS)
	$(AR) cr $@ $(OBJS)
	$(RANLIB) $@

# Note that $> $^ is for compatibility with both GNU make and BSD make
readdir.so: jim-readdir.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-readdir.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-readdir.o $(SH_LIBJIM) 

array.so: jim-array.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-array.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-array.o $(SH_LIBJIM) 

clock.so: jim-clock.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-clock.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-clock.o $(SH_LIBJIM) 

file.so: jim-file.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-file.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-file.o $(SH_LIBJIM) 

posix.so: jim-posix.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-posix.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-posix.o $(SH_LIBJIM) 

regexp.so: jim-regexp.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-regexp.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-regexp.o $(SH_LIBJIM) 

syslog.so: jim-syslog.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-syslog.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-syslog.o $(SH_LIBJIM) 

readline.so: jim-readline.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-readline.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-readline.o $(SH_LIBJIM) @LDLIBS_readline@

pack.so: jim-pack.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-pack.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-pack.o $(SH_LIBJIM) @LDLIBS_pack@

sqlite.so: jim-sqlite.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-sqlite.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-sqlite.o $(SH_LIBJIM) @LDLIBS_sqlite@

sqlite3.so: jim-sqlite3.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-sqlite3.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-sqlite3.o $(SH_LIBJIM) @LDLIBS_sqlite3@

win32.so: jim-win32.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-win32.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-win32.o $(SH_LIBJIM) @LDLIBS_win32@

mk.so: jim-mk.cpp
	$(CXX) $(CXXFLAGS) $(SHOBJ_CFLAGS) -c -o jim-mk.o $> $^
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-mk.o $(SH_LIBJIM) @LDLIBS_mk@

sdl.so: jim-sdl.c
	$(CC) $(CFLAGS) $(SHOBJ_CFLAGS) -c -o jim-sdl.o $> $^
	$(CC) $(CFLAGS) $(LDFLAGS) $(SHOBJ_LDFLAGS) -o $@ jim-sdl.o $(SH_LIBJIM) @LDLIBS_sdl@

Tcl.html: jim_tcl.txt
	/usr/bin/tclsh ./make-index $> $^ | asciidoc -o $@ -d manpage - || cp ./Tcl_shipped.html Tcl.html

clean:
	rm -f *.o *.so lib*.a $(JIMSH) Tcl.html _*.c

distclean: clean
	rm -f jimautoconf.h jim-config.h Makefile config.log autosetup/jimsh0.c autosetup/jimsh0

ship: Tcl.html
	cp $< Tcl_shipped.html

# automake compatibility. do nothing for all these targets
EMPTY_AUTOMAKE_TARGETS := dvi pdf ps info html tags ctags mostlyclean maintainer-clean check installcheck installdirs \
 install-pdf install-ps install-info install-html -install-dvi uninstall install-data
.PHONY: $(EMPTY_AUTOMAKE_TARGETS)
$(EMPTY_AUTOMAKE_TARGETS):

# automake compatibility - install sources from the current dir to $(distdir)
distdir_full := $(shell cd $(distdir); pwd)
distdir:
	cd "."; git ls-files | cpio -pdmu $(distdir_full)

reconfig:
	CC='gcc' /home/imx28/20161209/ltib/rpm/BUILD/usb-modeswitch-2.3.0/jim/configure --disable-lineedit "--with-out-jim-ext=stdlib posix load signal syslog" --prefix=/usr

lib: $(LIBJIM)

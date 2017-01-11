# Makefile
#
# Copyright (c) 2004 by Internet Systems Consortium, Inc. ("ISC")
# Copyright (c) 1995-2003 by Internet Software Consortium
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
# OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
#   Internet Systems Consortium, Inc.
#   950 Charter Street
#   Redwood City, CA 94063
#   <info@isc.org>
#   http://www.isc.org/
#
# This software has been written for Internet Systems Consortium
# by Ted Lemon in cooperation with Vixie Enterprises and Nominum, Inc.
# To learn more about Internet Systems Consortium, see
# ``http://www.isc.org/''.  To learn more about Vixie Enterprises,
# see ``http://www.vix.com''.   To learn more about Nominum, Inc., see
# ``http://www.nominum.com''.

all:
	@sysname=`./configure --print-sysname`; \
	 if [ ! -d work.$$sysname ]; then \
	   echo No build directory for $$sysname - please run ./configure.; \
	else \
	   (cd work.$$sysname; make all); \
	fi
	$(CROSS)gcc -g -o tests/parser/parse tests/parser/parse.c

install:
	@sysname=`./configure --print-sysname`; \
	 if [ ! -d work.$$sysname ]; then \
	   echo No build directory for $$sysname - please run ./configure.; \
	else \
	   (cd work.$$sysname; make install); \
	fi
	cp tests/config_script/dhclient.conf  $(prefix)/etc/
	cp tests/config_script/dhcpd.conf $(prefix)/etc/
	install -c -m 777 tests/config_script/dhclient-exit-hooks $(prefix)/etc/
	mkdir $(prefix)/etc/rc.d/
	install -d  $(prefix)/etc/rc.d/init.d/
	install -c -m 444 tests/startup_script/S30dhclient $(prefix)/sbin/
	install -c -m 444 tests/startup_script/S30dhclient $(prefix)/etc/rc.d/init.d/
	install -c -m 444 tests/startup_script/S31dhcpd $(prefix)/etc/rc.d/init.d/
	chmod a+x $(prefix)/sbin/S30dhclient
	chmod a+x $(prefix)/etc/rc.d/init.d/S30dhclient
	chmod a+x $(prefix)/etc/rc.d/init.d/S31dhcpd
	install -d $(prefix)/var/state/
	install -d $(prefix)/var/state/dhcp/
	install -c -m 666 tests/config_script/dhcpd.leases  $(prefix)/var/state/dhcp/dhcpd.leases
	install -c -m 666 tests/config_script/dhclient.leases $(prefix)/var/state/dhcp/dhclient.leases
	mkdir $(prefix)/etc/test
	mkdir $(prefix)/etc/test/test_script/
	mkdir $(prefix)/etc/test/config_script/
	cp -rf tests/config_script/* $(prefix)/etc/test/config_script/
	cp -rf tests/test_script/* $(prefix)/etc/test/test_script/
	chmod a+x $(prefix)/etc/test/test_script/*
	install -d  $(prefix)/bin/
	install  -c -m 444 tests/parser/parse $(prefix)/bin/
	chmod a+x $(prefix)/bin/parse


depend:
	@sysname=`./configure --print-sysname`; \
	 if [ ! -d work.$$sysname ]; then \
	   echo No build directory for $$sysname - please run ./configure.; \
	else \
	   (cd work.$$sysname; make depend); \
	fi

clean:
	@sysname=`./configure --print-sysname`; \
	 if [ ! -d work.$$sysname ]; then \
	   echo No build directory for $$sysname - please run ./configure.; \
	else \
	   (cd work.$$sysname; make clean); \
	fi
	rm -f tests/parser/parse 

realclean:
	@sysname=`./configure --print-sysname`; \
	 if [ ! -d work.$$sysname ]; then \
	   echo No build directory for $$sysname - please run ./configure.; \
	else \
	   (cd work.$$sysname; make realclean); \
	fi

distclean:
	@sysname=`./configure --print-sysname`; \
	 if [ ! -d work.$$sysname ]; then \
	   echo No build directory for $$sysname - please run ./configure.; \
	else \
	   (cd work.$$sysname; make distclean); \
	fi

links:
	@sysname=`./configure --print-sysname`; \
	 if [ ! -d work.$$sysname ]; then \
	   echo No build directory for $$sysname - please run ./configure.; \
	else \
	   (cd work.$$sysname; make links); \
	fi


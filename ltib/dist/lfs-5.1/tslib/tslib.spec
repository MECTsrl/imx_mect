%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Abstraction layer for touchscreen panel events 
Name            : tslib
Version         : 1.0
Release         : 3
License         : LGPL
Vendor          : Freescale
Packager        : Ross Wille
Group           : System Environment/Libraries
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed tslib for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Libraries
AutoReqProv     : no

%Description rfs
tslib package contents restricted to just the files that are
needed at run time on the target.


%Description
%{summary}


%Prep
export LC_ALL
LC_ALL=C

%setup -T -c -n %{name}
cd ..; rmdir %{name}; ln -s ../../../projects/%{name} %{name}


%Build
export LC_ALL
LC_ALL=C

# Timestamp order is important.
for f in configure.ac configure.in aclocal.m4 configure config.h.in Makefile.am Makefile.in; do
	find . -name $f -exec touch {} \;
done
ac_cv_func_malloc_0_nonnull=yes ./configure CC=${TOOLCHAIN_PREFIX}gcc --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}

# Remove unused platform binaries
for so in arctic2.so collie.so corgi.so h3600.so mk712.so; do
	rm -f $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/usr/lib/ts/$so
done


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/bin/ts_calibrate
%{pfx}/usr/bin/ts_harvest
%{pfx}/usr/bin/ts_print
%{pfx}/usr/bin/ts_print_raw
%{pfx}/usr/bin/ts_test
%{pfx}/usr/etc/ts.conf
%{pfx}/usr/lib/libts-1.0.so.0
%{pfx}/usr/lib/libts-1.0.so.0.1.1
%{pfx}/usr/lib/libts.so
%{pfx}/usr/lib/ts/arctic2.so
%{pfx}/usr/lib/ts/collie.so
%{pfx}/usr/lib/ts/corgi.so
%{pfx}/usr/lib/ts/dejitter.so
%{pfx}/usr/lib/ts/h3600.so
%{pfx}/usr/lib/ts/input.so
%{pfx}/usr/lib/ts/linear.so
%{pfx}/usr/lib/ts/linear_h2200.so
%{pfx}/usr/lib/ts/mk712.so
%{pfx}/usr/lib/ts/pthres.so
%{pfx}/usr/lib/ts/ucb1x00.so
%{pfx}/usr/lib/ts/variance.so

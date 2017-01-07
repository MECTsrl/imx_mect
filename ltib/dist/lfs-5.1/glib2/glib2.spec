%define pfx /opt/freescale/rootfs/%{_target_cpu}
%define archname glib

Summary         : A library of functions used by GDK, GTK+, and many applications
Name            : glib2
Version         : 2.18.1
Release         : 1
License         : LGPL
Vendor          : Freescale
Packager        : Stuart Hughes/Kurt Mahan
Group           : System Environment/Libraries
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed glib2 for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Libraries
AutoReqProv     : no

%Description rfs
glib2 package contents restricted to just the files that are
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
# prevent configure from trying to compile and
# run test binaries for the target.
glib_cv_stack_grows=no \
glib_cv_uscore=no \
ac_cv_func_posix_getpwuid_r=yes \
ac_cv_func_posix_getgrgid_r=yes \
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT%{pfx}


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/bin/glib-genmarshal
%{pfx}/usr/bin/glib-gettextize
%{pfx}/usr/bin/glib-mkenums
%{pfx}/usr/bin/gobject-query
%{pfx}/usr/bin/gtester
%{pfx}/usr/bin/gtester-report
%{pfx}/usr/lib/libgio-2.0.so
%{pfx}/usr/lib/libgio-2.0.so.0
%{pfx}/usr/lib/libgio-2.0.so.0.1800.1
%{pfx}/usr/lib/libglib-2.0.so
%{pfx}/usr/lib/libglib-2.0.so.0
%{pfx}/usr/lib/libglib-2.0.so.0.1800.1
%{pfx}/usr/lib/libgmodule-2.0.so
%{pfx}/usr/lib/libgmodule-2.0.so.0
%{pfx}/usr/lib/libgmodule-2.0.so.0.1800.1
%{pfx}/usr/lib/libgobject-2.0.so
%{pfx}/usr/lib/libgobject-2.0.so.0
%{pfx}/usr/lib/libgobject-2.0.so.0.1800.1
%{pfx}/usr/lib/libgthread-2.0.so
%{pfx}/usr/lib/libgthread-2.0.so.0
%{pfx}/usr/lib/libgthread-2.0.so.0.1800.1
%{pfx}/usr/share/aclocal/glib-2.0.m4
%{pfx}/usr/share/aclocal/glib-gettext.m4
%{pfx}/usr/share/glib-2.0/gettext/mkinstalldirs
%{pfx}/usr/share/glib-2.0/gettext/po/Makefile.in.in

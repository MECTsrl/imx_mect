%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : SQLite database engine
Name            : sqlite
Version         : 3.6.12
Release         : 1
License         : Public Domain
Vendor          : SQLite Consortium
Packager        : ProFUSION embedded systems <contact@profusion.mobi>
Group           : System Environment/Libraries
URL             : http://www.sqlite.org/
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed sqlite for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Libraries
AutoReqProv     : no

%Description rfs
sqlite package contents restricted to just the files that are
needed at run time on the target.


%Description
SQLite is a software library that implements a self-contained, serverless, zero-configuration, transactional SQL database engine.


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
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make -j$(nproc)


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/bin/sqlite3
%{pfx}/usr/lib/libsqlite3.so
%{pfx}/usr/lib/libsqlite3.so.0
%{pfx}/usr/lib/libsqlite3.so.0.8.6

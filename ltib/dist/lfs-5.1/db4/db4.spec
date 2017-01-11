%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : The Berkeley DB database library (version 4) for C
Name            : db4
Version         : 4.5.20
Release         : 0
License         : GPL-like BSD variant
Vendor          : Freescale
Packager        : Emil Medve
Group           : System Environment/Libraries
URL             : http://www.oracle.com/database/berkeley-db
Source          : db-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

Oracle Berkeley DB is a family of open source embeddable databases that allows developers to
incorporate within their applications a fast, scalable, transactional database engine with
industrial grade reliability and availability. As a result, customers and end-users will experience
an application that simply works, reliably manages data, can scale under extreme load, but requires
no ongoing database administration. As a developer, you can focus on your application and be
confident that Oracle Berkeley DB will manage your persistence needs

WARNING: Please note that this package has a GPL-like license!

%Prep
%setup -n db-%{version}

%Build
cd build_unix
../dist/configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} --enable-compat185
make

%Install
rm -rf $RPM_BUILD_ROOT
make -C build_unix install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
rm -rf $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/*.la
chmod +w $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/bin/db_archive    \
         $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/bin/db_checkpoint \
         $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/bin/db_deadlock   \
         $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/bin/db_dump       \
         $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/bin/db_hotbackup  \
         $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/bin/db_load       \
         $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/bin/db_printlog   \
         $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/bin/db_recover    \
         $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/bin/db_stat       \
         $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/bin/db_upgrade    \
         $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/bin/db_verify

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*

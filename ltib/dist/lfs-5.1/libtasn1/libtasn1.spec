%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : ASN.1 library used in GNUTLSASN.1 library used in GNUTLS
Name            : libtasn1
Version         : 1.8
Release         : 1
Vendor          : Freescale
Packager        : Rob Herring
Group           : Productivity/Networking/Security
Source          : %{name}-%{version}.tar.gz
Patch0          : libtasn1-1.8-config-cflags-fix.patch
License         : LGPL
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup
%patch0 -p1

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
rm -f $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/*.la

%Clean
rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

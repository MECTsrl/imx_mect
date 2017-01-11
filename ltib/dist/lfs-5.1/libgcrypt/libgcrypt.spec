%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : A general-purpose cryptography library.
Name            : libgcrypt
Version         : 1.4.4
Release         : 1
Vendor          : Freescale
Packager        : Rob Herring
Group           : System Environment/Libraries
Source          : %{name}-%{version}.tar.bz2
License         : LGPL
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build
export GPG_ERROR_CONFIG=${DEV_IMAGE}/usr/bin/gpg-error-config
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

%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Writes i.MX233-style boot streams to a NAND Flash medium.
Name            : kobs-ng
Version         : 2.6.35.3
Release         : 1.1.0
License         : GPL
Vendor          : Freescale
Packager        : Patrick Turley
Group           : MAD Linux
URL             : http://www.freescale.com
Source          : %{name}-%{version}-%{release}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup -n %{name}-%{version}-%{release}

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
mkdir -p $RPM_BUILD_ROOT/%{pfx}/root
install -m 0644 dot-kobs $RPM_BUILD_ROOT/%{pfx}/root/.kobs

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*

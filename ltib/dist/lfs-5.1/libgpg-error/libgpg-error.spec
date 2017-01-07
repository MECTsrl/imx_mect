%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : This is a library that defines common error values for all GnuPG components.
Name            : libgpg-error
Version         : 1.7
Release         : 1
Vendor          : Freescale
Packager        : Rob Herring
Group           : Development/Libraries/C
Source          : %{name}-%{version}.tar.bz2
License         : LGPL
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make CC_FOR_BUILD="${BUILDCC}"

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
rm -f $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/*.la

%Clean
rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

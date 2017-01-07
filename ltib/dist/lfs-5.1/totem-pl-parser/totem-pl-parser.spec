%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Totem Movie Player
Name            : totem-pl-parser
Version         : 2.26.2
Release         : 1
License         : LGPL
Vendor          : Freescale
Packager        : Rob Herring
Group           : System Environment/Daemons
Source          : %{name}-%{version}.tar.bz2
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build
export PKG_CONFIG_PATH=${PKG_CONFIG_PATH}:${DEV_IMAGE}/usr/share/pkgconfig
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



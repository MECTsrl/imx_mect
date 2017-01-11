%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Xorg X11 mouse input driver
Name            : xorg-x11-drv-mouse
Version         : 1.4.0
Release         : 1
License         : MIT
Vendor          : Freescale
Packager        : Rob Herring
Group           : User Interface/X Hardware Support
URL             : http://www.x.org
Source0         : xf86-input-mouse-%{version}.tar.bz2
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep

%setup -q -n xf86-input-mouse-%{version}


%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make


%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
find $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/ -name "*.la" | xargs rm -f


%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*

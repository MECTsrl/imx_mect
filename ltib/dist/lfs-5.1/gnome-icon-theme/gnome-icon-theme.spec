%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : icon data files for GNOME desktop
Name            : gnome-icon-theme
Version         : 2.24.0
Release         : 1
Vendor          : Freescale
Packager        : Rob Herring
Group           : System Environment/Libraries
Source          : %{name}-%{version}.tar.bz2
License         : GPL
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} --disable-icon-mapping
make

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}

%Clean
rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

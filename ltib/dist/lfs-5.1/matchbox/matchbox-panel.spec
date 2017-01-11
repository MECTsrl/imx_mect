%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Matchbox Panel
Name            : matchbox-panel
Version         : 0.9.3
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Rob Herring
Group           : User Interface/Desktops
Source          : %{name}-%{version}.tar.bz2
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}


%Clean
rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*



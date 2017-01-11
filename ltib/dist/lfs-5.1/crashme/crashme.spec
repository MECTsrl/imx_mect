%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Random test
Name            : crashme
Version         : 2.4
Release         : 1
License         : Distributable
Vendor          : GEORGE J. CARRETTE, CONCORD, MASSACHUSETTS.
Packager        : Hake Huang
Group           : Applications/System
Source          : %{name}-%{version}.tar.bz2
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
URL             : http://people.delphiforums.com/gjc/crashme.html

%Description
%{summary}

%Prep
%setup

%Build
make

%Install
rm -rf $RPM_BUILD_ROOT
install -d $RPM_BUILD_ROOT/%{pfx}/usr/bin
install crashme $RPM_BUILD_ROOT/%{pfx}/usr/bin

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)

%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : control programs for Video for Linux
Name            : fmtools
Version         : 1.0.2
Release         : 1
License         : GPL
Vendor          : Russell Kroll
Packager        : Hake Huang
Group           : Applications/System
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
URL             : http://www.stanford.edu/~blp/fmtools/fmtools-1.0.2.tar.gz

%Description
%{summary}

%Prep
%setup

%Build
make

%Install
rm -rf $RPM_BUILD_ROOT
install -d $RPM_BUILD_ROOT/%{pfx}/usr/bin
install fm $RPM_BUILD_ROOT/%{pfx}/usr/bin
install fmscan $RPM_BUILD_ROOT/%{pfx}/usr/bin

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*


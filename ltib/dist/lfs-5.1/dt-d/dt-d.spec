%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Data Test Program
Name            : dt.d-WIP
Version         : 15.14
Release         : 1
License         : Public domain
Vendor          : Robin's Nest Software Inc.
Packager        : Hake Huang
Group           : Applications/System
Source          : dt-source.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
URL             : http://home.comcast.net/~SCSIguy/SCSI_FAQ/RMiller_Tools/dt.html

%Description
%{summary}

%Prep
%setup -n %{name}

%Build
make -f Makefile.linux

%Install
rm -rf $RPM_BUILD_ROOT
install -d $RPM_BUILD_ROOT/%{pfx}/usr/bin
install dt $RPM_BUILD_ROOT/%{pfx}/usr/bin

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*


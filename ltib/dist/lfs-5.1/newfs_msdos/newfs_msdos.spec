%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Utilities for making and checking MS-DOS FAT filesystems on Linux.
Name            : newfs_msdos
Version         : 1.33
Release         : 1
License         : BSD
Vendor          : Freescale
Packager        : Terry Lv
Group           : Applications/System
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build
make CROSS_COMPILE=${TOOLCHAIN_PREFIX}

%Install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}/sbin
#make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}

install -m 755 -s newfs_msdos $RPM_BUILD_ROOT/%{pfx}/sbin/newfs_msdos
ln -sf newfs_msdos $RPM_BUILD_ROOT/%{pfx}/sbin/mkfs.vfat
ln -sf newfs_msdos $RPM_BUILD_ROOT/%{pfx}/sbin/mkfs.msdos

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*

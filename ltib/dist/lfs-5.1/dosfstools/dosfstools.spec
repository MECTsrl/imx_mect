%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Utilities for making and checking MS-DOS FAT filesystems on Linux.
Name            : dosfstools
Version         : 3.0.12
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Alan Tull
Group           : Applications/System
Source          : dosfstools-3.0.12.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build
make CC="${TOOLCHAIN_PREFIX}gcc"

%Install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}/sbin
mkdir -p $RPM_BUILD_ROOT/%{pfx}/%{_mandir}/man8

install -m 755 -s mkdosfs $RPM_BUILD_ROOT/%{pfx}/sbin/mkdosfs
ln -sf mkdosfs $RPM_BUILD_ROOT/%{pfx}/sbin/mkfs.vfat
ln -sf mkdosfs $RPM_BUILD_ROOT/%{pfx}/sbin/mkfs.msdos

install -m 755 -s dosfsck $RPM_BUILD_ROOT/%{pfx}/sbin/dosfsck
ln -sf dosfsck $RPM_BUILD_ROOT/%{pfx}/sbin/fsck.msdos
ln -sf dosfsck $RPM_BUILD_ROOT/%{pfx}/sbin/fsck.vfat

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*

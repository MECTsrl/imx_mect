%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Universal Bootloader firmware
Name            : u-boot
Version         : cf.20081108
Release         : 0
License         : GPL
Vendor          : Freescale
Packager        : Matt Waddel
Group           : Applications/System
Source          : u-boot-%{version}.tar.gz
Patch0          : u-boot-2008.10-mii-driver.patch
Patch1          : u-boot-2008.10-rambar.patch
Patch2          : u-boot-cf.20081108-FEC-TX-fix.patch
Patch3          : u-boot-2008.10-rambar-2.patch
Patch4          : u-boot-cf-2008.10-unzip-fix.patch
Patch5          : u-boot-cf.53017defs.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

Open source u-boot version 2008.10 with uClinux corrections

%Prep
%setup -n u-boot
%patch0 -p1
%patch1 -p1
%patch2 -p1
%patch3 -p1
%patch4 -p1
%patch5 -p1

%Build
PKG_U_BOOT_CONFIG_TYPE=${SYSCFG_BOOT_CPU}
make distclean
make HOSTCC="$BUILDCC" CROSS_COMPILE=$TOOLCHAIN_PREFIX $PKG_U_BOOT_CONFIG_TYPE
make HOSTCC="$BUILDCC" HOSTSTRIP="$BUILDSTRIP" CROSS_COMPILE=$TOOLCHAIN_PREFIX

%Install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}/boot
for i in u-boot.bin u-boot
do
    cp $i $RPM_BUILD_ROOT/%{pfx}/boot
done

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*

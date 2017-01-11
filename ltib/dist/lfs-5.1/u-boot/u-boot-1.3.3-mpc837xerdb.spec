%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Universal Bootloader firmware
Name            : u-boot
Version         : 1.3.3
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Joe D'Abbraccio
Group           : Applications/System
Source          : %{name}-%{version}.tar.bz2 
Patch1          : %{name}-pre-%{version}-mpc837xerdb-cfg.patch
Patch2          : %{name}-pre-%{version}-mpc837xerdb-nand.patch
Patch3          : %{name}-%{version}-improved-ddr-settings.patch
Patch4          : %{name}-%{version}-mpc837xerdb-pcie-support.patch
Patch5          : %{name}-%{version}-mpc837xerdb-esdhc-support.patch
Patch6          : %{name}-%{version}-mpc837xerdb-en-bootcmd.patch
Patch7          : %{name}-1.3.0-mpc83xx-rodata-str-1.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

All source and patches from Freescale.

%Prep
%setup -n %{name}-%{version}
%patch1 -p1
%patch2 -p1
%patch3 -p1
%patch4 -p1
%patch5 -p1
%patch6 -p1
%patch7 -p1

%Build
PKG_U_BOOT_CONFIG_TYPE=${PKG_U_BOOT_CONFIG_TYPE:-MPC8379RDB_config}
make HOSTCC="$BUILDCC" CROSS_COMPILE=$TOOLCHAIN_PREFIX $PKG_U_BOOT_CONFIG_TYPE
make HOSTCC="$BUILDCC" HOSTSTRIP="$BUILDSTRIP" \
     CROSS_COMPILE=$TOOLCHAIN_PREFIX $PKG_U_BOOT_BUILD_ARGS all

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

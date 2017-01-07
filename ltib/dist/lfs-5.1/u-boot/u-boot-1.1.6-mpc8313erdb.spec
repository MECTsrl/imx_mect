%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Universal Bootloader firmware
Name            : u-boot
Version         : 1.1.6
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Vivienne Li
Group           : Applications/System
Source          : %{name}-%{version}.tar.bz2
Patch0          : u-boot-1.1.6-fsl-1-mpc83xx-20061206.patch
Patch1          : u-boot-1.1.6-mpc8313erdb-general.patch
Patch2          : u-boot-1.1.6-mpc8313erdb-cpu-1.patch
Patch3          : u-boot-1.1.6-mpc8313erdb-board-1.patch
Patch4          : u-boot-1.1.6-vsc7385-load-v3.patch
Patch5          : u-boot-1.1.6-mpc8313erdb-nand-autoboot.patch
Patch6          : u-boot-1.1.6-mpc8313erdb-nand-bootloader.patch
Patch7          : u-boot-1.1.6-mpc8313erdb-power-management.patch
Patch8          : u-boot-1.1.6-mpc8313erdb-Core-CSB-frequence-2.patch
Patch9          : u-boot-1.1.6-make-fixes.patch
Patch10         : u-boot-1.1.6-83xx-ACR-optimizations.patch
Patch11         : u-boot-1.1.6-mpc8313-rodata-str-1.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
 U-Boot 1.1.6 configured for MPC8313E RDB board.
 The patch file used is based on source changes from
 http://opensource.freescale.com/pub/scm/u-boot-83xx.git (a public git repository)
 using the tree with sha1 value 21fb83dfa2dcba7982eeb54f4ca7bc1056582c1e.

%{summary}

All source and patches from Freescale.

%Prep
%setup -n %{name}-%{version}
%patch0 -p1
%patch1 -p1
%patch2 -p1
%patch3 -p1
%patch4 -p1
%patch5 -p1
%patch6 -p1
%patch7 -p1
%patch8 -p1
%patch9 -p1
%patch10 -p1
%patch11 -p1

%Build
PKG_U_BOOT_CONFIG_TYPE=${PKG_U_BOOT_CONFIG_TYPE:-MPC8313ERDB_config}
make HOSTCC="$BUILDCC" CROSS_COMPILE=$TOOLCHAIN_PREFIX $PKG_U_BOOT_CONFIG_TYPE
make HOSTCC="$BUILDCC" HOSTSTRIP="$BUILDSTRIP" \
     CROSS_COMPILE=$TOOLCHAIN_PREFIX $PKG_U_BOOT_BUILD_ARGS all

%Install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}/boot
for i in u-boot.bin u-boot examples/vsc7385_load/vsc7385_load.bin
do
    cp $i $RPM_BUILD_ROOT/%{pfx}/boot
done
if [ -f u-boot-nand.bin ] 
then
    cp u-boot-nand.bin $RPM_BUILD_ROOT/%{pfx}/boot
fi

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*

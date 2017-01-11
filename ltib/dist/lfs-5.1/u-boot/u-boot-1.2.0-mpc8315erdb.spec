%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Universal Bootloader firmware
Name            : u-boot
Version         : 1.2.0
Release         : 20080627
License         : GPL
Vendor          : Freescale
Packager        : Olivia Yin
Group           : Applications/System
Source          : %{name}-%{version}.tar.bz2
Patch0          : u-boot-1.2.0-mpc8315erdb-pre.patch
Patch1          : u-boot-1.2.0-mpc8315erdb-soc.patch
Patch2          : u-boot-1.2.0-mpc8315erdb-PHY.patch
Patch3          : u-boot-1.2.0-mpc8315erdb-platform.patch
Patch4          : u-boot-1.2.0-mpc8315erdb-nand-controller.patch
Patch5          : u-boot-1.2.0-mpc8315erdb-nand-boot.patch
Patch6          : u-boot-1.2.0-mpc8315erdb-serdes.patch
Patch7          : u-boot-1.2.0-mpc8315erdb-pcie.patch
Patch8          : u-boot-fsl-1.3.0-MPC83xx-CW.patch
Patch9          : u-boot-1.2.0-mpc8315erdb-silicon-1.1-1.2.patch
Patch10         : u-boot-1.2.0-mpc8315erdb-extra-config-for-333-266MHz.patch
Patch11         : u-boot-1.2.0-mpc8315erdb-resume-deep-sleep.patch
Patch12         : u-boot-1.2.0-mpc8315erdb-improve-ddr-performance.patch
Patch13         : u-boot-1.2.0-mpc8315erdb-fix-PCI-IO-base.patch
Patch14		: u-boot-1.3.0-mpc83xx-rodata-str-1.patch

BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
U-Boot 1.2.0 for MPC8315 RDB board.

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
%patch12 -p1
%patch13 -p1
%patch14 -p1



%Build
PKG_U_BOOT_CONFIG_TYPE=${PKG_U_BOOT_CONFIG_TYPE:-MPC8315RDB_config}
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
if [ -f u-boot-nand.bin ] 
then
    cp u-boot-nand.bin $RPM_BUILD_ROOT/%{pfx}/boot
fi

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*

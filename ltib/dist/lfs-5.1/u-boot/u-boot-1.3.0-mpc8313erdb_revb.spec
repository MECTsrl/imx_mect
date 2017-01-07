%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Universal Bootloader firmware
Name            : u-boot
Version         : 1.3.0
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Ken Wan
Group           : Applications/System
Source          : %{name}-%{version}.tar.bz2
patch0          : u-boot-1.3.0-mpc83xx-rodata-str-1.patch
Patch1          : u-boot-fsl-1.3.0-mpc8313erdb-rev2-support.patch
Patch2          : u-boot-fsl-1.3.0-mpc8313erdb-rev2.1-support.patch
Patch3          : u-boot-fsl-1.3.0-mpc8313erdb-vsc7385-support.patch
Patch4          : u-boot-fsl-1.3.0-mpc8313erdb-fix-vitesse-7385-firmware.patch
Patch5          : u-boot-fsl-1.3.0-mpc8313erdb-nand-boot.patch
Patch6          : u-boot-fsl-1.3.0-mpc8313erdb-SGMII.patch
Patch7          : u-boot-fsl-1.3.0-mpc8313erdb-DDR-config.patch
Patch8          : u-boot-fsl-1.3.0-mpc8313erdb-performance-tuning-for-TSEC.patch
Patch9          : u-boot-fsl-1.3.0-mpc8313erdb-SPCR-fix.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
 U-Boot 1.3.0 plus Freescale patches.

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

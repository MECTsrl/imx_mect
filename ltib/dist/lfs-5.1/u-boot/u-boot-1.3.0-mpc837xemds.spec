%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Universal Bootloader firmware
Name            : u-boot
Version         : 1.3.0
Release         : 2008
License         : GPL
Vendor          : Freescale
Packager        : Olivia Yin
Group           : Applications/System
Source          : %{name}-%{version}.tar.bz2
Patch0          : u-boot-fsl-1.3.0-MPC837x-SoC.patch
Patch1          : u-boot-fsl-1.3.0-MPC837xEMDS-basic.patch
Patch2          : u-boot-fsl-1.3.0-NAND-controller.patch
Patch3          : u-boot-fsl-1.3.0-MPC837x-serdes.patch
Patch4          : u-boot-fsl-1.3.0-ext2fs-bugfix.patch
Patch5          : u-boot-fsl-1.3.0-MPC837xEMDS-SATA-controller.patch
Patch6          : u-boot-fsl-1.3.0-MPC837x-PCIE.patch
Patch7          : u-boot-fsl-1.3.0-MPC837xEMDS-eSDHC-controller.patch
Patch8          : u-boot-fsl-1.3.0-MPC837xEMDS-NAND-boot.patch
Patch9          : u-boot-fsl-1.3.0-MPC837xEMDS-PCI-PCIE-config.patch
Patch10         : u-boot-fsl-1.3.0-MPC837xEMDS-SGMII.patch
Patch11         : u-boot-fsl-1.3.0-MPC83xx-CW.patch
Patch12         : u-boot-1.3.0-mpc83xx-rodata-str-1.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
U-Boot 1.3.0-rc3 updated for MPC837xE MDS boards.

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

%Build
PKG_U_BOOT_CONFIG_TYPE=${PKG_U_BOOT_CONFIG_TYPE:-MPC837XEMDS_config}
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

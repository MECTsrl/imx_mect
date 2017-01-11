%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Universal Bootloader firmware
Name            : u-boot
Version         : 1.3.4
Release         : rc1 
License         : GPL
Vendor          : Freescale
Packager        : Olivia Yin
Group           : Applications/System
Source          : u-boot-%{version}.tar.bz2
Patch1          : u-boot-fsl-1.3.4-mpc8536ds_CPU.patch
Patch2          : u-boot-fsl-1.3.4-mpc8536ds_board.patch
Patch3          : u-boot-fsl-1.3.4-mpc8536ds_MMC.patch
Patch4          : u-boot-fsl-1.3.4-mpc8536ds_eSDHC.patch
Patch5          : u-boot-fsl-1.3.4-mpc8536ds_DDR.patch
Patch6          : u-boot-fsl-1.3.4-mpc8536ds_wakeup_on_ARP.patch
Patch7          : u-boot-fsl-1.3.4-mpc8536ds_boot_from_SD.patch
Patch8          : u-boot-fsl-1.3.4-mpc8536ds_DDR_1T.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

Open source u-boot 1.3.4  plus Freescale patches

%Prep
%setup -n %{name}-%{version}
%patch1 -p1
%patch2 -p1
%patch3 -p1
%patch4 -p1
%patch5 -p1
%patch6 -p1
%patch7 -p1
%patch8 -p1

%Build
PKG_U_BOOT_CONFIG_TYPE=${PKG_U_BOOT_CONFIG_TYPE:-MPC8536DS_config}
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

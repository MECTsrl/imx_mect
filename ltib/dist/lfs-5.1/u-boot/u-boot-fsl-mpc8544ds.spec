%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Universal Bootloader firmware
Name            : u-boot
Version         : 1.3.0
Release         : rc3
License         : GPL
Vendor          : Freescale
Packager        : Roy Zang
Group           : Applications/System
Source          : u-boot-v1.3.0.rc3.tar.gz
Patch0		: u-boot-fsl-1.2.0-FSL_PCIe_reset.patch
Patch1          : u-boot-fsl-1.2.0-MPC8544DS_2T_DDR.patch
Patch2          : u-boot-fsl-1.2.0-MPC8544DS_IO.patch
Patch3		: u-boot-fsl-1.2.0-POLL_DQ7_STATUS-2.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

Open source u-boot 1.2.0  plus Freescale patches

%Prep
%setup -n %{name}
%patch0 -p1
%patch1 -p1
%patch2 -p1
%patch3 -p1

%Build
PKG_U_BOOT_CONFIG_TYPE=${PKG_U_BOOT_CONFIG_TYPE:-MPC8544DS_config}
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

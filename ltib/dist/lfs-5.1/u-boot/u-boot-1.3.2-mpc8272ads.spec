%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Universal Bootloader firmware
Name            : u-boot
Version         : 1.3.2
Release         : fsl20080623
License         : GPL
Vendor          : Freescale
Packager        : Ken Wan
Group           : Applications/System
Source          : %{name}-%{version}.tar.bz2
patch1          : u-boot-1.3.2-mpc8272ads-rodata-str-1.patch
Patch2          : u-boot-fsl-1.3.2-mpc8272ads-Common-CFI.patch
Patch3          : u-boot-fsl-1.3.2-mpc8272ads-Fix-CIP-bit-in-HRCWH.patch
Patch4          : u-boot-fsl-1.3.2-mpc8272ads-Add-FDT-support.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

U-Boot 1.3.2 plus Freescale patches.

%Prep
%setup -n %{name}-%{version}
%patch1 -p1
%patch2 -p1
%patch3 -p1
%patch4 -p1

%Build
PKG_U_BOOT_CONFIG_TYPE=${PKG_U_BOOT_CONFIG_TYPE:-MPC8272ADS_config}
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

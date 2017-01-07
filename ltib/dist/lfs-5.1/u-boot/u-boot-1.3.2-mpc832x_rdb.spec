%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Universal Bootloader firmware
Name            : u-boot
Version         : 1.3.2
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Michael Barkowski
Group           : Applications/System
Source          : %{name}-%{version}.tar.bz2
Patch0          : u-boot-fsl-1.3.0-MPC83xx-CW.patch
Patch1          : u-boot-1.3.2-mpc8323erdb-use-readable-DDR-config-macros.patch
Patch2          : u-boot-1.3.2-mpc8323erdb-Improve-the-system-performance.patch
Patch3          : u-boot-1.3.2-mpc8323erdb-EEPROM.patch
Patch4          : u-boot-1.3.2-mpc83xx-add-h-w-flash-protection.patch
Patch5          : u-boot-1.3.2-mpc83xx-don-t-disable-autoboot.patch
Patch6          : u-boot-1.3.0-mpc83xx-rodata-str-1.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
 U-Boot 1.3.2 configured for MPC8323ERDB board.

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

%Build
PKG_U_BOOT_CONFIG_TYPE=${PKG_U_BOOT_CONFIG_TYPE:-MPC8323ERDB_config}
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

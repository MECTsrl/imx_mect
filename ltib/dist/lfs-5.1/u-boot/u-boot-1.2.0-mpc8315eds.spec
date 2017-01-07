%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Universal Bootloader firmware
Name            : u-boot
Version         : 1.2.0
Release         : 20071031
License         : GPL
Vendor          : Freescale
Packager        : P.V.Suresh
Group           : NCSG
Source          : %{name}-%{version}.tar.bz2
Patch0          : u-boot-1.2.0-mpc8315eds-pre.patch
Patch1          : u-boot-1.2.0-mpc8315eds-board.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
 U-Boot 1.2.0 configured for MPC8315E DS board.

%{summary}

All source and patches from Freescale.

%Prep
%setup -n %{name}-%{version}
%patch0 -p1
%patch1 -p1

%Build
PKG_U_BOOT_CONFIG_TYPE=${PKG_U_BOOT_CONFIG_TYPE:-MPC8315EDS_33_config}
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

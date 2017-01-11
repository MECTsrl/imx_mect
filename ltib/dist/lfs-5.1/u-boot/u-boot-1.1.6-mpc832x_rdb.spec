%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Universal Bootloader firmware
Name            : u-boot
Version         : 1.1.6
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Michael Barkowski
Group           : Applications/System
Source          : %{name}-%{version}.tar.bz2
Patch0          : u-boot-1.1.6-fsl-1-mpc83xx-20061206.patch
Patch1          : u-boot-1.1.6-fsl-1-Fix-the-UEC-driver-bug-of-QE.patch
Patch2          : u-boot-1.1.6-fsl-1-streamline-the-83xx-immr-head-file.patch
Patch3          : u-boot-1.1.6-fsl-1-Add-support-for-the-MPC832XEMDS-board.patch
Patch4          : u-boot-1.1.6-fsl-1-Add-the-MPC832XEMDS-board-readme.patch
Patch5          : u-boot-1.1.6-fsl-1-Added-MPC8323E-RDB-board-support-2.patch
Patch6          : u-boot-1.1.6-fsl-1-UEC-remove-udelay.patch
Patch7          : u-boot-1.1.6-83xx-optimizations.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
 U-Boot 1.1.6 configured for mpc8323e RDB board.
 Patch0 is based on source changes from
 http://opensource.freescale.com/pub/scm/u-boot-83xx.git (a public git repository)
 using the tree with sha1 value dd520bf314c7add4183c5191692180f576f96b60.
 This git tag is identified for this code baseline: U-Boot-1_1_6-fsl-1
 Patch 5 is new, for this board.

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

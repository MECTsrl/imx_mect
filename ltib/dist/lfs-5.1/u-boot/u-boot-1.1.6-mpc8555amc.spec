%define pfx /opt/freescale/rootfs/%{_target_cpu}
%define dversion 1.1.6
%define pkg_name u-boot


Summary         : Universal Bootloader firmware
Name            : u-boot
Version         : 1.1.6
Release         : 0
License         : GPL
Vendor          : www.denx.de + Freescale Patches
Packager        : John Traill
Group           : Applications/System
Source          : %{pkg_name}-%{dversion}.tar.bz2
Patch0          : u-boot-1.1.6-MPC8555AMC.patch
Patch1          : u-boot-1.1.6-upmconfig.patch
Patch2          : u-boot-1.1.6-boot_cmd.patch
Patch3          : u-boot-1.1.6-spd_sdram.patch
Patch4          : u-boot-1.1.6-tsec.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup -n %{pkg_name}-%{dversion}
%patch0 -p1
%patch1 -p1
%patch2 -p1
%patch3 -p1
%patch4 -p1

%Build
PKG_U_BOOT_CONFIG_TYPE=${PKG_U_BOOT_CONFIG_TYPE:-MPC8555AMC_config}
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

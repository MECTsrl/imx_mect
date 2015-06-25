%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : imx233/imx28-style boot stream image creation
Name            : imx-bootlets-src
Version         : 11.01.00
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Terry Lv
Group           : Tools
Source          : %{name}-%{version}.tar.gz
Patch1          : imx-bootlets-src-11.01.00-1315841439.patch
Patch2          : imx-bootlets-src-11.01.00-1332172356.patch
Patch3          : imx-bootlets-src-11.01.00-1337962710.patch
Patch4          : imx-bootlets-src-11.01.00-1412693346.patch
Patch5          : imx-bootlets-src-11.01.00-1418123773.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}


# patch1 imx-bootlets-src-11.01.00-1315841439.patch: modify the boot arguments in order to boot from flash instead of memory card.
# patch2 imx-bootlets-src-11.01.00-1332172356.patch: modify power prep to not use battery for boot but to keep battery values updated in the battmonitor register.
# patch3 : modifies boot_stream preparation to write results in a diffrent directory based on the current selected kernel
# patch4: modifies boot_stream to drive the GPMI nand flash by ref_gpmi and not ref_xtal
%Description
%{summary}

%Prep
%setup
%patch1 -p1
%patch2 -p1
%patch3 -p1
%patch4 -p1
%patch5 -p1

%Build
. %{_builddir}/../../config/platform/imx/.config
if [ "x$CONFIG_KERNEL_35_IPIPE" = "xy" ]; then
	CURR_KERN_VER="_ipipe"
else
	CURR_KERN_VER=""

fi
export CURR_KERN_VER

export CMDLINE1="$PKG_BOOT_STREAM_CMDLINE1"
export CMDLINE2="$PKG_BOOT_STREAM_CMDLINE2"
export CMDLINE3="$PKG_BOOT_STREAM_CMDLINE3"
export CMDLINE4="$PKG_BOOT_STREAM_CMDLINE4"

PLATFORMSHORTNAME=`echo $PLATFORM | sed "s,imx\([0-9]*\).*,MX\1,g"`
if [ "x$PLATFORMSHORTNAME" = "xMX233" ]
then
    make -j1 MEM_TYPE="${PKG_BOOT_STREAM_MEMTYPE_PRECONFIG}"
else
    make -j1 MEM_TYPE="${PKG_BOOT_STREAM_MEMTYPE_PRECONFIG}" BOARD=iMX28_EVK
fi

%Install
rm -rf $RPM_BUILD_ROOT

. %{_builddir}/../../config/platform/imx/.config
if [ "x$CONFIG_KERNEL_35_IPIPE" = "xy" ]; then
	CURR_KERN_VER="_ipipe"
else
	CURR_KERN_VER=""

fi

mkdir -p $RPM_BUILD_ROOT/%{pfx}/boot$CURR_KERN_VER
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}/boot$CURR_KERN_VER

%Clean
rm -rf $RPM_BUILD_ROOT
make clean

%Files
%defattr(-,root,root)
%{pfx}/*

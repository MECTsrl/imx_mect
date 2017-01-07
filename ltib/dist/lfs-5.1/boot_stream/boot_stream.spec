%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : imx233/imx28-style boot stream image creation
Name            : imx-bootlets-src
Version         : 2.6.35.3
Release         : 1.1.0
License         : GPL
Vendor          : Freescale
Packager        : Terry Lv
Group           : Tools
Source1         : updater_ivt.sb
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package mfg
Summary         : Trimmed imx-bootlets-src for manufacturing tool requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Tools
AutoReqProv     : no

%Description mfg
imx-bootlets-src package contents restricted to the files
needed to program the target.


# patch1 imx-bootlets-src-11.01.00-1315841439.patch: modify the boot arguments in order to boot from flash instead of memory card.
# patch2 imx-bootlets-src-11.01.00-1332172356.patch: modify power prep to not use battery for boot but to keep battery values updated in the battmonitor register.
# patch3 : modifies boot_stream preparation to write results in a diffrent directory based on the current selected kernel
# patch4: modifies boot_stream to drive the GPMI nand flash by ref_gpmi and not ref_xtal
%Description
%{summary}


%Prep
export LC_ALL
LC_ALL=C

%setup -T -c -n %{name}
cd ..; rmdir %{name}; ln -s ../../../projects/%{name} %{name}


%Build
export LC_ALL
LC_ALL=C

export CMDLINE1="$PKG_BOOT_STREAM_CMDLINE1"
export CMDLINE2="$PKG_BOOT_STREAM_CMDLINE2"
export CMDLINE3="$PKG_BOOT_STREAM_CMDLINE3"
export CMDLINE4="$PKG_BOOT_STREAM_CMDLINE4"

PLATFORMSHORTNAME=`echo $PLATFORM | sed "s,imx\([0-9]*\).*,MX\1,g"`
if test "$PLATFORMSHORTNAME" = "MX233"; then
    make -j1 MEM_TYPE="${PKG_BOOT_STREAM_MEMTYPE_PRECONFIG}"
else
    make -j1 MEM_TYPE="${PKG_BOOT_STREAM_MEMTYPE_PRECONFIG}" BOARD=iMX28_EVK
fi


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}/boot
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}/boot

install -m 644 %{SOURCE1} $RPM_BUILD_ROOT/%{pfx}/boot


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make clean


%Files
%defattr(-,root,root)
%{pfx}/*

%Files mfg
%defattr(-,root,root)
%{pfx}/boot/imx28_ivt_linux.sb
%{pfx}/boot/updater_ivt.sb

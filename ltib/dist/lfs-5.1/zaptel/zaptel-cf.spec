%define base %(echo %{_prefix} | sed -e s,/usr.*$,,)
%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : zaptel drivers and utilities
Name            : zaptel
Version         : 1.4.12.1
Release         : 1
License         : GPL
Vendor          : Digium/SDCS
Packager        : Vadim Lebedev at mbdsys dot com
Group           : Applications/Communication
Source          : %{name}-%{version}.tar.gz
Source1         : zaptel_rpm_devices.tmpl
Patch1          : zaptel-1.4.12.1-m68k-1.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup
%patch1 -p1

%Build
ORIG_PATH=$PATH
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
export PATH=$UNSPOOF_PATH

PKG_ZAPTEL_PRECONFIG=${PKG_ZAPTEL_PRECONFIG:-zaptel.menuselect.makeopts}
if [ -f "$PLATFORM_PATH/${PKG_ZAPTEL_PRECONFIG}" ]
then
    cp $PLATFORM_PATH/$PKG_ZAPTEL_PRECONFIG menuselect.makeopts
else
    if [ -f "$CONFIG_DIR/defaults/$PKG_ZAPTEL_PRECONFIG" ]
    then
        cp "$CONFIG_DIR/defaults/$PKG_ZAPTEL_PRECONFIG"  menuselect.makeopts
    fi
fi
if [ -n "$PKG_ZAPTEL_WANT_CF" -o -n "$SCB_WANT_CF" ]
then
    make menuconfig HOSTCC='/usr/bin/gcc' HOSTCFLAGS='-B/usr/bin' HOSTLDFLAGS="-B/usr/bin" HOSTLD=/usr/bin/ld HOSTAR=/usr/bin/ar 
    cp menuselect.makeopts $PLATFORM_PATH/$PKG_ZAPTEL_PRECONFIG
fi

if [ ! -f menuselect.makeopts ]; then
    cd menuselect && CC="$BUILDCC" ./configure && make
fi
export PATH=$ORIG_PATH

KSRC_DIR=${PKG_KERNEL_PATH_PRECONFIG:-$RPM_BUILD_DIR/linux}
KBOUT="$(eval echo $PKG_KERNEL_KBUILD_PRECONFIG)"
KBOUT=${KBOUT:-$KSRC_DIR}
if grep -q 'CONFIG_PPC_MERGE=y' $KBOUT/.config
then
    LINTARCH=powerpc
fi
if grep -q 'CONFIG_M68K=y' $KBOUT/.config
then
    LINTARCH=m68k
fi
if [ ! -f $KBOUT/.config ]
then
    cat <<TXT
You need a built unpacked kernel source tree in:
$KBOUT
to build kernel modules
TXT
    exit 1
fi

if [ -f $KBOUT/include/config/kernel.release ]
then
    KVER=`cat $KBOUT/include/config/kernel.release`
else
    KVER="`perl -e '$/ = ""; $_ = <>; m,VERSION\s*=\s*(\d)\s*PATCHLEVEL\s*=\s*(\d+)\s*SUBLEVEL\s*=\s*(\d+)\s*EXTRAVERSION[ \t]*=[ \t]*(\S*),m; print  "$1.$2.$3$4"' $KSRC_DIR/Makefile`"
fi


make  HOSTCC='/usr/bin/gcc' HOSTCFLAGS='-B/usr/bin' HOSTLDFLAGS="-B/usr/bin" HOSTLD=/usr/bin/ld HOSTAR=/usr/bin/ar KSRC=$KSRC_DIR KVERS=$KVER ARCH=$LINTARCH DEB_HOST_GNU_TYPE=$LINTARCH

%Install
KSRC_DIR=${PKG_KERNEL_PATH_PRECONFIG:-$RPM_BUILD_DIR/linux}
KBOUT="$(eval echo $PKG_KERNEL_KBUILD_PRECONFIG)"
KBOUT=${KBOUT:-$KSRC_DIR}
if grep -q 'CONFIG_PPC_MERGE=y' $KBOUT/.config
then
    LINTARCH=powerpc
fi
if grep -q 'CONFIG_M68K=y' $KBOUT/.config
then
    LINTARCH=m68k
fi
if [ ! -f $KBOUT/.config ]
then
    cat <<TXT
You need a built unpacked kernel source tree in:
$KBOUT
to build kernel modules
TXT
    exit 1
fi

if [ -f $KBOUT/include/config/kernel.release ]
then
    KVER=`cat $KBOUT/include/config/kernel.release`
else
    KVER="`perl -e '$/ = ""; $_ = <>; m,VERSION\s*=\s*(\d)\s*PATCHLEVEL\s*=\s*(\d+)\s*SUBLEVEL\s*=\s*(\d+)\s*EXTRAVERSION[ \t]*=[ \t]*(\S*),m; print  "$1.$2.$3$4"' $KSRC_DIR/Makefile`"
fi

rm -rf $RPM_BUILD_ROOT
make modules ARCH=$LINTARCH DESTDIR=$RPM_BUILD_ROOT/%{pfx} HOSTCC='/usr/bin/gcc' HOSTCFLAGS='-B/usr/bin' HOSTLDFLAGS="-B/usr/bin" HOSTLD=/usr/bin/ld HOSTAR=/usr/bin/ar KSRC=$KSRC_DIR KVERS=$KVER DEB_HOST_GNU_TYPE=$LINTARCH

make install-modules install-programs ARCH=$LINTARCH DESTDIR=$RPM_BUILD_ROOT/%{pfx} HOSTCC='/usr/bin/gcc' HOSTCFLAGS='-B/usr/bin' HOSTLDFLAGS="-B/usr/bin" HOSTLD=/usr/bin/ld HOSTAR=/usr/bin/ar KSRC=$KSRC_DIR KVERS=$KVER DEB_HOST_GNU_TYPE=$LINTARCH

# zaptel.conf
cat <<EOF > $RPM_BUILD_ROOT/%{pfx}/etc/zaptel.conf
loadzone = us
defaultzone = us
fxsks = 2
fxoks = 1
EOF


# create the rpm style device nodes
perl -p -e 's,/pfx,/%{pfx},g' %{SOURCE1} > /tmp/rpm_devices


%Clean
rm -rf $RPM_BUILD_ROOT

%Files -f /tmp/rpm_devices
%defattr(-,root,root)
%{pfx}/*

%changelog
* Wed Jul 16 2008 Vadim Lebedev <vadim@mbdsys.com>
- Initial version

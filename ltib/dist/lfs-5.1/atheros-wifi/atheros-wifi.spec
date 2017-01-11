%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Atheros wifi driver source code
Name            : atheros-wifi
Version         : 2.6.35.3
Release         : 1.1.0
License         : GPL
Vendor          : ATHEROS
Packager        : Lily Zhang
Group           : System/Servers
Source          : %{name}-%{version}-%{release}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
This package provides atheros wifi driver.

%{summary}

%Prep
%setup -n %{name}-%{version}-%{release}

%Build
# build the libraries and kernel modules
if [ -z "$PKG_KERNEL_KBUILD_PRECONFIG" ]
then
      KERNELDIR="$PWD/../linux"
      KBUILD_OUTPUT="$PWD/../linux"
else
      KERNELDIR="$PKG_KERNEL_PATH_PRECONFIG"
      KBUILD_OUTPUT="$(eval echo ${PKG_KERNEL_KBUILD_PRECONFIG})"
fi

export CROSS_COMPILE=$TOOLCHAIN_PREFIX
cd 2.2.1.83/AR6K_ANDROID_SDK.2.2.1.83/host
./comp.sh 1 $KERNELDIR

%Install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}

KERNEL_VER=`perl -e '
    foreach  ( glob("$ENV{DEV_IMAGE}/lib/modules/*") ) {
        next unless -d $_;
        if( m,/lib/modules/(\d\.\d[\S]+), ) {
            print $1;
            last;
        }
    } '`

cd 2.2.1.83/AR6K_ANDROID_SDK.2.2.1.83/host
./comp.sh 4 $RPM_BUILD_ROOT/%{pfx} $KERNEL_VER

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(755,root,root)
%{pfx}/*

%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : platform specific libraries for imx platform
Name            : imx-lib
Version         : 2.6.35.3
Release         : 1.1.0
License         : LGPL
Vendor          : Freescale
Packager        : Rob Herring
Group           : Test
Source		: %{name}-%{version}-%{release}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup -n %{name}-%{version}-%{release}

%Build
if [ -z "$PKG_KERNEL_KBUILD_PRECONFIG" ]
then
      KERNELDIR="$PWD/../linux"
      KBUILD_OUTPUT="$PWD/../linux"
else
      KERNELDIR="$PKG_KERNEL_PATH_PRECONFIG"
      KBUILD_OUTPUT="$(eval echo ${PKG_KERNEL_KBUILD_PRECONFIG})"
fi

if [ -n "$IMX_LIB_DIR" ]
then
	cd $IMX_LIB_DIR
fi

PLATFORM_UPPER="$(echo $PLATFORM | awk '{print toupper($0)}')"

# Build libraries
INCLUDE="-I$DEV_IMAGE/usr/src/linux/include \
-I$KERNELDIR/drivers/mxc/security/rng/include \
-I$KERNELDIR/drivers/mxc/security/sahara2/include"
make -j1 PLATFORM=$PLATFORM_UPPER INCLUDE="$INCLUDE" all

%Install
if [ -z "$PKG_KERNEL_KBUILD_PRECONFIG" ]
then
      KERNELDIR="$PWD/../linux"
      KBUILD_OUTPUT="$PWD/../linux"
else
      KERNELDIR="$PKG_KERNEL_PATH_PRECONFIG"
      KBUILD_OUTPUT="$(eval echo ${PKG_KERNEL_KBUILD_PRECONFIG})"
fi

rm -rf $RPM_BUILD_ROOT

if [ -n "$IMX_LIB_DIR" ]
then
	cd $IMX_LIB_DIR
fi

# install libraries and headers
PLATFORM_UPPER="$(echo $PLATFORM | awk '{print toupper($0)}')"
make PLATFORM=$PLATFORM_UPPER DEST_DIR=$RPM_BUILD_ROOT/%{pfx} install

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(755,root,root)
%{pfx}/*

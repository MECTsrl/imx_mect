%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : platform specific unit tests for mxc platform
Name            : imx-test
Version         : 11.01.00
Release         : 1
License         : GPL/Other
Vendor          : Freescale
Packager        : Rob Herring
Group           : Test
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed imx-test for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Test
AutoReqProv     : no

%Description rfs
imx-test package contents restricted to just the files that are
needed at run time on the target.


%Description
%{summary}

%Prep
export LC_ALL
LC_ALL=C

%setup

%Build
export LC_ALL
LC_ALL=C

if [ -z "$PKG_KERNEL_KBUILD_PRECONFIG" ]
then
      KERNELDIR="$PWD/../linux"
      KBUILD_OUTPUT="$PWD/../linux"
else
      KERNELDIR="$PKG_KERNEL_PATH_PRECONFIG"
      KBUILD_OUTPUT="$(eval echo ${PKG_KERNEL_KBUILD_PRECONFIG})"
fi

if [ -n "$IMX_TEST_DIR" ]
then
	cd $IMX_TEST_DIR
fi

PLATFORM_UPPER="$(echo $PLATFORM | awk '{print toupper($0)}')"

# Build modules
make -C module_test KBUILD_OUTPUT=$KBUILD_OUTPUT LINUXPATH=$KERNELDIR

# Build test apps
INCLUDE="-I$DEV_IMAGE/usr/src/linux/include \
-I$KERNELDIR/drivers/mxc/security/rng/include \
-I$KERNELDIR/drivers/mxc/security/sahara2/include"
make -j1 PLATFORM=$PLATFORM_UPPER INCLUDE="$INCLUDE" test

%Install
export LC_ALL
LC_ALL=C

if [ -z "$PKG_KERNEL_KBUILD_PRECONFIG" ]
then
      KERNELDIR="$PWD/../linux"
      KBUILD_OUTPUT="$PWD/../linux"
else
      KERNELDIR="$PKG_KERNEL_PATH_PRECONFIG"
      KBUILD_OUTPUT="$(eval echo ${PKG_KERNEL_KBUILD_PRECONFIG})"
fi

rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}/unit_tests

if [ -n "$IMX_TEST_DIR" ]
then
	cd $IMX_TEST_DIR
fi

# install modules
make -C module_test -j1 LINUXPATH=$KERNELDIR KBUILD_OUTPUT=$KBUILD_OUTPUT \
       DEPMOD=/bin/true INSTALL_MOD_PATH=$RPM_BUILD_ROOT/%{pfx} install

PLATFORM_UPPER="$(echo $PLATFORM | awk '{print toupper($0)}')"
make PLATFORM=$PLATFORM_UPPER DESTDIR=$RPM_BUILD_ROOT/%{pfx}/unit_tests install

cd %{_builddir}/%{name}-%{version}
( cd $RPM_BUILD_ROOT > /dev/null; find .%{pfx} \( \( -not -type d \) -o \( -type d -empty \) \) -print | sed 's/^\.//' ) > all_files.lst
sed -n '
    p
' all_files.lst > rfs_files.lst

%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files -f all_files.lst
%defattr(-,root,root)

%Files rfs -f rfs_files.lst
%defattr(-,root,root)

%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : MBX 3D driver and app
Name            : mbx-src
Version         : 2.6.35.3
Release         : 1.1.0
License         : Proprietary
Vendor          : Freescale
Packager        : Yi Li
Group           : System/Servers
Source          : %{name}-%{version}-%{release}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
This package provides proprietary kernel modules, libraries, and
test code source from the MBX OpenGL ES (GX200) DDK. The Linux OpenGL ES
DDK implements OpenGL-ES for MBX and variants along with 2D acceleration
via MBX within the Linux operating system. The target kernel version for
the DDK is Linux 2.6. The OpenGL-ES driver is ported from the reference
OpenGL-ES for MBX and variants. Hardware 2D acceleration is achieved
implementing the freedesktop.org KDrive X server in terms of the PVR2D
loadable module for MBX.

%{summary}

%Prep
%setup -n %{name}-%{version}-%{release}

%Build
export MBX_HOME=$PWD/MBX_OGLES_OVG_DDK_for_Linux_3_5_RC1
if [ -z "$PKG_KERNEL_KBUILD_PRECONFIG" ]
then
      export MBXKBUILDOUTPUT=$PWD/../linux
      export KERNELDIR=$PWD/../linux
      export KERNELINCDIR=$DEV_IMAGE/usr/src/linux
      export KERNELINCDIR=$KERNELDIR
else
      export KERNELDIR=$PKG_KERNEL_PATH_PRECONFIG
      MBXKBUILDOUTPUT="$(eval echo ${PKG_KERNEL_KBUILD_PRECONFIG})"
      export MBXKBUILDOUTPUT=${MBXKBUILDOUTPUT}
      export KERNELINCDIR=$DEV_IMAGE/usr/src/linux
fi

export PVR_CONSUMER_ROOT=${MBX_HOME}/embedded

# build the libraries, kernel modules and tests
cd $PVR_CONSUMER_ROOT/build/arm_mbxlite_linux
make -j1

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

mkdir -p $RPM_BUILD_ROOT/%{pfx}/lib/modules/$KERNEL_VER

cd $PWD/MBX_OGLES_OVG_DDK_for_Linux_3_5_RC1/embedded/binary_arm_mbxlite_linux_release
./install.sh -v --no-x --root $RPM_BUILD_ROOT/%{pfx}

# Package up the build results and leave in rpm/SOURCES for mbx-bin spec file
mkdir mbx-bin-%{version}
mv $RPM_BUILD_ROOT/%{pfx}/* mbx-bin-%{version}
tar -zcf mbx-bin-%{version}.tar.gz mbx-bin-%{version}
# todo fix this to use rpmdir or something better than TOP:
cp -f mbx-bin-%{version}.tar.gz $TOP/rpm/RPMS/"$LINTARCH"
cp -f mbx-bin-%{version}.tar.gz $TOP/rpm/SOURCES

# Now delete everything we just tarred up.  mbx-bin spec file will install it.
rm -rf $RPM_BUILD_ROOT/%{pfx}
# Create an empty directory for rpm to have something install or it won't be happy.
mkdir -p $RPM_BUILD_ROOT/%{pfx}/etc

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(755,root,root)
%{pfx}/*

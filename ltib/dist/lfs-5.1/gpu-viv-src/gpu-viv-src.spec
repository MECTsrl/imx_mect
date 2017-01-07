%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : GPU on imx6q that supports OpenGLES and OpenVG
Name            : gpu-viv-src
Version         : 2.6.35.3
Release         : 1.1.0
License         : Proprietary
Vendor          : Vivante
Packager        : Richard Zhao
Group           : Development/Libraries
Source          : %{name}-%{version}-%{release}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup -n %{name}-%{version}-%{release}

%Build
CROSS_COMPILE=${TOOLCHAIN_PREFIX}
export DFB_DIR=$DEV_IMAGE/usr
export ROOTFS_USR=${DEFPFX}/usr/ubuntu_arm_lib
cd driver
./driver_build_sample.sh clean
rm -Rf ../driver-x11
cp -r ../driver ../driver-x11
cp -r ../driver ../driver-dfb
./driver_build_sample.sh
export X11_ARM_DIR=${DEFPFX}/usr/ubuntu_arm_lib
export ROOTFS_USR=
cd ../driver-x11
./driver_build_sample_x11.sh
unset X11_ARM_DIR

export BUILD_OPTION_EGL_API_FB=0
export EGL_API_DFB=1
cd ../driver-dfb
./driver_build_sample.sh
unset EGL_API_DFB
unset BUILD_OPTION_EGL_API_FB

export X11_ARM_DIR=
export DFB_DIR=
cd ../test
./test_build_sample.sh clean
#rm -Rf ../test-x11
#cp -r ../test ../test-x11
./test_build_sample.sh
#export X11_ARM_DIR=$DEV_IMAGE/usr
#cd ../test-x11
#./test_build_sample_x11.sh
#export X11_ARM_DIR=

%Install
SOC=$(echo $PLATFORM | cut -d_ -f1 | cut -c2-)
OUTPUT_PKG="gpu-viv-bin-$SOC-%{version}"

rm -rf $RPM_BUILD_ROOT
install -d $RPM_BUILD_ROOT/%{pfx}
install -d $RPM_BUILD_ROOT/%{pfx}/usr/lib
install -d $RPM_BUILD_ROOT/%{pfx}/usr/lib/directfb-1.4-0
install -d $RPM_BUILD_ROOT/%{pfx}/usr/lib/directfb-1.4-0/gfxdrivers

cp -raf driver/build/sdk/drivers/* $RPM_BUILD_ROOT/%{pfx}/usr/lib
mv $RPM_BUILD_ROOT/%{pfx}/usr/lib/libEGL.so $RPM_BUILD_ROOT/%{pfx}/usr/lib/libEGL-fb.so
mv $RPM_BUILD_ROOT/%{pfx}/usr/lib/libGAL.so $RPM_BUILD_ROOT/%{pfx}/usr/lib/libGAL-fb.so
mv $RPM_BUILD_ROOT/%{pfx}/usr/lib/libVIVANTE.so $RPM_BUILD_ROOT/%{pfx}/usr/lib/libVIVANTE-fb.so
cp -af driver-x11/build/sdk/drivers/libEGL.so $RPM_BUILD_ROOT/%{pfx}/usr/lib/libEGL-x11.so
cp -af driver-x11/build/sdk/drivers/libGAL.so $RPM_BUILD_ROOT/%{pfx}/usr/lib/libGAL-x11.so
cp -af driver-x11/build/sdk/drivers/libVIVANTE.so $RPM_BUILD_ROOT/%{pfx}/usr/lib/libVIVANTE-x11.so
cp -af driver-dfb/build/sdk/drivers/libEGL.so $RPM_BUILD_ROOT/%{pfx}/usr/lib/libEGL-dfb.so
cp -af driver-dfb/build/sdk/drivers/libGAL.so $RPM_BUILD_ROOT/%{pfx}/usr/lib/libGAL-dfb.so
cp -af driver-dfb/build/sdk/drivers/libVIVANTE.so $RPM_BUILD_ROOT/%{pfx}/usr/lib/libVIVANTE-dfb.so
(cd $RPM_BUILD_ROOT/%{pfx}/usr/lib/; ln -s libEGL-fb.so libEGL.so)
(cd $RPM_BUILD_ROOT/%{pfx}/usr/lib/; ln -s libGAL-fb.so libGAL.so)
(cd $RPM_BUILD_ROOT/%{pfx}/usr/lib/; ln -s libVIVANTE-fb.so libVIVANTE.so)
mv $RPM_BUILD_ROOT/%{pfx}/usr/lib/libdirectfb_gal.so \
   $RPM_BUILD_ROOT/%{pfx}/usr/lib/directfb-1.4-0/gfxdrivers/

install -d $RPM_BUILD_ROOT/%{pfx}/opt/viv_samples
cp -af test/build/sdk/samples/* $RPM_BUILD_ROOT/%{pfx}/opt/viv_samples/
#install -d $RPM_BUILD_ROOT/%{pfx}/opt/viv_samples-x11
#cp -af driver-x11/build/sdk/samples/* $RPM_BUILD_ROOT/%{pfx}/opt/viv_samples-x11/
#cp -af test-x11/build/sdk/samples/* $RPM_BUILD_ROOT/%{pfx}/opt/viv_samples-x11/

install -d $RPM_BUILD_ROOT/%{pfx}/usr/include/
cp -af driver/build/sdk/include/* $RPM_BUILD_ROOT/%{pfx}/usr/include

# Package up the build results and leave in rpm/SOURCES
rm -rf $OUTPUT_PKG
install -d $OUTPUT_PKG
mv $RPM_BUILD_ROOT/%{pfx}/* $OUTPUT_PKG
tar -zcf $OUTPUT_PKG.tar.gz $OUTPUT_PKG
# todo fix this to use rpmdir or something better than TOP:
install $OUTPUT_PKG.tar.gz $TOP/rpm/RPMS/"$LINTARCH"
install $OUTPUT_PKG.tar.gz $TOP/rpm/SOURCES

# Now delete everything we just tarred up.
rm -rf $RPM_BUILD_ROOT/%{pfx}
# Create an empty directory for rpm to have something install or it won't be happy.
install -d $RPM_BUILD_ROOT/%{pfx}/usr

%Clean
rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

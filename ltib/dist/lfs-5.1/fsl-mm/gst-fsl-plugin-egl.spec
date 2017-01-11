%define pfx /opt/freescale/rootfs/%{_target_cpu}
Summary         : Gstreamer Freescale EGL Plugin
Name            : gst-fsl-plugin-EGL
Version         : 2.0.10
Release         : 1
License         : LGPL
Vendor          : Freescale Semiconductor
Packager        : Sario Hu
Group           : Applications/System
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build
export PKG_CONFIG="`which pkg-config` --static "
PLATFORMSHORTNAME=`echo $PLATFORM | sed "s,imx\([0-9]*\).*,MX\1,g"`
if [ "x$PLATFORMSHORTNAME" = "xMX27" ]
then
export FBHEADER_PATH=$DEV_IMAGE/usr/src/linux/include/asm-arm/arch-mxc
else
export FBHEADER_PATH=$DEV_IMAGE/usr/src/linux/include/
fi

export CORE_CODEC_INC_PATH=$DEV_IMAGE/usr/include/mm_ghdr
export CORE_PARSER_INC_PATH=$DEV_IMAGE/usr/include/mm_ghdr
export CORE_CODEC_LIB_PATH=$DEV_IMAGE/usr/lib/
export CORE_PARSER_LIB_PATH=$DEV_IMAGE/usr/lib/


#./autogen.sh
./configure --prefix=%{_prefix} --host=$CFGHOST \
	    --build=%{_build} NM=nm \
	    PLATFORM=`echo $PLATFORM | sed "s,imx\([0-9]*\).*,MX\1,g"`\
        BUILDER=LTIB\
        VERSION=%{version} PACKAGE=gst-fsl-plugin
make PLATFORM=`echo $PLATFORM | sed "s,imx\([0-9]*\).*,MX\1,g"` BUILDER=LTIB

%Install
rm -rf $RPM_BUILD_ROOT

make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}/
find $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/ -name "*.la" | xargs rm -f
find $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/ -name "*.a" | xargs rm -f

rm -rf $DEV_IMAGE/usr/include/mm_ghdr
rm -rf $DEV_IMAGE/usr/lib/pkgconfig/fsl-mm-core.pc

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*

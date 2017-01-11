%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : DirectFB is a graphics library for embedded systems
Name            : DirectFB
Version         : 1.4.0
Release         : 1
License         : LGPL
Vendor          : Freescale
Packager        : WMSG
Group           : System Environment/Base
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build
OPT_CFGHOST=`echo ${TOOLCHAIN_PREFIX} | perl -n -e 's,-$,,;print'`
#KHDR_DIR=$DEV_IMAGE/usr/src/linux/include

export FREETYPE_CONFIG=${DEV_IMAGE}/usr/bin/freetype-config
export FREETYPE_CFLAGS="`${FREETYPE_CONFIG} --prefix=${DEV_IMAGE}/%{_prefix} --cflags`"
export FREETYPE_LIBS="`${FREETYPE_CONFIG} --prefix=${DEV_IMAGE}/%{_prefix} --libs`"

export LIBPNG_CONFIG=${DEV_IMAGE}/%{_prefix}/bin/libpng-config
export PKG_CONFIG_PATH=${DEV_IMAGE}/%{_prefix}/lib/pkgconfig

if [ -n "$PKG_DIRECTFB_WANT_TS" ]
then
    TSOPTS="--with-inputdrivers=tslib,keyboard,linuxinput"
else 
    TSOPTS="--with-inputdrivers=keyboard,ps2mouse,linuxinput"
fi
./configure --enable-shared --host=${OPT_CFGHOST} --target=${OPT_CFGHOST}	\
		--prefix=%{_prefix} --libdir="%{_prefix}/lib" --includedir="%{_prefix}/include"	\
		--build=%{_build}	\
		LIBS="-lz"	\
		--disable-x11 --disable-voodoo --disable-mmx --disable-see	\
		--disable-sdl --enable-jpeg --enable-zlib --enable-png	\
		--enable-gif --enable-freetype --enable-video4linux	\
		--enable-video4linux2 --with-gfxdrivers=none --enable-fbdev=yes	\
		--disable-devmem --enable-multi=no $TSOPTS

make

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
find $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib -name \*.la | xargs rm -f

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*

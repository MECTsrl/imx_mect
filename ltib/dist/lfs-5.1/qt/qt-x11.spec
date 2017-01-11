%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Qt
Name            : qt-everywhere-opensource-src
Version         : 4.6.0
Release         : 0
License         : GNU GPL
Vendor          : Freescale
Packager        : Rogerio Pimentel
Group           : System Environment/Libraries
Source          : %{name}-%{version}.tar.gz
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
URL             : http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.6.0.tar.gz

%Description
%{summary}

%Prep
%setup

#Checking what packages are available

XTRA_OPTS=""
XTRA_OPTS_CONFIG=""

if [ -n "$PKG_QT_PHONON" ]
then
    XTRA_OPTS="$XTRA_OPTS -multimedia -phonon -phonon-backend -lgstreamer-0.10"
    XTRA_OPTS_CONFIG="$XTRA_OPTS_CONFIG -lgstreamer-0.10 -lxml2 -lasound"
fi

#if PKG_AMD_GPU_X11_BIN_MX51 is already installed, uncomment the following line to add OpenGLES 2 support
XTRA_OPTS_CONFIG="$XTRA_OPTS_CONFIG -lgsl -lEGL -lgsl -lc2d -lpanel2"

#if PKG_MBX_BIN is already installed, uncomment the following line to add OpenGLES 1.1 support
#XTRA_OPTS_CONFIG="$XTRA_OPTS_CONFIG -lgsl -lEGL"

#Creating mkspec

mkdir mkspecs/linux-g++-mx
initscript=mkspecs/linux-g++-mx/qmake.conf
cat > $initscript << EOF
#
# qmake configuration for building with arm-none-linux-gnueabi-g++
#

QMAKE_CC		= arm-none-linux-gnueabi-gcc
QMAKE_CFLAGS		+= -pipe
QMAKE_CFLAGS_DEPS	+= -M
QMAKE_CFLAGS_WARN_ON	+= -Wall -W
QMAKE_CFLAGS_WARN_OFF	+= -w
QMAKE_CFLAGS_RELEASE	+= -O2
QMAKE_CFLAGS_DEBUG	+= -g
QMAKE_CFLAGS_SHLIB	+= -fPIC
QMAKE_CFLAGS_STATIC_LIB	+= -fPIC
QMAKE_CFLAGS_YACC	+= -Wno-unused -Wno-parentheses
QMAKE_CFLAGS_HIDESYMS   += -fvisibility=hidden
QMAKE_CFLAGS_PRECOMPILE += -x c-header -c \${QMAKE_PCH_INPUT} -o \${QMAKE_PCH_OUTPUT}
QMAKE_CFLAGS_USE_PRECOMPILE += -include \${QMAKE_PCH_OUTPUT_BASE}

QMAKE_CXX		= arm-none-linux-gnueabi-g++
QMAKE_CXXFLAGS		+= \$\$QMAKE_CFLAGS"
QMAKE_CXXFLAGS_DEPS	+= \$\$QMAKE_CFLAGS_DEPS
QMAKE_CXXFLAGS_WARN_ON	+= \$\$QMAKE_CFLAGS_WARN_ON
QMAKE_CXXFLAGS_WARN_OFF	+= \$\$QMAKE_CFLAGS_WARN_OFF
QMAKE_CXXFLAGS_RELEASE	+= \$\$QMAKE_CFLAGS_RELEASE
QMAKE_CXXFLAGS_DEBUG	+= \$\$QMAKE_CFLAGS_DEBUG
QMAKE_CXXFLAGS_SHLIB	+= \$\$QMAKE_CFLAGS_SHLIB
QMAKE_CXXFLAGS_STATIC_LIB += \$\$QMAKE_CFLAGS_STATIC_LIB
QMAKE_CXXFLAGS_YACC	+= \$\$QMAKE_CFLAGS_YACC
QMAKE_CXXFLAGS_HIDESYMS += \$\$QMAKE_CFLAGS_HIDESYMS -fvisibility-inlines-hidden
QMAKE_CXXFLAGS_PRECOMPILE += -x c++-header -c \${QMAKE_PCH_INPUT} -o \${QMAKE_PCH_OUTPUT}
QMAKE_CXXFLAGS_USE_PRECOMPILE = \$\$QMAKE_CFLAGS_USE_PRECOMPILE

QMAKE_LINK		= arm-none-linux-gnueabi-g++
QMAKE_LINK_SHLIB	= arm-none-linux-gnueabi-g++
QMAKE_LINK_C		= arm-none-linux-gnueabi-gcc
QMAKE_LINK_C_SHLIB	= arm-none-linux-gnueabi-gcc
QMAKE_LFLAGS		+=
QMAKE_LFLAGS_RELEASE	+= -Wl,-O1
QMAKE_LFLAGS_DEBUG	+=
QMAKE_LFLAGS_APP	+=
QMAKE_LFLAGS_SHLIB	+= -shared
QMAKE_LFLAGS_PLUGIN	+= \$\$QMAKE_LFLAGS_SHLIB
QMAKE_LFLAGS_SONAME	+= -Wl,-soname,
QMAKE_LFLAGS_THREAD	+=
QMAKE_LFLAGS_NOUNDEF	+= -Wl,--no-undefined
QMAKE_RPATH		= -Wl,-rpath,

QMAKE_PCH_OUTPUT_EXT    = .gch

# -Bsymbolic-functions (ld) support
QMAKE_LFLAGS_BSYMBOLIC_FUNC = -Wl,-Bsymbolic-functions
QMAKE_LFLAGS_DYNAMIC_LIST = -Wl,--dynamic-list,

QMAKE_CFLAGS_THREAD	+= -D_REENTRANT
QMAKE_CXXFLAGS_THREAD	+= \$\$QMAKE_CFLAGS_THREAD

QMAKE_INCDIR          = $RPM_BUILD_DIR/../../rootfs/usr/include $RPM_BUILD_DIR/../../rootfs/usr/include/glib-2.0 $RPM_BUILD_DIR/../../rootfs/usr/lib/glib-2.0/include/ \
			$RPM_BUILD_DIR/../../rootfs/usr/include/gstreamer-0.10/ $RPM_BUILD_DIR/../../rootfs/usr/include/libxml2/ $RPM_BUILD_DIR/../../rootfs/usr/include/freetype2
QMAKE_LIBDIR          = $RPM_BUILD_DIR/../../rootfs/usr/lib
QMAKE_INCDIR_X11      = $RPM_BUILD_DIR/../../rootfs/usr/include/X11
QMAKE_LIBDIR_X11      = $RPM_BUILD_DIR/../../rootfs/usr/lib
QMAKE_INCDIR_QT       = \$\$[QT_INSTALL_HEADERS]
QMAKE_LIBDIR_QT       = \$\$[QT_INSTALL_LIBS]
QMAKE_INCDIR_OPENGL   = $RPM_BUILD_DIR/../../rootfs/usr/include/GL
QMAKE_LIBDIR_OPENGL   = $RPM_BUILD_DIR/../../rootfs/usr/lib
QMAKE_INCDIR_POWERVR  = $RPM_BUILD_DIR/../../rootfs/usr/include
QMAKE_INCDIR_OPENGL_ES1 = $RPM_BUILD_DIR/../../rootfs/usr/include/GLES
QMAKE_LIBDIR_OPENGL_ES1 = $RPM_BUILD_DIR/../../rootfs/usr/lib
QMAKE_INCDIR_OPENGL_ES1CL = $RPM_BUILD_DIR/../../rootfs/usr/include/GLES
QMAKE_LIBDIR_OPENGL_ES1CL = $RPM_BUILD_DIR/../../rootfs/usr/lib
QMAKE_INCDIR_OPENGL_ES2 = $RPM_BUILD_DIR/../../rootfs/usr/include/GLES2
QMAKE_LIBDIR_OPENGL_ES2 = $RPM_BUILD_DIR/../../rootfs/usr/lib
QMAKE_INCDIR_EGL      = $RPM_BUILD_DIR/../../rootfs/usr/include/EGL
QMAKE_LIBDIR_EGL      = $RPM_BUILD_DIR/../../rootfs/usr/lib
QMAKE_INCDIR_OPENVG   = $RPM_BUILD_DIR/../../rootfs/usr/include/VG
QMAKE_LIBDIR_OPENVG   = $RPM_BUILD_DIR/../../rootfs/usr/lib

QMAKE_LIBS            = -lglib-2.0 -lgthread-2.0 -lz -lgmodule-2.0 -lgobject-2.0 -lxcb -lXau -lxcb-xlib -lXext -lXrender -lX11 -lfreetype -lexpat -lfontconfig -lSM -lICE $XTRA_OPTS_CONFIG
QMAKE_LIBS_DYNLOAD    = -ldl
QMAKE_LIBS_X11        = -lX11
QMAKE_LIBS_X11SM      =
QMAKE_LIBS_NIS        = -lnsl
QMAKE_LIBS_OPENGL     = -lGLU -lGL
QMAKE_LIBS_OPENGL_QT  = -lGL
QMAKE_LIBS_OPENGL_ES1 = -lGLESv1_CM
QMAKE_LIBS_OPENGL_ES1CL = -lGLES_CL
QMAKE_LIBS_OPENGL_ES2 = -lGLESv2
QMAKE_LIBS_OPENVG     = -lOpenVG
QMAKE_LIBS_THREAD     = -lpthread
QMAKE_LIBS_EGL	      = -lEGL

QMAKE_MOC             = \$\$[QT_INSTALL_BINS]/moc
QMAKE_UIC             = \$\$[QT_INSTALL_BINS]/uic

QMAKE_AR              = arm-none-linux-gnueabi-ar cqs
QMAKE_OBJCOPY         = arm-none-linux-gnueabi-objcopy
QMAKE_RANLIB          = arm-none-linux-gnueabi-ranlib

QMAKE_TAR             = tar -cf
QMAKE_GZIP            = gzip -9f

QMAKE_COPY            = cp -f
QMAKE_COPY_FILE       = \$(COPY)
QMAKE_COPY_DIR        = \$(COPY) -r
QMAKE_MOVE            = mv -f
QMAKE_DEL_FILE        = rm -f
QMAKE_DEL_DIR         = rmdir
QMAKE_STRIP           = arm-none-linux-gnueabi-strip
QMAKE_STRIPFLAGS_LIB += --strip-unneeded
QMAKE_CHK_DIR_EXISTS  = test -d
QMAKE_MKDIR           = mkdir -p
QMAKE_INSTALL_FILE    = install -m 644 -p
QMAKE_INSTALL_PROGRAM = install -m 755 -p

MAKEFILE_GENERATOR      = UNIX
TEMPLATE                = app
CONFIG                 += qt warn_on release incremental link_prl
QT                     += core gui network
QMAKE_INCREMENTAL_STYLE = sublib

load(qt_config)
EOF

chmod 744 $initscript

initscript=mkspecs/linux-g++-mx/qplatformdefs.h
cat > $initscript << EOF

#include "../linux-g++/qplatformdefs.h"

EOF

chmod 744 $initscript

%Build

export PATH=$UNSPOOF_PATH

# Unset compiler to prevent gcc being used when the cross
unset CC CXX

# Unset PLATFORM because this is used as host machine.
unset PLATFORM

#if PKG_AMD_GPU_X11_BIN_MX51 is already installed, uncomment the following line to add OpenGLES 2 support
XTRA_OPTS="$XTRA_OPTS -opengl es2"

#if PKG_MBX_BIN is already installed, uncomment the following line to add OpenGLES 1.1 support
#XTRA_OPTS="$XTRA_OPTS -opengl es1"

#./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} --disable-gtk-test
./configure --prefix=/home/rogerio/ltib/imx51_april_2010/ltib/rootfs/usr/local/Trolltech -arch arm -xplatform linux-g++-mx -release \
	-qt-gfx-linuxfb -qt-kbd-tty -little-endian -host-little-endian -fontconfig -sm -v -opensource -confirm-license $XTRA_OPTS

make

%Install

export PATH=$UNSPOOF_PATH

install -d $RPM_BUILD_ROOT/%{pfx}/usr/local/Trolltech
install -d $RPM_BUILD_ROOT/%{pfx}/usr/lib

cp -a demos $RPM_BUILD_ROOT/%{pfx}/usr/local/Trolltech
cp -a examples $RPM_BUILD_ROOT/%{pfx}/usr/local/Trolltech
cp -a lib/* $RPM_BUILD_ROOT/%{pfx}/usr/lib

export PATH=$SPOOF_PATH

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*

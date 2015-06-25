%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Qt
Name            : qt-everywhere-opensource-src
Version         : 4.8.5
Release         : 0
License         : GNU GPL
Vendor          : Freescale
Packager        : Rogerio Pimentel
Group           : System Environment/Libraries
Source          : %{name}-%{version}.tar.gz
Patch1          : qt-everywhere-opensource-src-4.8.5-1394522957.patch
Patch2          : qt-everywhere-opensource-src-4.8.5-1420823826.patch
Patch3          : qt-everywhere-opensource-src-4.8.5-1420823825.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
URL             : http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.8.5.tar.gz

%Description
%{summary}

%Prep
%setup

#Checking what packages are available

export XTRA_OPTS=""
export XTRA_OPTS_CONFIG=""

#if [ -n "$PKG_QT_PHONON" ]
#then
#    export XTRA_OPTS="$XTRA_OPTS -multimedia -phonon -phonon-backend -lgstreamer-0.10"
#    export XTRA_OPTS_CONFIG="$XTRA_OPTS_CONFIG -lgstreamer-0.10 -lxml2 -lasound"
#fi

#if PKG_AMD_GPU_BIN_MX51 is already installed, uncomment the following line to add OpenGLES 2 support
#export XTRA_OPTS_CONFIG="$XTRA_OPTS_CONFIG -lGLESv2 -lEGL -lgsl -lc2d -lpanel2"

#if PKG_MBX_BIN is already installed, uncomment the following line to add OpenGLES 1.1 support
#export XTRA_OPTS_CONFIG="$XTRA_OPTS_CONFIG -lEGL -lEGL"

mkdir mkspecs/qws/linux-g++-mx
initscript=mkspecs/qws/linux-g++-mx/qmake.conf
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
QMAKE_CXXFLAGS		+= \$\$QMAKE_CFLAGS
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
QMAKE_LFLAGS_RELEASE	+=-Wl,-O1
QMAKE_LFLAGS_DEBUG	+=
QMAKE_LFLAGS_APP	+=
QMAKE_LFLAGS_SHLIB	+= -shared
QMAKE_LFLAGS_PLUGIN	+= \$\$QMAKE_LFLAGS_SHLIB
QMAKE_LFLAGS_SONAME	+= -Wl,-soname,
QMAKE_LFLAGS_THREAD	+=
QMAKE_LFLAGS_NOUNDEF	+= -Wl,--no-undefined
QMAKE_LFLAGS_RPATH	= -Wl,-rpath,

QMAKE_PCH_OUTPUT_EXT    = .gch

# -Bsymbolic-functions (ld) support
QMAKE_LFLAGS_BSYMBOLIC_FUNC = -Wl,-Bsymbolic-functions
QMAKE_LFLAGS_DYNAMIC_LIST = -Wl,--dynamic-list,

QMAKE_CFLAGS_THREAD	+= -D_REENTRANT
QMAKE_CXXFLAGS_THREAD	+= \$\$QMAKE_CFLAGS_THREAD

QMAKE_INCDIR          = $RPM_BUILD_DIR/../../rootfs/usr/include $RPM_BUILD_DIR/../../rootfs/usr/include/glib-2.0 \
			$RPM_BUILD_DIR/../../rootfs/usr/lib/glib-2.0/include/
QMAKE_LIBDIR          = $RPM_BUILD_DIR/../../rootfs/usr/lib
QMAKE_INCDIR_X11      =
QMAKE_LIBDIR_X11      =


QMAKE_LIBS            = -lglib-2.0 -lgthread-2.0 -lz -lgmodule-2.0 -lgobject-2.0 -lts -lfreetype
QMAKE_LIBS_DYNLOAD    = -ldl
QMAKE_LIBS_X11        =
QMAKE_LIBS_X11SM      =
QMAKE_LIBS_NIS        = -lnsl
QMAKE_LIBS_THREAD     = -lpthread


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
QMAKE_CHK_DIR_EXISTS  = test -d
QMAKE_MKDIR           = mkdir -p
QMAKE_INSTALL_FILE    = install -m 644 -p
QMAKE_INSTALL_PROGRAM = install -m 755 -p

MAKEFILE_GENERATOR      = UNIX
TEMPLATE                = app
CONFIG                 += qt warn_on release incremental link_prl
QT                     += core gui 
QMAKE_INCREMENTAL_STYLE = sublib

load(qt_config)
EOF

chmod 744 $initscript

initscript=mkspecs/qws/linux-g++-mx/qplatformdefs.h
cat > $initscript << EOF

#include "../../linux-g++/qplatformdefs.h"

EOF
chmod 744 $initscript
%patch1 -p1
%patch2 -p1
%patch3 -p1

%Build

export PATH=$UNSPOOF_PATH

# Unset compiler to prevent gcc being used when the cross
# tools should be used. (Trolltech issue# 138807)
unset CC CXX

# Unset PLATFORM because this is used as host machine.
unset PLATFORM

#if PKG_AMD_GPU_BIN_MX51 is already installed, uncomment the following line to add OpenGLES 2 support
#export XTRA_OPTS="$XTRA_OPTS -opengl es2"

#if PKG_MBX_BIN is already installed, uncomment the following line to add OpenGLES 1.1 support
#export XTRA_OPTS="$XTRA_OPTS -opengl es1"



#QT initial configuration before valmar shrinking
#./configure --prefix=$RPM_BUILD_DIR/../../rootfs/usr/local/Trolltech -embedded arm -xplatform qws/linux-g++-mx -release \
# -qt-gfx-transformed -qt-gfx-linuxfb -qt-kbd-tty -qt-mouse-tslib -plugin-sql-sqlite -little-endian -host-little-endian -fontconfig -sm -v -opensource -confirm-license $XTRA_OPTS


./configure --prefix=$RPM_BUILD_DIR/../../rootfs/usr/local/Trolltech -embedded arm -xplatform qws/linux-g++-mx -release -fast -shared  -no-largefile \
 -qt-gfx-transformed -qt-gfx-linuxfb -qt-gfx-vnc -qt-kbd-tty -no-accessibility -no-stl -no-xmlpatterns -no-qt3support -no-multimedia -no-phonon -no-phonon-backend -no-svg -no-webkit -no-javascript-jit -no-script -no-scripttools -no-declarative -no-mmx -no-3dnow -no-sse -no-sse2 -no-sse3 -no-ssse3 \
 -qt-mouse-tslib -plugin-sql-sqlite -plugin-sql-mysql -little-endian -host-little-endian -fontconfig -sm -v -opensource -confirm-license -nomake demos -nomake examples  $XTRA_OPTS

make

%Install

export PATH=$UNSPOOF_PATH
install -d $RPM_BUILD_ROOT/%{pfx}/usr/local/Trolltech
install -d $RPM_BUILD_ROOT/%{pfx}/usr/lib

cp -a demos $RPM_BUILD_ROOT/%{pfx}/usr/local/Trolltech
cp -a examples $RPM_BUILD_ROOT/%{pfx}/usr/local/Trolltech
cp -a lib/* $RPM_BUILD_ROOT/%{pfx}/usr/lib

$TOOLCHAIN_PATH/bin/${TOOLCHAIN_PREFIX}strip --strip-unneeded $RPM_BUILD_ROOT/%{pfx}/usr/lib/libQt*.so.4.8.5

if [ -x plugins/sqldrivers/libqsqlite.so ]; then
cp -a plugins/sqldrivers/libqsqlite.so $RPM_BUILD_ROOT/%{pfx}/usr/lib/
fi

if [ -x plugins/sqldrivers/libqsqlmysql.so ]; then
cp -a plugins/sqldrivers/libqsqlmysql.so $RPM_BUILD_ROOT/%{pfx}/usr/lib/
fi

export PATH=$SPOOF_PATH

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*

%define pfx /opt/freescale/rootfs/%{_target_cpu}
%define archivename qt-everywhere-opensource-src

Summary         : Qt
Name            : qt-embedded
Version         : 4.8.5
Release         : 1
License         : LGPL v2.1
Vendor          : Freescale
Packager        : Rogerio Pimentel
Group           : System Environment/Libraries
URL             : http://get.qt.nokia.com/qt/source/%{archivename}-%{version}.tar.gz
%if %{?toolchain:1}%{!?toolchain:0}
Source          : %{archivename}-%{version}.tar.gz
Patch1          : %{archivename}-%{version}-1394522957.patch
Patch2          : %{archivename}-%{version}-1420823826.patch
Patch3          : %{archivename}-%{version}-1420823825.patch
%endif
BuildRoot       : %{_tmppath}/%{name}-%{version}
Prefix          : %{pfx}
AutoReqProv     : no


%if %{?toolchain:0}%{!?toolchain:1}

%Package rfs
Summary         : Trimmed qt-embedded for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Libraries
AutoReqProv     : no

%Description rfs
qt-embedded package contents restricted to just the files that
are needed at run time on the target.

%endif


%Description
%{summary}


%Prep
export LC_ALL
LC_ALL=C

%if %{?toolchain:0}%{!?toolchain:1}

%setup -T -c -n %{name}
cd ..; rmdir %{name}; ln -s ../../../projects/%{name} %{name}

%else

%setup -n %{archivename}-%{version}
%patch1 -p1
%patch2 -p1
%patch3 -p1

%endif


%Build
export LC_ALL
LC_ALL=C

# Set configuration.
#
export XTRA_OPTS=""
export XTRA_OPTS_CONFIG=""

mkdir mkspecs/qws/linux-g++-mx
initscript=mkspecs/qws/linux-g++-mx/qmake.conf
cat > $initscript << EOF
include(../..//common/gcc-base-unix.conf)
include(../..//common/g++-unix.conf)
include(../../common/linux.conf)
include(../../common/qws.conf)

#
# qmake configuration for building with arm-none-linux-gnueabi-g++
#

QMAKE_CC                       = /opt/CodeSourcery/bin/arm-none-linux-gnueabi-gcc
QMAKE_CFLAGS                  += -pipe
QMAKE_CFLAGS_DEPS             += -M
QMAKE_CFLAGS_WARN_ON          += -Wall -W
QMAKE_CFLAGS_WARN_OFF         += -w
QMAKE_CFLAGS_RELEASE          += -O2
QMAKE_CFLAGS_DEBUG            += -g
QMAKE_CFLAGS_SHLIB            += -fPIC
QMAKE_CFLAGS_STATIC_LIB       += -fPIC
QMAKE_CFLAGS_YACC             += -Wno-unused -Wno-parentheses
QMAKE_CFLAGS_HIDESYMS         += -fvisibility=hidden
#QMAKE_CFLAGS_PRECOMPILE       += -x c-header -c \${QMAKE_PCH_INPUT} -o \${QMAKE_PCH_OUTPUT}
#QMAKE_CFLAGS_USE_PRECOMPILE   += -include \${QMAKE_PCH_OUTPUT_BASE}

QMAKE_CXX                      = /opt/CodeSourcery/bin/arm-none-linux-gnueabi-g++
QMAKE_CXXFLAGS                += \$\$QMAKE_CFLAGS
QMAKE_CXXFLAGS_DEPS           += \$\$QMAKE_CFLAGS_DEPS
QMAKE_CXXFLAGS_WARN_ON        += \$\$QMAKE_CFLAGS_WARN_ON
QMAKE_CXXFLAGS_WARN_OFF       += \$\$QMAKE_CFLAGS_WARN_OFF
QMAKE_CXXFLAGS_RELEASE        += \$\$QMAKE_CFLAGS_RELEASE
QMAKE_CXXFLAGS_DEBUG          += \$\$QMAKE_CFLAGS_DEBUG
QMAKE_CXXFLAGS_SHLIB          += \$\$QMAKE_CFLAGS_SHLIB
QMAKE_CXXFLAGS_STATIC_LIB     += \$\$QMAKE_CFLAGS_STATIC_LIB
QMAKE_CXXFLAGS_YACC           += \$\$QMAKE_CFLAGS_YACC
QMAKE_CXXFLAGS_HIDESYMS       += \$\$QMAKE_CFLAGS_HIDESYMS -fvisibility-inlines-hidden
#QMAKE_CXXFLAGS_PRECOMPILE     += -x c++-header -c \${QMAKE_PCH_INPUT} -o \${QMAKE_PCH_OUTPUT}
#QMAKE_CXXFLAGS_USE_PRECOMPILE  = \$\$QMAKE_CFLAGS_USE_PRECOMPILE

QMAKE_LINK                     = /opt/CodeSourcery/bin/arm-none-linux-gnueabi-g++
QMAKE_LINK_SHLIB               = /opt/CodeSourcery/bin/arm-none-linux-gnueabi-g++
QMAKE_LINK_C                   = /opt/CodeSourcery/bin/arm-none-linux-gnueabi-gcc
QMAKE_LINK_C_SHLIB             = /opt/CodeSourcery/bin/arm-none-linux-gnueabi-gcc
QMAKE_LFLAGS                  +=
QMAKE_LFLAGS_RELEASE          += -Wl,-O1
QMAKE_LFLAGS_DEBUG            +=
QMAKE_LFLAGS_APP              +=
QMAKE_LFLAGS_SHLIB            += -shared
QMAKE_LFLAGS_PLUGIN           += \$\$QMAKE_LFLAGS_SHLIB
QMAKE_LFLAGS_SONAME           += -Wl,-soname,
QMAKE_LFLAGS_THREAD           +=
QMAKE_LFLAGS_NOUNDEF          += -Wl,--no-undefined
QMAKE_LFLAGS_RPATH             = -Wl,-rpath,

QMAKE_PCH_OUTPUT_EXT           = .gch

# -Bsymbolic-functions (ld) support
QMAKE_LFLAGS_BSYMBOLIC_FUNC    = -Wl,-Bsymbolic-functions
QMAKE_LFLAGS_DYNAMIC_LIST      = -Wl,--dynamic-list,

QMAKE_CFLAGS_THREAD           += -D_REENTRANT
QMAKE_CXXFLAGS_THREAD         += \$\$QMAKE_CFLAGS_THREAD

%if %{?toolchain:1}%{!?toolchain:0}
QMAKE_INCDIR                   = %{toolchain_install_dir}/include %{toolchain_install_dir}/include/glib-2.0 %{toolchain_install_dir}/lib/glib-2.0/include/
QMAKE_LIBDIR                   = %{toolchain_install_dir}/lib
QMAKE_LIBS                     =
%else
QMAKE_INCDIR                   = $RPM_BUILD_DIR/../../rootfs/usr/include $RPM_BUILD_DIR/../../rootfs/usr/include/glib-2.0 $RPM_BUILD_DIR/../../rootfs/usr/lib/glib-2.0/include/
QMAKE_LIBDIR                   = $RPM_BUILD_DIR/../../rootfs/usr/lib
QMAKE_LIBS                     = -lglib-2.0 -lgthread-2.0 -lz -lgmodule-2.0 -lgobject-2.0 -lts -lfreetype
%endif
QMAKE_INCDIR_X11               =
QMAKE_LIBDIR_X11               =
QMAKE_LIBS_DYNLOAD             = -ldl
QMAKE_LIBS_X11                 =
QMAKE_LIBS_X11SM               =
QMAKE_LIBS_NIS                 = -lnsl
QMAKE_LIBS_THREAD              = -lpthread


QMAKE_MOC                      = \$\$[QT_INSTALL_BINS]/moc
QMAKE_UIC                      = \$\$[QT_INSTALL_BINS]/uic

QMAKE_AR                       = /opt/CodeSourcery/bin/arm-none-linux-gnueabi-ar cqs
QMAKE_OBJCOPY                  = /opt/CodeSourcery/bin/arm-none-linux-gnueabi-objcopy
QMAKE_RANLIB                   = /opt/CodeSourcery/bin/arm-none-linux-gnueabi-ranlib

QMAKE_TAR                      = tar -cf
QMAKE_GZIP                     = gzip -9f

QMAKE_COPY                     = cp -f
QMAKE_COPY_FILE                = \$(COPY)
QMAKE_COPY_DIR                 = \$(COPY) -r
QMAKE_MOVE                     = mv -f
QMAKE_DEL_FILE                 = rm -f
QMAKE_DEL_DIR                  = rmdir
QMAKE_STRIP                    = /opt/CodeSourcery/bin/arm-none-linux-gnueabi-strip
QMAKE_CHK_DIR_EXISTS           = test -d
QMAKE_MKDIR                    = mkdir -p
QMAKE_INSTALL_FILE             = install -m 644 -p
QMAKE_INSTALL_PROGRAM          = install -m 755 -p

MAKEFILE_GENERATOR             = UNIX
TEMPLATE                       = app
CONFIG                        += qt warn_on release incremental link_prl
QT                            += core gui
QMAKE_INCREMENTAL_STYLE        = sublib

load(qt_config)
EOF

chmod 744 $initscript

initscript=mkspecs/qws/linux-g++-mx/qplatformdefs.h
cat > $initscript << EOF

#include "../../linux-g++/qplatformdefs.h"

EOF
chmod 744 $initscript

test -n "$UNSPOOF_PATH" && export PATH=$UNSPOOF_PATH

# Unset compiler to prevent gcc being used when the cross
# tools should be used. (Trolltech issue# 138807)
unset CC CXX

# Unset PLATFORM because this is used as host machine.
unset PLATFORM

# Timestamp order is important.
for f in configure.ac configure.in aclocal.m4 configure config.h.in Makefile.am Makefile.in; do
	find . -name $f -exec touch {} \;
done
MAKEFLAGS=j$(nproc) ./configure \
%if %{?toolchain:1}%{!?toolchain:0}
	--prefix=%{toolchain_install_dir} \
%else
	--prefix=$RPM_BUILD_DIR/../../rootfs/usr/local/Trolltech \
	-plugin-sql-mysql \
	-qt-mouse-tslib \
%endif
	-xplatform qws/linux-g++-mx \
	-confirm-license \
	-embedded arm \
	-fast \
	-fontconfig \
	-host-little-endian \
	-little-endian \
	-no-3dnow \
	-no-accessibility \
	-no-declarative \
	-no-javascript-jit \
	-no-largefile \
	-nomake demos \
	-nomake examples \
	-no-mmx \
	-no-multimedia \
	-no-phonon \
	-no-phonon-backend \
	-no-qt3support \
	-no-script \
	-no-scripttools \
	-no-sse \
	-no-sse2 \
	-no-sse3 \
	-no-ssse3 \
	-no-stl \
	-no-svg \
	-no-webkit \
	-no-xmlpatterns \
	-opensource \
	-plugin-sql-sqlite \
	-qt-gfx-linuxfb \
	-qt-gfx-transformed \
	-qt-gfx-vnc \
	-qt-kbd-tty \
	-release \
	-shared \
	-sm \
	-v \
	$XTRA_OPTS

make -j$(nproc)


%Install
export LC_ALL
LC_ALL=C

test -n "$UNSPOOF_PATH" && export PATH=$UNSPOOF_PATH

%if %{?toolchain:1}%{!?toolchain:0}

make INSTALL_ROOT=%{buildroot} install

%else

install -d $RPM_BUILD_ROOT/%{pfx}%{_prefix}/lib
cp -a lib/* $RPM_BUILD_ROOT/%{pfx}%{_prefix}/lib
$TOOLCHAIN_PATH/bin/${TOOLCHAIN_PREFIX}strip --strip-unneeded $RPM_BUILD_ROOT/%{pfx}%{_prefix}/lib/libQt*.so.%{version}
test -x plugins/sqldrivers/libqsqlite.so && install -m 644 plugins/sqldrivers/libqsqlite.so $RPM_BUILD_ROOT/%{pfx}%{_prefix}/lib
test -x plugins/sqldrivers/libqsqlmysql.so && install -m 644 plugins/sqldrivers/libqsqlmysql.so $RPM_BUILD_ROOT/%{pfx}%{_prefix}/lib

%endif


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%if %{?toolchain:1}%{!?toolchain:0}

%Files
%defattr(-,root,root)
%{toolchain_install_dir}/*

%else

%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/lib/README
%{pfx}/usr/lib/fonts/DejaVuSans-Bold.ttf
%{pfx}/usr/lib/fonts/DejaVuSans-BoldOblique.ttf
%{pfx}/usr/lib/fonts/DejaVuSans-Oblique.ttf
%{pfx}/usr/lib/fonts/DejaVuSans.ttf
%{pfx}/usr/lib/fonts/DejaVuSansMono-Bold.ttf
%{pfx}/usr/lib/fonts/DejaVuSansMono-BoldOblique.ttf
%{pfx}/usr/lib/fonts/DejaVuSansMono-Oblique.ttf
%{pfx}/usr/lib/fonts/DejaVuSansMono.ttf
%{pfx}/usr/lib/fonts/DejaVuSerif-Bold.ttf
%{pfx}/usr/lib/fonts/DejaVuSerif-BoldOblique.ttf
%{pfx}/usr/lib/fonts/DejaVuSerif-Oblique.ttf
%{pfx}/usr/lib/fonts/DejaVuSerif.ttf
%{pfx}/usr/lib/fonts/README
%{pfx}/usr/lib/fonts/UTBI____.pfa
%{pfx}/usr/lib/fonts/UTB_____.pfa
%{pfx}/usr/lib/fonts/UTI_____.pfa
%{pfx}/usr/lib/fonts/UTRG____.pfa
%{pfx}/usr/lib/fonts/Vera.ttf
%{pfx}/usr/lib/fonts/VeraBI.ttf
%{pfx}/usr/lib/fonts/VeraBd.ttf
%{pfx}/usr/lib/fonts/VeraIt.ttf
%{pfx}/usr/lib/fonts/VeraMoBI.ttf
%{pfx}/usr/lib/fonts/VeraMoBd.ttf
%{pfx}/usr/lib/fonts/VeraMoIt.ttf
%{pfx}/usr/lib/fonts/VeraMono.ttf
%{pfx}/usr/lib/fonts/VeraSe.ttf
%{pfx}/usr/lib/fonts/VeraSeBd.ttf
%{pfx}/usr/lib/fonts/c0419bt_.pfb
%{pfx}/usr/lib/fonts/c0582bt_.pfb
%{pfx}/usr/lib/fonts/c0583bt_.pfb
%{pfx}/usr/lib/fonts/c0611bt_.pfb
%{pfx}/usr/lib/fonts/c0632bt_.pfb
%{pfx}/usr/lib/fonts/c0633bt_.pfb
%{pfx}/usr/lib/fonts/c0648bt_.pfb
%{pfx}/usr/lib/fonts/c0649bt_.pfb
%{pfx}/usr/lib/fonts/cour.pfa
%{pfx}/usr/lib/fonts/courb.pfa
%{pfx}/usr/lib/fonts/courbi.pfa
%{pfx}/usr/lib/fonts/couri.pfa
%{pfx}/usr/lib/fonts/cursor.pfa
%{pfx}/usr/lib/fonts/dejavu_sans_11_50.qpf2
%{pfx}/usr/lib/fonts/fixed_120_50.qpf
%{pfx}/usr/lib/fonts/fixed_70_50.qpf
%{pfx}/usr/lib/fonts/helvetica_100_50.qpf
%{pfx}/usr/lib/fonts/helvetica_100_50i.qpf
%{pfx}/usr/lib/fonts/helvetica_100_75.qpf
%{pfx}/usr/lib/fonts/helvetica_100_75i.qpf
%{pfx}/usr/lib/fonts/helvetica_120_50.qpf
%{pfx}/usr/lib/fonts/helvetica_120_50i.qpf
%{pfx}/usr/lib/fonts/helvetica_120_75.qpf
%{pfx}/usr/lib/fonts/helvetica_120_75i.qpf
%{pfx}/usr/lib/fonts/helvetica_140_50.qpf
%{pfx}/usr/lib/fonts/helvetica_140_50i.qpf
%{pfx}/usr/lib/fonts/helvetica_140_75.qpf
%{pfx}/usr/lib/fonts/helvetica_140_75i.qpf
%{pfx}/usr/lib/fonts/helvetica_180_50.qpf
%{pfx}/usr/lib/fonts/helvetica_180_50i.qpf
%{pfx}/usr/lib/fonts/helvetica_180_75.qpf
%{pfx}/usr/lib/fonts/helvetica_180_75i.qpf
%{pfx}/usr/lib/fonts/helvetica_240_50.qpf
%{pfx}/usr/lib/fonts/helvetica_240_50i.qpf
%{pfx}/usr/lib/fonts/helvetica_240_75.qpf
%{pfx}/usr/lib/fonts/helvetica_240_75i.qpf
%{pfx}/usr/lib/fonts/helvetica_80_50.qpf
%{pfx}/usr/lib/fonts/helvetica_80_50i.qpf
%{pfx}/usr/lib/fonts/helvetica_80_75.qpf
%{pfx}/usr/lib/fonts/helvetica_80_75i.qpf
%{pfx}/usr/lib/fonts/japanese_230_50.qpf
%{pfx}/usr/lib/fonts/l047013t.pfa
%{pfx}/usr/lib/fonts/l047016t.pfa
%{pfx}/usr/lib/fonts/l047033t.pfa
%{pfx}/usr/lib/fonts/l047036t.pfa
%{pfx}/usr/lib/fonts/l048013t.pfa
%{pfx}/usr/lib/fonts/l048016t.pfa
%{pfx}/usr/lib/fonts/l048033t.pfa
%{pfx}/usr/lib/fonts/l048036t.pfa
%{pfx}/usr/lib/fonts/l049013t.pfa
%{pfx}/usr/lib/fonts/l049016t.pfa
%{pfx}/usr/lib/fonts/l049033t.pfa
%{pfx}/usr/lib/fonts/l049036t.pfa
%{pfx}/usr/lib/fonts/micro_40_50.qpf
%{pfx}/usr/lib/fonts/unifont_160_50.qpf
%{pfx}/usr/lib/libQtCore.so
%{pfx}/usr/lib/libQtCore.so.4
%{pfx}/usr/lib/libQtCore.so.4.8
%{pfx}/usr/lib/libQtCore.so.4.8.5
%{pfx}/usr/lib/libQtGui.so
%{pfx}/usr/lib/libQtGui.so.4
%{pfx}/usr/lib/libQtGui.so.4.8
%{pfx}/usr/lib/libQtGui.so.4.8.5
%{pfx}/usr/lib/libQtNetwork.so
%{pfx}/usr/lib/libQtNetwork.so.4
%{pfx}/usr/lib/libQtNetwork.so.4.8
%{pfx}/usr/lib/libQtNetwork.so.4.8.5
%{pfx}/usr/lib/libQtSql.so
%{pfx}/usr/lib/libQtSql.so.4
%{pfx}/usr/lib/libQtSql.so.4.8
%{pfx}/usr/lib/libQtSql.so.4.8.5
%{pfx}/usr/lib/libQtXml.so
%{pfx}/usr/lib/libQtXml.so.4
%{pfx}/usr/lib/libQtXml.so.4.8
%{pfx}/usr/lib/libQtXml.so.4.8.5
%{pfx}/usr/lib/libqsqlite.so
%{pfx}/usr/lib/libqsqlmysql.so

%endif

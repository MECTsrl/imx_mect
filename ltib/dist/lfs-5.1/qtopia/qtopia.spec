%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : qtopia palmtop environment
Name            : qtopia-free
Version         : 2.2.0
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : John Rigby
Group           : System Environment/Graphics
Source          : %{name}-src-%{version}.tar.gz
# These patches can be platform specific but must be safe for application
# on all platforms.
Patch1		: qtopia-free-2.2.0-0001-24Aug2006-ppc-qconfig.patch
Patch2		: qtopia-free-2.2.0-0002-24Aug2006-ppc-libavcodec-bigendian.patch
Patch3		: qtopia-free-2.2.0-0003-24Aug2006-qconfig-cursor-mouse.patch
Patch4		: qtopia-free-2.2.0-0004-24Aug2006-rgb555-and-swapped-byte-video.patch
Patch5		: qtopia-free-2.2.0-0005-24Aug2006-mpc5200-nogetospace.patch
Patch6		: qtopia-free-2.2.0-0006-24Aug2006-native-endian-audio.patch
Patch7		: qtopia-free-2.2.0-0007-24Aug2006-standard-touchscreen.patch
Patch9		: qtopia-free-2.2.0-0009-24Aug2006-mx21-buttons.patch
Patch10		: qtopia-free-2.2.0-0010-24Aug2006-dfltmouse-tpanel-and-screensaver.patch
Patch11		: qtopia-free-2.2.0-0011-24Aug2006-mxc-platform.patch
Patch12		: qtopia-free-2.2.0-0012-24Aug2006-mpc5200-platform.patch
Patch13		: qtopia-free-2.2.0-0013-08Sep2006-mx21-platform.patch
Patch14		: qtopia-free-2.2.0-0014-29Aug2006-gcc-4.1.1.patch
Patch15		: qtopia-free-2.2.0-0015-05Sep2006-keep_cursor.patch
Patch16		: qtopia-free-2.2.0-taskbar.patch
Patch17		: qtopia-free-2.2.0-linux_input_h
Patch18		: qtopia-free-2.2.0-ppc64-compiler-include-2.patch
Patch19		: qtopia-free-2.2.0-disable-dqt-options.patch
Patch20		: qtopia-free-2.2.0-headers-2.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup -n %{name}-%{version}
%patch1 -p1
%patch2 -p1
%patch3 -p1
%patch4 -p1
%patch5 -p1
%patch6 -p1
%patch7 -p1
%patch9 -p1
%patch10 -p1
%patch11 -p1
%patch12 -p1
%patch13 -p1
%patch14 -p1
%patch15 -p1
%patch16 -p1
%patch17 -p1
%patch18 -p1
%patch19 -p1
%patch20 -p1

# Define QWS_PLATFORM and specifiy extra qte and qpe configure options
case "$PLATFORM" in
    imx27ads | imx31ads | imx32ads | mxc*)
	export QWS_PLATFORM=mxc
	export EXTRA_QTE_CONFIG=
	if [ -n "$PKG_QTOPIA_WANT_TSLIB" ]
	then
		export EXTRA_QTE_CONFIG="-tslib"
		export QWS_TOUCHSCREEN=/dev/input/ts0
	fi
	export EXTRA_QPE_CONFIG="-edition pda -displaysize 240x320"
	export QWS_KEYBOARD=USB:/dev/input/keyboard0
	;;
    imx21ads)
	export QWS_PLATFORM=mx21
	export EXTRA_QTE_CONFIG=
	export EXTRA_QPE_CONFIG="-edition pda -displaysize 240x320"
	export QWS_KEYBOARD=Buttons
	;;
    mpc5200)
	export QWS_PLATFORM=mpc5200
	export EXTRA_QTE_CONFIG="-rgb555 -swapbytes_video"
	export EXTRA_QPE_CONFIG="-rgb555 -swapbytes_video"
	export QWS_KEYBOARD=TTY
	;;

   imx35_3stack)
        export QWS_PLATFORM=mxc
        if [ -n "$PKG_QTOPIA_WANT_TSLIB" ]
        then
                export EXTRA_QTE_CONFIG="-tslib"
                export QWS_TOUCHSCREEN=/dev/input/ts0
        fi
        export EXTRA_QPE_CONFIG="-edition pda -displaysize 800x480"
        export QWS_KEYBOARD=USB:/dev/input/keyboard0
        ;;

    imx*)
	export QWS_PLATFORM=mxc
	if [ -n "$PKG_QTOPIA_WANT_TSLIB" ]
	then
		export EXTRA_QTE_CONFIG="-tslib"
		export QWS_TOUCHSCREEN=/dev/input/ts0
	fi
	export EXTRA_QPE_CONFIG="-edition pda -displaysize 480x640"
	export QWS_KEYBOARD=USB:/dev/input/keyboard0
	;;
    qs875s)
	export QWS_PLATFORM=qs875s
	;;
esac

# Use toolchain flags when not spoofing
export EXTRA_CFLAGS=$TOOLCHAIN_CFLAGS
export EXTRA_LDFLAGS=$TOOLCHAIN_CFLAGS

echo export EXTRA_QPE_CONFIG=\"$EXTRA_QPE_CONFIG\" > ltibqtopiaconfig
echo export EXTRA_QTE_CONFIG=\"$EXTRA_QTE_CONFIG\" >> ltibqtopiaconfig
echo export EXTRA_CFLAGS=\"$EXTRA_CFLAGS\" >> ltibqtopiaconfig
echo export EXTRA_LDFLAGS=\"$EXTRA_LDFLAGS\" >> ltibqtopiaconfig
echo export PKG_QTOPIA_WANT_MOUSE=\"$PKG_QTOPIA_WANT_MOUSE\" >> ltibqtopiaconfig

echo export QWS_PLATFORM=$QWS_PLATFORM >> ltibqtopiaconfig
echo export QWS_KEYBOARD=\"$QWS_KEYBOARD\" >> ltibqtopiaconfig
echo export QWS_TOUCHSCREEN=\"$QWS_TOUCHSCREEN\" >> ltibqtopiaconfig

echo 'Note that e2fsprogs-devel, libjpeg/libjpeg-devel, uuid-dev/libuuid,'
echo 'and gettext (msgfmt) packages are required on the host.'

# tmake and qmake config
#   use linux-arm-g++ configuration as a starting point
cp -r tmake/lib/qws/linux-arm-g++ tmake/lib/qws/linux-$QWS_PLATFORM-g++
cp -r qtopia/mkspecs/qws/linux-arm-g++ qtopia/mkspecs/qws/linux-$QWS_PLATFORM-g++

# create generic q/s/l/q/custom-linux-$QWS_PLATFORM-g++.* files if not created by a patch
test -e qtopia/src/libraries/qtopia/custom-linux-$QWS_PLATFORM-g++.h \
	|| cp qtopia/src/libraries/qtopia/custom-linux-generic-g++.h qtopia/src/libraries/qtopia/custom-linux-$QWS_PLATFORM-g++.h
test -e qtopia/src/libraries/qtopia/custom-linux-$QWS_PLATFORM-g++.cpp \
	|| cp qtopia/src/libraries/qtopia/custom-linux-generic-g++.cpp qtopia/src/libraries/qtopia/custom-linux-$QWS_PLATFORM-g++.cpp


%Build
. ./ltibqtopiaconfig
export UC_QWS_PLATFORM=`perl -e "print uc $QWS_PLATFORM"`

#   substitututions for cross build
perl -p -i -e 's,arm-linux-,$ENV{TOOLCHAIN_PREFIX},;
               s,^((?:QMAKE|TMAKE)_CFLAGS\s+).*,$1 = -pipe -I. -I $ENV{DEV_IMAGE}/usr/include -DQT_QWS_$ENV{UC_QWS_PLATFORM} $ENV{EXTRA_CFLAGS},;
               s,^((?:QMAKE|TMAKE)_LFLAGS\s+).*,$1 = -L $ENV{DEV_IMAGE}/usr/lib $ENV{EXTRA_LDFLAGS},;
               s,^((?:QMAKE|TMAKE)_CXXFLAGS\s+.*),$1 $ENV{EXTRA_CFLAGS},;
               if( $ENV{PKG_QTOPIA_WANT_TSLIB} ) {
                   s,^((?:QMAKE)_LIBS\s+).*,$1 = -lts,;
               }
              ' tmake/lib/qws/linux-$QWS_PLATFORM-g++/tmake.conf \
                qtopia/mkspecs/qws/linux-$QWS_PLATFORM-g++/qmake.conf

export PATH=$UNSPOOF_PATH
echo yes | ./configure \
  -qte    "-platform linux-x86-g++ -xplatform linux-$QWS_PLATFORM-g++ \
    -depths 16,32 -system-jpeg -no-opengl -no-xft -no-sm -no-qvfb -no-vnc \
    ${EXTRA_QTE_CONFIG} \
    -no-g++-exceptions -no-xft -embedded -qconfig qpe" \
  -qpe    "-platform linux-g++ -xplatform linux-$QWS_PLATFORM-g++ \
    -arch $GNUTARCH -no-qvfb -with-libffmpeg -qconfig qpe \
    ${EXTRA_QPE_CONFIG} \
    -l jpeg -l uuid"
./qtopia/scripts/buildQtopiaTools -check
make

# Cache the host tools to save time after the first build.
if [ "$PKG_QTOPIA_WANT_CACHE_HOST_TOOLS" = "y" ]; then
	# This will save tools in ~/.qtopia_220_cache
	./qtopia/scripts/cacheQtopiaTools
fi


%Install
. ./ltibqtopiaconfig
export PATH=$UNSPOOF_PATH
echo creating qtopia install image
make install > /dev/null
rm -rf $RPM_BUILD_ROOT
install -d $RPM_BUILD_ROOT/%{pfx}
cp -a qtopia/image/opt $RPM_BUILD_ROOT/%{pfx}
install -d $RPM_BUILD_ROOT/%{pfx}/etc/rc.d/init.d

#initscript=$RPM_BUILD_ROOT/%{pfx}/etc/rc.d/rc.qpe
initscript=$RPM_BUILD_ROOT/%{pfx}/etc/rc.d/init.d/qtopia
cat > $initscript << EOF
#!/bin/sh
#
# Copyright 2006, Freescale Semiconductor Inc.
#
# Set QPE_USE_MOUSE to "y" to use mouse 
# otherwise touchscreen will be used
#
# tslib environment
if [ -n "$PKG_QTOPIA_WANT_TSLIB" ]
then
    export TSLIB_TSDEVICE="$QWS_TOUCHSCREEN"
    export TSLIB_PLUGINDIR=/usr/lib/ts
    export TSLIB_CONFFILE=/usr/etc/ts.conf
fi
HOME=/root
QPE_USE_MOUSE="$PKG_QTOPIA_WANT_MOUSE"
export HOME QPE_USE_MOUSE
# make sure usb input, mouse, and ts nodes exist
mkdir -p /dev/input
test -c /dev/input/event1 || mknod /dev/input/event1 c 13 65
test -c /dev/input/mice || mknod /dev/input/mice c 13 63
test -c /dev/ts || mknod /dev/ts c 11 0
QTDIR=/opt/Qtopia
QPEDIR=/opt/Qtopia
LD_LIBRARY_PATH=/opt/Qtopia/lib
PATH=/opt/Qtopia/bin:\$PATH
QWS_SIZE="1024x768"
export QTDIR QPEDIR LD_LIBRARY_PATH PATH QWS_SIZE
QWS_KEYBOARD="$QWS_KEYBOARD"
export QWS_KEYBOARD
if [ _\$QPE_USE_MOUSE = "_y" ]
then
QWS_MOUSE_PROTO="USB:/dev/input/mice"
export QWS_MOUSE_PROTO
# overide pointer calibration when using mouse
touch /etc/pointercal 
else
# changing the :/dev/ts part will have no effect as it 
# is hardcoded in the source
QWS_MOUSE_PROTO="TPanel:/dev/ts"
# hide cursor when using touchscreen
QWS_HIDE_CURSOR="Yes"
export QWS_MOUSE_PROTO QWS_HIDE_CURSOR
if [ -c /dev/tty0 ]; then
echo -e -n '\033[?25l' > /dev/tty0
echo -e -n '\033[9]' > /dev/tty0
fi
if [ -c /dev/vc/0 ]; then
echo -e -n '\033[?25l' > /dev/vc/0
echo -e -n '\033[9]' > /dev/vc/0
fi
# remove pointercal if it is empty
[ -f /etc/pointercal -a ! -s /etc/pointercal ] && rm -f /etc/pointercal
fi
cd /opt/Qtopia/bin
./qpe > /dev/null 2>&1 &
#./qpe &
EOF

chmod 744 $initscript
echo '1' > $RPM_BUILD_ROOT/%{pfx}/etc/firstuse
# setup Storage.conf
install -d $RPM_BUILD_ROOT/%{pfx}/root/Settings
cat > $RPM_BUILD_ROOT/%{pfx}/root/Settings/Storage.conf << EOF
[rootfs]
Name = Internal Storage
Removeable = 0
[/dev/sda1]
Name = USB Flash Drive
Removable = 1
EOF

# make sure the strip scripts are run cross
export PATH=$SPOOF_PATH

%Clean
rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*



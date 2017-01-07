%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Matchbox Desktop
Name            : matchbox-desktop
Version         : 0.9.1
Release         : 2
License         : GPL
Vendor          : Freescale
Packager        : Rob Herring
Group           : User Interface/Desktops
Source          : %{name}-%{version}.tar.bz2
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}

export PATH=$UNSPOOF_PATH
export LD_LIBRARY_PATH=$UNSPOOF_LD_LIBRARY_PATH
echo creating fslgnome
install -d $RPM_BUILD_ROOT/%{pfx}/etc/rc.d/init.d

initscript=$RPM_BUILD_ROOT%{pfx}/etc/rc.d/init.d/fslgnome
cat > $initscript << EOF
#!/bin/sh
#
# Copyright 2009, Freescale Semiconductor Inc.
#
export LD_LIBRARY_PATH=/usr/lib:/usr/bin:\$LD_LIBRARY_PATH
export GST_PLUGIN_PATH=/usr/lib/fsl_mm_linux/lib/gstreamer-0.10:/usr/lib/gstreamer-0.10:\$GST_PLUGIN_PATH
export PATH=/usr/bin:/usr/lib:\$PATH
export TSLIB_TSDEVICE=/dev/input/ts0
export TSLIB_CONFFILE=/usr/etc/ts.conf
export TSLIB_PLUGINDIR=/usr/lib/ts
export TSLIB_CALIBFILE=/usr/etc/pointercal
export TSLIB_FBDEVICE=/dev/fb0
export TSLIB_CONSOLEDEVICE=/dev/tty
export FONTCONFIG_FILE=/etc/fonts/fonts.conf
export DISPLAY=:0

if [ -e /usr/var/run/dbus/pid ]; then
	rm /usr/var/run/dbus/pid
fi

# Protect the DMA Zone and avoid memory allocation error
echo 1 1 > /proc/sys/vm/lowmem_reserve_ratio

# If support D-Bus as the IPC, need start dbus daemon and dbus lanuch
dbus-uuidgen > /usr/var/lib/dbus/machine-id
dbus-daemon --system
sleep 2
if test -z "\$DBUS_SESSION_BUS_ADDRESS" ; then
      ## if not found, launch a new one
        $(echo "eval \`dbus-launch --sh-syntax \`")
        echo "D-Bus per-session daemon address is: \$DBUS_SESSION_BUS_ADDRESS"
fi
sleep 1

if [ -e /tmp/.X0-lock ]; then
        rm /tmp/.X0-lock
fi
hald --daemon=yes
sleep 2
# Start X-server from starx script
startx &
EOF
chmod 744 $initscript

startxscript=$RPM_BUILD_ROOT%{pfx}/usr/bin/startx
cat > $startxscript << EOF
#!/bin/sh
IS_BABBAGE=NO
grep Babbage /proc/cpuinfo > /dev/null 2>&1
if [ \$? = 0 ]; then
	IS_BABBAGE=YES
	Xfbdev -keybd keyboard,,device=/dev/input/keyboard0 -mouse mouse,2,device=/dev/input/mice &
fi

if [ -L /dev/input/ts0 ]; then
	Xfbdev -mouse tslib,2,device=/dev/input/ts0 -mouse mouse,2,device=/dev/input/mice&
else
	Xfbdev -mouse mouse,2,device=/dev/input/mice&
fi

sleep 8

matchbox-window-manager -d :0 -use_lowlight no -use_titlebar yes -use_cursor yes&
matchbox-desktop&
matchbox-panel  --bgtrans yes  &
sleep 5
# Calibrate when using the rootfs the first time
# Check whether the touch screen exists
if [ -L /dev/input/ts0 ]; then
	ls /usr/etc | grep pointercal > /dev/null 2>&1
	if [ \$? = 1 ]; then
		ts_calibrate
	fi
fi
EOF
chmod 744 $startxscript

%Clean
rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*



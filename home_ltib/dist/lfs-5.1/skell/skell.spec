%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Skelleton files for an embedded root filesystem
Name            : skell
Version         : 1.18
Release         : 2
License         : GPL
Vendor          : Freescale
Packager        : Steve Papacharalambous/Stuart Hughes
Group           : System Environment/Utilities
Source          : %{name}-%{version}.tar.gz
Patch1          : skell-1.18-dropbear_args.patch
Patch2          : skell-1.17-imx.patch
Patch3          : skell-1.16-imx-fsl-gstplugin.patch
Patch4          : skell-1.19-imx-fsl-gnome.patch
Patch5          : skell-1.19-imx-hal-messagebus.patch
Patch6          : skell-1.18-mect-config.patch
Patch7          : skell-1.18-1317731895.patch
Patch8          : skell-1.18-1318337638.patch
Patch9          : skell-1.18-1319030600.patch
Patch10          : skell-1.18-1328695400.patch
Patch11          : skell-1.18-1329225205.patch
Patch12          : skell-1.18-1332342531.patch
Patch13          : skell-1.18-1333039892.patch
Patch14          : skell-1.18-1349102220.patch
Patch15          : skell-1.18-1353931133.patch
Patch16          : skell-1.18-1416848812.patch
Patch17          : skell-1.18-1418999072.patch
Patch18          : skell-1.18-1420825964.patch
Patch19          : skell-1.18-1421745467.patch
Patch20          : skell-1.18-1421838801.patch
Patch21          : skell-1.18-1423222246.patch
Patch22          : skell-1.18-1427985138.patch
Patch23          : skell-1.18-1428680350.patch
Patch24          : skell-1.18-1429175466.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

# skell-1.18-mect-config.patch : prepare a skell with read only partition and data partition
# skell-1.18-1317731895.patch  : add the environment variable for touchscreen and QT, remove rc.conf because is already created by sysconfig package
# skell-1.18-1318337638.patch  : disable httpd and create the character device /dev/buzzer
# skell-1.18-1328695400.patch  : add the autoexec script
# skell-1.18-1329225205.patch  : fix the LCD calibration sync problem, add the MAC configuration at power-on
#Patch12          : skell-1.18-1332342531.patch add S10setup script to file system 
#Patch13          : skell-1.18-1333039892.patch modified S10setup script
#Patch14          : skell-1.18-1349102220.patch modified S10setup script, added root password
#Patch15          : skell-1.18-1353931133.patch modified S10setup script
#Patch16          : skell-1.18-1355479713.patch modified S10setup to work with the autoexec logic. Added S!0setup and autoexec in /usr/bin
#Patch22          : skell-1.18-1427985138.patch remove the unecessary sleep at boot scripts and change the command to detect the usb
%Description
%{summary}

%Prep
%setup
%patch1 -p1
%patch2 -p1
%patch3 -p1
%patch4 -p1
%patch5 -p1
%patch6 -p1
%patch7 -p1
%patch8 -p1
%patch9 -p1
%patch10 -p1
%patch11 -p1
%patch12 -p1
%patch13 -p1
%patch14 -p1
%patch15 -p1

DESTDIR=$RPM_BUILD_ROOT/%{pfx} 
echo $DESTDIR
%patch16 -p1
%patch17 -p1
%patch18 -p1
%patch19 -p1
%patch20 -p1
%patch21 -p1
%patch22 -p1
%patch23 -p1
%patch24 -p1




%Build
DESTDIR=$RPM_BUILD_ROOT/%{pfx} 
echo $DESTDIR

%Install
rm -rf $RPM_BUILD_ROOT
DESTDIR=$RPM_BUILD_ROOT/%{pfx} 
echo $DESTDIR
make DESTDIR=$RPM_BUILD_ROOT/%{pfx} install

if [ -z "$PKG_SKELL_WANT_TERMINFO" ]
then
    rm -rf $RPM_BUILD_ROOT/%{pfx}/usr/share/terminfo
fi

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%attr(0666, root, root) %dev(c, 5, 0) %{pfx}/dev/tty
%attr(0600, root, root) %dev(c, 5, 1) %{pfx}/dev/console
%attr(0666, root, root) %dev(c, 1, 3) %{pfx}/dev/null
%{pfx}/*

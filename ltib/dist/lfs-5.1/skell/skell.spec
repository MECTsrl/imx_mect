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
Source1         : skell-mect-dev.tar.bz2
Source2         : rootfs_patch.tar.bz2
Source3         : skell-local.tar.bz2
Patch1          : skell-1.18-dropbear_args.patch
Patch2          : skell-1.17-imx.patch
Patch3          : skell-1.16-imx-fsl-gstplugin.patch
Patch4          : skell-1.19-imx-fsl-gnome.patch
Patch5          : skell-1.19-imx-hal-messagebus.patch
Patch6          : skell-1.18-mect-config.patch
Patch7          : skell-1.18-1317731895.patch
Patch8          : skell-1.18-1318337638.patch
Patch9          : skell-1.18-1319030600.patch
Patch10         : skell-1.18-1328695400.patch
Patch11         : skell-1.18-1329225205.patch
Patch12         : skell-1.18-1332342531.patch
Patch13         : skell-1.18-1333039892.patch
Patch14         : skell-1.18-1349102220.patch
Patch15         : skell-1.18-1353931133.patch
Patch16         : skell-1.18-1416848812.patch
Patch17         : skell-1.18-1418999072.patch
Patch18         : skell-1.18-1420825964.patch
Patch19         : skell-1.18-1421745467.patch
Patch20         : skell-1.18-1421838801.patch
Patch21         : skell-1.18-1423222246.patch
Patch22         : skell-1.18-1427985138.patch
Patch23         : skell-1.18-1428680350.patch
Patch24         : skell-1.18-1429172043.patch
Patch25         : skell-1.18-1431590614.patch
Patch26         : skell-1.18-ld-xenomai-libs.patch
Patch27         : skell-1.18-root-home-perms.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no

# skell-1.18-mect-config.patch : prepare a skell with read only partition and data partition
# skell-1.18-1317731895.patch  : add the environment variable for touchscreen and QT, remove rc.conf because is already created by sysconfig package
# skell-1.18-1318337638.patch  : disable httpd and create the character device /dev/buzzer
# skell-1.18-1328695400.patch  : add the autoexec script
# skell-1.18-1329225205.patch  : fix the LCD calibration sync problem, add the MAC configuration at power-on
#Patch12          : skell-1.18-1332342531.patch add S10setup script to file system 
#Patch13          : skell-1.18-1333039892.patch modified S10setup script
#Patch14          : skell-1.18-1349102220.patch modified S10setup script, added root password
#Patch15          : skell-1.18-1353931133.patch modified S10setup script
#Patch16          : skell-1.18-1355479713.patch modified S10setup to work with the autoexec logic. Added S10setup and autoexec in /usr/bin
#Patch22          : skell-1.18-1427985138.patch remove the unecessary sleep at boot scripts and change the command to detect the usb
#Patch25          : skell-1.18-1431590614.patch set the backglight first of all into the autoexec script


%Package rfs
Summary         : Trimmed skell for root file system requirements.
Group           : Applications/File
AutoReqProv     : no
%Description rfs
skell package contents restricted to just the files that are
needed at run time on the target.

%Package lfs
Summary         : Skeleton for local file system.
Group           : Applications/File
Prefix          : %{pfx}/local
AutoReqProv     : no
%Description lfs
Basic contents of the local file system.


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
%patch16 -p1
%patch17 -p1
%patch18 -p1
%patch19 -p1
%patch20 -p1
%patch21 -p1
%patch22 -p1
%patch23 -p1
%patch24 -p1
%patch25 -p1
%patch26 -p1
%patch27 -p1

%Build
DESTDIR=$RPM_BUILD_ROOT/%{pfx} 

%Install
rm -rf $RPM_BUILD_ROOT
DESTDIR=$RPM_BUILD_ROOT/%{pfx} 
make DESTDIR=$RPM_BUILD_ROOT/%{pfx} install

test -z "$PKG_SKELL_WANT_TERMINFO" && rm -rf $RPM_BUILD_ROOT/%{pfx}%{_prefix}/share/terminfo

sudo tar xjvf %{SOURCE1} -C $RPM_BUILD_ROOT/%{pfx}
tar xjvf %{SOURCE2} -C $RPM_BUILD_ROOT/%{pfx}
tar xjvf %{SOURCE3} -C $RPM_BUILD_ROOT/%{pfx}

cd %{_builddir}/%{name}-%{version}
( cd $RPM_BUILD_ROOT; find .%{pfx} \( \( -not -type d \) -o \( -type d -empty \) \) -print | sed 's/^\.//' ) > all_files.lst
sed '
    \,^%{pfx}/boot, d;
    \,%{pfx}%{_includedir}, d;
    \,^%{pfx}/local, d;
    \,^%{pfx}/\.keepme, d;
' all_files.lst > rfs_files.lst

%Clean
sudo rm -rf $RPM_BUILD_ROOT

%Files -f all_files.lst
%defattr(-,root,root)
%attr(0666, root, root) %dev(c, 5, 0) %{pfx}/dev/tty
%attr(0600, root, root) %dev(c, 5, 1) %{pfx}/dev/console
%attr(0666, root, root) %dev(c, 1, 3) %{pfx}/dev/null

%Files rfs -f rfs_files.lst
%defattr(-,root,root)
%attr(0666, root, root) %dev(c, 5, 0) %{pfx}/dev/tty
%attr(0600, root, root) %dev(c, 5, 1) %{pfx}/dev/console
%attr(0666, root, root) %dev(c, 1, 3) %{pfx}/dev/null

%Files lfs
%defattr(-,root,root)
%{pfx}/local/*
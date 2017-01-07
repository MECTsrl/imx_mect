%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : X.Org server
Name            : xorg-server
Version         : 1.6.1
Release         : 2
License         : X11
Vendor          : X.Org Foundation
Packager        : ProFUSION embedded systems <contact@profusion.mobi>
Group           : System Environment/Libraries
URL             : http://www.x.org/
Source          : %{name}-%{version}.tar.bz2
Patch1          : %{name}-disable-lcd-auto-blank.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
The official package for X.Org server, being compiled with kdrive.

%Prep
%setup
%patch1 -p1

%Build
rpm --dbpath %{_dbpath} -q tslib &>/dev/null
if [ $? ]
then
    extra_opts='--enable-tslib'
fi

# By default we'll use the original options that build kdrive 
# and override the ones we need for a full Xorg
if [ -n "$PKG_XORG_SERVER_WANT_XORG" ]
then
    extra_opts="$extra_opts --enable-xorg --enable-dga"
fi

./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} \
            --enable-composite  --enable-kdrive --disable-dri --disable-xinerama --disable-xf86vidmode --disable-xnest --enable-xfbdev --disable-dmx --disable-glx --with-default-font-path=built-ins $extra_opts

perl -000 -pi.bak -e 's,-lts,, if m,^Xfbdev_DEPENDENCIES|Xephyr_DEPENDENCIES,' \
                              hw/kdrive/fbdev/Makefile hw/kdrive/ephyr/Makefile

make

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
find $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/ -name "*.la" | xargs rm -f

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*


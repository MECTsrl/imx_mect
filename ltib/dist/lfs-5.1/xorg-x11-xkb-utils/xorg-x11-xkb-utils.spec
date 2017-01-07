%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : X.Org X11 xkb utilities
Name            : xorg-x11-xkb-utils
Version         : 7.2
Release         : 4
License         : MIT/X11
Vendor          : Freescale
Packager        : LTIB addsrpms
Group           : User Interface/X
URL             : http://www.x.org
Source0         : ftp://ftp.x.org/pub/individual/app/xkbutils-1.0.1.tar.bz2
Source1         : ftp://ftp.x.org/pub/individual/app/xkbcomp-1.0.2.tar.bz2
Source2         : ftp://ftp.x.org/pub/individual/app/xkbevd-1.0.2.tar.bz2
Source3         : ftp://ftp.x.org/pub/individual/app/xkbprint-1.0.1.tar.bz2
Source4         : ftp://ftp.x.org/pub/individual/app/setxkbmap-1.0.4.tar.bz2
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

NOTE: this was imported by ltib -m addsrpms xorg-x11-xkb-utils-7.2-4.fc9.src.rpm

%Prep

%setup -q -c xorg-x11-xkb-utils-7.2 -a1 -a2 -a3 -a4


%Build
export CFLAGS="-DHAVE_STRCASECMP"
for pkg in xkbutils setxkbmap xkbcomp xkbevd xkbprint ; do
    cd $pkg-*
    ./configure  --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
    make
    cd ..
done


%Install
rm -rf $RPM_BUILD_ROOT
for pkg in xkbutils setxkbmap xkbcomp xkbevd xkbprint ; do
    cd $pkg-*
    make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
    cd ..
done


%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*

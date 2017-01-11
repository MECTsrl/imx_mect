%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : libXft
Name            : libXft
Version         : 2.1.13
Release         : 1
License         : X11
Vendor          : Freescale
Packager        : Rob Herring
Group           : System Environment/Libraries
Source          : %{name}-%{version}.tar.bz2
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}
Xorg libraries.

Packages can be found here:
http://xorg.freedesktop.org/releases/individual/lib/

%Prep
%setup

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} \
    --sysconfdir=/etc --disable-malloc0returnsnull \
    --mandir=/usr/share/man --localstatedir=/var
make

%Install
make DESTDIR=$RPM_BUILD_ROOT/%{pfx} install
rm -f $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/*.la

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*



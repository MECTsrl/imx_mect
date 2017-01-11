%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Microwindows demo code for use with M52277
Name            : m52277evb-demo
Version         : 1.0
Release         : 0
License         : BSD
Vendor          : Freescale
Packager        : Matt Waddel
Group           : System Environment/Utilities
Source          : m52277evb-demo-%{version}.tar.gz
Patch1          : m52277evb-demo-1.0-max-slides.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
Example code used demonstrate the touchscreen capabilities of the 
M52277EVB hardware.

%Prep
%setup -n %{name}
%patch1 -p1

%Build
make LDFLAGS=$DEV_IMAGE/usr/lib/libnano-X.a

%Install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}/usr/bin
install -m 755 mcf5227x_button $RPM_BUILD_ROOT/%{pfx}/usr/bin/mcf5227x_button
install -m 755 mcf5227x_slides $RPM_BUILD_ROOT/%{pfx}/usr/bin/mcf5227x_slides

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*

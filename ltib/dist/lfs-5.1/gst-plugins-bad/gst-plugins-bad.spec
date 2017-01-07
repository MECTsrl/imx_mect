%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : GStreamer Plugins Bad
Name            : gst-plugins-bad
Version         : 0.10.11
Release         : 1
License         : LGPL
Vendor          : Freescale
Packager        : Kurt Mahan
Group           : Applications/System
Source          : gst-plugins-bad-%{version}.tar.bz2
Patch1          : gst-plugins-bad-0.10.4-relink.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup
%patch1 -p1

%Build
./configure --prefix=%{_prefix} --host=$CFGHOST \
	    --build=%{_build} --disable-valgrind \
	    --disable-x --disable-xvid \
	    --disable-ximagesrc --disable-jack \
	    --disable-sdl --disable-sdltest \
	    --x-includes= --x-libraries= \
	    --without-check NM=nm
make

%Install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
find $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib -name "*.la" | xargs rm -f

%Clean
rm -rf $RPM_BUILD_ROOT

%Files
%defattr(-,root,root)
%{pfx}/*

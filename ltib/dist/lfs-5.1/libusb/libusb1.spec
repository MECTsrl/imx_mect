%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : A library which allows userspace access to USB devices 
Name            : libusb1
Version         : 1.0.20
Release         : 1
License         : LGPL
Vendor          : MECT
Packager        : Mihai Lazarescu
Group           : System Environment/Libraries
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed down libusb-1.x to just run time libraries
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Libraries
AutoReqProv     : no

%Description rfs
libusb-1.x package contents restricted to just the libraries
that are needed at run time on the target.


%Description
%{summary}.


%Prep
export LC_ALL
LC_ALL=C

%setup -T -c -n %{name}
cd ..; rmdir %{name}; ln -s ../../../projects/%{name} %{name}


%Build
export LC_ALL
LC_ALL=C

# Timestamp order is important.
for f in configure.ac configure.in aclocal.m4 configure config.h.in Makefile.am Makefile.in; do
	find . -name $f -exec touch {} \;
done
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} --disable-udev --disable-build-docs
make -j1


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make -j1 install DESTDIR=$RPM_BUILD_ROOT/%{pfx}


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/lib/libusb-1.0.so
%{pfx}/usr/lib/libusb-1.0.so.0
%{pfx}/usr/lib/libusb-1.0.so.0.1.0

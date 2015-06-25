%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Library to allow control of basic functions in socketcan from userspace
Name            : libsocketcan
Version         : 0.0.8
Release         : 0
License         : GNU LGPLv2.1
Vendor          : Freescale
Packager        : Rogerio Pimentel
Group           : System Environment/Libraries
Source          : %{name}-%{version}.tar.gz
Patch1          : libsocketcan-0.0.8-1317716454.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
URL             : http://www.pengutronix.de/software/libsocketcan/download/

%Description
%{summary}

%Prep
%setup
%patch1 -p1

%Build


./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
#./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} CC=/opt/freescale/usr/local/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-fsl-linux-gnueabi-gcc

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

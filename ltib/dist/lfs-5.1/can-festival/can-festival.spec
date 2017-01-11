%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : CANopen stack implementation
Name            : can-festival
Version         : 3.0
Release         : rc3
License         : LGPL
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Development/System
URL             : http://www.canfestival.org/
Source          : CanFestival-%{version}-%{release}.tgz
Patch0          : can-festival-build.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed %{name} for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Development/System
AutoReqProv     : no

%Description rfs
%{name} package contents trimmed to just the files
needed at run time on the target.


%description
CANopen is a CAN based highter layer protocol. It defines some
protocols to:
- Configure a CAN network.
- Transmit data to a specific node or in broadcast.
- Administrate the network. For example detecting a not
  responding node.


%Prep
export LC_ALL
LC_ALL=C

%setup -n CanFestival-%{version}-%{release}
%patch0 -p1

# Timestamp order is important.
for f in configure.ac configure.in aclocal.m4 configure config.h.in Makefile.am Makefile.in; do
	find . -name $f -exec touch {} \;
done
ROOTFS=${DEV_IMAGE} ./configure \
	--target=unix \
	--arch=${LINTARCH} \
	--timers=xeno \
	--prefix=/usr \
	--can=socket


%Build
export LC_ALL
LC_ALL=C

make \
	PROG_CFLAGS=-I${DEV_IMAGE}/usr/xenomai/include \
	EXE_CFLAGS_PATH="-L${DEV_IMAGE}/usr/xenomai/lib -lxenomai"

%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

make \
	PROG_CFLAGS=-I${DEV_IMAGE}/usr/xenomai/include \
	EXE_CFLAGS_PATH="-L${DEV_IMAGE}/usr/xenomai/lib -lxenomai" \
	PREFIX=$RPM_BUILD_ROOT%{pfx}/usr \
	install

### %define  LIBPATH ${RPM_BUILD_ROOT}%{_elinos_install_dir}/%{_elinos_conftarget}/lib
### %define  BINPATH ${RPM_BUILD_ROOT}%{_elinos_target_dir}/%{_elinos_libc}/default/usr/bin
### 
### install -d -m 755 %{LIBPATH}
### install -d -m 755 %{BINPATH}
### 
### make -C CanOpen/CanOpenMain -f MakefileLinux LIBPATH=%{LIBPATH} install
### make -C CanOpen/CanOpenDriverLinux -f MakefileLinux LIBPATH=%{LIBPATH} install
### make -C CanOpen/CanOpenDriverLinuxPeak -f MakefileLinux LIBPATH=%{LIBPATH} install


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/lib/libcanfestival_can_socket.so

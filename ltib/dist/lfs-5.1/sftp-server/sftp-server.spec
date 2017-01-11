%define pfx /opt/freescale/rootfs/%{_target_cpu}
%define aname openssh
%define avers 4.3p2

Summary         : sftp-server using SSH protocol versions 1 and 2
Name            : sftp-server
Version         : %{avers}
Release         : 1
License         : BSD
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/Internet
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed sftp-server for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/Internet
AutoReqProv     : no

%Description rfs
sftp-server package contents restricted to just the files that
are needed at run time on the target.


%Description
%{summary}


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
LD=gcc ./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} --with-zlib=$DEV_IMAGE/usr/lib --with-ldflags=-L$DEV_IMAGE/usr/lib
make -j$(nproc) sysconfdir=%{_sysconfdir}/ssh sftp-server


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

make -j1 DESTDIR=$RPM_BUILD_ROOT/%{pfx} sysconfdir=%{_sysconfdir}/ssh install


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/libexec/sftp-server

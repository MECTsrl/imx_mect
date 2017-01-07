%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : A full-featured SSL VPN solution
Name            : openvpn
Version         : 2.3.10
Release         : 1
License         : GPLv2
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/Internet
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed %{name} for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/Internet
AutoReqProv     : no

%Description rfs
%{name} package contents limited to just the files
needed at run time on the target.


%Description
OpenVPN is a robust and highly flexible tunneling application
that uses all of the encryption, authentication, and
certification features of the OpenSSL library to securely
tunnel IP networks over a single UDP or TCP port.  It can
use the Marcus Franz Xaver Johannes Oberhumer's LZO library
for compression.


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
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} --disable-plugin-auth-pam

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
%{pfx}/usr/sbin/openvpn
%{pfx}/usr/lib/openvpn/plugins/openvpn-plugin-down-root.so

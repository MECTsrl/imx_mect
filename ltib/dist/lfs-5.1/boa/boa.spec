%define base %(echo %{_prefix} | sed -e s,/usr.*$,,)
%define pfx /opt/freescale/rootfs/%{_target_cpu}


Summary         : Lightweight http server for embedded systems
Name            : boa
Version         : 0.94.14rc21
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : System/Servers
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed %{name} for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System/Servers
AutoReqProv     : no

%Description rfs
%{name} package contents limited to just the files
needed at run time on the target.


%Description
%{summary}

This is the uclinux version extracted
from uClinux-dist-test-20050906.tar.gz at
http://www.uclinux.org/pub/uClinux/dist/


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
ac_cv_func_setvbuf_reversed=no \
CFLAGS="-DSERVER_ROOT='\"/etc\"' -g -Os" \
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make -j1


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

mkdir -p $RPM_BUILD_ROOT%{pfx}/%{base}/etc/conf
mkdir -p $RPM_BUILD_ROOT%{pfx}/%{base}/var/log/boa
mkdir -p $RPM_BUILD_ROOT%{pfx}/%{_prefix}/sbin
install -m 755 src/boa $RPM_BUILD_ROOT%{pfx}/%{_prefix}/sbin/
install -m 755 src/boa_indexer $RPM_BUILD_ROOT%{pfx}/%{_prefix}/sbin/
ln -s conf/boa.conf $RPM_BUILD_ROOT%{pfx}/%{base}/etc/boa.conf
ln -s boa $RPM_BUILD_ROOT%{pfx}/%{_prefix}/sbin/boa_d


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/etc/boa.conf
%{pfx}/etc/conf
%{pfx}/usr/sbin/boa
%{pfx}/usr/sbin/boa_d
%{pfx}/usr/sbin/boa_indexer
%{pfx}/var/log/boa

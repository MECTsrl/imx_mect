%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Host/service/network monitoring agent for Nagios
Name            : nrpe
Version         : 2.15
Release         : 1
License         : GPLv2
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed %{name} for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no

%Description rfs
%{name} package contents restricted to just the files that
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
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} --with-ssl-inc=$DEV_IMAGE/usr --with-ssl-lib=$DEV_IMAGE/usr/lib --enable-command-args
make


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT%{pfx}%{_prefix}

make DESTDIR=$RPM_BUILD_ROOT%{pfx} NAGIOS_INSTALL_OPTS= NRPE_INSTALL_OPTS= install


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/bin/nrpe

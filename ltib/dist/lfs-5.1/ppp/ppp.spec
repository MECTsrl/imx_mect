%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Point-to-Point Protocol daemon
Name            : ppp
Version         : 2.4.4
Release         : 1
License         : BSD-like and GPL and Public Domain
Vendor          : Freescale
Packager        : Michael Barkowski
Group           : System Environment/Daemons
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed ppp for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Daemons
AutoReqProv     : no

%Description rfs
ppp package contents restricted to just the files that are
needed at run time on the target.


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
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build} --mandir=%{_mandir}
if [ "$PKG_PPP_WANT_FILTER" = "y" ]
then
    echo "Including support for PPP packet filtering.  Requires libpcap and kernel driver support."
    make -j1 FILTER=y
else
    make -j1
fi


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make -j1 install INSTALL=install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
mkdir -p $RPM_BUILD_ROOT/%{pfx}/var/lock


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/lib/pppd/2.4.4/minconn.so
%{pfx}/lib/pppd/2.4.4/passprompt.so
%{pfx}/lib/pppd/2.4.4/passwordfd.so
%{pfx}/lib/pppd/2.4.4/pppoatm.so
%{pfx}/lib/pppd/2.4.4/radattr.so
%{pfx}/lib/pppd/2.4.4/radius.so
%{pfx}/lib/pppd/2.4.4/radrealms.so
%{pfx}/lib/pppd/2.4.4/rp-pppoe.so
%{pfx}/lib/pppd/2.4.4/winbind.so
%{pfx}/sbin/chat
%{pfx}/sbin/pppd
%{pfx}/sbin/pppdump
%{pfx}/sbin/pppoe-discovery
%{pfx}/sbin/pppstats

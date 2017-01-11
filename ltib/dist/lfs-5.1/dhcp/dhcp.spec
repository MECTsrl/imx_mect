%define base %(echo %{_prefix} | sed -e s,/usr.*$,,)
%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Internet Systems Consortium DHCP server, client, and relay agent
Name            : dhcp
Version         : 3.0.3b1
Release         : 1
License         : Internet Systems Consortium (distributable)
Vendor          : Freescale
Packager        : John Faith
Group           : Applications/Internet
URL             : http://www.isc.org/sw/dhcp/
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed dhcp for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/Internet
AutoReqProv     : no

%Description rfs
dhcp package contents restricted to just the files that are
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
./configure
make -j$(nproc)


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

make install prefix=$RPM_BUILD_ROOT%{pfx}

mkdir -p $RPM_BUILD_ROOT%{pfx}%{_prefix}/share
mv $RPM_BUILD_ROOT%{pfx}%{_prefix}/man  $RPM_BUILD_ROOT%{pfx}%{_prefix}/share
chmod 755 $RPM_BUILD_ROOT%{pfx}/%base/sbin/dhclient-script

for i in %pfx/%base/etc/test %pfx/%base/etc/rc.d \
         %pfx/%base/sbin/S30dhclient %pfx/%_prefix/local
do
    rm -rf $RPM_BUILD_ROOT/$i
done

if [ -z "$PKG_DHCP_WANT_CLIENT" ]; then
    for i in %pfx/%base/etc/dhclient.conf \
             %pfx/%base/var/state/dhcp/dhclient.leases \
             %pfx/%base/sbin/dhclient-script \
             %pfx/%base/sbin/dhclient \
             %pfx/%base/bin/parse \
             %pfx/%base/etc/dhclient-exit-hooks \
             %pfx/%base/etc/dhclient.conf \
             %pfx/%_mandir/man5/dhclient.conf.5 \
             %pfx/%_mandir/man5/dhclient.leases.5 \
             %pfx/%_mandir/man8/dhclient-script.8 \
             %pfx/%_mandir/man8/dhclient.8
    do
        rm -rf $RPM_BUILD_ROOT$i
    done
fi

if [ -z "$PKG_DHCP_WANT_SERVER" ]; then
    for i in %pfx/%base/etc/dhcpd.conf \
             %pfx/%_bindir/omshell \
             %pfx/%_mandir/man1/omshell.1 \
             %pfx/%_mandir/man3/dhcpctl.3 \
             %pfx/%_mandir/man3/omapi.3 \
             %pfx/%_mandir/man3/omshell.3 \
             %pfx/%_mandir/man5/dhcp-eval.5 \
             %pfx/%_mandir/man5/dhcp-options.5 \
             %pfx/%_mandir/man5/dhcpd.conf.5 \
             %pfx/%_mandir/man5/dhcpd.leases.5 \
             %pfx/%_mandir/man8/dhcpd.8 \
             %pfx/%_mandir/man8/dhcrelay.8 \
             %pfx/%_sbindir/dhcpd \
             %pfx/%_sbindir/dhcrelay \
             %pfx/%base/var/state/dhcp/dhcpd.leases
     do
        rm -rf $RPM_BUILD_ROOT$i
     done
fi


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/bin/parse
%{pfx}/etc/dhclient-exit-hooks
%{pfx}/sbin/dhclient
%{pfx}/sbin/dhclient-script
%{pfx}/usr/bin
%{pfx}/usr/sbin
%{pfx}/var/state/dhcp/dhclient.leases

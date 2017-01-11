%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary		: Tools for managing kernel packet filtering capabilities
Name		: iptables
Version		: 1.4.2
Release		: 1
License		: GPL
Vendor		: Freescale
Packager	: Stuart Hughes, Emil Medve
Group		: System Environment/Base
URL		: http://www.netfilter.org/projects/iptables
BuildRoot	: %{_tmppath}/%{name}
Prefix		: %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed %{name} for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group		: System Environment/Base
AutoReqProv     : no

%Description rfs
%{name} package contents limited to just the files
needed at run time on the target.


%Description
%{summary}

iptables is the userspace command line program used to configure
the Linux 2.4.x and 2.6.x IPv4 packet filtering ruleset. It
is targeted towards system administrators

Since Network Address Translation is also configured from the
packet filter ruleset, iptables is used for this, too

The iptables package also includes ip6tables. ip6tables is
used for configuring the IPv6 packet filter

iptables requires a kernel that features the ip_tables packet
filter. This includes all 2.4.x and 2.6.x kernel releases

Main Features
* listing the contents of the packet filter ruleset
* adding/removing/modifying rules in the packet filter ruleset
* listing/zeroing per-rule counters of the packet filter ruleset


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
./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT/%{pfx}
find $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/lib/ -name "*.la" | xargs rm -f


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/lib/libxtables.so
%{pfx}/usr/lib/libxtables.so.0
%{pfx}/usr/lib/libxtables.so.0.0.0
%{pfx}/usr/libexec/xtables/libxt_CLASSIFY.so
%{pfx}/usr/libexec/xtables/libxt_CONNMARK.so
%{pfx}/usr/libexec/xtables/libxt_CONNSECMARK.so
%{pfx}/usr/libexec/xtables/libxt_DSCP.so
%{pfx}/usr/libexec/xtables/libxt_MARK.so
%{pfx}/usr/libexec/xtables/libxt_NFLOG.so
%{pfx}/usr/libexec/xtables/libxt_NFQUEUE.so
%{pfx}/usr/libexec/xtables/libxt_NOTRACK.so
%{pfx}/usr/libexec/xtables/libxt_RATEEST.so
%{pfx}/usr/libexec/xtables/libxt_SECMARK.so
%{pfx}/usr/libexec/xtables/libxt_TCPMSS.so
%{pfx}/usr/libexec/xtables/libxt_TCPOPTSTRIP.so
%{pfx}/usr/libexec/xtables/libxt_TOS.so
%{pfx}/usr/libexec/xtables/libxt_TRACE.so
%{pfx}/usr/libexec/xtables/libxt_comment.so
%{pfx}/usr/libexec/xtables/libxt_connbytes.so
%{pfx}/usr/libexec/xtables/libxt_connlimit.so
%{pfx}/usr/libexec/xtables/libxt_connmark.so
%{pfx}/usr/libexec/xtables/libxt_conntrack.so
%{pfx}/usr/libexec/xtables/libxt_dccp.so
%{pfx}/usr/libexec/xtables/libxt_dscp.so
%{pfx}/usr/libexec/xtables/libxt_esp.so
%{pfx}/usr/libexec/xtables/libxt_hashlimit.so
%{pfx}/usr/libexec/xtables/libxt_helper.so
%{pfx}/usr/libexec/xtables/libxt_iprange.so
%{pfx}/usr/libexec/xtables/libxt_l7pm.so
%{pfx}/usr/libexec/xtables/libxt_length.so
%{pfx}/usr/libexec/xtables/libxt_limit.so
%{pfx}/usr/libexec/xtables/libxt_mac.so
%{pfx}/usr/libexec/xtables/libxt_mark.so
%{pfx}/usr/libexec/xtables/libxt_multiport.so
%{pfx}/usr/libexec/xtables/libxt_owner.so
%{pfx}/usr/libexec/xtables/libxt_physdev.so
%{pfx}/usr/libexec/xtables/libxt_pkttype.so
%{pfx}/usr/libexec/xtables/libxt_quota.so
%{pfx}/usr/libexec/xtables/libxt_rateest.so
%{pfx}/usr/libexec/xtables/libxt_sctp.so
%{pfx}/usr/libexec/xtables/libxt_standard.so
%{pfx}/usr/libexec/xtables/libxt_state.so
%{pfx}/usr/libexec/xtables/libxt_statistic.so
%{pfx}/usr/libexec/xtables/libxt_string.so
%{pfx}/usr/libexec/xtables/libxt_tcp.so
%{pfx}/usr/libexec/xtables/libxt_tcpmss.so
%{pfx}/usr/libexec/xtables/libxt_time.so
%{pfx}/usr/libexec/xtables/libxt_tos.so
%{pfx}/usr/libexec/xtables/libxt_u32.so
%{pfx}/usr/libexec/xtables/libxt_udp.so
%{pfx}/usr/sbin/iptables
%{pfx}/usr/sbin/iptables-multi
%{pfx}/usr/sbin/iptables-restore
%{pfx}/usr/sbin/iptables-save

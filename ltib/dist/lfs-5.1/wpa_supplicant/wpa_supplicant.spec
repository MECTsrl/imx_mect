%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : WPA Supplicant for wifi
Name            : wpa_supplicant
Version         : 0.5.9
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Sam Yang
Group           : Applications/System
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed %{name} to just the runtimes needed on the root file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no

%Description rfs
%{name} package contents reduced to just the runtimes
that are needed on the target.


%Description
%{name} is an implementation of the WPA Supplicant component,
i.e., the part that runs in the client stations. It implements WPA key
negotiation with a WPA Authenticator and EAP authentication with
Authentication Server. In addition, it controls the roaming and IEEE
802.11 authentication/association of the wlan driver.

%{summary}


%Prep
export LC_ALL
LC_ALL=C

%setup -T -c -n %{name}
cd ..; rmdir %{name}; ln -s ../../../projects/%{name} %{name}


%Build
export LC_ALL
LC_ALL=C

make CONFIG_L2_PACKET=linux prefix=%{_prefix}


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

make install CONFIG_L2_PACKET=linux prefix=%{_prefix} DESTDIR=$RPM_BUILD_ROOT/%{pfx}


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/sbin/wpa_cli
%{pfx}/usr/sbin/wpa_passphrase
%{pfx}/usr/sbin/wpa_supplicant

%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : USB Modeswitch gets mobile broadband cards in operational mode
Name            : usb-modeswitch
Version         : 2.3.0
Release         : 1
License         : LGPL
Vendor          : MECT
Packager        : Mihai Lazarescu
Group           : Applications/System
Source1         : usb_modeswitch_helper
Requires        : usb-modeswitch-data
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed down to just the run time files
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
Requires        : usb-modeswitch-data-rfs
AutoReqProv     : no

%Description rfs
%name} package contents trimmed to just the files
that are needed at run time on the target.


%Description
%{summary}.


%Prep
export LC_ALL
LC_ALL=C

%setup -T -c -n %{name}
cd ..; rmdir %{name}; ln -s ../../../projects/%{name} %{name}


%Build
export LC_ALL
LC_ALL=C

make


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

# Target install-static does not depend on external Tcl interpreter/libs.
make install-static DESTDIR=$RPM_BUILD_ROOT/%{pfx}

install -m755 -D %{SOURCE1} $RPM_BUILD_ROOT/%{pfx}/usr/sbin/$(basename %{SOURCE1})


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/sbin/usb_modeswitch
%{pfx}/usr/sbin/usb_modeswitch_helper

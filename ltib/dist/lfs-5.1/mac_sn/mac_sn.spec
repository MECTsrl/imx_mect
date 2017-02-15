%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : GUI to set up MAC address of Ethernet cards
Name            : mac_sn
Version         : 1.0
Release         : 1
License         : GPL
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/File
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed %{name} to just runtimes
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/File
AutoReqProv     : no

%Description rfs
%{name} package contents limited to just the files
needed at run time on the target system.


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

test -r Makefile && make clean
/opt/MECT/Trolltech/bin/qmake \
	-spec qws/linux-g++-mx \
	"INCLUDEPATH+=$RPM_BUILD_DIR/../../rootfs/usr/include $RPM_BUILD_DIR/../../rootfs/usr/src/linux/include" \
	"DEFINES+=TARGET_ARM" \
	"QMAKE_LIBDIR+=$RPM_BUILD_DIR/../../rootfs/usr/lib" \
	mac_sn.pro
make -j1


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

install -D -m 0755 mac_sn $RPM_BUILD_ROOT%{pfx}/usr/bin/mac_sn


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/bin/mac_sn

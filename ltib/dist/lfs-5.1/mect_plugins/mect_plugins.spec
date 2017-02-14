%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Custom Qt plugins for HMI development.
Name            : mect_plugins
Version: 0.0
Release         : 1
License         : GPL
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Libraries
URL             : http://www.mect.it/
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed %{name} to just the run-times needed in the root file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Libraries
AutoReqProv     : no

%Description rfs
%{name} package contents limited to just the run-times needed
on the target.


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

export MECT_RFSDIR
MECT_RFSDIR=$DEV_IMAGE

test -r Makefile && make clean
../../host_tools/Trolltech/bin/qmake -spec qws/linux-g++-mx qt_atcm.pro
make -j1


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make -j1 INSTALL_ROOT=$RPM_BUILD_ROOT%{pfx} install


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/lib/libATCMalarms.so
%{pfx}/usr/lib/libATCMalarms.so.1
%{pfx}/usr/lib/libATCMalarms.so.1.0
%{pfx}/usr/lib/libATCMalarms.so.1.0.0
%{pfx}/usr/lib/libATCMcommon.so
%{pfx}/usr/lib/libATCMcommon.so.1
%{pfx}/usr/lib/libATCMcommon.so.1.0
%{pfx}/usr/lib/libATCMcommon.so.1.0.0
%{pfx}/usr/lib/libATCMcommunication.so
%{pfx}/usr/lib/libATCMcommunication.so.1
%{pfx}/usr/lib/libATCMcommunication.so.1.0
%{pfx}/usr/lib/libATCMcommunication.so.1.0.0
%{pfx}/usr/lib/libATCMinputdialog.so
%{pfx}/usr/lib/libATCMinputdialog.so.1
%{pfx}/usr/lib/libATCMinputdialog.so.1.0
%{pfx}/usr/lib/libATCMinputdialog.so.1.0.0
%{pfx}/usr/lib/libATCMlogger.so
%{pfx}/usr/lib/libATCMlogger.so.1
%{pfx}/usr/lib/libATCMlogger.so.1.0
%{pfx}/usr/lib/libATCMlogger.so.1.0.0
%{pfx}/usr/lib/libATCMplugin.so
%{pfx}/usr/lib/libATCMplugin.so.1
%{pfx}/usr/lib/libATCMplugin.so.1.0
%{pfx}/usr/lib/libATCMplugin.so.1.0.0
%{pfx}/usr/lib/libATCMrecipe.so
%{pfx}/usr/lib/libATCMrecipe.so.1
%{pfx}/usr/lib/libATCMrecipe.so.1.0
%{pfx}/usr/lib/libATCMrecipe.so.1.0.0
%{pfx}/usr/lib/libATCMstore.so
%{pfx}/usr/lib/libATCMstore.so.1
%{pfx}/usr/lib/libATCMstore.so.1.0
%{pfx}/usr/lib/libATCMstore.so.1.0.0
%{pfx}/usr/lib/libATCMsystem.so
%{pfx}/usr/lib/libATCMsystem.so.1
%{pfx}/usr/lib/libATCMsystem.so.1.0
%{pfx}/usr/lib/libATCMsystem.so.1.0.0
%{pfx}/usr/lib/libATCMtrend.so
%{pfx}/usr/lib/libATCMtrend.so.1
%{pfx}/usr/lib/libATCMtrend.so.1.0
%{pfx}/usr/lib/libATCMtrend.so.1.0.0
%{pfx}/usr/lib/libATCMutility.so
%{pfx}/usr/lib/libATCMutility.so.1
%{pfx}/usr/lib/libATCMutility.so.1.0
%{pfx}/usr/lib/libATCMutility.so.1.0.0

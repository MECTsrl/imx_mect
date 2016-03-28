%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : ATCM control runtime system application
Name            : local-ATCMcontrol_RunTimeSystem
Version         : %(echo ${MECT_BUILD_ATCMCRT_TAG})
Release         : 1
License         : GPL
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/File
Source          : local.tar.bz2
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}/local
AutoReqProv     : no

%description
ATCM control runtime system provides the run-time execution
environment for the PLC applications built using the ATCM
control engineering SDK.

%prep
export LC_ALL
LC_ALL=C

%build
export LC_ALL
LC_ALL=C

%install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{pfx}/local
cd $RPM_BUILD_ROOT/%{pfx}/local
tar xjvf %{SOURCE0} ./root/fcrts.ATCMcontrol_RunTimeSystem
mv root/fcrts.ATCMcontrol_RunTimeSystem root/fcrts

%clean
sudo rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%{pfx}/local/root/fcrts

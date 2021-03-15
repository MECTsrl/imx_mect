%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Application files for the embedded root filesystem
Name            : local
Version         : 1.0
Release         : 1
License         : GPL
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Utilities
Source          : local.tar.bz2
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}/local
AutoReqProv     : no

%description
%{summary}


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

mkdir -p $RPM_BUILD_ROOT%{pfx}/local
tar xjvf %{SOURCE0} -C $RPM_BUILD_ROOT%{pfx}/local

cd $RPM_BUILD_ROOT%{pfx}/local/root
rm -f fcrts fcrts.4c_runtime fcrts.ATCMcontrol_RunTimeSystem

%clean
sudo rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%attr(0755, root, root) %dir %{pfx}/local/control
%attr(0755, root, root) %dir %{pfx}/local/data/store
%attr(0755, root, root) %dir %{pfx}/local/data/files
%attr(0755, root, root) %dir %{pfx}/local/data/trends
%attr(0755, root, root) %dir %{pfx}/local/sd_card
%attr(0755, root, root) %dir %{pfx}/local/update

%attr(0777, root, root) %dir %{pfx}/local/flash/root/sqldrivers
%{pfx}/local/flash/root/sqldrivers/libqsqlite.so
%{pfx}/local/flash/root/sqldrivers/libqsqlmysql.so
%{pfx}/local/flash/root/sqldrivers/libsqlite3.so
%{pfx}/local/flash/root/sqldrivers/libsqlite3.so.0
%{pfx}/local/flash/root/sqldrivers/libsqlite3.so.0.8.6

%{pfx}/local/retentive

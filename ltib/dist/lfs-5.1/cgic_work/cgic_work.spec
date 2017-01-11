%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Support for web-based reporting and configuration
Name            : cgic_work
Version         : 0.0
Release         : 1
License         : GPL
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System/Servers
URL             : http://www.mect.it/
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed %{name} to just the run-times needed in the root file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System/Servers
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
%{pfx}/usr/share/www/.passwd
%{pfx}/usr/share/www/alarms_manager.cgi
%{pfx}/usr/share/www/changepwd.cgi
%{pfx}/usr/share/www/checkpwd.cgi
%{pfx}/usr/share/www/config_manager.cgi
%{pfx}/usr/share/www/date_time.cgi
%{pfx}/usr/share/www/display.cgi
%{pfx}/usr/share/www/display_csv.cgi
%{pfx}/usr/share/www/display_setup.cgi
%{pfx}/usr/share/www/extract
%{pfx}/usr/share/www/factory_reset.cgi
%{pfx}/usr/share/www/factory_reset_confirm.cgi
%{pfx}/usr/share/www/filebrowser.cgi
%{pfx}/usr/share/www/filesmanager.cgi
%{pfx}/usr/share/www/formatsdcard.cgi
%{pfx}/usr/share/www/getdatesinterval
%{pfx}/usr/share/www/index.cgi
%{pfx}/usr/share/www/info.cgi
%{pfx}/usr/share/www/lan_config.cgi
%{pfx}/usr/share/www/lan_setup.cgi
%{pfx}/usr/share/www/load.cgi
%{pfx}/usr/share/www/login.cgi
%{pfx}/usr/share/www/logout.cgi
%{pfx}/usr/share/www/logs_extractor.cgi
%{pfx}/usr/share/www/logs_filter.cgi
%{pfx}/usr/share/www/logs_manager.cgi
%{pfx}/usr/share/www/managepwd.cgi
%{pfx}/usr/share/www/menu.cgi
%{pfx}/usr/share/www/reboot.cgi
%{pfx}/usr/share/www/recipes_manager.cgi
%{pfx}/usr/share/www/reset_mass_storage.cgi
%{pfx}/usr/share/www/reset_passwords.cgi
%{pfx}/usr/share/www/select
%{pfx}/usr/share/www/select-template.html
%{pfx}/usr/share/www/style.css
%{pfx}/usr/share/www/trend_manager.cgi
%{pfx}/usr/share/www/underconstruction.cgi
%{pfx}/usr/share/www/updateall.cgi
%{pfx}/usr/share/www/updatetime.cgi
%{pfx}/usr/share/www/upgrade.cgi
%{pfx}/usr/share/www/upload.cgi

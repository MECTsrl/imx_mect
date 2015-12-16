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

%Package ATCMcontrol_RunTimeSystem
Summary         : ATCM control runtime system application
Version         : %(echo ${MECT_BUILD_ATCMCRT_TAG})
Release         : 1
Group           : Applications/File
AutoReqProv     : no
%Description ATCMcontrol_RunTimeSystem
ATCM control runtime system provides the run-time execution
environment for the PLC applications built using the ATCM
control engineering SDK.

%Package cgic_work
Summary         : CGI C workers for MECT operator panels
Group           : Applications/File
AutoReqProv     : no
%Description cgic_work
CGI C workers provide various configuration pages and data
colletion and set utilities.

%Package setup_time
Summary         : Application for setting the time and date of the panel
Group           : Applications/File
AutoReqProv     : no
%Description setup_time
Application that provides the operator input for setting the
time and date of the panel.

%Package splash
Summary         : Notifies that panel update is in progress
Group           : Applications/File
AutoReqProv     : no
%Description splash
Simple application that provides a notification screen informing
the operator that a panel update is in progress.

%Package factory_data
Summary         : Factory preset values
Group           : Applications/File
AutoReqProv     : no
%Description factory_data
Factory preset values for all panel settings.


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
tar xjvf %{SOURCE0} -C $RPM_BUILD_ROOT/%{pfx}/local

%clean
sudo rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%{pfx}/local/control
%{pfx}/local/data
%{pfx}/local/etc
%{pfx}/local/factory_data.tar.gz
%{pfx}/local/flash/control
%{pfx}/local/flash/data/customstore/test.csv
%{pfx}/local/flash/data/customtrend/trend1.csv
%{pfx}/local/flash/data/recipe/test/test1.csv
%{pfx}/local/flash/data/store
%{pfx}/local/flash/data/trends
%{pfx}/local/flash/etc/sysconfig/brightness
%{pfx}/local/flash/etc/sysconfig/chatscripts
%{pfx}/local/flash/etc/sysconfig/img/splash.png
%{pfx}/local/flash/etc/sysconfig/img/systool.png
%{pfx}/local/flash/etc/sysconfig/net.conf
%{pfx}/local/flash/etc/sysconfig/.passwd
%{pfx}/local/flash/etc/sysconfig/ppp
%{pfx}/local/flash/root/backing_file
%{pfx}/local/flash/root/fcrts
%{pfx}/local/flash/root/make_usb_device
%{pfx}/local/flash/root/safe_hmi
%{pfx}/local/flash/root/setparam
%{pfx}/local/flash/root/setup_time
%{pfx}/local/flash/root/splash
%{pfx}/local/flash/root/sqldrivers/libqsqlite.so
%{pfx}/local/flash/root/sqldrivers/libqsqlmysql.so
%{pfx}/local/flash/root/writemac
%{pfx}/local/home
%{pfx}/local/retentive
%{pfx}/local/root
%{pfx}/local/sd_card
%{pfx}/local/update
%{pfx}/local/www/alarms_manager.cgi
%{pfx}/local/www/changepwd.cgi
%{pfx}/local/www/checkpwd.cgi
%{pfx}/local/www/config_manager.cgi
%{pfx}/local/www/date_time.cgi
%{pfx}/local/www/display.cgi
%{pfx}/local/www/display.cgi.new
%{pfx}/local/www/display_csv.cgi
%{pfx}/local/www/display_setup.cgi
%{pfx}/local/www/display_setup.cgi.new
%{pfx}/local/www/extract
%{pfx}/local/www/factory_reset.cgi
%{pfx}/local/www/filebrowser.cgi
%{pfx}/local/www/filesmanager.cgi
%{pfx}/local/www/formatsdcard.cgi
%{pfx}/local/www/getdatesinterval
%{pfx}/local/www/index.cgi
%{pfx}/local/www/info.cgi
%{pfx}/local/www/lan_config.cgi
%{pfx}/local/www/lan_setup.cgi
%{pfx}/local/www/load.cgi
%{pfx}/local/www/login.cgi
%{pfx}/local/www/logout.cgi
%{pfx}/local/www/logs_extractor.cgi
%{pfx}/local/www/logs_filter.cgi
%{pfx}/local/www/logs_manager.cgi
%{pfx}/local/www/managepwd.cgi
%{pfx}/local/www/menu.cgi
%{pfx}/local/www/reboot.cgi
%{pfx}/local/www/recipes_manager.cgi
%{pfx}/local/www/reset_mass_storage.cgi
%{pfx}/local/www/reset_passwords.cgi
%{pfx}/local/www/select
%{pfx}/local/www/select-template.html
%{pfx}/local/www/style.css
%{pfx}/local/www/trend_manager.cgi
%{pfx}/local/www/underconstruction.cgi
%{pfx}/local/www/updateall.cgi
%{pfx}/local/www/updatetime.cgi
%{pfx}/local/www/upgrade.cgi
%{pfx}/local/www/upload.cgi

%files ATCMcontrol_RunTimeSystem
%defattr(-,root,root)
%{pfx}/local/flash/root/fcrts

%files cgic_work
%defattr(-,root,root)
%{pfx}/local/www/updateall.cgi
%{pfx}/local/www/upgrade.cgi
%{pfx}/local/www/getdatesinterval
%{pfx}/local/www/extract

%files setup_time
%defattr(-,root,root)
%{pfx}/local/flash/root/setup_time

%files splash
%defattr(-,root,root)
%{pfx}/local/flash/root/splash

%files factory_data
%defattr(-,root,root)
%{pfx}/local/factory_data.tar.gz

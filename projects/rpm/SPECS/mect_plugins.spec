Summary         : Custom Qt plugins for HMI development.
Name            : mect_plugins
Version         : %{ver}
Release         : 1_%{rel}
License         : GPL
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Libraries
Source          : mect_plugins-%{version}.tar
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{RFSDIR}
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


%description
%{summary}

%prep
export LC_ALL
LC_ALL=C

%setup

%build
export LC_ALL
LC_ALL=C

%{QMAKE} RFSDIR=%{RFSDIR} -spec qws/linux-g++-mx qt_atcm.pro
#make -j`grep -c ^processor /proc/cpuinfo`
make -j1

%install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make -j1 INSTALL_ROOT=%{buildroot} install

%clean
sudo rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%{RFSDIR}/usr/include/alarms.h
%{RFSDIR}/usr/include/alarms_history.h
%{RFSDIR}/usr/include/alphanumpad.h
%{RFSDIR}/usr/include/app_cfg_file.h
%{RFSDIR}/usr/include/app_config.h
%{RFSDIR}/usr/include/app_logprint.h
%{RFSDIR}/usr/include/app_usb.h
%{RFSDIR}/usr/include/app_var_list.h
%{RFSDIR}/usr/include/atcmanimation.h
%{RFSDIR}/usr/include/atcmbutton.h
%{RFSDIR}/usr/include/atcmcombobox.h
%{RFSDIR}/usr/include/atcmdate.h
%{RFSDIR}/usr/include/atcmgraph.h
%{RFSDIR}/usr/include/atcmlabel.h
%{RFSDIR}/usr/include/atcmlcdnumber.h
%{RFSDIR}/usr/include/atcmled.h
%{RFSDIR}/usr/include/atcmplugin.h
%{RFSDIR}/usr/include/atcmprogressbar.h
%{RFSDIR}/usr/include/atcmslider.h
%{RFSDIR}/usr/include/atcmspinbox.h
%{RFSDIR}/usr/include/atcmstyle.h
%{RFSDIR}/usr/include/atcmtime.h
%{RFSDIR}/usr/include/buzzer_settings.h
%{RFSDIR}/usr/include/comm_status.h
%{RFSDIR}/usr/include/common.h
%{RFSDIR}/usr/include/commpar_rtu.h
%{RFSDIR}/usr/include/commpar_tcp.h
%{RFSDIR}/usr/include/commpar_tcprtu.h
%{RFSDIR}/usr/include/cross_table_utility.h
%{RFSDIR}/usr/include/data_manager.h
%{RFSDIR}/usr/include/datalog_set.h
%{RFSDIR}/usr/include/defines.h
%{RFSDIR}/usr/include/display_settings.h
%{RFSDIR}/usr/include/global_functions.h
%{RFSDIR}/usr/include/global_var.h
%{RFSDIR}/usr/include/hmi_logger.h
%{RFSDIR}/usr/include/info.h
%{RFSDIR}/usr/include/io_layer_comm.h
%{RFSDIR}/usr/include/item_selector.h
%{RFSDIR}/usr/include/main.h
%{RFSDIR}/usr/include/menu.h
%{RFSDIR}/usr/include/numpad.h
%{RFSDIR}/usr/include/options.h
%{RFSDIR}/usr/include/page0.h
%{RFSDIR}/usr/include/pagebrowser.h
%{RFSDIR}/usr/include/recipe.h
%{RFSDIR}/usr/include/recipe_select.h
%{RFSDIR}/usr/include/screensaver.h
%{RFSDIR}/usr/include/setstyle.h
%{RFSDIR}/usr/include/sgdd.h
%{RFSDIR}/usr/include/store.h
%{RFSDIR}/usr/include/store_extract.h
%{RFSDIR}/usr/include/store_filter.h
%{RFSDIR}/usr/include/time_set.h
%{RFSDIR}/usr/include/trend.h
%{RFSDIR}/usr/include/trend_option.h
%{RFSDIR}/usr/include/trend_other.h
%{RFSDIR}/usr/include/trend_range.h
%{RFSDIR}/usr/include/utility.h
%{RFSDIR}/usr/lib/libATCMalarms.so
%{RFSDIR}/usr/lib/libATCMalarms.so.1
%{RFSDIR}/usr/lib/libATCMalarms.so.1.0
%{RFSDIR}/usr/lib/libATCMalarms.so.1.0.0
%{RFSDIR}/usr/lib/libATCMcommon.so
%{RFSDIR}/usr/lib/libATCMcommon.so.1
%{RFSDIR}/usr/lib/libATCMcommon.so.1.0
%{RFSDIR}/usr/lib/libATCMcommon.so.1.0.0
%{RFSDIR}/usr/lib/libATCMcommunication.so
%{RFSDIR}/usr/lib/libATCMcommunication.so.1
%{RFSDIR}/usr/lib/libATCMcommunication.so.1.0
%{RFSDIR}/usr/lib/libATCMcommunication.so.1.0.0
%{RFSDIR}/usr/lib/libATCMinputdialog.so
%{RFSDIR}/usr/lib/libATCMinputdialog.so.1
%{RFSDIR}/usr/lib/libATCMinputdialog.so.1.0
%{RFSDIR}/usr/lib/libATCMinputdialog.so.1.0.0
%{RFSDIR}/usr/lib/libATCMlogger.so
%{RFSDIR}/usr/lib/libATCMlogger.so.1
%{RFSDIR}/usr/lib/libATCMlogger.so.1.0
%{RFSDIR}/usr/lib/libATCMlogger.so.1.0.0
%{RFSDIR}/usr/lib/libATCMplugin.so
%{RFSDIR}/usr/lib/libATCMplugin.so.1
%{RFSDIR}/usr/lib/libATCMplugin.so.1.0
%{RFSDIR}/usr/lib/libATCMplugin.so.1.0.0
%{RFSDIR}/usr/lib/libATCMrecipe.so
%{RFSDIR}/usr/lib/libATCMrecipe.so.1
%{RFSDIR}/usr/lib/libATCMrecipe.so.1.0
%{RFSDIR}/usr/lib/libATCMrecipe.so.1.0.0
%{RFSDIR}/usr/lib/libATCMstore.so
%{RFSDIR}/usr/lib/libATCMstore.so.1
%{RFSDIR}/usr/lib/libATCMstore.so.1.0
%{RFSDIR}/usr/lib/libATCMstore.so.1.0.0
%{RFSDIR}/usr/lib/libATCMsystem.so
%{RFSDIR}/usr/lib/libATCMsystem.so.1
%{RFSDIR}/usr/lib/libATCMsystem.so.1.0
%{RFSDIR}/usr/lib/libATCMsystem.so.1.0.0
%{RFSDIR}/usr/lib/libATCMtrend.so
%{RFSDIR}/usr/lib/libATCMtrend.so.1
%{RFSDIR}/usr/lib/libATCMtrend.so.1.0
%{RFSDIR}/usr/lib/libATCMtrend.so.1.0.0
%{RFSDIR}/usr/lib/libATCMutility.so
%{RFSDIR}/usr/lib/libATCMutility.so.1
%{RFSDIR}/usr/lib/libATCMutility.so.1.0
%{RFSDIR}/usr/lib/libATCMutility.so.1.0.0

%files rfs
%defattr(-,root,root)
%{RFSDIR}/usr/lib/libATCMalarms.so
%{RFSDIR}/usr/lib/libATCMalarms.so.1
%{RFSDIR}/usr/lib/libATCMalarms.so.1.0
%{RFSDIR}/usr/lib/libATCMalarms.so.1.0.0
%{RFSDIR}/usr/lib/libATCMcommon.so
%{RFSDIR}/usr/lib/libATCMcommon.so.1
%{RFSDIR}/usr/lib/libATCMcommon.so.1.0
%{RFSDIR}/usr/lib/libATCMcommon.so.1.0.0
%{RFSDIR}/usr/lib/libATCMcommunication.so
%{RFSDIR}/usr/lib/libATCMcommunication.so.1
%{RFSDIR}/usr/lib/libATCMcommunication.so.1.0
%{RFSDIR}/usr/lib/libATCMcommunication.so.1.0.0
%{RFSDIR}/usr/lib/libATCMinputdialog.so
%{RFSDIR}/usr/lib/libATCMinputdialog.so.1
%{RFSDIR}/usr/lib/libATCMinputdialog.so.1.0
%{RFSDIR}/usr/lib/libATCMinputdialog.so.1.0.0
%{RFSDIR}/usr/lib/libATCMlogger.so
%{RFSDIR}/usr/lib/libATCMlogger.so.1
%{RFSDIR}/usr/lib/libATCMlogger.so.1.0
%{RFSDIR}/usr/lib/libATCMlogger.so.1.0.0
%{RFSDIR}/usr/lib/libATCMplugin.so
%{RFSDIR}/usr/lib/libATCMplugin.so.1
%{RFSDIR}/usr/lib/libATCMplugin.so.1.0
%{RFSDIR}/usr/lib/libATCMplugin.so.1.0.0
%{RFSDIR}/usr/lib/libATCMrecipe.so
%{RFSDIR}/usr/lib/libATCMrecipe.so.1
%{RFSDIR}/usr/lib/libATCMrecipe.so.1.0
%{RFSDIR}/usr/lib/libATCMrecipe.so.1.0.0
%{RFSDIR}/usr/lib/libATCMstore.so
%{RFSDIR}/usr/lib/libATCMstore.so.1
%{RFSDIR}/usr/lib/libATCMstore.so.1.0
%{RFSDIR}/usr/lib/libATCMstore.so.1.0.0
%{RFSDIR}/usr/lib/libATCMsystem.so
%{RFSDIR}/usr/lib/libATCMsystem.so.1
%{RFSDIR}/usr/lib/libATCMsystem.so.1.0
%{RFSDIR}/usr/lib/libATCMsystem.so.1.0.0
%{RFSDIR}/usr/lib/libATCMtrend.so
%{RFSDIR}/usr/lib/libATCMtrend.so.1
%{RFSDIR}/usr/lib/libATCMtrend.so.1.0
%{RFSDIR}/usr/lib/libATCMtrend.so.1.0.0
%{RFSDIR}/usr/lib/libATCMutility.so
%{RFSDIR}/usr/lib/libATCMutility.so.1
%{RFSDIR}/usr/lib/libATCMutility.so.1.0
%{RFSDIR}/usr/lib/libATCMutility.so.1.0.0

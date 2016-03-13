Summary         : Custom Qt plugins for HMI development.
Name            : mect_plugins
Version         : %(echo ${MECT_BUILD_PLUGINSCRT_TAG})
Release         : 1
License         : GPL
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Libraries
Source          : %{name}-%{version}.tar
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{MECT_RFSDIR}
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

%{MECT_QMAKE} -spec qws/linux-g++-mx qt_atcm.pro
#make -j`grep -c ^processor /proc/cpuinfo`
make -j1

%install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make -j1 INSTALL_ROOT=%{buildroot} install

%clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%{MECT_RFSDIR}/usr/include/alarms.h
%{MECT_RFSDIR}/usr/include/alarms_history.h
%{MECT_RFSDIR}/usr/include/alphanumpad.h
%{MECT_RFSDIR}/usr/include/app_config.h
%{MECT_RFSDIR}/usr/include/app_logprint.h
%{MECT_RFSDIR}/usr/include/app_usb.h
%{MECT_RFSDIR}/usr/include/app_var_list.h
%{MECT_RFSDIR}/usr/include/atcmanimation.h
%{MECT_RFSDIR}/usr/include/atcmbutton.h
%{MECT_RFSDIR}/usr/include/atcmcombobox.h
%{MECT_RFSDIR}/usr/include/atcmdate.h
%{MECT_RFSDIR}/usr/include/atcmgraph.h
%{MECT_RFSDIR}/usr/include/atcmlabel.h
%{MECT_RFSDIR}/usr/include/atcmlcdnumber.h
%{MECT_RFSDIR}/usr/include/atcmled.h
%{MECT_RFSDIR}/usr/include/atcmplugin.h
%{MECT_RFSDIR}/usr/include/atcmprogressbar.h
%{MECT_RFSDIR}/usr/include/atcmslider.h
%{MECT_RFSDIR}/usr/include/atcmspinbox.h
%{MECT_RFSDIR}/usr/include/atcmstyle.h
%{MECT_RFSDIR}/usr/include/atcmtime.h
%{MECT_RFSDIR}/usr/include/common.h
%{MECT_RFSDIR}/usr/include/system_ini.h
%{MECT_RFSDIR}/usr/include/cross_table_utility.h
%{MECT_RFSDIR}/usr/include/data_manager.h
%{MECT_RFSDIR}/usr/include/defines.h
%{MECT_RFSDIR}/usr/include/display_settings.h
%{MECT_RFSDIR}/usr/include/global_functions.h
%{MECT_RFSDIR}/usr/include/global_var.h
%{MECT_RFSDIR}/usr/include/hmi_logger.h
%{MECT_RFSDIR}/usr/include/info.h
%{MECT_RFSDIR}/usr/include/io_layer_comm.h
%{MECT_RFSDIR}/usr/include/item_selector.h
%{MECT_RFSDIR}/usr/include/main.h
%{MECT_RFSDIR}/usr/include/menu.h
%{MECT_RFSDIR}/usr/include/numpad.h
%{MECT_RFSDIR}/usr/include/options.h
%{MECT_RFSDIR}/usr/include/page0.h
%{MECT_RFSDIR}/usr/include/pagebrowser.h
%{MECT_RFSDIR}/usr/include/recipe.h
%{MECT_RFSDIR}/usr/include/recipe_select.h
%{MECT_RFSDIR}/usr/include/screensaver.h
%{MECT_RFSDIR}/usr/include/setstyle.h
%{MECT_RFSDIR}/usr/include/store.h
%{MECT_RFSDIR}/usr/include/store_extract.h
%{MECT_RFSDIR}/usr/include/store_filter.h
%{MECT_RFSDIR}/usr/include/time_set.h
%{MECT_RFSDIR}/usr/include/trend.h
%{MECT_RFSDIR}/usr/include/trend_option.h
%{MECT_RFSDIR}/usr/include/trend_other.h
%{MECT_RFSDIR}/usr/include/trend_range.h
%{MECT_RFSDIR}/usr/include/utility.h
%{MECT_RFSDIR}/usr/lib/libATCMalarms.so
%{MECT_RFSDIR}/usr/lib/libATCMalarms.so.1
%{MECT_RFSDIR}/usr/lib/libATCMalarms.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMalarms.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMcommon.so
%{MECT_RFSDIR}/usr/lib/libATCMcommon.so.1
%{MECT_RFSDIR}/usr/lib/libATCMcommon.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMcommon.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMcommunication.so
%{MECT_RFSDIR}/usr/lib/libATCMcommunication.so.1
%{MECT_RFSDIR}/usr/lib/libATCMcommunication.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMcommunication.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMinputdialog.so
%{MECT_RFSDIR}/usr/lib/libATCMinputdialog.so.1
%{MECT_RFSDIR}/usr/lib/libATCMinputdialog.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMinputdialog.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMlogger.so
%{MECT_RFSDIR}/usr/lib/libATCMlogger.so.1
%{MECT_RFSDIR}/usr/lib/libATCMlogger.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMlogger.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMplugin.so
%{MECT_RFSDIR}/usr/lib/libATCMplugin.so.1
%{MECT_RFSDIR}/usr/lib/libATCMplugin.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMplugin.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMrecipe.so
%{MECT_RFSDIR}/usr/lib/libATCMrecipe.so.1
%{MECT_RFSDIR}/usr/lib/libATCMrecipe.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMrecipe.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMstore.so
%{MECT_RFSDIR}/usr/lib/libATCMstore.so.1
%{MECT_RFSDIR}/usr/lib/libATCMstore.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMstore.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMsystem.so
%{MECT_RFSDIR}/usr/lib/libATCMsystem.so.1
%{MECT_RFSDIR}/usr/lib/libATCMsystem.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMsystem.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMtrend.so
%{MECT_RFSDIR}/usr/lib/libATCMtrend.so.1
%{MECT_RFSDIR}/usr/lib/libATCMtrend.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMtrend.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMutility.so
%{MECT_RFSDIR}/usr/lib/libATCMutility.so.1
%{MECT_RFSDIR}/usr/lib/libATCMutility.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMutility.so.1.0.0

%files rfs
%defattr(-,root,root)
%{MECT_RFSDIR}/usr/lib/libATCMalarms.so
%{MECT_RFSDIR}/usr/lib/libATCMalarms.so.1
%{MECT_RFSDIR}/usr/lib/libATCMalarms.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMalarms.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMcommon.so
%{MECT_RFSDIR}/usr/lib/libATCMcommon.so.1
%{MECT_RFSDIR}/usr/lib/libATCMcommon.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMcommon.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMcommunication.so
%{MECT_RFSDIR}/usr/lib/libATCMcommunication.so.1
%{MECT_RFSDIR}/usr/lib/libATCMcommunication.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMcommunication.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMinputdialog.so
%{MECT_RFSDIR}/usr/lib/libATCMinputdialog.so.1
%{MECT_RFSDIR}/usr/lib/libATCMinputdialog.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMinputdialog.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMlogger.so
%{MECT_RFSDIR}/usr/lib/libATCMlogger.so.1
%{MECT_RFSDIR}/usr/lib/libATCMlogger.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMlogger.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMplugin.so
%{MECT_RFSDIR}/usr/lib/libATCMplugin.so.1
%{MECT_RFSDIR}/usr/lib/libATCMplugin.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMplugin.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMrecipe.so
%{MECT_RFSDIR}/usr/lib/libATCMrecipe.so.1
%{MECT_RFSDIR}/usr/lib/libATCMrecipe.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMrecipe.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMstore.so
%{MECT_RFSDIR}/usr/lib/libATCMstore.so.1
%{MECT_RFSDIR}/usr/lib/libATCMstore.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMstore.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMsystem.so
%{MECT_RFSDIR}/usr/lib/libATCMsystem.so.1
%{MECT_RFSDIR}/usr/lib/libATCMsystem.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMsystem.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMtrend.so
%{MECT_RFSDIR}/usr/lib/libATCMtrend.so.1
%{MECT_RFSDIR}/usr/lib/libATCMtrend.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMtrend.so.1.0.0
%{MECT_RFSDIR}/usr/lib/libATCMutility.so
%{MECT_RFSDIR}/usr/lib/libATCMutility.so.1
%{MECT_RFSDIR}/usr/lib/libATCMutility.so.1.0
%{MECT_RFSDIR}/usr/lib/libATCMutility.so.1.0.0

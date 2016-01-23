%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Default HMI application.
Name            : mect_apps
Version         : %(echo ${MECT_BUILD_APPSCRT_TAG})
Release         : 1
License         : GPL
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
Source          : %{name}-%{version}.tar
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}/local
AutoReqProv     : no


%Package lfs-TPAC1007_4AA
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no

%Description lfs-TPAC1007_4AA
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

d=TPAC1007_04_AA/Local_IO_HMI
if test -d $d; then
	cd $d

	%{MECT_QMAKE} \
		-spec qws/linux-g++-mx \
		"INCLUDEPATH+=${MECT_RFSDIR}/usr/include ${MECT_RFSDIR}/usr/src/linux/include" \
		"DEFINES+=TARGET_ARM" \
		"QMAKE_LIBDIR+=${MECT_RFSDIR}/usr/lib" \
		Local_IO_HMI.pro
	make -j`grep -c ^processor /proc/cpuinfo`

	cd -
fi

%install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

d=TPAC1007_04_AA/Local_IO_HMI
if test -d $d; then
	cd $d

	install -m755 -D hmi                   $RPM_BUILD_ROOT%{pfx}/local/flash/root/hmi
	install -m644 -D config/Alarms.csv     $RPM_BUILD_ROOT%{pfx}/local/etc/sysconfig/Alarms.csv
	install -m644 -D config/Crosstable.csv $RPM_BUILD_ROOT%{pfx}/local/etc/sysconfig/Crosstable.csv
	install -m644 -D config/lang_table.csv $RPM_BUILD_ROOT%{pfx}/local/etc/sysconfig/lang_table.csv
	install -m644 -D config/splash.png     $RPM_BUILD_ROOT%{pfx}/local/etc/sysconfig/img/splash.png
	install -m644 -D config/store1.csv     $RPM_BUILD_ROOT%{pfx}/local/flash/data/customstore/store1.csv
	install -m644 -D config/system.ini     $RPM_BUILD_ROOT%{pfx}/local/etc/system/system.ini
	install -m644 -D config/trend1.csv     $RPM_BUILD_ROOT%{pfx}/local/flash/data/customtrend/trend1.csv

	cd -
fi

%clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%{pfx}/local/flash/root/hmi
%{pfx}/local/etc/sysconfig/Alarms.csv
%{pfx}/local/etc/sysconfig/Crosstable.csv
%{pfx}/local/etc/sysconfig/img/splash.png
%{pfx}/local/etc/sysconfig/lang_table.csv
%{pfx}/local/etc/system/system.ini
%{pfx}/local/flash/data/customstore/store1.csv
%{pfx}/local/flash/data/customtrend/trend1.csv

%files lfs-TPAC1007_4AA
%defattr(-,root,root)
%{pfx}/local/flash/root/hmi
%{pfx}/local/etc/sysconfig/Alarms.csv
%{pfx}/local/etc/sysconfig/Crosstable.csv
%{pfx}/local/etc/sysconfig/img/splash.png
%{pfx}/local/etc/sysconfig/lang_table.csv
%{pfx}/local/etc/system/system.ini
%{pfx}/local/flash/data/customstore/store1.csv
%{pfx}/local/flash/data/customtrend/trend1.csv

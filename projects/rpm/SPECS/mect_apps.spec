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
Patch0          : mect_apps-TPAC1007_3-windows-to-linux.patch
Patch1          : mect_apps-TPAC1007_4AA-windows-to-linux.patch
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}/local
AutoReqProv     : no


# TPAC1007_3
#
%Package lfs-TPAC1007_3
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TPAC1007_3/local

%Description lfs-TPAC1007_3
%{name} package contents limited to just the run-times needed
on the target.

# TPAC1007_4AA
#
%Package lfs-TPAC1007_4AA
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TPAC1007_4AA/local

%Description lfs-TPAC1007_4AA
%{name} package contents limited to just the run-times needed
on the target.


%description
%{summary}

%prep
export LC_ALL
LC_ALL=C

%setup

%patch0 -p1
%patch1 -p1

%build
export LC_ALL
LC_ALL=C

# TPAC1007_3
#
d=TPAC1007/Local_IO_HMI
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

# TPAC1007_4AA
#
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

# TPAC1007_3
#
d=TPAC1007/Local_IO_HMI
if test -d $d; then
	cd $d

	install -m755 -D hmi                   $RPM_BUILD_ROOT%{pfx}/TPAC1007_3/local/root/hmi
	install -m644 -D config/Crosstable.csv $RPM_BUILD_ROOT%{pfx}/TPAC1007_3/local/etc/sysconfig/Crosstable.csv
	install -m644 -D config/splash.png     $RPM_BUILD_ROOT%{pfx}/TPAC1007_3/local/etc/sysconfig/img/splash.png
	install -m644 -D config/system.ini     $RPM_BUILD_ROOT%{pfx}/TPAC1007_3/local/etc/sysconfig/system.ini
	install -m644 -D config/trend1.csv     $RPM_BUILD_ROOT%{pfx}/TPAC1007_3/local/data/customtrend/trend1.csv

	cd -
fi

# TPAC1007_4AA
#
d=TPAC1007_04_AA/Local_IO_HMI
if test -d $d; then
	cd $d

	install -m755 -D hmi                   $RPM_BUILD_ROOT%{pfx}/TPAC1007_4AA/local/root/hmi
	install -m644 -D config/Crosstable.csv $RPM_BUILD_ROOT%{pfx}/TPAC1007_4AA/local/etc/sysconfig/Crosstable.csv
	install -m644 -D config/splash.png     $RPM_BUILD_ROOT%{pfx}/TPAC1007_4AA/local/etc/sysconfig/img/splash.png
	install -m644 -D config/system.ini     $RPM_BUILD_ROOT%{pfx}/TPAC1007_4AA/local/etc/sysconfig/system.ini
	install -m644 -D config/trend1.csv     $RPM_BUILD_ROOT%{pfx}/TPAC1007_4AA/local/data/customtrend/trend1.csv

	cd -
fi

%clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)

%files lfs-TPAC1007_3
%defattr(-,root,root)
%{pfx}/TPAC1007_3/local/root/hmi
%{pfx}/TPAC1007_3/local/etc/sysconfig/Crosstable.csv
%{pfx}/TPAC1007_3/local/etc/sysconfig/img/splash.png
%{pfx}/TPAC1007_3/local/etc/sysconfig/system.ini
%{pfx}/TPAC1007_3/local/data/customtrend/trend1.csv

%files lfs-TPAC1007_4AA
%defattr(-,root,root)
%{pfx}/TPAC1007_4AA/local/root/hmi
%{pfx}/TPAC1007_4AA/local/etc/sysconfig/Crosstable.csv
%{pfx}/TPAC1007_4AA/local/etc/sysconfig/img/splash.png
%{pfx}/TPAC1007_4AA/local/etc/sysconfig/system.ini
%{pfx}/TPAC1007_4AA/local/data/customtrend/trend1.csv

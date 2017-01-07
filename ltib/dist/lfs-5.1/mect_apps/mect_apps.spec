%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Default HMI application.
Name            : mect_apps
Version         : 0.0
Release         : 1
License         : GPL
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
URL             : http://www.mect.it/
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}/local
AutoReqProv     : no

# TP1043_01_A
#
%Package lfs-TP1043_01_A
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TP1043_01_A/local

%Description lfs-TP1043_01_A
%{name} package contents limited to just the run-times needed
on the target.

# TP1043_01_B
#
%Package lfs-TP1043_01_B
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TP1043_01_B/local

%Description lfs-TP1043_01_B
%{name} package contents limited to just the run-times needed
on the target.

# TP1057_01_A
#
%Package lfs-TP1057_01_A
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TP1057_01_A/local

%Description lfs-TP1057_01_A
%{name} package contents limited to just the run-times needed
on the target.

# TP1057_01_B
#
%Package lfs-TP1057_01_B
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TP1057_01_B/local

%Description lfs-TP1057_01_B
%{name} package contents limited to just the run-times needed
on the target.

# TP1070_01_A
#
%Package lfs-TP1070_01_A
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TP1070_01_A/local

%Description lfs-TP1070_01_A
%{name} package contents limited to just the run-times needed
on the target.

# TP1070_01_B
#
%Package lfs-TP1070_01_B
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TP1070_01_B/local

%Description lfs-TP1070_01_B
%{name} package contents limited to just the run-times needed
on the target.

# TP1070_01_C
#
%Package lfs-TP1070_01_C
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TP1070_01_C/local

%Description lfs-TP1070_01_C
%{name} package contents limited to just the run-times needed
on the target.

# TPAC1007_03
#
%Package lfs-TPAC1007_03
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TPAC1007_03/local

%Description lfs-TPAC1007_03
%{name} package contents limited to just the run-times needed
on the target.

# TPAC1007_04_AA
#
%Package lfs-TPAC1007_04_AA
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TPAC1007_04_AA/local

%Description lfs-TPAC1007_04_AA
%{name} package contents limited to just the run-times needed
on the target.

# TPAC1007_04_AB
#
%Package lfs-TPAC1007_04_AB
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TPAC1007_04_AB/local

%Description lfs-TPAC1007_04_AB
%{name} package contents limited to just the run-times needed
on the target.

# TPAC1007_04_AC
#
%Package lfs-TPAC1007_04_AC
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TPAC1007_04_AC/local

%Description lfs-TPAC1007_04_AC
%{name} package contents limited to just the run-times needed
on the target.

# TPAC1007_LV
#
%Package lfs-TPAC1007_LV
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TPAC1007_LV/local

%Description lfs-TPAC1007_LV
%{name} package contents limited to just the run-times needed
on the target.

# TPAC1006
#
%Package lfs-TPAC1006
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TPAC1006/local

%Description lfs-TPAC1006
%{name} package contents limited to just the run-times needed
on the target.

# TPAC1008_01
#
%Package lfs-TPAC1008_01
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TPAC1008_01/local

%Description lfs-TPAC1008_01
%{name} package contents limited to just the run-times needed
on the target.

# TPAC1008_02_AA
#
%Package lfs-TPAC1008_02_AA
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TPAC1008_02_AA/local

%Description lfs-TPAC1008_02_AA
%{name} package contents limited to just the run-times needed
on the target.

# TPAC1008_02_AB
#
%Package lfs-TPAC1008_02_AB
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TPAC1008_02_AB/local

%Description lfs-TPAC1008_02_AB
%{name} package contents limited to just the run-times needed
on the target.

# TPAC1008_02_AD
#
%Package lfs-TPAC1008_02_AD
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TPAC1008_02_AD/local

%Description lfs-TPAC1008_02_AD
%{name} package contents limited to just the run-times needed
on the target.

# TPAC1008_02_AE
#
%Package lfs-TPAC1008_02_AE
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TPAC1008_02_AE/local

%Description lfs-TPAC1008_02_AE
%{name} package contents limited to just the run-times needed
on the target.

# TPAC1008_02_AF
#
%Package lfs-TPAC1008_02_AF
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TPAC1008_02_AF/local

%Description lfs-TPAC1008_02_AF
%{name} package contents limited to just the run-times needed
on the target.

# TPLC100
#
%Package lfs-TPLC100
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TPLC100/local

%Description lfs-TPLC100
%{name} package contents limited to just the run-times needed
on the target.

# TPLC150
#
%Package lfs-TPLC150
Summary         : Trimmed %{name} to just the run-times needed for local file system.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/System
AutoReqProv     : no
Prefix          : %{pfx}/TPLC150/local

%Description lfs-TPLC150
%{name} package contents limited to just the run-times needed
on the target.

%description
%{summary}


%prep
export LC_ALL
LC_ALL=C

%setup -T -c -n %{name}
cd ..; rmdir %{name}; ln -s ../../../projects/%{name} %{name}

# Do not re-generate the systemicons resources (use Windows-specific paths).
find -L %{name} -name qrc_systemicons.cpp -exec touch {} \;


%build
export LC_ALL
LC_ALL=C

export MECT_RFSDIR
MECT_RFSDIR=$DEV_IMAGE
export MECT_QT_INSTALL_DIR
MECT_QT_INSTALL_DIR=/opt/Trolltech

# Target (or placeholder) names
for t in \
	AnyTPAC \
	TP1043_01_A \
	TP1043_01_B \
	TP1057_01_A \
	TP1057_01_B \
	TP1070_01_A \
	TP1070_01_B \
	TP1070_01_C \
	TPAC1006 \
	TPAC1007_03 \
	TPAC1007_04_AA \
	TPAC1007_04_AB \
	TPAC1007_04_AC \
	TPAC1007_LV \
	TPAC1008_01 \
	TPAC1008_02_AA \
	TPAC1008_02_AB \
	TPAC1008_02_AD \
	TPAC1008_02_AE \
	TPAC1008_02_AF \
; do
	test -z "$t" && exit 1
	test -d $t || test -d AnyTPAC || exit 1

	if test -d $t/Simple; then
		d=$t/Simple
		p=Simple.pro
	elif test -d AnyTPAC/Empty_HMI; then
		d=AnyTPAC/Empty_HMI
		p=Empty_HMI.pro
	else
		exit 1
	fi
	test -z "$d" -o -z "$p" && exit 1

	cd $d

	$MECT_QT_INSTALL_DIR/bin/lrelease $p
	$MECT_QT_INSTALL_DIR/bin/qmake \
		-spec qws/linux-g++-mx \
		"INCLUDEPATH+=${MECT_RFSDIR}/usr/include ${MECT_RFSDIR}/usr/src/linux/include" \
		"DEFINES+=TARGET_ARM" \
		"QMAKE_LIBDIR+=${MECT_RFSDIR}/usr/lib" \
		$p

	make -j1

	cd -
done


%install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

# Source-destination tuplets
(
	echo  AnyTPAC         TPLC100         ;
	echo  AnyTPAC         TPLC150         ;
	echo  TPAC1006        TPAC1006        ;
	echo  TP1043_01_A     TP1043_01_A     ;
	echo  TP1043_01_B     TP1043_01_B     ;
	echo  TP1057_01_A     TP1057_01_A     ;
	echo  TP1057_01_B     TP1057_01_B     ;
	echo  TP1070_01_A     TP1070_01_A     ;
	echo  TP1070_01_B     TP1070_01_B     ;
	echo  TP1070_01_C     TP1070_01_C     ;
	echo  TPAC1007_03     TPAC1007_03     ;
	echo  TPAC1007_LV     TPAC1007_LV     ;
	echo  TPAC1008_01     TPAC1008_01     ;
	echo  TPAC1007_04_AA  TPAC1007_04_AA  ;
	echo  TPAC1007_04_AB  TPAC1007_04_AB  ;
	echo  TPAC1007_04_AC  TPAC1007_04_AC  ;
	echo  TPAC1008_02_AA  TPAC1008_02_AA  ;
	echo  TPAC1008_02_AB  TPAC1008_02_AB  ;
	echo  TPAC1008_02_AD  TPAC1008_02_AD  ;
	echo  TPAC1008_02_AE  TPAC1008_02_AE  ;
	echo  TPAC1008_02_AF  TPAC1008_02_AF  ;
) \
| while read t d; do
	test -z $t && exit 1
	test -d $t || exit 1

	if test -d $t/Simple; then
		t=$t/Simple
	elif test -d $t/Empty_HMI; then
		t=$t/Empty_HMI
	else
		exit 1
	fi
	test -z "$t" && exit 1

	cd $t

	test -r hmi \
		&& install -m755 -D hmi                   $RPM_BUILD_ROOT%{pfx}/$d/local/root/hmi
	test -r config/Crosstable.csv \
		&& install -m644 -D config/Crosstable.csv $RPM_BUILD_ROOT%{pfx}/$d/local/etc/sysconfig/Crosstable.csv
	test -r config/splash.png \
		&& install -m644 -D config/splash.png     $RPM_BUILD_ROOT%{pfx}/$d/local/etc/sysconfig/img/splash.png
	test -r config/system.ini \
		&& install -m644 -D config/system.ini     $RPM_BUILD_ROOT%{pfx}/$d/local/etc/sysconfig/system.ini
	test -r config/trend1.csv \
		&& install -m644 -D config/trend1.csv     $RPM_BUILD_ROOT%{pfx}/$d/local/data/customtrend/trend1.csv
	test -r config/network0.cmg \
		&& install -m644 -D config/network0.cmg   $RPM_BUILD_ROOT%{pfx}/$d/local/etc/sysconfig/network0.cmg
	test -r config/iomap0.cmg \
		&& install -m644 -D config/iomap0.cmg     $RPM_BUILD_ROOT%{pfx}/$d/local/etc/sysconfig/iomap0.cmg

	cd -
done


%clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%files
%defattr(-,root,root)
%{pfx}/*

%files lfs-TP1043_01_A
%defattr(-,root,root)
%{pfx}/TP1043_01_A/local/root/hmi
%{pfx}/TP1043_01_A/local/etc/sysconfig/Crosstable.csv
%{pfx}/TP1043_01_A/local/etc/sysconfig/img/splash.png
%{pfx}/TP1043_01_A/local/etc/sysconfig/system.ini
%{pfx}/TP1043_01_A/local/data/customtrend/trend1.csv

%files lfs-TP1043_01_B
%defattr(-,root,root)
%{pfx}/TP1043_01_B/local/root/hmi
%{pfx}/TP1043_01_B/local/etc/sysconfig/Crosstable.csv
%{pfx}/TP1043_01_B/local/etc/sysconfig/img/splash.png
%{pfx}/TP1043_01_B/local/etc/sysconfig/system.ini
%{pfx}/TP1043_01_B/local/data/customtrend/trend1.csv

%files lfs-TP1057_01_A
%defattr(-,root,root)
%{pfx}/TP1057_01_A/local/root/hmi
%{pfx}/TP1057_01_A/local/etc/sysconfig/Crosstable.csv
%{pfx}/TP1057_01_A/local/etc/sysconfig/img/splash.png
%{pfx}/TP1057_01_A/local/etc/sysconfig/system.ini
%{pfx}/TP1057_01_A/local/data/customtrend/trend1.csv

%files lfs-TP1057_01_B
%defattr(-,root,root)
%{pfx}/TP1057_01_B/local/root/hmi
%{pfx}/TP1057_01_B/local/etc/sysconfig/Crosstable.csv
%{pfx}/TP1057_01_B/local/etc/sysconfig/img/splash.png
%{pfx}/TP1057_01_B/local/etc/sysconfig/system.ini
%{pfx}/TP1057_01_B/local/data/customtrend/trend1.csv

%files lfs-TP1070_01_A
%defattr(-,root,root)
%{pfx}/TP1070_01_A/local/root/hmi
%{pfx}/TP1070_01_A/local/etc/sysconfig/Crosstable.csv
%{pfx}/TP1070_01_A/local/etc/sysconfig/img/splash.png
%{pfx}/TP1070_01_A/local/etc/sysconfig/system.ini
%{pfx}/TP1070_01_A/local/data/customtrend/trend1.csv

%files lfs-TP1070_01_B
%defattr(-,root,root)
%{pfx}/TP1070_01_B/local/root/hmi
%{pfx}/TP1070_01_B/local/etc/sysconfig/Crosstable.csv
%{pfx}/TP1070_01_B/local/etc/sysconfig/img/splash.png
%{pfx}/TP1070_01_B/local/etc/sysconfig/system.ini
%{pfx}/TP1070_01_B/local/data/customtrend/trend1.csv

%files lfs-TP1070_01_C
%defattr(-,root,root)
%{pfx}/TP1070_01_C/local/root/hmi
%{pfx}/TP1070_01_C/local/etc/sysconfig/Crosstable.csv
%{pfx}/TP1070_01_C/local/etc/sysconfig/img/splash.png
%{pfx}/TP1070_01_C/local/etc/sysconfig/system.ini
%{pfx}/TP1070_01_C/local/data/customtrend/trend1.csv

%files lfs-TPAC1007_03
%defattr(-,root,root)
%{pfx}/TPAC1007_03/local/root/hmi
%{pfx}/TPAC1007_03/local/etc/sysconfig/Crosstable.csv
%{pfx}/TPAC1007_03/local/etc/sysconfig/img/splash.png
%{pfx}/TPAC1007_03/local/etc/sysconfig/system.ini
%{pfx}/TPAC1007_03/local/data/customtrend/trend1.csv

%files lfs-TPAC1007_04_AA
%defattr(-,root,root)
%{pfx}/TPAC1007_04_AA/local/root/hmi
%{pfx}/TPAC1007_04_AA/local/etc/sysconfig/Crosstable.csv
%{pfx}/TPAC1007_04_AA/local/etc/sysconfig/img/splash.png
%{pfx}/TPAC1007_04_AA/local/etc/sysconfig/system.ini
%{pfx}/TPAC1007_04_AA/local/data/customtrend/trend1.csv

%files lfs-TPAC1007_04_AB
%defattr(-,root,root)
%{pfx}/TPAC1007_04_AB/local/root/hmi
%{pfx}/TPAC1007_04_AB/local/etc/sysconfig/Crosstable.csv
%{pfx}/TPAC1007_04_AB/local/etc/sysconfig/img/splash.png
%{pfx}/TPAC1007_04_AB/local/etc/sysconfig/system.ini
%{pfx}/TPAC1007_04_AB/local/data/customtrend/trend1.csv

%files lfs-TPAC1007_04_AC
%defattr(-,root,root)
%{pfx}/TPAC1007_04_AC/local/root/hmi
%{pfx}/TPAC1007_04_AC/local/etc/sysconfig/Crosstable.csv
%{pfx}/TPAC1007_04_AC/local/etc/sysconfig/img/splash.png
%{pfx}/TPAC1007_04_AC/local/etc/sysconfig/system.ini
%{pfx}/TPAC1007_04_AC/local/data/customtrend/trend1.csv

%files lfs-TPAC1007_LV
%defattr(-,root,root)
%{pfx}/TPAC1007_LV/local/root/hmi
%{pfx}/TPAC1007_LV/local/etc/sysconfig/Crosstable.csv
%{pfx}/TPAC1007_LV/local/etc/sysconfig/img/splash.png
%{pfx}/TPAC1007_LV/local/etc/sysconfig/system.ini
%{pfx}/TPAC1007_LV/local/data/customtrend/trend1.csv

%files lfs-TPAC1006
%defattr(-,root,root)
%{pfx}/TPAC1006/local/root/hmi
%{pfx}/TPAC1006/local/etc/sysconfig/Crosstable.csv
%{pfx}/TPAC1006/local/etc/sysconfig/img/splash.png
%{pfx}/TPAC1006/local/etc/sysconfig/system.ini
%{pfx}/TPAC1006/local/data/customtrend/trend1.csv
%{pfx}/TPAC1006/local/etc/sysconfig/iomap0.cmg
%{pfx}/TPAC1006/local/etc/sysconfig/network0.cmg

%files lfs-TPAC1008_01
%defattr(-,root,root)
%{pfx}/TPAC1008_01/local/root/hmi
%{pfx}/TPAC1008_01/local/etc/sysconfig/Crosstable.csv
%{pfx}/TPAC1008_01/local/etc/sysconfig/img/splash.png
%{pfx}/TPAC1008_01/local/etc/sysconfig/system.ini
%{pfx}/TPAC1008_01/local/data/customtrend/trend1.csv
%{pfx}/TPAC1008_01/local/etc/sysconfig/iomap0.cmg
%{pfx}/TPAC1008_01/local/etc/sysconfig/network0.cmg

%files lfs-TPAC1008_02_AA
%defattr(-,root,root)
%{pfx}/TPAC1008_02_AA/local/root/hmi
%{pfx}/TPAC1008_02_AA/local/etc/sysconfig/Crosstable.csv
%{pfx}/TPAC1008_02_AA/local/etc/sysconfig/img/splash.png
%{pfx}/TPAC1008_02_AA/local/etc/sysconfig/system.ini
%{pfx}/TPAC1008_02_AA/local/data/customtrend/trend1.csv
%{pfx}/TPAC1008_02_AA/local/etc/sysconfig/iomap0.cmg
%{pfx}/TPAC1008_02_AA/local/etc/sysconfig/network0.cmg

%files lfs-TPAC1008_02_AB
%defattr(-,root,root)
%{pfx}/TPAC1008_02_AB/local/root/hmi
%{pfx}/TPAC1008_02_AB/local/etc/sysconfig/Crosstable.csv
%{pfx}/TPAC1008_02_AB/local/etc/sysconfig/img/splash.png
%{pfx}/TPAC1008_02_AB/local/etc/sysconfig/system.ini
%{pfx}/TPAC1008_02_AB/local/data/customtrend/trend1.csv
%{pfx}/TPAC1008_02_AB/local/etc/sysconfig/iomap0.cmg
%{pfx}/TPAC1008_02_AB/local/etc/sysconfig/network0.cmg

%files lfs-TPAC1008_02_AD
%defattr(-,root,root)
%{pfx}/TPAC1008_02_AD/local/root/hmi
%{pfx}/TPAC1008_02_AD/local/etc/sysconfig/Crosstable.csv
%{pfx}/TPAC1008_02_AD/local/etc/sysconfig/img/splash.png
%{pfx}/TPAC1008_02_AD/local/etc/sysconfig/system.ini
%{pfx}/TPAC1008_02_AD/local/data/customtrend/trend1.csv
%{pfx}/TPAC1008_02_AD/local/etc/sysconfig/iomap0.cmg
%{pfx}/TPAC1008_02_AD/local/etc/sysconfig/network0.cmg

%files lfs-TPAC1008_02_AE
%defattr(-,root,root)
%{pfx}/TPAC1008_02_AE/local/root/hmi
%{pfx}/TPAC1008_02_AE/local/etc/sysconfig/Crosstable.csv
%{pfx}/TPAC1008_02_AE/local/etc/sysconfig/img/splash.png
%{pfx}/TPAC1008_02_AE/local/etc/sysconfig/system.ini
%{pfx}/TPAC1008_02_AE/local/data/customtrend/trend1.csv
%{pfx}/TPAC1008_02_AE/local/etc/sysconfig/iomap0.cmg
%{pfx}/TPAC1008_02_AE/local/etc/sysconfig/network0.cmg

%files lfs-TPAC1008_02_AF
%defattr(-,root,root)
%{pfx}/TPAC1008_02_AF/local/root/hmi
%{pfx}/TPAC1008_02_AF/local/etc/sysconfig/Crosstable.csv
%{pfx}/TPAC1008_02_AF/local/etc/sysconfig/img/splash.png
%{pfx}/TPAC1008_02_AF/local/etc/sysconfig/system.ini
%{pfx}/TPAC1008_02_AF/local/data/customtrend/trend1.csv
%{pfx}/TPAC1008_02_AF/local/etc/sysconfig/iomap0.cmg
%{pfx}/TPAC1008_02_AF/local/etc/sysconfig/network0.cmg

%files lfs-TPLC100
%defattr(-,root,root)
%{pfx}/TPLC100/local/root/hmi
%{pfx}/TPLC100/local/etc/sysconfig/Crosstable.csv
%{pfx}/TPLC100/local/etc/sysconfig/img/splash.png
%{pfx}/TPLC100/local/etc/sysconfig/system.ini
%{pfx}/TPLC100/local/data/customtrend/trend1.csv

%files lfs-TPLC150
%defattr(-,root,root)
%{pfx}/TPLC150/local/root/hmi
%{pfx}/TPLC150/local/etc/sysconfig/Crosstable.csv
%{pfx}/TPLC150/local/etc/sysconfig/img/splash.png
%{pfx}/TPLC150/local/etc/sysconfig/system.ini
%{pfx}/TPLC150/local/data/customtrend/trend1.csv

%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary		: Userspace device files
Name		: udev
Version		: 117
Release		: 5
License		: GPL
Vendor		: Freescale
Packager	: Duck
Group		: System Environment/Base
Source		: %{name}-%{version}.tar.bz2
Patch0		: udev-117-init-script.patch
Patch1		: udev-imx-input-rules-3.patch
Patch2		: udev-automount-v3.patch
Patch3		: udev-117-init_script.patch
Patch4		: udev-117-mount.patch
Patch5          : udev-117-imx-lowcase2.patch
Patch6          : udev-117-imx-input-event.patch
Patch7          : udev-117-add-mxc-mem.patch
Patch8		: udev-117-add-mxc-rtc.patch
Patch9          : udev-hal-modify-volumeid-link.patch
Patch10		: udev-117-add-mxs-viim.patch
Patch11         : udev-117-add_stmp3xxx_ts0.patch
Patch12         : udev-117-mxs-ts0.patch
Patch13         : udev-117-mxc-ipu-dev-privilege.patch
Patch14         : udev-117-mxc-vpu.patch
Patch15         : udev-117-chg-to-attrs.patch
BuildRoot	: %{_tmppath}/%{name}
Prefix		: %{pfx}
AutoReqProv     : no

# List of extra things to build, which must be
# passed to make at build time and install time.
# Use an rpm variable, so we only need to define
# it once.
%define extras "extras/volume_id extras/path_id extras/usb_id extras/firmware"


%Package rfs
Summary         : Trimmed udev for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Base
AutoReqProv     : no

%Description rfs
udev package contents restricted to just the files that are
needed at run time on the target.


%Description
%{summary}

%Prep
export LC_ALL
LC_ALL=C

%setup
%patch0 -p1
%patch1 -p1
%patch2 -p1
%patch3 -p1
%patch4 -p1
%patch5 -p1
%patch6 -p1
%patch7 -p1
%patch8 -p1
%patch9 -p1
%patch10 -p1
%patch11 -p1
%patch12 -p1
%patch13 -p1
%patch14 -p1
%patch15 -p1

%Build
export LC_ALL
LC_ALL=C

make EXTRAS=%{extras}

%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make install EXTRAS=%{extras} DESTDIR=$RPM_BUILD_ROOT%{pfx}
install -m 644 etc/udev/packages/40-alsa.rules $RPM_BUILD_ROOT%{pfx}/etc/udev/rules.d

# To avoid duplication removed as skell installs this and all the
# other init scripts.
#install -d $RPM_BUILD_ROOT/%{pfx}/etc/rc.d/init.d
#install -m 744 etc/udev/ltib/init_script $RPM_BUILD_ROOT/%{pfx}/etc/rc.d/init.d/udev

if [ "$PKG_UDEV_WANT_IMX" = "y" ]
then
	install -m 644 etc/udev/ltib/??-imx*.rules $RPM_BUILD_ROOT%{pfx}/etc/udev/rules.d
fi

if [ "$PKG_UDEV_WANT_AUTOMOUNT" = "y" ]
then
	install -m 644 etc/udev/ltib/65-automount.rules $RPM_BUILD_ROOT%{pfx}/etc/udev/rules.d
fi

if [ "$PKG_UDEV_WANT_NON_RAID" = "y" ]
then
	# For non-raid systems, add the '--skip-raid' arg to vol_id cmds
	# in all udev rules.
	# This prevents vol_id from trying to read the last sector of a device
	# for raid info, which is problematic for devices which report their
	# capacity incorrectly.

	perl -pi -e 's/vol_id /vol_id --skip-raid /' \
		$RPM_BUILD_ROOT%{pfx}/etc/udev/rules.d/*
fi

cd %{_builddir}/%{name}-%{version}
( cd $RPM_BUILD_ROOT > /dev/null; find .%{pfx} \( \( -not -type d \) -o \( -type d -empty \) \) -print | sed 's/^\.//' ) > all_files.lst
sed '
    \,^%{pfx}%{_libdir}/pkgconfig, d;
    \,^%{pfx}%{_mandir}, d;
    \,^%{pfx}%{_includedir}, d;
' all_files.lst > rfs_files.lst

%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files -f all_files.lst
%defattr(-,root,root)

%Files rfs -f rfs_files.lst
%defattr(-,root,root)

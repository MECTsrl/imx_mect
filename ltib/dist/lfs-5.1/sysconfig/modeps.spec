%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Generate module dependency file
Name            : modeps
Version         : 1.0
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : System Environment/Base
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed modeps for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Base
AutoReqProv     : no

%Description rfs
modeps package contents restricted to just the files that are
needed at run time on the target.


%Description
%{summary}


%Prep
export LC_ALL
LC_ALL=C


%Build
export LC_ALL
LC_ALL=C


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT%{pfx}/lib/modules
if [ -f $DEV_IMAGE/boot/vmlinux ]
then 
    # generate modules.dep
    KERNEL_VER=`strings $DEV_IMAGE/boot/vmlinux | perl -n -e 'print($1), exit(0) if m,Linux version ([\S]+),'`
    if [ -n "$KERNEL_VER" ]
    then
        mkdir -p $RPM_BUILD_ROOT%{pfx}/lib/modules/$KERNEL_VER
        #depmod.pl -b $DEV_IMAGE/lib/modules/$KERNEL_VER -F $DEV_IMAGE/boot/System.map --stdout > $RPM_BUILD_ROOT/%{pfx}/lib/modules/$KERNEL_VER/modules.dep
	# TODO: depmod should be added to host tools insted of relying on the host one.
	sudo depmod -a -b $DEV_IMAGE -F $DEV_IMAGE/boot/System.map $KERNEL_VER
	install -m 644 $DEV_IMAGE/lib/modules/$KERNEL_VER/modules.* $RPM_BUILD_ROOT%{pfx}/lib/modules/$KERNEL_VER/
    fi
fi


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/lib/modules/2.6.35.3/modules.alias
%{pfx}/lib/modules/2.6.35.3/modules.dep

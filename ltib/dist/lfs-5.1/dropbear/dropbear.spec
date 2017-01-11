%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : Dropbear SSH server and client (embedded)
Name            : dropbear
Version         : 2016.73
Release         : 1
License         : MIT
Vendor          : Freescale
Packager        : Stuart Hughes
Group           : Applications/Internet
Source1         : dropbear_hackable_rsa_host_key
Source2         : dropbear_rsa_host_key
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed dropbear for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : Applications/Internet
AutoReqProv     : no

%Description rfs
dropbear package contents restricted to just the files that
are needed at run time on the target.


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

test "$PKG_DROPBEAR_WANT_URANDOM_DEV" = "y" && perl -pi -e 's,^#define DROPBEAR_RANDOM_DEV.*,#define DROPBEAR_RANDOM_DEV "/dev/urandom",; ' options.h

test "$PKG_DROPBEAR_WANT_NO_REV_DNS" = "y" && perl -pi -e 's,^(#define DO_HOST_LOOKUP),//\1,; ' options.h

test "$PKG_DROPBEAR_WANT_NO_X11FWD" = "y" && perl -pi -e 's,^(#define ENABLE_X11FWD),//\1,; ' options.h

# Timestamp order is important.
for f in configure.ac configure.in aclocal.m4 configure config.h.in Makefile.am Makefile.in; do
	find . -name $f -exec touch {} \;
done
LD=gcc ./configure --prefix=%{_prefix} --host=$CFGHOST --build=%{_build}
make PROGRAMS="dropbear dbclient dropbearkey dropbearconvert scp" MULTI=1 SCPPROGRESS=1


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT

mkdir -p $RPM_BUILD_ROOT/%{pfx}/etc/dropbear
for d in bin sbin; do
    mkdir -p $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/$d
done

install -m755 dropbearmulti $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/sbin

ln -s %{_prefix}/sbin/dropbearmulti $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/sbin/dropbear
for i in dbclient dropbearconvert dropbearkey scp ssh; do
    ln -s %{_prefix}/sbin/dropbearmulti $RPM_BUILD_ROOT/%{pfx}/%{_prefix}/bin/$i
done

test "$PKG_DROPBEAR_WANT_HACKABLE_KEY" = "y" && install -m644 -D %{SOURCE1} $RPM_BUILD_ROOT/%{pfx}/etc/dropbear/dropbear_rsa_host_key

# Set custom host key.
install -m644 -D %{SOURCE2} $RPM_BUILD_ROOT%{pfx}/etc/dropbear/dropbear_rsa_host_key


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%dir %{pfx}/etc/dropbear
%{pfx}/etc/dropbear/dropbear_rsa_host_key
%{pfx}/usr/bin/dbclient
%{pfx}/usr/bin/dropbearconvert
%{pfx}/usr/bin/dropbearkey
%{pfx}/usr/bin/scp
%{pfx}/usr/bin/ssh
%{pfx}/usr/sbin/dropbear
%{pfx}/usr/sbin/dropbearmulti

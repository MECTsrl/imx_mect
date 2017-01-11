%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : xenomai - Real Time extension for the Linux kernel
Name            : xenomai
Version         : 2.6.0
Release         : 1
License         : GPL
Vendor          : Freescale
Packager        : Mect
Group           : System Environment
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed xenomai for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment
AutoReqProv     : no

%Description rfs
xenomai package contents restricted to just the files that
are needed at run time on the target.


%Description
%{summary}

#The Prep target is performed together with the kernel if kernel with ipipe is selected.
#  %{name}-%{version}


%Prep
export LC_ALL
LC_ALL=C

%setup -T -c -n %{name}
cd ..; rmdir %{name}; ln -s ../../../projects/%{name} %{name}


%Build
export LC_ALL
LC_ALL=C

# Timestamp order is important.
for f in configure.ac configure.in aclocal.m4 configure config.h.in Makefile.am Makefile.in; do
	find . -name $f -exec touch {} \;
done
./configure CFLAGS="-march=armv5te" LDFLAGS="-march=armv5te" --build=%{_build} --host=$CFGHOST
make DESTDIR=$RPM_BUILD_ROOT%{pfx} all


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT%{pfx} install


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}%{_prefix}/xenomai/lib/libanalogy.so
%{pfx}%{_prefix}/xenomai/lib/libanalogy.so.1
%{pfx}%{_prefix}/xenomai/lib/libanalogy.so.1.0.0
%{pfx}%{_prefix}/xenomai/lib/libnative.so
%{pfx}%{_prefix}/xenomai/lib/libnative.so.3
%{pfx}%{_prefix}/xenomai/lib/libnative.so.3.0.0
%{pfx}%{_prefix}/xenomai/lib/libpsos.so
%{pfx}%{_prefix}/xenomai/lib/libpsos.so.0
%{pfx}%{_prefix}/xenomai/lib/libpsos.so.0.0.0
%{pfx}%{_prefix}/xenomai/lib/libpthread_rt.so
%{pfx}%{_prefix}/xenomai/lib/libpthread_rt.so.1
%{pfx}%{_prefix}/xenomai/lib/libpthread_rt.so.1.0.0
%{pfx}%{_prefix}/xenomai/lib/librtdm.so
%{pfx}%{_prefix}/xenomai/lib/librtdm.so.1
%{pfx}%{_prefix}/xenomai/lib/librtdm.so.1.0.0
%{pfx}%{_prefix}/xenomai/lib/libuitron.so
%{pfx}%{_prefix}/xenomai/lib/libuitron.so.0
%{pfx}%{_prefix}/xenomai/lib/libuitron.so.0.0.0
%{pfx}%{_prefix}/xenomai/lib/libvrtx.so
%{pfx}%{_prefix}/xenomai/lib/libvrtx.so.0
%{pfx}%{_prefix}/xenomai/lib/libvrtx.so.0.0.0
%{pfx}%{_prefix}/xenomai/lib/libvxworks.so
%{pfx}%{_prefix}/xenomai/lib/libvxworks.so.1
%{pfx}%{_prefix}/xenomai/lib/libvxworks.so.1.0.0
%{pfx}%{_prefix}/xenomai/lib/libxenomai.so
%{pfx}%{_prefix}/xenomai/lib/libxenomai.so.0
%{pfx}%{_prefix}/xenomai/lib/libxenomai.so.0.0.0
### TODO Remove all below.
%{pfx}%{_prefix}/xenomai/bin/arith
%{pfx}%{_prefix}/xenomai/bin/check-vdso
%{pfx}%{_prefix}/xenomai/bin/clocktest
%{pfx}%{_prefix}/xenomai/bin/cmd_bits
%{pfx}%{_prefix}/xenomai/bin/cmd_read
%{pfx}%{_prefix}/xenomai/bin/cmd_write
%{pfx}%{_prefix}/xenomai/bin/cond-torture-native
%{pfx}%{_prefix}/xenomai/bin/cond-torture-posix
%{pfx}%{_prefix}/xenomai/bin/cyclictest
%{pfx}%{_prefix}/xenomai/bin/dohell
%{pfx}%{_prefix}/xenomai/bin/insn_bits
%{pfx}%{_prefix}/xenomai/bin/insn_read
%{pfx}%{_prefix}/xenomai/bin/insn_write
%{pfx}%{_prefix}/xenomai/bin/irqloop
%{pfx}%{_prefix}/xenomai/bin/klatency
%{pfx}%{_prefix}/xenomai/bin/latency
%{pfx}%{_prefix}/xenomai/bin/mutex-torture-native
%{pfx}%{_prefix}/xenomai/bin/mutex-torture-posix
%{pfx}%{_prefix}/xenomai/bin/rtcanrecv
%{pfx}%{_prefix}/xenomai/bin/rtcansend
%{pfx}%{_prefix}/xenomai/bin/rtdm
%{pfx}%{_prefix}/xenomai/bin/switchtest
%{pfx}%{_prefix}/xenomai/bin/wakeup-time
%{pfx}%{_prefix}/xenomai/bin/wf_generate
%{pfx}%{_prefix}/xenomai/bin/wrap-link.sh
%{pfx}%{_prefix}/xenomai/bin/xeno
%{pfx}%{_prefix}/xenomai/bin/xeno-config
%{pfx}%{_prefix}/xenomai/bin/xeno-regression-test
%{pfx}%{_prefix}/xenomai/bin/xeno-test
%{pfx}%{_prefix}/xenomai/bin/xeno-test-run
%{pfx}%{_prefix}/xenomai/bin/xeno-test-run-wrapper
%{pfx}%{_prefix}/xenomai/lib/pkgconfig/libxenomai_native.pc
%{pfx}%{_prefix}/xenomai/lib/pkgconfig/libxenomai_posix.pc
%{pfx}%{_prefix}/xenomai/lib/pkgconfig/libxenomai_psos+.pc
%{pfx}%{_prefix}/xenomai/lib/pkgconfig/libxenomai_rtdm.pc
%{pfx}%{_prefix}/xenomai/lib/pkgconfig/libxenomai_uitron.pc
%{pfx}%{_prefix}/xenomai/lib/pkgconfig/libxenomai_vrtx.pc
%{pfx}%{_prefix}/xenomai/lib/pkgconfig/libxenomai_vxworks.pc
%{pfx}%{_prefix}/xenomai/lib/posix.wrappers
%{pfx}%{_prefix}/xenomai/sbin/analogy_config
%{pfx}%{_prefix}/xenomai/sbin/rtcanconfig
%{pfx}%{_prefix}/xenomai/sbin/rtps
%{pfx}%{_prefix}/xenomai/share/xenomai/regression/native+posix/mq_select
%{pfx}%{_prefix}/xenomai/share/xenomai/regression/native/heap
%{pfx}%{_prefix}/xenomai/share/xenomai/regression/native/leaks
%{pfx}%{_prefix}/xenomai/share/xenomai/regression/native/mayday
%{pfx}%{_prefix}/xenomai/share/xenomai/regression/native/tsc
%{pfx}%{_prefix}/xenomai/share/xenomai/regression/posix/leaks
%{pfx}%{_prefix}/xenomai/share/xenomai/regression/posix/shm

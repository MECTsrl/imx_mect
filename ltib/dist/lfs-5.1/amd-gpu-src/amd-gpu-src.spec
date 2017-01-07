%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : GPU on mx51/mx35 that supports OpenGLES and OpenVG
Name            : amd-gpu-src
Version         : 2.6.35.3
Release         : 1.1.0
License         : Proprietary
Vendor          : AMD
Packager        : Wu Guoxing
Group           : Development/Libraries
Source          : %{name}-%{version}-%{release}.tar.gz 
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}

%Description
%{summary}

%Prep
%setup -n %{name}-%{version}-%{release}

%Build

if [ "${PKG_AMD_GPU_X11_BIN_BUILD_OPT}" = "y" ]
then
	export BUILD_EGL_X=1
	export X_PREFIX=$DEV_IMAGE/usr
fi

SOC=$(echo $PLATFORM | cut -d_ -f1 | cut -c2-)

if [ "$SOC" = "mx50" ]
then
	make -C driver/build/linux/mx35 -f build_all.mk Z160_HIGH_PRECISION=1
else
	make -C driver/build/linux/$SOC -f build_all.mk
fi

%Install
SOC=$(echo $PLATFORM | cut -d_ -f1 | cut -c2-)
if [ "${PKG_AMD_GPU_X11_BIN_BUILD_OPT}" = "y" ]
then
        OUTPUT_PKG="amd-gpu-x11-bin-$SOC-%{version}"
else
        OUTPUT_PKG="amd-gpu-bin-$SOC-%{version}"
fi

rm -rf $RPM_BUILD_ROOT
install -d $RPM_BUILD_ROOT/%{pfx}

install -d $RPM_BUILD_ROOT/%{pfx}/usr/lib
if [ "$SOC" = "mx50" ]
then
	cp -af driver/build/linux/mx35/lib/*.so* $RPM_BUILD_ROOT/%{pfx}/usr/lib
	install driver/build/linux/mx35/lib/libcsi.a $RPM_BUILD_ROOT/%{pfx}/usr/lib
	install driver/build/linux/mx35/lib/libres.a $RPM_BUILD_ROOT/%{pfx}/usr/lib
else
	cp -af driver/build/linux/$SOC/lib/*.so* $RPM_BUILD_ROOT/%{pfx}/usr/lib
	install driver/build/linux/$SOC/lib/libcsi.a $RPM_BUILD_ROOT/%{pfx}/usr/lib
	install driver/build/linux/$SOC/lib/libres.a $RPM_BUILD_ROOT/%{pfx}/usr/lib
fi

install -d $RPM_BUILD_ROOT/%{pfx}/usr/bin
if [ "$SOC" = "mx50" ]
then
	install driver/build/linux/mx35/bin/* $RPM_BUILD_ROOT/%{pfx}/usr/bin
else
	install driver/build/linux/$SOC/bin/* $RPM_BUILD_ROOT/%{pfx}/usr/bin
fi

install -d $RPM_BUILD_ROOT/%{pfx}/usr/include/EGL
install driver/include/public/EGL/* $RPM_BUILD_ROOT/%{pfx}/usr/include/EGL
install -d $RPM_BUILD_ROOT/%{pfx}/usr/include/VG
install driver/include/public/VG/* $RPM_BUILD_ROOT/%{pfx}/usr/include/VG
install -d $RPM_BUILD_ROOT/%{pfx}/usr/include/KHR
install driver/include/public/KHR/* $RPM_BUILD_ROOT/%{pfx}/usr/include/KHR
if [ "$SOC" = "mx51" ]
then
    install -d $RPM_BUILD_ROOT/%{pfx}/usr/include/GLES
    install driver/include/public/GLES/* $RPM_BUILD_ROOT/%{pfx}/usr/include/GLES
    install -d $RPM_BUILD_ROOT/%{pfx}/usr/include/GLES2
    install driver/include/public/GLES2/* $RPM_BUILD_ROOT/%{pfx}/usr/include/GLES2
fi

# Package up the build results and leave in rpm/SOURCES for amd-gpu-bin spec file
rm -rf $OUTPUT_PKG
install -d $OUTPUT_PKG
mv $RPM_BUILD_ROOT/%{pfx}/* $OUTPUT_PKG
tar -zcf $OUTPUT_PKG.tar.gz $OUTPUT_PKG
# todo fix this to use rpmdir or something better than TOP:
install $OUTPUT_PKG.tar.gz $TOP/rpm/RPMS/"$LINTARCH"
install $OUTPUT_PKG.tar.gz $TOP/rpm/SOURCES

# Now delete everything we just tarred up.  csr-wifi-bin spec file will install it.
rm -rf $RPM_BUILD_ROOT/%{pfx}
# Create an empty directory for rpm to have something install or it won't be happy.
install -d $RPM_BUILD_ROOT/%{pfx}/usr

%Clean
rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*



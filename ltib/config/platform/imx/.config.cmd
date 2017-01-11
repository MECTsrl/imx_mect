deps_config := \
	../../userspace/defaults.lkc \
	../../userspace/post_build_script.lkc \
	../../userspace/deployment.lkc \
	../../userspace/network.lkc \
	../../userspace/sysconfig.lkc \
	../../userspace/extra_packages.lkc \
	fsl_mm.lkc \
	packages.lkc \
	../../userspace/packages.lkc \
	../../userspace/distro.lkc \
	../../userspace/kernel_dir_build.lkc \
	../../userspace/u-boot-dir-build.lkc \
	../../userspace/toolchain.lkc \
	../../userspace/libc_type.lkc \
	../../userspace/features.lkc \
	../../userspace/endian.lkc \
	main.lkc

.config include/linux/autoconf.h: $(deps_config)

$(deps_config):

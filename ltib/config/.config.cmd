deps_config := \
	userspace/defaults.lkc \
	../config/platform/imx/preconfigs.lkc

.config include/linux/autoconf.h: $(deps_config)

$(deps_config):

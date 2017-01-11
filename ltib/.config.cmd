deps_config := \
	/home/imx28/mect/ltib/config/main.lkc

.config include/linux/autoconf.h: $(deps_config)

$(deps_config):

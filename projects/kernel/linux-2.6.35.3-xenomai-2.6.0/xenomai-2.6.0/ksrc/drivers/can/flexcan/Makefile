# Makefile frag for Linux v2.6 and v3.x

EXTRA_CFLAGS += -D__IN_XENOMAI__ -Iinclude/xenomai -Idrivers/xenomai/can -Idrivers/xenomai/can/flexcan

obj-$(CONFIG_XENO_DRIVERS_CAN_FLEXCAN) += xeno_can_flexcan.o
obj-$(CONFIG_XENO_DRIVERS_CAN_FLEXCAN) += xeno_can_flexcan_imx28.o

xeno_can_flexcan-y := rtcan_flexcan.o rtcan_flexcan_proc.o rtcan_flexcan_mbm.o
xeno_can_flexcan_imx28-y := rtcan_flexcan_imx28.o

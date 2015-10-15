# LTIB installation for MECT operator panels based on Freescale i.MX28 processors

Downloads, configures and installs LTIB image build environment and Codesurcery target toolchain for MECT operator panels based on Freescale i.MX28 processors:

- with on board I/O:
[TPAC1007] (http://www.mect.it/en/products/control-and-automation/operator-panels-with-plcpac/tpac1007/),
[TPAC1006] (http://www.mect.it/en/products/control-and-automation/operator-panels-with-plcpac/tpac1006/),
[TPAC1008] (http://www.mect.it/en/products/control-and-automation/operator-panels-with-plcpac/tpac1008/)
- only RTU:
[TP1043] (http://www.mect.it/en/products/control-and-automation/operator-panels/tp1043/),
[TP1057] (http://www.mect.it/en/products/control-and-automation/operator-panels/tp1057/),
[TP1070] (http://www.mect.it/en/products/control-and-automation/operator-panels/tp1070/)

## Build instructions

LTIB should be installed by an unprivileged user. However, it requires root privileges for some operations.

Build prerequisites:

- a working (minimal) Ubuntu 14.04 LTS installation
- the top-level Makefile in this repository
- GNU make from Ubuntu repositories
- passwordless sudo enabled for the user that performs the build

Build steps:

1. install the **make utility**: *apt-get install make*
1. enable the build user for passwordless sudo: edit */etc/sudoers* and append a line as follows **<user name> ALL=(ALL) NOPASSWD: ALL**
1. create the top-level directory for LTIB installation with R/W permissions for the user, e.g.: mkdir ~/imx_mect
1. download the top-level Makefile from this repository in the top-level directory that was created in the previous step
1. install the toolchain, LTIB and create the target image files: **make -C ~/imx_mect/Makefile clean all**
1. create the target images for TPAC 1007 in *~/imx_mect/images-all/tpac_1007*: **make -C ~/imx_mect/Makefile tpac_1007**

## Main build steps

The main steps of the build process are:

- check and update the host environment
- download LTIB, toolchain for cross-compilation, Qt, and their configuration and patches
- install and patch LTIB
- installation of the toolchain for cross-compilation and Qt
- build image for the target

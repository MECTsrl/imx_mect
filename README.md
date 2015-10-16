# LTIB installation for MECT operator panels based on Freescale i.MX28 processors

The build downloads, configures and installs LTIB image build environment and Codesurcery target toolchain for MECT operator panels based on Freescale i.MX28 processors:

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

- a working (minimal) Ubuntu 14.04 LTS
- the top-level Makefile in this repository
- GNU make from Ubuntu repositories
- sudo enabled for the user that builds (optionally passwordless)

Build steps:

1. install the *make* utility from the Linux distribution:

        apt-get install make

1. enable the build user for (passwordless) sudo: edit */etc/sudoers* and append a line as follows:

        <user name> ALL=(ALL:ALL) ALL

   or passwordless:

        <user name> ALL=(ALL) NOPASSWD: ALL

1. create the build directory for LTIB with read and write permissions for the build user. Assuming the name of the directory is *imx_mect* in the home of the build user:

        mkdir ~/imx_mect

1. download the top-level Makefile from this repository in the build directory created in the previous step
1. install the toolchain and LTIB, and create the target image files:

        make -C ~/imx_mect/Makefile clean all

1. create the target images for TPAC 1007 in *~/imx_mect/images-all/tpac_1007*:

        make -C ~/imx_mect/Makefile tpac_1007


## Main build steps

The main steps of the Makefile-driven build process are:

- check and update the host environment
- download LTIB, toolchain for cross-compilation, Qt, and their configurations and patches
- install and patch LTIB
- install the toolchain for cross-compilation, compile and install Qt
- build the image for the target  
  The build process automatically downloads source archives and packages, when needed.  
  If one of the downloads fail, the build can be resumed by restarting manually LTIB:

        cd ~/imx_mect/ltib; ./ltib

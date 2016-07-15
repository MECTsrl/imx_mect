# LTIB installation for MECT operator panels based on Freescale i.MX28 processors

The build downloads, configures and installs the LTIB image build environment and the Codesurcery target toolchain for the MECT operator panels based on Freescale i.MX28 processors:

- with on-board I/O:
[TPAC1007](http://www.mect.it/en/products/control-and-automation/operator-panels-with-plcpac/tpac1007/),
[TPAC1006](http://www.mect.it/en/products/control-and-automation/operator-panels-with-plcpac/tpac1006/),
[TPAC1008](http://www.mect.it/en/products/control-and-automation/operator-panels-with-plcpac/tpac1008/)
- with RTU only:
[TP1043](http://www.mect.it/en/products/control-and-automation/operator-panels/tp1043/),
[TP1057](http://www.mect.it/en/products/control-and-automation/operator-panels/tp1057/),
[TP1070](http://www.mect.it/en/products/control-and-automation/operator-panels/tp1070/)

## Build instructions

LTIB is built and installed as an unprivileged user, but it requires root privileges for some operations.

### Build prerequisites

- a working (minimal) Ubuntu 14.04 LTS
- a git clone of this project
- GNU make from the Linux distribution repositories
- sudo enabled for the user that performs the build (optionally without a password)

### Build steps

1. Install the *make* and *git* utilities from the Linux distribution repositories:

        apt-get install make git

1. Enable the build user for sudo (optionally without a password).  
   Edit */etc/sudoers* and append a line as follows:

        <user name> ALL=NOPASSWD: /usr/bin/rpm, /opt/freescale/ltib/usr/bin/rpm

   or without a password (security risk):

        <user name> ALL=(ALL) NOPASSWD: ALL

1. Create the LTIB build directory with read and write permissions for the user that performs the build. E.g., assuming that the name of the directory is *imx_mect* in the home directory of the build user:

        mkdir -p ~/imx_mect

1. Clone this repository in the build directory created in the previous step (copy-paste the appropriate *clone URL* from the GitHub site):

        git clone <clone URL> ~/imx_mect

1. Install the toolchain and LTIB, and build the target image packages (RPMs):

        cd ~/imx_mect           # Top-level directory
        make clean
	make

More build options can be found in the [extended developer documentaiton](https://github.com/MECTsrl/imx_mect/wiki).

At the end, the build flow creates the archive needed to program TPAC 1007 480x272 devices in *~/imx_mect/images-all/TPAC1007_04_AA_r\<version\>.zip*.

Unpack the archive in the *Profiles* directory of [Freescale i.MX Manufacturing Toolkit](https://www.freescale.com/webapp/sps/download/license.jsp?colCode=IMX_MFG_TOOL) and follow the Freescale instructions to program the device.

## Main steps of the first build

The Makefile-driven build flow performs in sequence:

- checks and updates the host environment
- downloads the LTIB, toolchain for cross-compilation, Qt, and their configurations and patches
- installs and patches the LTIB
- installs the toolchain for cross-compilation, compiles and installs Qt on the host
- builds all configured packets (RPMs) to program the target device
- builds the target file systems by installing the appropriate packages (RPMs)
- builds the project for the Freescale i.MX Manufacturing Toolkit that can be used to flash the target device

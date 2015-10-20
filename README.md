# LTIB installation for MECT operator panels based on Freescale i.MX28 processors

The build downloads, configures and installs the LTIB image build environment and Codesurcery target toolchain for MECT operator panels based on Freescale i.MX28 processors:

- with on board I/O:
[TPAC1007] (http://www.mect.it/en/products/control-and-automation/operator-panels-with-plcpac/tpac1007/),
[TPAC1006] (http://www.mect.it/en/products/control-and-automation/operator-panels-with-plcpac/tpac1006/),
[TPAC1008] (http://www.mect.it/en/products/control-and-automation/operator-panels-with-plcpac/tpac1008/)
- only RTU:
[TP1043] (http://www.mect.it/en/products/control-and-automation/operator-panels/tp1043/),
[TP1057] (http://www.mect.it/en/products/control-and-automation/operator-panels/tp1057/),
[TP1070] (http://www.mect.it/en/products/control-and-automation/operator-panels/tp1070/)

## Build instructions

LTIB is built and installed as an unprivileged user but it requires root privileges for some operations.

### Build prerequisites

- a working (minimal) Ubuntu 14.04 LTS
- a git clone of this directory
- GNU make from the Linux distribution repositories
- sudo enabled for the user that performs the build (optionally without a password)

### Build steps

1. Install the *make* and *git* utilities from the Linux distribution repositories:

        apt-get install make git

1. Enable the build user for sudo (optionally without a password).  
   Edit */etc/sudoers* and append a line as follows:

        <user name> ALL=(ALL:ALL) ALL

   or without a password (security risk):

        <user name> ALL=(ALL) NOPASSWD: ALL

1. Create the LTIB build directory with read and write permissions for the user that performs the build. E.g., assuming that the name of the directory is *imx_mect* in the home directory of the build user:

        mkdir -p ~/imx_mect

1. Clone this repository in the build directory created in the previous step (copy-paste the appropriate *clone URL* from the GitHub site):

        cd ~/imx_mect
        git clone <clone URL>

1. Install the toolchain and LTIB, and create the target image files:

        cd ~/imx_mect
        make clean all

1. Create the target images for TPAC 1007 in *~/imx_mect/images-all/tpac_1007*:

        cd ~/imx_mect
        make tpac_1007

## Main steps of the automatic build

The Makefile-driven build flow does in sequence:

- checks and updates the host environment
- downloads LTIB, toolchain for cross-compilation, Qt, and their configurations and patches
- installs and patch LTIB
- installs the toolchain for cross-compilation, compiles and installs Qt
- builds the image for the target.  
  The build process automatically downloads the source archives and packages, as they are needed.  
  If any of these downloads fails, the build is aborted. It can be resumed by restarting manually the build of the target image using LTIB:

        cd ~/imx_mect/ltib
        ./ltib

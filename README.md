# imx_mect
Linux Kernel and LTIB GNU RootFS for MECT operator panels based on i.MX28:

- with on board I/O:
[TPAC1007] (http://www.mect.it/en/products/control-and-automation/operator-panels-with-plcpac/tpac1007/),
[TPAC1006] (http://www.mect.it/en/products/control-and-automation/operator-panels-with-plcpac/tpac1006/),
[TPAC1008] (http://www.mect.it/en/products/control-and-automation/operator-panels-with-plcpac/tpac1008/)

- only RTU:
[TP1043] (http://www.mect.it/en/products/control-and-automation/operator-panels/tp1043/),
[TP1057] (http://www.mect.it/en/products/control-and-automation/operator-panels/tp1057/),
[TP1070] (http://www.mect.it/en/products/control-and-automation/operator-panels/tp1070/)

Everything is tested on Ubuntu10.10 i686 (http://old-releases.ubuntu.com/releases/maverick/)

- Install CodeSourcery [Sourcery G++ Lite for ARM GNU Linux 2011.3.0.41] (http://www.codesourcery.com/sgpp/lite/arm/portal/package8742/public/arm-none-linux-gnueabi/arm-2011.03-41-arm-none-linux-gnueabi.bin)

- Install ltib [L2.6.35\_1.1.0\_ER\_SOURCE] (http://www.freescale.com/webapp/sps/site/prod_summary.jsp?code=i.MX281&fpsp=1&tab=Design_Tools_Tab#)

- Download [qt-everywhere-opensource-src-4.8.5.tar.gz] (https://download.qt.io/archive/qt/4.8/4.8.5/qt-everywhere-opensource-src-4.8.5.tar.gz) into /opt/freescale/

- Apply the Mect patches as follows:

  - in /opt/freescale/ checkout the packages from https://github.com/MECTsrl/imx\_mect/opt\_freescale/
  - in ${HOME}/ltib/ checkout the specs and configurations from https://github.com/MECTsrl/imx\_mect/home\_ltib/

- Build LTIB as usual, obtaining the 3 files:
    - imx28\_ivt\_linux.sb
    - rootfs.tar.bz2
    - local.tar.bz2
  available at http://www.mect.it/download/MectSuite\_1.3.1\_Extra/Kernel+RootFS\_rel5.3rc2\_SourceryGCC/TPAC1007\_480x272/


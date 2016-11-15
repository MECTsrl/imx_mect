#!/bin/sh

IMX_MECT=$(git ls-remote --tags https://github.com/MECTsrl/imx_mect.git | sort -t/ -k3 -V | cut -d/ -f3 | tail -n 1)
MECT_APPS=$(git ls-remote --tags https://github.com/MECTsrl/mect_apps.git | sort -t/ -k3 -V | cut -d/ -f3 | grep -v '^v2.9rc2$' | tail -n 1)
MECT_PLUGINS=$(git ls-remote --tags https://github.com/MECTsrl/mect_plugins.git | sort -t/ -k3 -V | cut -d/ -f3 | tail -n 1)
ATCMCONTROLRUNTIMESYSTEM=$(git ls-remote --tags https://github.com/MECTsrl/ATCMcontrol_RunTimeSystem.git | sort -t/ -k3 -V | cut -d/ -f3 | tail -n 1)

echo "Setting MECT_BUILD_IMXMECT_TAG to $IMX_MECT"
sed -i '/^\(export \)\?\bMECT_BUILD_IMXMECT_TAG\b/ s/\(MECT_BUILD_IMXMECT_TAG.*=\).*/\1 '$IMX_MECT'/' Makefile

echo "Setting MECT_BUILD_ATCMCRT_TAG to $ATCMCONTROLRUNTIMESYSTEM"
sed -i '/^\(export \)\?\bMECT_BUILD_ATCMCRT_TAG\b/ s/\(MECT_BUILD_ATCMCRT_TAG.*=\).*/\1 '$ATCMCONTROLRUNTIMESYSTEM'/' Makefile

echo "Setting MECT_BUILD_PLUGINSCRT_TAG to $MECT_PLUGINS"
sed -i '/^\(export \)\?\bMECT_BUILD_PLUGINSCRT_TAG\b/ s/\(MECT_BUILD_PLUGINSCRT_TAG.*=\).*/\1 '$MECT_PLUGINS'/' Makefile

echo "Setting MECT_BUILD_APPSCRT_TAG to $MECT_APPS"
sed -i '/^\(export \)\?\bMECT_BUILD_APPSCRT_TAG\b/ s/\(MECT_BUILD_APPSCRT_TAG.*=\).*/\1 '$MECT_APPS'/' Makefile

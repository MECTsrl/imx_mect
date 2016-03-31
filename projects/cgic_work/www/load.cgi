#!/bin/sh

# Questo è il file load.cgi, lo script che raccoglie le
# impostazioni

WWW_DIR="/local/www"
#WWW_DIR="/usr/share/www"
TARGET_NAME=""
COMPANY_NAME="MECT"
HOME_PAGE="menu.cgi"
BASE_DIR="/local/data"
LOCAL_ETC_DIR="/local/etc/sysconfig"

RECIPE_DIR="recipe"
ALARMS_DIR="alarms"
STORE_DIR="store"
PARTIAL_STORE_DIR="customstore"
TREND_DIR="customtrend"
SCREENSHOT_DIR="screenshot"
CONFIG_DIR="AC3_STRATEGIES"

PWDFILE="$WWW_DIR/.passwd"
SESSIONFILE="/tmp/.session"

FACTORY_DATA="/local/factory_data.tar.gz"
#FACTORY_PWD="/local/factory_pwd.tar.gz"
NETCONF="/local/etc/sysconfig/net.conf"
MACCONF="/etc/mac.conf"
SERIALCONF="/etc/serial.conf"

SIGN=/usr/bin/sign

PWDUSER=""
PWDSUPERUSER=""
PWDADMIN=""
PWDUSERDEFAULT="111111"
PWDSUPERUSERDEFAULT="222222"
PWDADMINDEFAULT="1357924680"

if [ -e $SESSIONFILE ]
then
	if [ -e $PWDFILE ]
	then
		. $PWDFILE
	fi
	. $SESSIONFILE
	if [ "$SESSION_NB" != "`grep GET /var/log/boa/access_log | grep -c '"-"'`" ]
	then 
		rm -f $SESSIONFILE
		PASSWORD="XXX"$SESSION_NB"vs"`grep GET /var/log/boa/access_log | grep -c '"-"'`"XXX"
	fi
fi


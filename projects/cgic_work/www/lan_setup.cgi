#!/bin/sh

DATA=`cat`

. ./load.cgi

[ -f "$NETCONF" ] && . "$NETCONF"

for x in `echo $DATA | tr "&" "\n"`; do
	eval $x
done

echo MAC0="$MAC0"                            > $NETCONF
echo IPADDR0="$IP1.$IP2.$IP3.$IP4"          >> $NETCONF
echo NETMASK0="$NM1.$NM2.$NM3.$NM4"         >> $NETCONF
echo GATEWAY0="$GW1.$GW2.$GW3.$GW4"         >> $NETCONF
echo NAMESERVER01="$DN11.$DN12.$DN13.$DN14" >> $NETCONF
echo NAMESERVER02="$DN21.$DN22.$DN23.$DN24" >> $NETCONF
echo MAC1="$MAC1"                           >> $NETCONF
echo IPADDR1="$IPADDR1"                     >> $NETCONF
echo NETMASK1="$NETMASK1"                   >> $NETCONF
echo GATEWAY1="$GATEWAY1"                   >> $NETCONF
echo NAMESERVER11="$NAMESERVER11"           >> $NETCONF
echo NAMESERVER12="$NAMESERVER12"           >> $NETCONF
sync

/etc/rc.d/init.d/autoexec stop > /dev/null 2>&1
if [ -x /usr/bin/splash ]
then
	/usr/bin/splash --text "Modify network ..." --dimension 42 -qws > /dev/null 2>&1 &
fi
# not working
/etc/rc.d/init.d/network restart
if [ $? == 0 ]
then
	TABLE="<table style=\"border:solid 2px #335970;\" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >"
	MSG="Network setting updated. Reboot the system to apply the modification."
else
	TABLE="<table style=\"border:solid 2px #FF0000;\" bgcolor=#fffbff cellspacing=10 cellpadding=4 align=center >"
	MSG="Problem to update network settings"
fi
if [ -x /usr/bin/splash ]
then
	killall splash
fi
/etc/rc.d/init.d/autoexec start > /dev/null 2>&1

cat <<EOF
Content-Type: text/html

<html>
<head>
<title>LAN SETUP</title>
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<div id="container">
<div id="header">
<table width="100%">
<tr align="right">
<td>
EOF
. ./info.cgi
cat <<EOF
</td>
</tr>
<tr>
<td>
<h1>REMOTE UPDATER</h1>
</td>
</tr>
</table>
</div>
<center>
<div id="content">
EOF
echo $TABLE
cat <<EOF
<table style="border:solid 2px #335970;" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >
<tbody>
<tr>
<td>
EOF
echo "$MSG"      
cat <<EOF
</td>
</tr>
</tbody>
</table>
</div>                                                                                
EOF
echo "<input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
echo "<input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='lan_config.cgi'\">"
echo "<input class=bottoni type=\"button\" value=\"Reboot\" onclick=\"window.location.href='reboot.cgi?COMMAND=REBOOT'\">"
cat <<EOF
</center>
</div>                                                                                
EOF
echo "         <div id=\"footer\"><h2>$COMPANY_NAME</h2></div>"
cat <<EOF
</body>
</html>
EOF

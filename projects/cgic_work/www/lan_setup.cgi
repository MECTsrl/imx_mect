#!/bin/sh

DATA=`cat`

. ./load.cgi

[ -f "$NETCONF" ] && . "$NETCONF"

for x in `echo $DATA | tr "&" "\n"`; do
	eval $x
done 

if [ $ip != '' ]; then
echo MAC0="$MAC0"       > $NETCONF
echo IPADDR0=$ip       >> $NETCONF
echo NETMASK0=$nm      >> $NETCONF
echo GATEWAY0=$gw      >> $NETCONF
echo NAMESERVER01=$dn1 >> $NETCONF
echo NAMESERVER02=$dn2 >> $NETCONF
echo MAC1="$MAC1"                           >> $NETCONF
echo IPADDR1="$IPADDR1"                     >> $NETCONF
echo NETMASK1="$NETMASK1"                   >> $NETCONF
echo GATEWAY1="$GATEWAY1"                   >> $NETCONF
echo NAMESERVER11="$NAMESERVER11"           >> $NETCONF
echo NAMESERVER12="$NAMESERVER12"           >> $NETCONF
sync
fi

cat $NETCONF | grep $ip
if [ $? == 0 ]
then
	REFRESH="<meta http-equiv=\"refresh\" content=\"1;url=http://$ip/lan_config.cgi\">" 
	TABLE="<table style=\"border:solid 2px #335970;\" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >"
	MSG="Network setting updated, Reboot for the changes to take effect."
else
	TABLE="<table style=\"border:solid 2px #FF0000;\" bgcolor=#fffbff cellspacing=10 cellpadding=4 align=center >"
	MSG="Problem to update network settings"
	
fi

cat <<EOF
Content-Type: text/html

<html>
<head>
<title>LAN Manager</title>
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<div id="container">
		<div id="header">
			<table width="100%">
				<tr align="left">
					<td>
						<h1><img src="$LOGO_NAME" style="width:240px;height:136px;float=left;vertical-align:middle;">  $TARGET_NAME Lan Manager</h1>
					</td>
					<td>
EOF
. ./info.cgi
cat <<EOF
					</td>
				</tr>
			</table>
		</div> <!-- end div header -->
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
</body>
</html>
EOF

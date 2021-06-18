#!/bin/sh

. ./load.cgi

if [ -e $FACTORY_DATA ]
then
	/etc/rc.d/init.d/autoexec stop > /dev/null 2>&1
	if [ -x /usr/bin/splash ]
	then
		/usr/bin/splash --text "Restore factory ..." --dimension 42 -qws > /dev/null 2>&1 &
	fi
	old_dir=`pwd`
	cd /local
	tar xzf $FACTORY_DATA -C /
	if [ $? == 0 ]
	then
		chown root:root -R /local
		#reset also network configuration and put factory_test with exe permission
		cd $old_dir
		. ./load.cgi
		chmod +x /local/root/factory_test
		sed -i /IPADDR0/d  "$NETCONF"
		sed -i /NETMASK0/d  "$NETCONF"
		sed -i /GATEWAY0/d  "$NETCONF"
		sed -i /NAMESERVER01/d  "$NETCONF"
		sed -i /NAMESERVER02/d  "$NETCONF"
		sed -i '2i\IPADDR0=192.168.5.211' "$NETCONF"
		sed -i '3i\NETMASK0=255.255.255.0' "$NETCONF"
		sed -i '4i\GATEWAY0=192.168.5.10' "$NETCONF"
		sed -i '5i\NAMESERVER01=' "$NETCONF"
		sed -i '6i\NAMESERVER02=' "$NETCONF"

		MSG="The target has been reset."
	else
		MSG="Error in restoring defaults"
	fi
	cd $old_dir
	sync
	if [ -x /usr/bin/splash ]
	then
		killall splash
	fi
	/etc/rc.d/init.d/autoexec start > /dev/null 2>&1
else
	MSG="Error missing factory data"
fi

cat <<EOF
Content-Type: text/html

<html>
<head>
<title>$TARGET_NAME RESET FACTORY DEFAULTS</title>
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
	<div id="container">
		<div id="header">
			<table width="100%">
				<tr align="left">
					<td>
						<h1><img src="$LOGO_NAME" style="width:auto;height:136px;float=left;vertical-align:middle;">  $TARGET_NAME Factory Reset</h1>
					</td>
					<td>
EOF
. ./info.cgi
cat <<EOF
					</td>
				</tr>
			</table>
		</div> <!-- end div header -->
		<div id="content">
			<H3>
EOF
echo $MSG
cat <<EOF
			</H3>
		</div> <!-- end div content -->
<BR>
<center>
EOF
        echo "<input class=bottoni type=\"button\" value=\"Reboot\" onclick=\"window.location.href='reboot.cgi?COMMAND=REBOOT'\">"

cat <<EOF
</center>
	</div> <!-- end div container -->
</body>
</html>
EOF

#!/bin/sh

# Network configuration

. ./load.cgi

[ -f "$NETCONF" ] && . "$NETCONF"

#eval `echo "$NAMESERVER01" | sed 's/
#$//' | awk -F. '{ f = $1 == 0 ? 1 : $1; print "DN11=" f "\nDN12=" $2 "\nDN13=" $3 "\nDN14=" $4}'`
#eval `echo "$NAMESERVER02" | sed 's/
#$//' | awk -F. '{ f = $1 == 0 ? 1 : $1; print "DN21=" f "\nDN22=" $2 "\nDN23=" $3 "\nDN24=" $4}'`
#eval `echo "$IPADDR0" | sed 's/
#$//' | awk -F. '{ print "IP1=" $1 "\nIP2=" $2 "\nIP3=" $3 "\nIP4=" $4}'`
#eval `echo "$NETMASK0" | sed 's/
#$//' | awk -F. '{ f = $1 == 0 ? 1 : $1; print "NM1=" f "\nNM2=" $2 "\nNM3=" $3 "\nNM4=" $4}'`
#eval `echo "$GATEWAY0" | sed 's/
#$//' | awk -F. '{ f = $1 == 0 ? 1 : $1; print "GW1=" f "\nGW2=" $2 "\nGW3=" $3 "\nGW4=" $4}'`

IP=`grep 'IPADDR0=' $NETCONF  | cut -d'=' -f2 `
NM=`grep 'NETMASK0=' $NETCONF  | cut -d'=' -f2 `
GW=`grep 'GATEWAY0=' $NETCONF  | cut -d'=' -f2 `
DN1=`grep 'NAMESERVER01=' $NETCONF  | cut -d'=' -f2 `
DN2=`grep 'NAMESERVER02=' $NETCONF  | cut -d'=' -f2 `

#initialize unset value
[ -n "$DN11" ] || DN11=1
[ -n "$DN12" ] || DN12=0
[ -n "$DN13" ] || DN13=0
[ -n "$DN14" ] || DN14=0
[ -n "$DN21" ] || DN21=1
[ -n "$DN22" ] || DN22=0
[ -n "$DN23" ] || DN23=0
[ -n "$DN24" ] || DN24=0

cat <<EOF
Content-Type: text/html

<html>
<head>
<title>$TARGET_NAME LAN Manager</title>
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
	<div id="container">
<center>
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
        <div id="content">
            <div id="form"> 
                
                    <fieldset>
                        <legend>Network Configuration</legend>
                        <table>
                        <tbody>          
                        <tr>

EOF
echo "<div id=\"eth0\" class=\"container\">"
echo "<label>ETHERNET 0 Static: </label><br>"
echo "<form action=\"lan_setup.cgi\" method=\"POST\">"
     echo "<div><label>IP:	   </label><input name=\"ip\" type=\"text\" minlength=\"7\" maxlength=\"15\" size=\"15\" placeholder=\"xxx.xxx.xxx.xxx\" value=$IP  pattern=\"^((\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.){3}(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$\"></div><br>"
     echo "<div><label>NM:	 </label><input name=\"nm\" type=\"text\" minlength=\"7\" maxlength=\"15\" size=\"15\" placeholder=\"xxx.xxx.xxx.xxx\"value=$NM  pattern=\"^((\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.){3}(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$\"></div><br>"
     echo "<div><label>GW:	</label><input name=\"gw\" type=\"text\" minlength=\"7\" maxlength=\"15\" size=\"15\" placeholder=\"xxx.xxx.xxx.xxx\"value=$GW  pattern=\"^((\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.){3}(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$\"></div><br>"
     echo "<div><label>DN1:	</label><input name=\"dn1\" type=\"text\" minlength=\"7\" maxlength=\"15\" size=\"15\" placeholder=\"xxx.xxx.xxx.xxx\" value=$DN1  pattern=\"^((\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.){3}(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$\"></div><br>"
     echo "<div><label>DN2:	</label><input name=\"dn2\" type=\"text\" minlength=\"7\" maxlength=\"15\" size=\"15\" placeholder=\"xxx.xxx.xxx.xxx\" value=$DN2  pattern=\"^((\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.){3}(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$\"></div><br>"
     echo "<input class=bottoni type=\"submit\" value=\"Apply\"></form>"
     echo "</div>"
cat <<EOF
                        </tr>
                        </tbody>
                        </table>
					
                    </fieldset>
			</div> <!-- end div form -->
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
cat <<EOF
		</div> <!-- end div content -->
</center>
EOF
echo "         <div id=\"footer\"><h2></h2></div>"
cat <<EOF
	</div> <!-- end div container -->
</body>
</html>
EOF

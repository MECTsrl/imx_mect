#!/bin/sh

cat <<EOM
				<table STYLE="color:#CFF;">
					<tbody>
						<tr>
EOM
if  [ "$PASSWORD" != "" ] && [ "$PASSWORD" == "$PWDADMIN" ]
then
cat <<EOM
							<td>
								<b>Login:</b>
							</td>
							<td>
								Admin
							</td>
EOM
else
	if  [ "$PASSWORD" != "" ] && [ "$PASSWORD" == "$PWDUSER" ]
	then
cat <<EOM
							<td>
								<b>Login:</b>
							</td>
							<td>
								User
							</td>
EOM
	else
		if [ "$PASSWORD" != "" ] && [ "$PASSWORD" == "$PWDSUPERUSER" ]
		then
cat <<EOM
							<td>
								<b>Login:</b>
							</td>
							<td>
								SuperUser
							</td>
EOM
		else
			PASSWORD='IVALID'
		fi
	fi
fi
cat <<EOM
							<td>
								<b>IP:</b>
							</td>
							<td>
EOM
cat $NETCONF | grep IPADDR0 | cut -d\= -f2 | sed s/\"//g
cat <<EOM
							</td>
							<td>
								<b>MAC:</b>
							</td>
							<td>
EOM
cat $MACCONF | grep MAC0 | cut -d\= -f2 | sed s/\"//g
cat <<EOM
							</td>
							<td>
								<b>S/N:</b>
							</td>
							<td>
EOM
if [ -f $SERIALCONF ]; then
	cat $SERIALCONF | sed s/\"//g
else
	echo "-"
fi
cat <<EOM
							</td>
						</tr>
					</tbody>  
				</table>
EOM


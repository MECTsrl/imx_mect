#!/bin/sh

`cat | dos2unix | awk '{if ($0 ~ /Content-Disposition: form-data/) {split($0,a,"="); split(a[2],b,"\""); getline; getline; printf "export %s=%s\n", b[2],$0}}'`
. ./load.cgi

cat <<EOF
Content-Type: text/html

<html>
<head>
<title>$TARGET_NAME REMOTE UPDATER</title>
<link rel="stylesheet" type="text/css" href="style.css">
EOF
eval $QUERY_STRING

if [ ! `echo $ROOT_DIR | grep ^$RECIPE_DIR` ] && [ ! `echo $ROOT_DIR | grep ^$ALARMS_DIR` ] && [ ! `echo $ROOT_DIR | grep ^$STORE_DIR` ] && [ ! `echo $ROOT_DIR | grep ^$TREND_DIR` ] && [ ! `echo $ROOT_DIR | grep ^$SCREENSHOT_DIR` ]
then
echo "<META http-equiv=\"refresh\" content=\"0;URL=$HOME_PAGE\">"
cat <<EOF
</head>
<body>
</body>
</html>
EOF
exit 0
fi
cat <<EOF
<script language="JavaScript">
function toggle(source) {
  checkboxes = document.getElementsByName('foo');
  for(var i=0, n=checkboxes.length;i<n;i++) {
    checkboxes[i].checked = source.checked;
  }
}
</script>
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
<h1>$TARGET_NAME REMOTE UPDATER</h1>
</td>
</tr>
</table>
</div>
<div id="content">
<center>
<div id="form">

<form action="filesmanager.cgi" method="POST">
<fieldset>
EOF
if [ `echo $ROOT_DIR | grep ^$RECIPE_DIR` ]
then
 echo "<legend>Recipe files manager</legend><br>"
else
if [ `echo $ROOT_DIR | grep ^$ALARMS_DIR` ]
then
 echo "<legend>Alarms files manager</legend><br>"
else
if [ `echo $ROOT_DIR | grep ^$STORE_DIR` ]
then
 echo "<legend>Logs files manager</legend><br>"
else
if [ `echo $ROOT_DIR | grep ^$TREND_DIR` ]
then
 echo "<legend>Trend files manager</legend><br>"
else
if [ `echo $ROOT_DIR | grep ^$SCREENSHOT_DIR` ]
then
 echo "<legend>Screenshot files manager</legend><br>"
fi
fi
fi
fi
fi
cat <<EOF
<input type="checkbox" onClick="toggle(this)" /> Toggle All<br/>

<BR>
<table style="border:solid 2px #335970;" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >
<tbody>
<tr>
EOF
COLUMN_NB=6
i=0
for x in `ls $BASE_DIR/$ROOT_DIR/`; do
	i=$((i+1))
	if [ -d $BASE_DIR/$ROOT_DIR/$x ]
	then
		echo "<td><input type=\"checkbox\" name=\"foo\" value=\"$BASE_DIR/$ROOT_DIR/$x\"><a href=\"filebrowser.cgi?ROOT_DIR=$ROOT_DIR/$x\">$x</a></td>"
	else
		echo "<td><input type=\"checkbox\" name=\"foo\" value=\"$BASE_DIR/$ROOT_DIR/$x\">$x</td>"
	fi
	if [ $i -gt $COLUMN_NB ]
	then
		echo "</tr>"
		echo "<tr>"
		i=0
	fi
done
cat <<EOF
</tr>
</tbody>
</table>
<input type="hidden" name="ROOT_DIR" value="$ROOT_DIR">
<BR>
EOF
if [ -e $SESSIONFILE ]
then
. $SESSIONFILE
. $PWDFILE
if [ $PASSWORD != "" ] && [ "$PWDSUPERUSER" = "$PASSWORD" -o "$PWDADMIN" = "$PASSWORD" ]
then
cat <<EOF
<input class=bottoni type="submit" value="Delete" name="delete">
EOF
fi
fi
cat <<EOF
<input class=bottoni type="submit" value="Download" name="download">
</fieldset>
</form>

</div> <!-- end div form -->
<BR>
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
if [ "`dirname $ROOT_DIR`" != "." ]
then
	echo "<input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='filebrowser.cgi?ROOT_DIR=`dirname $ROOT_DIR`'\">"
else
	if [ `echo $ROOT_DIR | grep ^$RECIPE_DIR` ]
	then
		if [ "$ROOT_DIR" == "$RECIPE_DIR" ]
		then
			echo "<input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='recipes_manager.cgi'\">"
		else
			echo "<input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='recipes_manager.cgi'\">"
		fi
	else
		if [ `echo $ROOT_DIR | grep ^$ALARMS_DIR` ]
		then
			if [ "$ROOT_DIR" == "$ALARMS_DIR" ]
			then
				echo "<input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='$HOME_PAGE'\">"
			else
				echo "<input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='filebrowser.cgi?ROOT_DIR=$ALARMS_DIR'\">"
			fi
		else
			if [ `echo $ROOT_DIR | grep ^$STORE_DIR` ]
			then
				echo "<input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='logs_filter.cgi'\">"
			else
				if [ "$ROOT_DIR" == "$TREND_DIR" ]
				then
					echo "<input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='trend_manager.cgi'\">"
				else
					if [ "$ROOT_DIR" == "$SCREENSHOT_DIR" ]
					then
						echo "<input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='trend_manager.cgi'\">"
					else
						echo "<input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='trend_manager.cgi'\">"
					fi
				fi
			fi
		fi
	fi
fi

cat <<EOF
</center>
</div> <!-- end div content -->
EOF
echo "         <div id=\"footer\"><h2>$COMPANY_NAME</h2></div>"
cat <<EOF
</div> <!-- end div container -->
</body>
</html>
EOF
exit 0

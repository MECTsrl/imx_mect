#!/bin/sh

`cat | dos2unix | awk '{if ($0 ~ /Content-Disposition: form-data/) {split($0,a,"="); split(a[2],b,"\""); getline; getline; printf "export %s=%s\n", b[2],$0}}'`
. ./load.cgi

cat <<EOF
Content-Type: text/html

<html>
<head>
<title>$TARGET_NAME Files Manager</title>
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
				<tr align="left">
					<td>
						<h1><img src="$LOGO_NAME" style="width:240px;height:136px;float=left;vertical-align:middle;">  $TARGET_NAME Files Manager</h1>
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
<form name="tre" method="POST" enctype="multipart/form-data" action="upload.cgi">
<table style="border:solid 2px #335970;" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >
EOF
	
if [ "$ROOT_DIR" == "$RECIPE_DIR" ]
then
cat <<EOF
        <tbody>
        <tr>
        <td>
        <input type="file" name="RCPZIP" accept="application/zip" required>
        </td>
        <td>
        <input class=bottoni type="submit" value="Upload Recipe">
        </td>
        </tr>
        </tbody>
EOF
#elif [ "$ROOT_DIR" == "$ALARMS_DIR" ]
#then
#	echo "<td>"
#	echo "<input type=\"file\" name=\"LOGSTBL\" required>"
#	echo "</td>"
#	echo "<td>"
#	echo "<input class=bottoni type=\"submit\" value=\"Update Partial logs\">"
#	echo "</td>"

elif [ "$ROOT_DIR" == "$TREND_DIR" ]
then
cat <<EOF
        </tbody>
        <tr>
        <td>
        <input type="file" name="TRENDTBL" accept="application/csv" required>
        </td>
        <td>
        <input class=bottoni type="submit" value="Upload Trends">
        </td>
        </tr>
        </tbody>
EOF
#elif [ "$ROOT_DIR" == "$SCREENSHOT_DIR" ]
#then 	
#    	echo "<td>"
#	echo "<input type=\"file\" name=\"LOGSTBL\" required>"
#	echo "</td>"
#	echo "<td>"
#	echo "<input class=bottoni type=\"submit\" value=\"Update Partial logs\">"
#	echo "</td>"

fi	
cat <<EOF		
</tbody>
</table>
</form>
EOF
if [ "$ROOT_DIR" == "$STORE_DIR" ]
then
cat <<EOF
	<BR>	
	<fieldset>
	<legend>Custom Store manager</legend><br>
	<form action="filesmanager.cgi" method="POST">
	<table style="border:solid 2px #335970;" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >
	<tr>
EOF
head -1 `ls $BASE_DIR/$STORE_DIR/* | tail -1` | awk 'BEGIN{FS=";"}{for (i = 1; i <= NF; i++) {gsub(/[ \t]+/, "", $i); print $i;}}' > $BASE_DIR/$PARTIAL_STORE_DIR/Total.csv
for x in `ls $BASE_DIR/$PARTIAL_STORE_DIR`; do
		echo "<td>"
		echo "<input type=\"checkbox\" name=\"partialStore\" value=\"$BASE_DIR/$PARTIAL_STORE_DIR/$x\">"
		echo "<a href=\"display_csv.cgi?CSV_FILE=$BASE_DIR/$PARTIAL_STORE_DIR/$x\">`echo $x`</a>"
		echo "</td>"
done
cat<<EOF
	</tr>
	</table>
	<BR>
	<input class=bottoni type="submit" value="Download" name="download">
	</form>
	<BR>
	<form name="StorePost" method="POST" enctype="multipart/form-data" action="upload.cgi">
	<table style="border:solid 2px #335970;" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >
        <td>
        <input type="file" name="LOGSTBL" required>
        </td>
        <td>
        <input class=bottoni type="submit" value="Upload Partial logs">
        </td>
        </tbody>
	</table>
	</form> 
	</fieldset>
EOF
fi
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
cat <<EOF
</center>
</div> <!-- end div content -->
</div> <!-- end div container -->
</body>
</html>
EOF
exit 0

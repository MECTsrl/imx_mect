#!/bin/sh

. ./load.cgi

cat <<EOF
Content-Type: text/html

<html>
<head>
<title> $TARGET_NAME LOG DOWNLOAD </title>
<link rel="stylesheet" type="text/css" href="style.css">
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
						<h1><img src="$LOGO_NAME" style="width:240px;height:136px;float=left;vertical-align:middle;">  $TARGET_NAME Logs Manager </h1>
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
<form action="logs_extractor.cgi" method="POST">
<table style="border:solid 2px #335970;" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >
<thead>
	<tr>
		<td align="center">
		<b>Toggle All</b><BR><input type="checkbox" onClick="toggle(this)" />
		</td>
		<td><b>Log name</b><BR></td>
		<td><b>Initial date</b><BR>[YYYY/MM/DD]</td>
		<td><b>Initial time</b><BR>[hh:mm:ss]</td>
		<td><b>Final date</b><BR>[YYYY/MM/DD]</td>
		<td><b>Final time</b><BR>[hh:mm:ss]</td>
	</tr>
</thead>
<tbody>
EOF
head -1 `ls $BASE_DIR/$STORE_DIR/* | tail -1` | awk 'BEGIN{FS=";"}{for (i = 1; i <= NF; i++) {gsub(/[ \t]+/, "", $i); print $i;}}' > $BASE_DIR/$PARTIAL_STORE_DIR/Total.csv
for x in `ls $BASE_DIR/$PARTIAL_STORE_DIR`; do
	echo "<tr>"
		echo "<td align=\"center\">"
			echo "<input type=\"checkbox\" name=\"foo\" value=\"$BASE_DIR/$PARTIAL_STORE_DIR/$x\">"
		echo "</td>"
		echo "<td>"
		if  [ "$x" == "Total.csv" ]
		then
			echo "<a href=\"filebrowser.cgi?ROOT_DIR=$STORE_DIR\">`echo $x | cut -d. -f1`</a>";
		else
			echo "<a href=\"display_csv.cgi?CSV_FILE=$BASE_DIR/$PARTIAL_STORE_DIR/$x\">`echo $x | cut -d. -f1`</a>"
		fi
		echo "</td>"
		echo "<td>"
			echo "<input type=\"date\" name=\"datein\" value=\"\" size=\"4\">"
		echo "</td>"
		echo "<td>"
			echo "<input type=\"time\" name=\"timein\" value=\"\" size=\"2\">"
		echo "</td>"
		echo "<td>"
			echo "<input type=\"date\" name=\"datefin\" value=\"\" size=\"4\">"
		echo "</td>"
		echo "<td>"
			echo "<input type=\"time\" name=\"timefin\" value=\"\" size=\"2\">"
		echo "</td>"
	echo "</tr>"
done
cat <<EOF
</tbody>
</table>
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
</form>
                                                                            
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
echo "      <input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='logs_manager.cgi'\">"
cat <<EOF
</div>    
</center>
</div>                                                                                
</body>
</html>


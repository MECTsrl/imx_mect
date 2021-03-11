#!/bin/sh

. ./load.cgi

eval $QUERY_STRING

cat <<EOF
Content-Type: text/html

<html>
<head>
<title> REMOTE UPDATER </title>
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<div id="container">
		<div id="header">
			<table width="100%">
				<tr align="left">
					<td>
						<h1><img src="$LOGO_NAME" style="width:240px;height:136px;float=left;vertical-align:middle;">  Column Select</h1>
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
<table style="border:solid 2px #335970;" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >
<theader>
<b>
Column selected by 
EOF
basename $CSV_FILE
cat <<EOF
</b>
</theader>
<tbody>
EOF
awk 'BEGIN{\
		 FS=";"; \
	 }\
	 {\
		for (i = 0; i < NF; i++) {\
			print "<td>"$i"</td>";
		}\
	 }' $CSV_FILE
cat <<EOF
</tbody>
</table>
</div>                                                                                
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
echo "      <input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='filebrowser.cgi?ROOT_DIR=store'\">"
cat <<EOF
</center>
</div>                                                                                
EOF
echo "         <div id=\"footer\"><h2></h2></div>"
cat <<EOF
</body>
</html>


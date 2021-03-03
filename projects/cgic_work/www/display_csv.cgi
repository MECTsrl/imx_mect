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
<tr align="right">
<td>
EOF
. ./info.cgi
cat <<EOF
</td>
</tr>
<tr>
<td>
<h1>COLUMN SELECTED</h1>
</td>
</tr>
</table>
</div>
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
echo "      <input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='logs_filter.cgi'\">"
cat <<EOF
</center>
</div>                                                                                
EOF
echo "         <div id=\"footer\"><h2></h2></div>"
cat <<EOF
</body>
</html>


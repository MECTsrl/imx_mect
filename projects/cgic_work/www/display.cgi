#!/bin/sh

# Network configuration

. ./load.cgi

cat <<EOF
Content-Type: text/html

<html>
<head>
<title>$TARGET_NAME DISPLAY MANAGEMENT</title>
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
			<h1>$TARGET_NAME DISPLAY MANAGEMENT</h1>
</td>
</tr>
</table>
		</div>
<center>
        <div id="content">
<div id="form">
<fieldset>
                        <legend>Display</legend>
                <form name="brightness" action="display_setup.cgi" method="POST">
                        <table>
                        <tr>
	                        <td>
	    	                    Brightness:
        	                </td>
	                        <td>
EOF
SCALED_BRIGHTNESS=`cat $LOCAL_ETC_DIR/brightness | cut -d\  -f2`
BRIGHTNESS=`expr $SCALED_BRIGHTNESS \* 2`
#echo "    	                    <input type=\"decimal\" name=\"BRIGHTNESS\" value=\"`cat $LOCAL_ETC_DIR/brightness | cut -d\  -f2`\">"
echo "    	                    <input type=\"decimal\" name=\"BRIGHTNESS\" value=\"$BRIGHTNESS\">"
cat <<EOF							
        	                </td>
	                        <td>
								<input class=bottoni type="submit" value="Apply">
        	                </td>
                        </tr>
						</table>
                 </form>
                <form name="screensaver" action="display_setup.cgi" method="POST">
						<table>
                        <tr>
	                        <td>
	    	                    Screensaver:
        	                </td>
	                        <td>
EOF
eval `grep screen_saver_s $LOCAL_ETC_DIR/system.ini | awk '{print $1$2$3}'`
echo "    	                    <input type=\"decimal\" name=\"SCREENSAVER\" value=\"$screen_saver_s\">"
cat <<EOF							
        	                </td>
	                        <td>
								<input class=bottoni type="submit" value="Apply">
        	                </td>
                        </tr>
						</table>
                 </form>
                <form name="tscalib" action="display_setup.cgi" method="POST">
						<table>
                        <tr>
	                        <td>
	    	                    Touch calibration:
        	                </td>
	                        <td>
        	                </td>
	                        <td>
								<input class=bottoni type="submit" value="Start">
	    	                    <input type="hidden" name="TSCALIB" value="1">
        	                </td>
                        </tr>
                        </table>
                 </form>
</fieldset>

</div> <!-- end div form -->

EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
cat <<EOF
		</div> <!-- end div content -->
</center>
EOF
echo "         <div id=\"footer\"><h2>$COMPANY_NAME</h2></div>"
cat <<EOF
	</div> <!-- end div container -->
</body>
</html>
EOF

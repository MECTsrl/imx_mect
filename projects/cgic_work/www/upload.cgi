#!/bin/sh

. ./load.cgi

BASE_DIR="/local/data"
LOCAL_APP_DIR="/local/root"

SYSUPDATE=/local/sysupdate.sh
ERROR=1

if [ "$REQUEST_METHOD" = "POST" ]; then

  # dump the data
  TMPOUT=/local/fwupdate
  cat > $TMPOUT

  # extract the file name if the file is a receipe zip 
  FILENAME=`grep 'Content-Disposition: form-data; name=' | grep 'filename="' $TMPOUT | cut -d\; -f3 | cut -d\" -f2`
    
  # extract the type of upload
  SYSUPD=`head $TMPOUT | grep -c name=\"SYSUPD\"`
  HMI=`head $TMPOUT | grep -c name=\"HMI\"` 
  FCRTS=`head $TMPOUT | grep -c name=\"FCRTS\"` 
  PLC=`head $TMPOUT | grep -c name=\"PLC\"` 
  CROSSTBL=`head $TMPOUT | grep -c name=\"CROSSTBL\"` 
  SYSINI=`head $TMPOUT | grep -c name=\"SYSINI\"` 
  RCPTBL=`head $TMPOUT | grep -c name=\"RCPTBL\"` 
  RCPZIP=`head $TMPOUT | grep -c name=\"RCPZIP\"` 
  TRENDTBL=`head $TMPOUT | grep -c name=\"TRENDTBL\"` 
  LOGSTBL=`head $TMPOUT | grep -c name=\"LOGSTBL\"` 
  SPLASH=`head $TMPOUT | grep -c name=\"SPLASH\"` 

  # ship the first 4 lines and the lats line and the last \r
  cat $TMPOUT | sed '1,4d' | sed '$d' | sed '$s/.$//' > $TMPOUT.1

  if [ -s $TMPOUT.1 ]
  then

    if [ "$RCPTBL" != "1" ] && [ "$RCPZIP" != "1" ] && [ "$LOGSTBL" != "1" ] && [ "$TRENDTBL" != "1" ] && [ "$SPLASH" != "1" ]; then
	/etc/rc.d/init.d/autoexec stop > /dev/null 2>&1
	if [ -x /usr/bin/splash ]
	then
		/usr/bin/splash --text "Updating ..." --dimension 42 -qws > /dev/null 2>&1 &
	fi
    fi

  # SYSUPDATE
  if [ "$SYSUPD" == "1" ]
  then
	MSG="system update"
  	if  [ -s $TMPOUT.1 ]
	then
		mv $TMPOUT.1 $SYSUPDATE
		chmod 754 $SYSUPDATE
	  	$SYSUPDATE
		ERROR=$?
		rm -rf $SYSUPDATE
	else
		ERROR=1
	fi
  fi

  # HMI
  if [ "$HMI" = "1" ]; then
     MSG="hmi update"
     if [ -s $TMPOUT.1 ]; then
        mv $TMPOUT.1 $LOCAL_APP_DIR/hmi
        ERROR=$?
        chmod 754 $LOCAL_APP_DIR/hmi
     else
          ERROR=1
     fi
   fi

    # FCRTS
    if [ "$FCRTS" = "1" ]; then
        MSG="runtime update"
        if [ -s $TMPOUT.1 ]; then
            mv $TMPOUT.1 $LOCAL_APP_DIR/fcrts
            ERROR=$?
            chmod 754 $LOCAL_APP_DIR/fcrts
        else
            ERROR=1
        fi
    fi

    if [ "$PLC" = "1" ]; then
        MSG="PLC program update"
          if [ -s $TMPOUT.1 ]; then
            mv $TMPOUT.1 /local/control.tar.gz
            cd /local
            tar xzf /local/control.tar.gz
            ERROR=$?
			rm -f /local/control.tar.gz
            cd -
          else
              ERROR=1
          fi
    fi
    if [ "$CROSSTBL" = "1" ]; then
        MSG="Cross table"
          if [ -s $TMPOUT.1 ]; then
            mv $TMPOUT.1 $LOCAL_ETC_DIR/Crosstable.csv.tmp
            ERROR=$?
            chmod 644 $LOCAL_ETC_DIR/Crosstable.csv.tmp
            /usr/bin/dos2unix $LOCAL_ETC_DIR/Crosstable.csv.tmp
	    if diff Crosstable.csv.tmp Crosstable.csv >/dev/null; then
		#echo "SAME"
		mv $LOCAL_ETC_DIR/Crosstable.csv.tmp $LOCAL_ETC_DIR/Crosstable.csv
                chmod 644 $LOCAL_ETC_DIR/Crosstable.csv
	    else
		#echo "DIFFERENT"
#		/etc/rc.d/init.d/autoexec stop > /dev/null 2>&1
		LOG="`date '+%Y_%m_%d'`.log"
		if [ -e "$BASE_DIR/$STORE_DIR/$LOG" ]; then
			mv "$BASE_DIR/$STORE_DIR/$LOG" "$BASE_DIR/$STORE_DIR/`date '+%Y_%m_%d'`_`date '+%H%M%S'`.log"
		fi		
		mv $LOCAL_ETC_DIR/Crosstable.csv.tmp $LOCAL_ETC_DIR/Crosstable.csv
                chmod 644 $LOCAL_ETC_DIR/Crosstable.csv
	    fi
          else
              ERROR=1
        fi
    fi
    if [ "$SYSINI" = "1" ]; then
        MSG="Application Config"
          if [ -s $TMPOUT.1 ]; then
            mv $TMPOUT.1 $LOCAL_ETC_DIR/system.ini
            ERROR=$?
            chmod 644 $LOCAL_ETC_DIR/system.ini
            /usr/bin/dos2unix $LOCAL_ETC_DIR/system.ini
          else
              ERROR=1
        fi
    fi
    if [ "$RCPTBL" = "1" ]; then
        MSG="Recipe '$FILENAME'"
          if [ "$FILENAME" != "" ] && [ -s $TMPOUT.1 ]; then
            mv $TMPOUT.1 $BASE_DIR/$RECIPE_DIR/$FILENAME
            ERROR=$?
            chmod 644 $BASE_DIR/$RECIPE_DIR/$FILENAME
            /usr/bin/dos2unix $BASE_DIR/$RECIPE_DIR/$FILENAME
          else
              ERROR=1
        fi
    fi
    if [ "$LOGSTBL" = "1" ]; then
        MSG="Store '$FILENAME'"
          if [ "$FILENAME" != "" ] && [ -s $TMPOUT.1 ]; then
            mv $TMPOUT.1 $BASE_DIR/$PARTIAL_STORE_DIR/$FILENAME
            ERROR=$?
            chmod 644 $BASE_DIR/$PARTIAL_STORE_DIR/$FILENAME
            /usr/bin/dos2unix $BASE_DIR/$PARTIAL_STORE_DIR/$FILENAME
          else
              ERROR=1
        fi
    fi
    if [ "$TRENDTBL" = "1" ]; then
        MSG="Trend '$FILENAME'"
          if [ "$FILENAME" != "" ] && [ -s $TMPOUT.1 ]; then
            mv $TMPOUT.1 $BASE_DIR/$TREND_DIR/$FILENAME
            ERROR=$?
            chmod 644 $BASE_DIR/$TREND_DIR/$FILENAME
            /usr/bin/dos2unix $BASE_DIR/$TREND_DIR/$FILENAME
          else
              ERROR=1
        fi
    fi
    if [ "$RCPZIP" = "1" ]; then
        MSG="Recipe zip file"
          if [ -s $TMPOUT.1 ]; then
            mv $TMPOUT.1 $BASE_DIR/$RECIPE_DIR/.recipes.zip
            cd $BASE_DIR/$RECIPE_DIR
            /usr/bin/unzip -o $BASE_DIR/$RECIPE_DIR/.recipes.zip
            ERROR=$?
            cd -
            rm -f $BASE_DIR/$RECIPE_DIR/.recipes.zip
            chmod 644 $BASE_DIR/$RECIPE_DIR/*/*.csv
            /usr/bin/dos2unix $BASE_DIR/$RECIPE_DIR/*/*.csv
          else
              ERROR=1
        fi
    fi
    if [ "$SPLASH" = "1" ]; then
        MSG="Splash File"
          if [ -s $TMPOUT.1 ]; then
            mv $TMPOUT.1 $LOCAL_ETC_DIR/img/splash.png
            ERROR=$?
            chmod 644 $LOCAL_ETC_DIR/img/splash.png
          else
              ERROR=1
        fi
    fi
  else
  	ERROR=1
	rm -f $TMPOUT.1
    MSG="Empty file"
  fi
fi

cat <<EOF
Content-Type: text/html

<html>
<head>
<title>$TARGET_NAME Upload</title>
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<div id="container">
		<div id="header">
			<table width="100%">
				<tr align="left">
					<td>
						<h1><img src="$LOGO_NAME" style="width:240px;height:136px;float=left;vertical-align:middle;">  $TARGET_NAME Upload</h1>
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
EOF

if [ $ERROR != 0 ]
then
cat <<EOF
<table style="border:solid 2px #FF0000;" bgcolor=#fffbff cellspacing=10 cellpadding=4 align=center >
<tbody>
<tr>
<td>
Fail to upload $MSG
</td>
</tr>
EOF
else
cat <<EOF
<table style="border:solid 2px #335970;" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >
<tbody>
<tr>
<td>
    Upload $MSG successful.
EOF
cat <<EOF
</td>
</tr>
EOF
fi

    if [ "$RCPTBL" != "1" ] && [ "$RCPZIP" != "1" ] && [ "$LOGSTBL" != "1" ] && [ "$TRENDTBL" != "1" ] && [ "$SPLASH" != "1" ]; then
	if [ -x /usr/bin/splash ]
	then
		killall splash
	fi
	/etc/rc.d/init.d/autoexec start > /dev/null 2>&1
        echo "Restarting the application."
    fi

cat <<EOF
<tr>
<td>
<center>
<form>
 <input class=bottoni type="button" value="Home" onclick="window.location.href='menu.cgi'">
EOF
    if [ "$SPLASH" = "1" ]; then
	echo "<input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='config_manager.cgi'\">"
	echo "<input class=bottoni type=\"button\" value=\"Reboot\" onclick=\"window.location.href='reboot.cgi?COMMAND=REBOOT'\">"
    elif [ "$LOGSTBL" = "1" ]; then
        echo "<input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='filebrowser.cgi?ROOT_DIR=$STORE_DIR'\">"
    elif [ "$TRENDTBL" = 1 ]; then
        echo "<input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='filebrowser.cgi?ROOT_DIR=$TREND_DIR'\">"
    elif [ "$RCPTBL" = "1" ] || [ "$RCPZIP" = "1" ]; then
        echo "<input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='filebrowser.cgi?ROOT_DIR=$RECIPE_DIR'\">"
    else
     	echo "<input class=bottoni type=\"button\" value=\"Reboot\" onclick=\"window.location.href='reboot.cgi?COMMAND=REBOOT'\">"
    fi
cat <<EOF
</form>
</center>
</td>
</tr>

</tbody>
</table>
</div>                                                                                
</div>                                                                                
<div id="footer"><h2></h2></div> 
</body>
</html>
EOF

rm -f $TMPOUT $TMPOUT.1
sync

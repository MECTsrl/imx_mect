#!/bin/sh

DATA=`cat`

echo $DATA > /tmp/pippo
. ./load.cgi

ERROR=0
FILE=""
timefin=""


if [ `echo $DATA | grep download=` ]
then 
	ACTION="download"
elif [ `echo $DATA | grep delete=` ]
then
	ACTION="delete"
else
	ACTION=""
fi

if [ "$ACTION" != "" ]
then
for x in `echo $DATA | tr "&" "\n"`; do
   if [ `echo $x | grep 'foo='` ]
   then
   		FULLPATHFILE=`echo $x | cut -d= -f2 | sed s/'%2F'/'\/'/g`
		FILE=`basename $FULLPATHFILE`
	    	FILES="$FILES $FILE "
   else
   		x=`echo $x | sed s/'%2F'/'\/'/g`
   		x=`echo $x | sed s/'%3A'/':'/g`
		eval export $x
		if [ "`echo $x | cut -d= -f1`" == "timefin" ]
		then
		if [ $ACTION == "download" ]
		then
			if [ "$FILE" != "" ]
			then
				if [ ! -d $BASE_DIR/tmp ]
				then
					mkdir -p $BASE_DIR/tmp
				fi
				cd $BASE_DIR/tmp
				$WWW_DIR/extract "$BASE_DIR/$STORE_DIR" "." $FULLPATHFILE $datein $timein $datefin $timefin 2> /tmp/www.log 1> /tmp/filetozip.log
				
				if [ $? -ne 0 ]
				then
					ERROR=1
					break
				fi

				FILESTOACTION="$FILESTOACTION \n`cat /tmp/filetozip.log`"
				echo -e $FILESTOACTION > /tmp/filetozip.log
				FILESTOACTION=`cat /tmp/filetozip.log`
				rm -f /tmp/filetozip.log
				FILE=""
			fi
		else
			if [ "$FILE" != "" ]
			then
				if [ "$datein" != "" ]
				then
					if [ "$FILE" == "Total.csv" ]
					then
						FILE=""
						if [ "$datefin" != "" ]
						then
							for x in `$WWW_DIR/getdatesinterval $datein $datefin`; do
								if [ -e $BASE_DIR/$STORE_DIR/$x.log ]
								then
									FILESTOACTION="$FILESTOACTION $BASE_DIR/$STORE_DIR/$x.log"
									$SIGN $BASE_DIR/$STORE_DIR/$x.log | cut -d:\  -f1 > $BASE_DIR/$STORE_DIR/$x.log.sign
									FILESTOACTION="$FILESTOACTION $BASE_DIR/$STORE_DIR/$x.log.sign"
								fi
							done
						else
							if [ -e $BASE_DIR/$STORE_DIR/`echo $datein | sed s/'\/'/'_'/g`.log ]
							then
								FILESTOACTION="$FILESTOACTION $BASE_DIR/$STORE_DIR/`echo $datein | sed s/'\/'/'_'/g`.log"
								$SIGN $BASE_DIR/$STORE_DIR/`echo $datein | sed s/'\/'/'_'/g`.log | cut -d:\  -f1 > $BASE_DIR/$STORE_DIR/`echo $datein | sed s/'\/'/'_'/g`.log.sign
								FILESTOACTION="$FILESTOACTION $BASE_DIR/$STORE_DIR/`echo $datein | sed s/'\/'/'_'/g`.log.sign"
							fi
						fi
					else
						ERROR=1
						echo "cannot delete a partial log using a time filter" > /tmp/www.log
						FILESTOACTION=""
						FILE=""
						break
					fi
				else	
					
					if [ "$FILE" == "Total.csv" ]
					then
						FILESTOACTION="$FILESTOACTION $BASE_DIR/$STORE_DIR/*.log"
						FILESTOACTION="$FILESTOACTION $BASE_DIR/$STORE_DIR/*.log.sign"					
					else
						if [ -e $BASE_DIR/$PARTIAL_STORE_DIR/$FILE ]
						then
							FILESTOACTION="$FILESTOACTION $BASE_DIR/$PARTIAL_STORE_DIR/$FILE"
						fi
					fi
					FILE=""
				fi
			fi
		fi
		fi
   fi
done
else
	# no action
	ERROR=1
fi

if [ "$FILESTOACTION" == "" ]
then
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
						<h1><img src="$LOGO_NAME" style="width:240px;height:136px;float=left;vertical-align:middle;">  $TARGET_NAME Logs Management</h1>
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
<tbody>
<tr>
<td>
    Nothing to $ACTION
EOF
	if [ -e /tmp/www.log ]
	then
		echo " ["
		cat /tmp/www.log
		rm -f /tmp/www.log
		echo "] "
	fi
	if [$FILESTOACTION != "" ]
	then
		echo " -$FILESTOACTION-"
	fi
cat <<EOF
</td>
</tr>
</tbody>
</table>
</div>                                                                                
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
echo "      <input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='logs_filter.cgi'\">"
cat <<EOF
</center>
</div>                                                                                
</body>
</html>
EOF
exit 0
fi

old_dir=`pwd`

# elimina
if [ "$ERROR" == "0" ]
then
	if [ "$ACTION" == "delete" ]
	then
		rm -rf $FILESTOACTION
	else
	   # zip log file
	   zipfilename=`date '+%Y_%m_%d'`_`date '+%H%M%S'`.zip
	   
	   cd $BASE_DIR/tmp
	   /usr/bin/zip -q -r $zipfilename $FILESTOACTION
   	fi
   	ERROR=$?
   # clean the sign file
	for x in $FILESTOACTION; do
		if [ echo $x | grep .sign$ ]
		then
			rm -f $x
		fi
	done
fi

cat <<EOF
EOF

if [ "$ERROR" == "0" ]
then
if [ "$ACTION" == "delete" ]
then
. ./logs_filter.cgi
else
cat <<EOF
Content-type: multipart/x-zip
Content-disposition: attachment; filename="$zipfilename"

EOF
cat $zipfilename
rm -f $zipfilename
rm -rf $BASE_DIR/tmp
fi
else
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
						<h1><img src="$LOGO_NAME" style="width:240px;height:136px;float=left;vertical-align:middle;">  $TARGET_NAME Logs Management</h1>
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

<table style="border:solid 2px #FF0000;" bgcolor=#fffbff cellspacing=10 cellpadding=4 align=center >
<tbody>
<tr>
<td>
    Fail to $ACTION
EOF
	if [ -e /tmp/www.log ]
	then
		echo " ["
		cat /tmp/www.log
		rm -f /tmp/www.log
		echo "] "
	fi
	if [$FILESTOACTION != "" ]
	then
		echo " -$FILESTOACTION-"
	fi
cat <<EOF
</td>
</tr>
</tbody>
</table>
</div>
EOF
echo "      <input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='$HOME_PAGE'\">"
echo "      <input class=bottoni type=\"button\" value=\"Back\" onclick=\"window.location.href='logs_filter.cgi'\">"
cat <<EOF
</center>
</div>                                                                                
</body>
</html>

EOF
fi

cd $old_dir
rm -f $OUT_FILE_NAME

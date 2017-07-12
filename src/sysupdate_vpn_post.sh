# Fix password file permissions.
if test -f "$LUP"; then
    chown root:root "$LUP"
    chmod 0600 "$LUP"
fi

# Add/replace the new OpenVPN certificate.
if test -r "${MNTDIR}/${SN}.ovpn" -a "$(sed -n '/^\s*Subject: .*CN=/ { s/^.*CN=//; s/\/.*//; s/-mect$//; p; }' ${MNTDIR}/${SN}.ovpn)" = "$SN"; then
    if ! test -d "$OVPNCONF"; then
	rm -f "$OVPNCONF"
	mkdir -p "$OVPNCONF"
    fi

    if test -d "$OVPNCONF"; then
	# Disable any existing certificates.
	find "$OVPNCONF" -type f \( -iname \*.ovpn -o -iname \*.conf \) -exec mv {} {}.$(date '+%F-%T') \;

	install -m 644 "${MNTDIR}/${SN}.ovpn" "${OVPNCONF}/${SN}.ovpn"
	test -s "${OVPNCONF}/${SN}.ovpn" || echo -e "${ERRMSG} cannot install the OpenVPN certificate.\r" | tee /dev/tty1
    else
	echo -e "${ERRMSG} no OpenVPN configuration directory.\r" | tee /dev/tty1
    fi
else
    echo -e "${ERRMSG} no OpenVPN certificate for this device.\r" | tee /dev/tty1
fi

# Make sure that the cron tab is set for periodic log upload.
test -s "$CRONTAB" || touch "$CRONTAB"

# Uncomment the sync schedule, if present.
sed -i "/ $(echo $LUS | sed 's|/|\\/|g')"'\s*$/ { s/^[ 	#]*//; s/\s*$//; }' "$CRONTAB"

# Still no schedule?  Add it!
if ! grep -q " $LUS\\s*\$" "$CRONTAB"; then
    sed -n "/ $(echo $LUS | sed 's|/|\\/|g')"'\s*$/ { s/^[ 	#]*//; s/\s*$//; p; }' "${CRONTAB}.default" >> "$CRONTAB"

    # Still no schedule by now?  That's an error.
    grep -q "$LUS\\s*\$" "$CRONTAB" || echo -e "${ERRMSG} cron tab setup failed.\r" | tee /dev/tty1
fi

# Activate configuration changes.
"$OVPNRC" stop; sleep 1; "$OVPNRC" start
"$CRONRC" stop; sleep 1; "$CRONRC" start

# Exit
( echo -e "\r"; echo -e "Device update for MECT Remote Services succeeded.\r" ) | tee /dev/tty1
do_exit

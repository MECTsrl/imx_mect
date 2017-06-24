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
	test -s "${OVPNCONF}/${SN}.ovpn" || echo "${ERRMSG} cannot install the OpenVPN certificate." | tee /dev/tty1
    else
	echo "${ERRMSG} no OpenVPN configuration directory." | tee /dev/tty1
    fi
else
    echo "${ERRMSG} no OpenVPN certificate for this device." | tee /dev/tty1
fi

# Make sure that the cron tab is set for periodic log upload.
test -s "$CRONTAB" || touch "$CRONTAB"

# Uncomment the sync schedule, if present.
sed -i "/ $(echo $LUS | sed 's|/|\\/|g')"'\s*$/ { s/^[ 	#]*//; s/\s*$//; }' "$CRONTAB"

# Still no schedule?  Add it!
if ! grep -q " $LUS\\s*\$" "$CRONTAB"; then
    sed -n "/ $(echo $LUS | sed 's|/|\\/|g')"'\s*$/ { s/^[ 	#]*//; s/\s*$//; p; }' "${CRONTAB}.default" >> "$CRONTAB"

    # Still no schedule by now?  That's an error.
    grep -q "$LUS\\s*\$" "$CRONTAB" || echo "${ERRMSG} cron tab setup failed." | tee /dev/tty1
fi

# Restore the root file system access mode.
test "$RFSRW" -ne 0 && mount -oro,remount /

# Activate configuration changes.
"$OVPNRC" stop; sleep 1; "$OVPNRC" start
"$CRONRC" stop; sleep 1; "$CRONRC" start

# Exit
( echo ""; echo "Device update for MECT Remote Services succeeded." ) | tee /dev/tty1
do_exit

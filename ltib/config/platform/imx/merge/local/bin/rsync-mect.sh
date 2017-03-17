#!/bin/sh

IP="$(/sbin/ip addr show dev tun0 2>/dev/null | /usr/bin/awk '/ inet / { print $2; }')"
test -n "$IP" || exit 1

PIDFILE=/var/run/rsync-$IP.pid

test -s $PIDFILE && test -d /proc/$(cat $PIDFILE) && exit 2

/usr/bin/rsync -a --timeout=45 --password-file=/local/etc/rsync-mect.pwd /local/data/store/ mect@10.8.0.1::csv_tpac/$IP/ > /dev/null 2>&1 &

echo -n $! > $PIDFILE

#!/bin/sh

wlan="wlan0"

ctrl_dir=/local/var/run/wpa_supplicant
conf_dir=/local/etc/wpa_supplicant
conf_file="$conf_dir/default.conf"
resolv_file=/etc/resolv.conf

NETCONFIG=/local/etc/sysconfig/net.conf

INIT_NETWORK=/etc/rc.d/init.d/network


clear_defroutes_resolv()
{
    for r in "" `/sbin/route -n | awk '/^0\.0\.0\.0/ { print $2; }'`; do
        test -z "$r" && continue

        /sbin/route delete default gw "$r"
    done

    echo "" > $resolv_file
}

stop_dhclient()
{
    pid=`ps | awk '/\<dhclient .* '$wlan'\>/ { if (($5 == "dhclient") && ($7 == "'$wlan'")) print $1; }'`
    test -n "$pid" && kill $pid
}

ip_setup()
{
    test -r "$NETCONFIG" || return 1
    source "$NETCONFIG"

    test "$BOOTPROTOW0" = "[DHCP]" && IPADDRW0="dhcp"

    test -n "$IPADDRW0" || return 1

    clear_defroutes_resolv

    if test "$IPADDRW0" = "dhcp"; then
        stop_dhclient
        sleep 1
        dhclient -nw $wlan
    else
        if test -n "$NETMASKW0"; then
            /sbin/ifconfig $wlan $IPADDRW0 netmask $NETMASKW0
        else
            /sbin/ifconfig $wlan $IPADDRW0
        fi

        if test -n "$GATEWAYW0"; then
            /sbin/route add default gateway $GATEWAYW0 $wlan
        fi

        if test -n "$NAMESERVERW01"; then
            grep "nameserver\s\+$NAMESERVERW01" $resolv_file || echo "nameserver $NAMESERVERW01" >> $resolv_file
        fi

        if test -n "$NAMESERVERW02"; then
            grep "nameserver\s\+$NAMESERVERW02" $resolv_file || echo "nameserver $NAMESERVERW02" >> $resolv_file
        fi
    fi
}

setup()
{
    test $# -ne 2 && return 1

    mkdir -p "$conf_dir"

cat > "$conf_file" <<EOF
# File automatically created by $0.  Do not edit.

ctrl_interface=$ctrl_dir

update_config=0

ap_scan=1

network={
    ssid="$1"
    psk="$2"
}
EOF

    ifconfig -a | grep -q "\b${wlan}\b" || return 0

    mkdir -p "$ctrl_dir"
    if wpa_cli -p $ctrl_dir status > /dev/null 2>&1; then
        iwconfig "$wlan" essid ""

        ip_setup
    fi

    return 0
}

start()
{
    test -r "$conf_file" || return 1

    test -r "$NETCONFIG" || return 1
    source "$NETCONFIG"

    test "$ONBOOTW0" = "1" || return 0

    ifconfig -a | grep -q "\b${wlan}\b" || return 1

    mkdir -p "$ctrl_dir"
    if wpa_cli -p $ctrl_dir status > /dev/null 2>&1; then
	iwconfig "$wlan" essid ""       # Force reassociation.
    else
	wpa_supplicant -B -i "$wlan" -c "$conf_file" || return 1
    fi

    ip_setup

    return 0
}

stop()
{
    ifconfig -a | grep -q "\b${wlan}\b" || return 0

    test -d "$ctrl_dir" || return 1

    wpa_cli -p $ctrl_dir terminate 2>/dev/null \
        || killall wpa_supplicant 2>/dev/null

    ifconfig "$wlan" down 2>/dev/null

    stop_dhclient
    sleep 1

    if test -r "$NETCONFIG"; then
	source "$NETCONFIG"

	if test -n "$GATEWAY0"; then
	    clear_defroutes_resolv

	    test -x $INIT_NETWORK && $INIT_NETWORK restart
	fi
    fi

    return 0
}

scan()
{
    # Silence any unrelated message on stdout.

    ifconfig -a | grep -q "\b${wlan}\b" || return 1

    tf=/tmp/`basename $0`-$$.tmp || return 1

    wpa_cli -p $ctrl_dir status > /dev/null 2>&1
    status=$?

    if test "$status" -ne 0; then
        ifconfig $wlan up > /dev/null || return 1
    fi

    iwlist "$wlan" scanning > "$tf" || return 1

    if test "$status" -ne 0; then
        ifconfig $wlan down > /dev/null
    fi

    # stdout: <ESSID>\t<level>\t<quality>
    sed -n '
        /^\s*ESSID:/ { s/^\s*//; s/:/=/; s/"//g; p; }
        /^\s*Quality=/ { s/^\s*//; s/\s\+/\n/; s/Signal\s*//; s/\s\+dBm.*//; p; }
    ' "$tf" \
    | awk -F= '
        /^ESSID/ {
            essid = $2;

            print essid "\t" level "\t" quality;

            essid = "";
            level = "";
            quality = "";
        }

        /^Quality/ {
            quality = $2;
        }

        /^level/ {
            level = $2;
        }
    '

    rm -f "$tf"

    return 0
}


action="$1"
shift

case "$action" in
    "setup")
        setup "$@"
    ;;

    "start")
        start
    ;;

    "stop")
        stop
    ;;

    "scan")
        scan
    ;;

    *)
        echo "Usage: $(basename $0) <setup|start|stop|scan>" >&2

        exit 1
    ;;
esac

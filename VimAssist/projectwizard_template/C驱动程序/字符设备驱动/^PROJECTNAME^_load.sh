#!/bin/sh

module="^PROJECTNAME^"
device="^PROJECTNAME^"
mode="664"

/sbin/insmod ./${module}_out.ko $* || exit 1

# remove stale nodes
rm -f /dev/${device}[0-3]

major=`cat /proc/devices | awk "\\$2==\"$module\" {print \\$1}"`

mknod /dev/${device}0 c $major 0
mknod /dev/${device}1 c $major 1
mknod /dev/${device}2 c $major 2
mknod /dev/${device}3 c $major 3

#group="staff"
#grep -q '^staff:' /etc/group || group="wheel"

#chgrp $group /dev/${device}[0-3]
#chmod $mode /dev/${device}[0-3]

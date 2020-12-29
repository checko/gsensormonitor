#!/bin/bash
export PATH=\
/bin:\
/sbin:\
/usr/bin:\
/usr/sbin:\
/usr/bin/X11:\
/usr/local/bin:\
/usr/local/sbin

cp /sdcard/gmonitor /usr/local/bin/
cp /sdcard/startgmonitor.sh /usr/local/bin/
echo "startgmonitor.sh" >> /etc/rc.local

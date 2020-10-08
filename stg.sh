#!/bin/bash
echo 1 > /sys/class/input/input0/accel/enable
echo 100 > /sys/class/input/input0/accel/polling_rate
date > /data/ggg
/data/gmonitor >> /data/ggg


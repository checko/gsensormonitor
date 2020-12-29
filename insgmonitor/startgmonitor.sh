#!/bin/bash
echo 50 > /sys/class/input/input0/accel/polling_rate
echo 1 > /sys/class/input/input0/accel/enable
gmonitor &

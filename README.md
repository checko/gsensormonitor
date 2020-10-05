read g-sensor data from input interface, then print out.
-- must enable g-sensor first.

echo 1 > /sys/class/input/input0/accel/enable

and the polling period is polling_rate (ms).

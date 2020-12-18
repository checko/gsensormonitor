all:
	/usr/local/linaro-aarch64-2018.08-gcc8.2/bin/aarch64-linux-gnu-gcc gmonitor.c gpsspeed.c -o gmonitor

greadcheck:
	/usr/local/linaro-aarch64-2018.08-gcc8.2/bin/aarch64-linux-gnu-gcc greadcheck.c -o greadcheck


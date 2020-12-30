all: gmonitor greadcheck

gmonitor:
	/usr/local/linaro-aarch64-2018.08-gcc8.2/bin/aarch64-linux-gnu-gcc -g gmonitor.c gpsspeed.c sfio.c -o gmonitor
	cp gmonitor insgmonitor/

greadcheck:
	/usr/local/linaro-aarch64-2018.08-gcc8.2/bin/aarch64-linux-gnu-gcc greadcheck.c -o greadcheck


clean:
	rm gmonitor greadcheck


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>


static const char * const evval[]={
	"RELEASED",
	"PRESSED",
	"REPEATED"
};

#define INPUT_EVENT_TYPE    EV_MSC
#define INPUT_EVENT_X       MSC_SERIAL
#define INPUT_EVENT_Y       MSC_PULSELED
#define INPUT_EVENT_Z       MSC_GESTURE
#define INPUT_EVENT_TIME_MSB    MSC_SCAN
#define INPUT_EVENT_TIME_LSB    MSC_MAX


int main(void)
{
	const char *dev="/dev/input/event0";
	struct input_event ev;
	ssize_t n;
	int fd;
	long stime;

	fd = open(dev, O_RDONLY);
	if (fd==-1) {
		fprintf(stderr,"Cannot open %s: %s\n",dev,strerror(errno));
		return EXIT_FAILURE;
	}

	while(1) {
		n = read(fd, &ev, sizeof(ev));
		if (n == (ssize_t)-1) {
			if (errno==EINTR)
				continue;
			else
				break;
		}else
		if (n != sizeof(ev)) {
			errno = EIO;
			break;
		}

		if(ev.type == INPUT_EVENT_TYPE) {
			switch(ev.code) {
				case INPUT_EVENT_X:
					printf("X: %d\n",ev.value);
					break;
				case INPUT_EVENT_Y:
					printf("Y: %d\n",ev.value);
					break;
				case INPUT_EVENT_Z:
					printf("Z: %d\n",ev.value);
					break;
				case INPUT_EVENT_TIME_MSB:
					stime |= (long)ev.value << 32;
					break;
				case INPUT_EVENT_TIME_LSB:
					stime |= (long)ev.value & 0x00000000FFFFFFFF;
					break;
				default:
					printf("NOT VALID code: %d\n",ev.code);
			}
		}else if (ev.type == EV_SYN) {
			printf("%ld\n",stime);
			stime=0;
		}else{
			printf("NOT VALID TYPE: %d\n",ev.type);
		}

	}
	fflush(stdout);
	fprintf(stderr,"%s.\n",strerror(errno));
	return EXIT_FAILURE;
}

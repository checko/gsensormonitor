#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <signal.h>

static volatile int KeepRunning = 1;
void intHandler(int dummy)
{
	KeepRunning = 0;
}


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
	long stime=0;
	long ptime=0;

	int x,y,z,acc;
	double sx,sy,sz;
	z=y=z=sx=sy=sz=acc=0;

	fd = open(dev, O_RDONLY);
	if (fd==-1) {
		fprintf(stderr,"Cannot open %s: %s\n",dev,strerror(errno));
		return EXIT_FAILURE;
	}

	signal(SIGINT, intHandler);

	while(KeepRunning) {
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
					x = ev.value;
					break;
				case INPUT_EVENT_Y:
					y = ev.value;
					break;
				case INPUT_EVENT_Z:
					z = ev.value;
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
			stime = stime/1000000000;
			if(ptime != stime){
				sx = sx/acc/100000.;
				sy = sy/acc/100000.;
				sz = sz/acc/100000.;
				printf("%5.2f %5.2f %5.2f %ld\n",sx,sy,sz,stime);
				ptime = stime;
				x=y=z=sx=sy=sz=acc=0;
			}else{
				sx += x;
				sy += y;
				sz += z;
				acc++;
			}
			stime = 0;
		}else{
			printf("NOT VALID TYPE: %d\n",ev.type);
		}

	}

	printf("Exit!!\n");
	return 0;
}

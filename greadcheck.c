#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <signal.h>
#include <sys/select.h>


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

void writeOK(void)
{
	FILE *fd = fopen("/tmp/gsensorok","w");
	if (fd != NULL)
		fclose(fd);
}


int main(void)
{
	const char *dev="/dev/input/event0";
	struct input_event ev;
	ssize_t n;
	int fd;
	long stime=0;
	long ptime=0;
	int rv;

	fd_set set;
	struct timeval timeout;

	int x,y,z,acc;
	double sx,sy,sz;
	z=y=z=sx=sy=sz=acc=0;

	fd = open(dev, O_RDONLY);
	if (fd==-1) {
		printf("Cannot open %s: %s\n",dev,strerror(errno));
		return EXIT_FAILURE;
	}

	FD_ZERO(&set);
	FD_SET(fd, &set);
	timeout.tv_sec = 2;
	timeout.tv_usec = 0;

	rv = select(fd + 1, &set, NULL, NULL, &timeout);
	if(rv == -1){
		printf("cannot select\n");
		return EXIT_FAILURE;
	}else if(rv==0){
		printf("TimeOut!\n");
	}else{
		n = read(fd, &ev, sizeof(ev));
		if (n != sizeof(ev)) {
			printf("read error\n");
			return EXIT_FAILURE;
		}

		printf("OK!\n");
		writeOK();

	}

	fflush(stdout);
	return 0;
}

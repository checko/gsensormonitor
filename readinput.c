#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int timeout_ms = 5000;
	char input_dev[]="/dev/input/event0\0";
	int st;
	int ret;
	struct pollfd fds[1];

	fds[0].fd = open(input_dev, O_RDONLY | O_NONBLOCK);

	if(fds[0].fd < 0)
	{
		printf("error: unable open for reading %s\n",input_dev);
		return(0);
	}

	const int input_size=4096;
	unsigned char input_data[input_size];
	memset(input_data,0,input_size);

	fds[0].events = POLLIN;

	while(1)
	{
		ret = poll(fds, 1, timeout_ms);

		if(ret>0)
		{
			if(fds[0].revents)
			{
				ssize_t r = read(fds[0].fd, input_data, input_size);

				if(r <0)
				{
					printf("error %d\n",(int)r);
					break;
				}else
				{
					printf("total bytes read %d/%d\n",(int)r,input_size);

					for(int i=0; i<r; i++)
					{
						printf("%02X ",(unsigned char)input_data[i]);

					}
					printf("\n");
					memset(input_data,0,input_size);

				}
			}else
			{
				printf("error\n");
			}
		}else
		{
			printf("timeout\n");
		}
	}
	close(fds[0].fd);

	return 0;
}

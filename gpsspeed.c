#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFERSIZE 500
static char buffer[BUFFERSIZE];
static FILE *pFile;

char* getspeed(void)
{
	long lSize;
	size_t readlen;
	char *speed;
	char *end;

	rewind(pFile);
	readlen = fread(buffer, 1, BUFFERSIZE, pFile);
	buffer[readlen]=0x00;
		
	speed = strstr(buffer,"Speed:")+6;
	end = strchr(speed,' ');
	*end = 0x00;

	return speed;
}

void waitfileready(void)
{
	do
	{
		sleep(5);
		pFile = fopen("/tmp/gpsfix","rb");
	}while(pFile==NULL);
	fclose(pFile);

	while(1) {
		pFile = fopen("/tmp/gpsdata.txt","rb");
		if (pFile!=NULL) {
			return;
		}
		sleep(1);
	}

}

void closefile(void)
{
	fclose(pFile);
}


#if 0
int main()
{

	waitfileready();
	printf("gps ready\n");

	while(1) {
		printf("%s\n",getspeed());
		sleep(1);
	}

	closefile();
	return 0;

}
#endif

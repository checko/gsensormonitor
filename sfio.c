#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

char fname[100];

FILE *fp;

void sfopen(char *name)
{
	time_t t = time(NULL);
	struct tm ctime = *localtime(&t);
	int len = sprintf(fname,"%s%04d%02d%02d%02d%02d",name,ctime.tm_year+1900,ctime.tm_mon+1,ctime.tm_mday,ctime.tm_hour, ctime.tm_min);
	fname[len]=0x00;
	
	fp = fopen(fname,"w");
}

void sfclose(void)
{
	fclose(fp);
}

void sfprintf(char *format, ...)
{
	va_list argList;
	va_start(argList, format);
	vfprintf(fp,format,argList);
	va_end(argList);
	fflush(fp);
}

/*
int main(void)
{
	sfopen("gs");
	int i;
	for(i=0;i<10;i++)
		sfprintf("%d ",i);
	sfprintf("\n");
	sfclose();
	

	return 0;
}
*/

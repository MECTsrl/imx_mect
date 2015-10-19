#include <stdio.h>
#define __USE_XOPEN
#define _GNU_SOURCE
#include <time.h>
#include <string.h>

#define MAX_FIELDS_NB 128
#define LINE_SIZE 1024

int main (int argc, char * argv[])
{
	char * datein, * datefin;
	struct tm mytime;
	time_t datetimein, datetimefin;
	char tmp[32];

	if (argc != 3)
	{
		fprintf(stderr, "%d vs 3\n", argc);
		fprintf(stderr, "Usage: %s <datein> <datefin>\n", argv[0]);
		return 1;
	}

	datein     = argv[1];
	datefin    = argv[2];

	sprintf(tmp, "%s 00:00:00", datefin);
	if(strptime(tmp, "%Y/%m/%d %H:%M:%S", &mytime) == NULL)
	{
		fprintf(stderr, "invalid time '%s'\n", datefin);
		return 1;
	}
	datetimefin = mktime(&mytime);

	sprintf(tmp, "%s 00:00:00", datein);
	if(strptime(tmp, "%Y/%m/%d %H:%M:%S", &mytime) == NULL)
	{
		fprintf(stderr, "invalid time '%s'\n", datein);
		return 1;
	}
	datetimein = mktime(&mytime);

	while (difftime(datetimefin, datetimein) > 0)
	{
		datetimein = mktime(&mytime);
		strftime(tmp, sizeof(tmp), "%Y_%m_%d", &mytime);
		fprintf(stdout,"%s\n", tmp);
		mytime.tm_mday++;
	}

	return 0;
}


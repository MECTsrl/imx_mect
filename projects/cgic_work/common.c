
#include <stdio.h>
#include "cgic.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "common.h"

static int Update(char *file_id, char *file_name, char *action);
static int File(char *file_id, char *file_name);
static int isEmpty(char * filename);

int HandleSubmitSYSUPD()
{
	return Update("SYSUPD", "/local/root/sysupdate.sh",
		"chmod +x /local/root/sysupdate.sh"
		" && /local/root/sysupdate.sh"
		" && rm -f /local/root/sysupdate.sh");
}

int HandleSubmitHMI(void)
{
	return Update("HMI", "/local/root/hmi",
		"sync"
		" && chmod 754 /local/root/hmi");
}

int HandleSubmitCROSSTBL(void)
{
	return Update("CROSSTBL", "/local/etc/sysconfig/Crosstable.csv",
		"sync"
		" && /bin/chmod 644 /local/etc/sysconfig/Crosstable.csv" 
		" && /usr/bin/dos2unix /local/etc/sysconfig/Crosstable.csv");
}

int HandleSubmitSYSINI(void)
{
	return Update("SYSINI", "/local/etc/sysconfig/system.ini",
		"sync"
		" && /bin/chmod 644 /local/etc/sysconfig/system.ini"
		" && /usr/bin/dos2unix /local/etc/sysconfig/system.ini");
}

int HandleSubmitSPLASH(void)
{
	return Update("SPLASH", "/local/etc/sysconfig/img/splash.png",
		"sync"
		" && /bin/chmod 644 /local/etc/sysconfig/img/splash.png");
}

int HandleSubmitFCRTS(void)
{
	return Update("FCRTS", "/local/root/fcrts",
		"sync"
		" && chmod 754 /local/root/fcrts");
}

int HandleSubmitPLC(void)
{
	return Update("PLC", "/local/root/control.tar.gz",
		"tar -C /local/control/ xzf /local/root/control.tar.gz"
		" && rm /local/root/control.tar.gz");
}

static int Update(char *file_id, char *file_name, char *action)
{
	int rv = 0;
	char tmpfile[FILENAME_MAX];
	char cmdline[FILENAME_MAX];

	snprintf(tmpfile, FILENAME_MAX, "%s.tmp", file_name);
	if (File(file_id, tmpfile))
	{
		snprintf(cmdline, FILENAME_MAX, "rm -f %s", tmpfile);
		rv = system(cmdline);
		return 1;
	}
	if (isEmpty(tmpfile))
	{
		snprintf(cmdline, FILENAME_MAX, "rm -f %s", tmpfile);
		rv = system(cmdline);
		return 1;
	}
	snprintf(cmdline, FILENAME_MAX, "mv %s %s", tmpfile, file_name);
	rv = system(cmdline);
	rv = system(action);
	return rv;
}

static int File(char *file_id, char * file_name)
{
	cgiFilePtr file;
	char buffer[65536];
	int got;
	FILE *fp;

	if (file_name == NULL || file_id == NULL)
	{
		return 1;
	}
	if (cgiFormFileOpen(file_id, &file) != cgiFormSuccess)
	{
		fprintf(cgiOut, "<p>Could not open the file id='%s'.<p>\n", file_id);
		return 1;
	}
	fp = fopen(file_name, "w+");	
	if (fp == NULL)
	{
		return 1;
	}
	while (cgiFormFileRead(file, buffer, sizeof(buffer), &got) == cgiFormSuccess)
	{
		if (cgiHtmlEscapeDataOnFile(buffer, got, fp) != cgiFormSuccess){
			fprintf(cgiOut, "<p>cgiFormIO file error id='%s'.<p>\n", file_id);
			fclose(fp);
			return 1;
		}
	}
	if (cgiFormFileClose(file) != cgiFormSuccess)
	{
		fprintf(cgiOut, "<p>cgiFormCloseFailed error id='%s'.<p>\n", file_id);
		fclose(fp);
		return 1;
	}	
	fclose(fp);
	sync();
	return 0;
}

static int isEmpty(char * filename)
{
	FILE *file = fopen(filename, "r");

	if (file == NULL)
	{
		/* the file not exist */
		return 1;
	}
	fseek(file, 0, SEEK_END);
	if (ftell(file) == 0)
	{
		fclose(file);
		/* the file is empty */
		return 1;
	}
	fclose(file);
	/* the file is not empty */
	return 0;
}

#define SERVER_NAME "www.tpac010.net"

#include <stdio.h>
#include "cgic.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "common.h"

static void ShowForm(void);

static void ShowForm()
{
	fprintf(cgiOut, "<html>\n");
	
	fprintf(cgiOut, "<head>\n");
	fprintf(cgiOut, "<title>REMOTE UPDATER</title>\n");
	fprintf(cgiOut, "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\n");
	fprintf(cgiOut, "<style>\n");
	fprintf(cgiOut, ".nowrap {\n");
	fprintf(cgiOut, "  white-space: nowrap ;\n");
	fprintf(cgiOut, "}\n");
	fprintf(cgiOut, "</style>\n");
	fprintf(cgiOut, "</head>\n");
	
	fprintf(cgiOut, "<body>\n");

	fprintf(cgiOut, "<div id=\"container\">\n");
	fprintf(cgiOut, "<div id=\"header\">\n");
	fprintf(cgiOut, "<h1>UPDATE ALL</h1>\n");
	fprintf(cgiOut, "</div>\n");
	fprintf(cgiOut, "<div id=\"content\">\n");
	fprintf(cgiOut, "<div id=\"form\">\n"); 

	fprintf(cgiOut, "<form name=\"allform\" method=\"POST\" enctype=\"multipart/form-data\" ");
	fprintf(cgiOut, "	action=\"updateall.cgi\">\n");
	fprintf(cgiOut, "<table style=\"border:solid 2px #335970;\" bgcolor=#f1fbff cellspacing=1 cellpadding=4 align=center >\n");
	fprintf(cgiOut, "<tbody>\n");
	fprintf(cgiOut, "<tr>\n");
	fprintf(cgiOut, "<td>\n");	

	fprintf(cgiOut, "<table cellspacing=1 cellpadding=4 align=right>");
	fprintf(cgiOut, "<tbody>\n");
	fprintf(cgiOut, "<tr>\n");
	fprintf(cgiOut, "<td>\n");	
	fprintf(cgiOut, "<span class=\"nowrap\">Choose Alarms.csv file:</span>\n");
	fprintf(cgiOut, "</td>\n"); 	 
	fprintf(cgiOut, "<td>\n");
	fprintf(cgiOut, "<input type=\"file\" name=\"ALARMTBL\">\n");
	fprintf(cgiOut, "</td>\n");
	fprintf(cgiOut, "<td>\n");	
	fprintf(cgiOut, "</td>\n");
	fprintf(cgiOut, "</tr>\n");
	fprintf(cgiOut, "</tbody>\n");
	fprintf(cgiOut, "</table>\n");

	fprintf(cgiOut, "</tr>\n");
	fprintf(cgiOut, "</td>\n");	
	fprintf(cgiOut, "<tr>\n");
	fprintf(cgiOut, "<td>\n");	

	fprintf(cgiOut, "<table cellspacing=1 cellpadding=4 align=right>");
	fprintf(cgiOut, "<tbody>\n");
	fprintf(cgiOut, "<tr>\n");
	fprintf(cgiOut, "<td>\n");	
	fprintf(cgiOut, "<span class=\"nowrap\">Choose Crosstable.csv:</span>\n");
	fprintf(cgiOut, "</td>\n"); 	 
	fprintf(cgiOut, "<td>\n");
	fprintf(cgiOut, "<input type=\"file\" name=\"CROSSTBL\">\n");
	fprintf(cgiOut, "</td>\n");
	fprintf(cgiOut, "<td>\n");	
	fprintf(cgiOut, "</td>\n");
	fprintf(cgiOut, "</tr>\n");
	fprintf(cgiOut, "</tbody>\n");
	fprintf(cgiOut, "</table>\n");

	fprintf(cgiOut, "</td>\n");	
	fprintf(cgiOut, "</tr>\n");
	fprintf(cgiOut, "<tr>\n");
	fprintf(cgiOut, "<td>\n");	

	fprintf(cgiOut, "<table cellspacing=1 cellpadding=4 align=right>");
	fprintf(cgiOut, "<tbody>\n");
	fprintf(cgiOut, "<tr>\n");
	fprintf(cgiOut, "<td>\n");	
	fprintf(cgiOut, "<span class=\"nowrap\">Choose Commpar.csv file:</span>\n");
	fprintf(cgiOut, "</td>\n"); 	 
	fprintf(cgiOut, "<td>\n");
	fprintf(cgiOut, "<input type=\"file\" name=\"CFGTBL\">\n");
	fprintf(cgiOut, "</td>\n");
	fprintf(cgiOut, "<td>\n");	
	fprintf(cgiOut, "</td>\n");
	fprintf(cgiOut, "</tr>\n");
	fprintf(cgiOut, "</tbody>\n");
	fprintf(cgiOut, "</table>\n");

	fprintf(cgiOut, "</td>\n");	
	fprintf(cgiOut, "</tr>\n");
	fprintf(cgiOut, "<tr>\n");
	fprintf(cgiOut, "<td>\n");	

	fprintf(cgiOut, "<table cellspacing=1 cellpadding=4 align=right>");
	fprintf(cgiOut, "<tbody>\n");
	fprintf(cgiOut, "<tr>\n");
	fprintf(cgiOut, "<td>\n");	
	fprintf(cgiOut, "<span class=\"nowrap\">Choose config file:</span>\n");
	fprintf(cgiOut, "</td>\n"); 	 
	fprintf(cgiOut, "<td>\n");
	fprintf(cgiOut, "<input type=\"file\" name=\"ATNCFG\">\n");
	fprintf(cgiOut, "</td>\n");
	fprintf(cgiOut, "<td>\n");	
	fprintf(cgiOut, "</td>\n");
	fprintf(cgiOut, "</tr>\n");
	fprintf(cgiOut, "</tbody>\n");
	fprintf(cgiOut, "</table>\n");

	fprintf(cgiOut, "</td>\n");	
	fprintf(cgiOut, "</tr>\n");
	fprintf(cgiOut, "<tr>\n");
	fprintf(cgiOut, "<td>\n");	
	
	fprintf(cgiOut, "<table cellspacing=1 cellpadding=4 align=right>");
	fprintf(cgiOut, "<tbody>\n");
	fprintf(cgiOut, "<tr>\n");
	fprintf(cgiOut, "<td>\n");	
	fprintf(cgiOut, "<span class=\"nowrap\">Choose splash file:</span>\n");
	fprintf(cgiOut, "</td>\n"); 	 
	fprintf(cgiOut, "<td>\n");
	fprintf(cgiOut, "<input type=\"file\" name=\"SPLASH\">\n");
	fprintf(cgiOut, "</td>\n");
	fprintf(cgiOut, "<td>\n");	
	fprintf(cgiOut, "</td>\n");
	fprintf(cgiOut, "</tr>\n");
	fprintf(cgiOut, "</tbody>\n");
	fprintf(cgiOut, "</table>\n");

	fprintf(cgiOut, "</td>\n");	
	fprintf(cgiOut, "</tr>\n");
	fprintf(cgiOut, "<tr>\n");
	fprintf(cgiOut, "<td>\n");	
	
	fprintf(cgiOut, "<table cellspacing=1 cellpadding=4 align=right>");
	fprintf(cgiOut, "<tbody>\n");
	fprintf(cgiOut, "<tr>\n");
	fprintf(cgiOut, "<td>\n");	
	fprintf(cgiOut, "<span class=\"nowrap\">Choose hmi file:</span>\n");
	fprintf(cgiOut, "</td>\n"); 	 
	fprintf(cgiOut, "<td>\n");
	fprintf(cgiOut, "<input type=\"file\" name=\"HMI\">\n");
	fprintf(cgiOut, "</td>\n");
	fprintf(cgiOut, "<td>\n");	
	fprintf(cgiOut, "</td>\n");
	fprintf(cgiOut, "</tr>\n");
	fprintf(cgiOut, "</tbody>\n");
	fprintf(cgiOut, "</table>\n");

	fprintf(cgiOut, "</td>\n");	
	fprintf(cgiOut, "</tr>\n");
	fprintf(cgiOut, "</tbody>\n");
	fprintf(cgiOut, "</table>\n");
	
	fprintf(cgiOut, "</div>\n");	 

	fprintf(cgiOut, "<br>\n");
	fprintf(cgiOut, "<center>\n");
	fprintf(cgiOut, "<input class=bottoni type=\"submit\" value=\"Update\">\n");
	fprintf(cgiOut, "</center>\n");
	fprintf(cgiOut, "</form>\n");

}

int cgiMain() {

	int updatedALARMTBL =-1;
	int updatedCROSSTBL =-1;
	int updatedCFGTBL =-1;
	int updatedATNCFG =-1;
	int updatedSPLASH =-1;
	int updatedHMI =-1;
	char Action [32] = "";
	char filename[FILENAME_MAX];


	/* Send the content type, letting the browser know this is HTML */
	cgiHeaderContentType("text/html");

	/* Now show the form */
	ShowForm();
	// updated = 1;
	/* If a submit button has already been clicked, act on the 
	   submission of the form. */
	if (cgiFormFileName("ALARMTBL", filename, FILENAME_MAX) == cgiFormSuccess 
	 || cgiFormFileName("CROSSTBL", filename, FILENAME_MAX) == cgiFormSuccess
	 || cgiFormFileName("CFGTBL", filename, FILENAME_MAX) == cgiFormSuccess
	 || cgiFormFileName("ATNCFG", filename, FILENAME_MAX) == cgiFormSuccess
	 || cgiFormFileName("SPLASH", filename, FILENAME_MAX) == cgiFormSuccess
	 || cgiFormFileName("HMI", filename, FILENAME_MAX) == cgiFormSuccess
	) {
		/* stop */
		system("/etc/rc.d/init.d/autoexec stop > /dev/null 2>&1");
		sleep(1);
		if (cgiFormFileName("ALARMTBL", filename, FILENAME_MAX) == cgiFormSuccess) {
			updatedALARMTBL = HandleSubmitALARMTBL();
		}
		if (cgiFormFileName("CROSSTBL", filename, FILENAME_MAX) == cgiFormSuccess) {
			updatedCROSSTBL = HandleSubmitCROSSTBL();
		}
		if (cgiFormFileName("CFGTBL", filename, FILENAME_MAX) == cgiFormSuccess) {
			updatedCFGTBL = HandleSubmitCFGTBL();
		}
		if (cgiFormFileName("ATNCFG", filename, FILENAME_MAX) == cgiFormSuccess) {
			updatedATNCFG = HandleSubmitATNCFG();
		}
		if (cgiFormFileName("SPLASH", filename, FILENAME_MAX) == cgiFormSuccess) {
			updatedSPLASH = HandleSubmitSPLASH();
		}
		if (cgiFormFileName("HMI", filename, FILENAME_MAX) == cgiFormSuccess) {
			updatedHMI = HandleSubmitHMI();
		}
		system("/etc/rc.d/init.d/autoexec start > /dev/null 2>&1");
		/* start */

		fprintf(cgiOut, "<br>\n");
		char msgarray[3][64] = {
			"<font color=\"#000000\">None</font>", // updated... = -1
			"<font color=\"#00FF00\">Done</font>", // updated... = 0
			"<font color=\"#FF0000\">Fail</font>", // updated... = +1
		};
		if (updatedALARMTBL + updatedCROSSTBL + updatedCFGTBL + updatedATNCFG + updatedSPLASH + updatedHMI < 6) {
			fprintf(cgiOut, "<table style=\"border:3px solid #335970;\" align=center cellpadding=4 >\n");
			fprintf(cgiOut, "<tbody>\n");
			fprintf(cgiOut, "<tr>\n");
			fprintf(cgiOut, "	<td>\n");	
			fprintf(cgiOut, "		Report:<br>\n");
			fprintf(cgiOut, "	</td>\n");	
			fprintf(cgiOut, "	<td>\n");	
			fprintf(cgiOut, "	</td>\n");	
			fprintf(cgiOut, "</tr>\n");
			fprintf(cgiOut, "<tr>\n");
			fprintf(cgiOut, "	<td align=\"right\">\n");	
			fprintf(cgiOut, "		Alarms table:\n");
			fprintf(cgiOut, "	</td>\n");	
			fprintf(cgiOut, "	<td>\n");	
			fprintf(cgiOut, "		%s\n", msgarray[updatedALARMTBL + 1]);
			fprintf(cgiOut, "	</td>\n");	
			fprintf(cgiOut, "</tr>\n");
			fprintf(cgiOut, "<tr>\n");
			fprintf(cgiOut, "	<td align=\"right\">\n");	
			fprintf(cgiOut, "		Cross table:\n");
			fprintf(cgiOut, "	</td>\n");	
			fprintf(cgiOut, "	<td>\n");	
			fprintf(cgiOut, "		%s\n", msgarray[updatedCROSSTBL + 1]);
			fprintf(cgiOut, "	</td>\n");	
			fprintf(cgiOut, "</tr>\n");
			fprintf(cgiOut, "<tr>\n");
			fprintf(cgiOut, "	<td align=\"right\">\n");	
			fprintf(cgiOut, "		Commpar:\n");
			fprintf(cgiOut, "	</td>\n");	
			fprintf(cgiOut, "	<td>\n");	
			fprintf(cgiOut, "		%s\n", msgarray[updatedCFGTBL + 1]);
			fprintf(cgiOut, "	</td>\n");	
			fprintf(cgiOut, "</tr>\n");
			fprintf(cgiOut, "<tr>\n");
			fprintf(cgiOut, "	<td align=\"right\">\n");	
			fprintf(cgiOut, "		Config file:\n");
			fprintf(cgiOut, "	</td>\n");	
			fprintf(cgiOut, "	<td>\n");	
			fprintf(cgiOut, "		%s\n", msgarray[updatedATNCFG + 1]);
			fprintf(cgiOut, "	</td>\n");	
			fprintf(cgiOut, "</tr>\n");
			fprintf(cgiOut, "<tr>\n");
			fprintf(cgiOut, "	<td align=\"right\">\n");
			fprintf(cgiOut, "		Splash file:\n");
			fprintf(cgiOut, "	</td>\n");	
			fprintf(cgiOut, "	<td>\n");	
			fprintf(cgiOut, "		%s\n", msgarray[updatedSPLASH + 1]);
			fprintf(cgiOut, "	</td>\n");	
			fprintf(cgiOut, "</tr>\n");
			fprintf(cgiOut, "<tr>\n");
			fprintf(cgiOut, "	<td align=\"right\">\n");	
			fprintf(cgiOut, "		hmi file:\n");
			fprintf(cgiOut, "	</td>\n");
			fprintf(cgiOut, "	<td>\n");	
			fprintf(cgiOut, "		%s\n", msgarray[updatedHMI + 1]);
			fprintf(cgiOut, "	</td>\n");
			fprintf(cgiOut, "</tr>\n");
			fprintf(cgiOut, "</tbody>\n");
			fprintf(cgiOut, "</table>\n");
		}
		else if (updatedALARMTBL + updatedCROSSTBL + updatedCFGTBL + updatedATNCFG + updatedSPLASH + updatedHMI == 6) {
			fprintf(cgiOut, "<table style=\"border:3px solid #FF0000;\" align=center cellpadding=4 >\n");
			fprintf(cgiOut, "<tbody>\n");
			fprintf(cgiOut, "<tr>\n");
			fprintf(cgiOut, "<td>\n");	
			fprintf(cgiOut, "No file are updated '%s'.\n", Action);
			fprintf(cgiOut, "</td>\n");
			fprintf(cgiOut, "</tr>\n");
			fprintf(cgiOut, "</tbody>\n");
			fprintf(cgiOut, "</table>\n");
		}
	}

	fprintf(cgiOut, "<BR>\n");
	/* Finish up the page */
	fprintf(cgiOut, "<center>\n");
	fprintf(cgiOut, "<form>\n");
	fprintf(cgiOut, "<input class=bottoni type=\"button\" value=\"Home\" onclick=\"window.location.href='menu.cgi'\">\n");
	fprintf(cgiOut, "</form>\n");
	fprintf(cgiOut, "</center>\n");

	fprintf(cgiOut, "</div>\n");
	fprintf(cgiOut, "</div>\n");
	//fprintf(cgiOut, "<div id=\"footer\"><h2>MECT</h2></div>");
	fprintf(cgiOut, "</BODY>\n</HTML>\n");

	return 0;
}


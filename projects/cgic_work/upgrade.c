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
	fprintf(cgiOut, "<title>Script Loader</title>\n");
	fprintf(cgiOut, "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\n");
	fprintf(cgiOut, "</head>\n");
	
	fprintf(cgiOut, "<body>\n");

	fprintf(cgiOut, "<div id=\"header\">");
	fprintf(cgiOut, "<table width=\"100%\">");
	fprintf(cgiOut, "<tr align=\"left\">");
	fprintf(cgiOut, "<td>");
	fprintf(cgiOut, "<h1><img src=\"splash.img\" style=\"width:auto;height:136px;float=left;vertical-align:middle;\"> Script Loader</h1>");
	fprintf(cgiOut, "</td>");
	fprintf(cgiOut, "</tr>");
	fprintf(cgiOut, "</table>");
	fprintf(cgiOut, "</div> <!-- end div header -->");
	fprintf(cgiOut, "<div id=\"content\">\n");
	fprintf(cgiOut, "<div id=\"form\">\n"); 
	fprintf(cgiOut, "<table style=\"border:solid 2px #335970;\" bgcolor=#f1fbff cellspacing=10 cellpadding=4 align=center >\n");
	fprintf(cgiOut, "<tbody>\n");
	fprintf(cgiOut, "<tr>\n");
	fprintf(cgiOut, "<td>\n");	

	fprintf(cgiOut, "<form name=\"sysupdform\" method=\"POST\" enctype=\"multipart/form-data\" ");
	fprintf(cgiOut, "	action=\"upgrade.cgi\">\n");
	fprintf(cgiOut, "<table cellspacing=10 cellpadding=4 align=right>");
	fprintf(cgiOut, "<tbody>\n");
	fprintf(cgiOut, "<tr>\n");
	fprintf(cgiOut, "<td>\n");	
	fprintf(cgiOut, "Choose sysupdate.sh file:\n");
	fprintf(cgiOut, "</td>\n"); 	 
	fprintf(cgiOut, "<td>\n");
	fprintf(cgiOut, "<input type=\"file\" name=\"SYSUPD\" required>\n");
	fprintf(cgiOut, "</td>\n");
	fprintf(cgiOut, "<td>\n");	
	fprintf(cgiOut, "<input class=bottoni type=\"submit\" value=\"Update\">\n");
	fprintf(cgiOut, "</td>\n");
	fprintf(cgiOut, "</tr>\n");
	fprintf(cgiOut, "</tbody>\n");
	fprintf(cgiOut, "</table>\n");
	fprintf(cgiOut, "</form>\n");

	fprintf(cgiOut, "</td>\n");	
	fprintf(cgiOut, "</tr>\n");
	fprintf(cgiOut, "</tbody>\n");
	fprintf(cgiOut, "</table>\n");
	fprintf(cgiOut, "</form>\n");

	fprintf(cgiOut, "</td>\n");	
	fprintf(cgiOut, "</tr>\n");
	fprintf(cgiOut, "</tbody>\n");
	fprintf(cgiOut, "</table>\n");
	fprintf(cgiOut, "</form>\n");

	fprintf(cgiOut, "</td>\n");	
	fprintf(cgiOut, "</tr>\n");
	fprintf(cgiOut, "</tbody>\n");
	fprintf(cgiOut, "</table>\n");

	fprintf(cgiOut, "</div>\n");	 
}

int cgiMain() {

	int updated =-1;
	char Action [32];


	/* Send the content type, letting the browser know this is HTML */
	cgiHeaderContentType("text/html");

	/* Now show the form */
	ShowForm();
	// updated = 1;
	/* If a submit button has already been clicked, act on the 
	   submission of the form. */
	if (cgiFormSubmitClicked("SYSUPD") == cgiFormSuccess
	 || cgiFormSubmitClicked("HMI") == cgiFormSuccess
	 || cgiFormSubmitClicked("FCRTS") == cgiFormSuccess
	 || cgiFormSubmitClicked("PLC") == cgiFormSuccess
	) {
		/* stop */
		system("/etc/rc.d/init.d/autoexec stop > /dev/null 2>&1");
		sleep(1);
		if (cgiFormSubmitClicked("SYSUPD") == cgiFormSuccess)
		{
			updated = HandleSubmitSYSUPD();
			strcpy(Action, "SYSUPD");
		}
		else if (cgiFormSubmitClicked("HMI") == cgiFormSuccess)
		{
			updated = HandleSubmitHMI();
			strcpy(Action, "HMI");
		}
		else if (cgiFormSubmitClicked("FCRTS") == cgiFormSuccess)
		{
			updated = HandleSubmitFCRTS();
			strcpy(Action, "FCTRS");
		}
		else if (cgiFormSubmitClicked("PLC") == cgiFormSuccess)
		{
			updated = HandleSubmitPLC();
			strcpy(Action, "PLC");
		}
		/* start */
		system("/etc/rc.d/init.d/autoexec start > /dev/null 2>&1");
	} else {
		strcpy(Action, "UNKNOWN");
		updated = -1;
	}

	if (updated == 0) {
		fprintf(cgiOut, "<table style=\"border:3px solid #335970;\" align=center cellpadding=4 >\n");
		fprintf(cgiOut, "<tbody>\n");
		fprintf(cgiOut, "<tr>\n");
		fprintf(cgiOut, "<td>\n");	
		fprintf(cgiOut, "%s Updated.\n", Action);
		fprintf(cgiOut, "</td>\n");
		fprintf(cgiOut, "</tr>\n");
		fprintf(cgiOut, "</tbody>\n");
		fprintf(cgiOut, "</table>\n");
	}
	else if (updated == 1) {
		fprintf(cgiOut, "<table style=\"border:3px solid #FF0000;\" align=center cellpadding=4 >\n");
		fprintf(cgiOut, "<tbody>\n");
		fprintf(cgiOut, "<tr>\n");
		fprintf(cgiOut, "<td>\n");	
		fprintf(cgiOut, "Update error for action %s, please retry.\n", Action);
		fprintf(cgiOut, "</td>\n");
		fprintf(cgiOut, "</tr>\n");
		fprintf(cgiOut, "</tbody>\n");
		fprintf(cgiOut, "</table>\n");
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


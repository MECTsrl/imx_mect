/*
 * Parser program
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Copyright (C) 2005 Metrowerks , a freescale semiconductor , Inc . company.
 * ALL Rights Reserved.
 *
 */
/********************************************************************
 *			Includes
 ********************************************************************/
 #include <stdio.h>
 #include <string.h>
 #include <fcntl.h>
/********************************************************************
 *    			Main function
 *******************************************************************/
 int main(int argc,char *argv[])
 {
	
	char *token;
	char ip_address[16];
	int loop=0,size,i;
	FILE *fd ;
	char octets[5];
        ip_address[0]='\0';
	/* usage */
	if(argc==1)
	{
		printf("\n Usage : parse [SIP server data] [ file name] \n");
		
		return 0;		
	}
	/* open file which should contain sip server data */
	if((fd=fopen(argv[2],"w+"))==NULL)
	{
		return 0;
	}
	token=strtok(argv[1],":");
	if(!strcmp(token,"1"))
	{
	
		while((token=strtok(NULL,":"))!=NULL)
        	{							
			
                	fprintf(fd,"%d",strtol(token,NULL,16));
			loop++;
			if(loop==4)
			{
				fprintf(fd,"\n");
				loop=0;
			}
			else
			{
				fprintf(fd,".");
			}
	       	}		

	}
	else
	{
		while((token=strtok(NULL,":"))!=NULL)
                {
			size=strtol(token,NULL,16);
			for(i=0;i<size;i++)
			{                
				if((token=strtok(NULL,":"))!=NULL)
				{
                        		fprintf(fd,"%c",strtol(token,NULL,16));
				}
				else
				{
					fclose(fd);
					return 0;
				}
			}					
			fprintf(fd,".");
			if((token=strtok(NULL,":"))==NULL)
                        {
                                break;
                        }
			size=strtol(token,NULL,16);
                        for(i=0;i<size;i++)
                        {
                                if((token=strtok(NULL,":"))!=NULL)
                                {
                                        fprintf(fd,"%c",strtol(token,NULL,16));
                                }
                                else
                                {
                                        fclose(fd);
                                        return 0;
                                }
                        }
			fprintf(fd,"\n");
			if((token=strtok(NULL,":"))==NULL)
			{
				break;
			}
			size=strtol(token,NULL,16);
			if((size=strtol(token,NULL,16))!=0)
			{
				/*close file*/
				fclose(fd);
				return(0);
			}
                }

	}
	/*close file*/
	fclose(fd);	
	return 0;
 }

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define BUFF_SIZE 8096
#define VAR_COUNT 512
#define DATE_LENGHT 128
#define TAG_LEN 32

#define SEPARATOR ";"
#define FILEPATH "/local/data/store"

struct name_list {
    int number;
    char name[VAR_COUNT][TAG_LEN];
    int index[VAR_COUNT];
    int average[VAR_COUNT];
};
char tx_datetime[DATE_LENGHT];
unsigned delta;

int usage(void); //HTML
void searchForLimitsAndNames(char *date_from, char *date_to, struct name_list *var_list);
void searchForValues(char *date_from, char *date_to, struct name_list *var_list);
int searchForValuesInRow(char* buffer, struct name_list *var_list, char *date_from, char *date_to,
                         int isFirstFile, int isLastFile);//, char *tx_datetime, unsigned delta);
char *strtok_csv(char *string, const char *separators, char **savedptr);
void deltaAdder(char* date,unsigned delta);

int main(void)
{
    char *query_string = NULL;
    struct name_list var_list;
    char date_from[DATE_LENGHT];
    char date_to[DATE_LENGHT];
    int specifiedVariables = 0;

    int v;
    char *ptr = NULL;
    unsigned year, month, day, hours, minutes, seconds;

    //DEBUG
    //strcpy(query,"from=2018-11-10T17:13:00&to=2018-11-19T17:28:00&vars=SysImpActiveEnergy_0,Life_node08,SysExpActiveEnergy_1,SysImpActiveEnergy_7,SysExpActiveEnergy_0,MPT91_Temperatura,SysActivePower_8");//&DigIn_7_node13&Life_node08&SysExpActiveEnergy_0&MPT91_Temperatura");//DEBUG
    //strcpy(query,"from=2018-11-23T22:13:00&to=2018-11-26T23:59:11&*");
    //strcpy(query,"vars=*");
    //strcpy(query,"from=2018-09-13T01:00:00&to=2018-11-14T23:59:59&vars=SysImpActiveEnergy_0");
    //strcpy(query,"from=*&to=2018-11-25T01:00:00&vars=SysImpActiveEnergy_0");
    //if (query==NULL)
    //DEBUG

    // azzeramento
    var_list.number = 0;
    for (v=0;v<VAR_COUNT;v++)
    {
        var_list.name[v][0] = '\0';
        var_list.average[v]=0;
    }
    date_from[0] = '\0';
    date_to[0] = '\0';

    query_string = getenv("QUERY_STRING");
    if (query_string == NULL)
    {
        return usage();//HTML page
    }
    fprintf(stderr, "QUERY_STRING='%s'\n", query_string);

    ptr = strstr(query_string,"from=");
    if (ptr != NULL)
    {
        if (ptr[5] != '*') {
            if (6 == sscanf(ptr,"from=%u-%u-%uT%u:%u:%u",&year,&month,&day,&hours,&minutes,&seconds)) {
                sprintf(date_from,"%04u-%02u-%02uT%02u:%02u:%02u",year,month,day,hours, minutes, seconds);
            }
        }
    }

    ptr = strstr(query_string,"to=");
    if (ptr != NULL)
    {
        if (ptr[3] != '*') {
            if (6 == sscanf(ptr,"to=%u-%u-%uT%u:%u:%u",&year,&month,&day,&hours,&minutes,&seconds)) {
                sprintf(date_to,"%04u-%02u-%02uT%02u:%02u:%02u",year,month,day,hours, minutes, seconds);
            }
        }
    }
    ///////////////////Delta/////////
    ptr = strstr(query_string,"delta_s=");
    if (ptr != NULL)
    {
        if (ptr[8] != '0') {
           sscanf(ptr,"delta_s=%u",&delta);
            }
        else{
            delta=1;
        }
    }
    else{
        delta=1;
    }


    /////////////////////////////////
    ptr = strstr(query_string,"vars=");
    if (ptr != NULL && ptr[5] != '*' && ptr[5] != '\0')
    {
        // nomi variabili letti dalla query
        char buffer[BUFF_SIZE];
        char *r = NULL;

        strncpy(buffer, &ptr[5], BUFF_SIZE-1);
        ptr = strtok_r(buffer, ",&", &r);
        if (ptr != NULL)
        {
            do
            {
                if (var_list.number < VAR_COUNT)
                {
                    strncpy(var_list.name[var_list.number], ptr, TAG_LEN-1);
                    ++var_list.number;
                    specifiedVariables = 1;
                }
            }
            while ((ptr = strtok_r(NULL, ",&", &r)) != NULL);
        }
    }

    // eventuale giro negli header dei log per recuperare informazioni
    fprintf(stderr, "date_from='%s', date_to='%s', vars=%d\n", date_from, date_to, var_list.number);

    if (strlen(date_from) == 0 || strlen(date_to) == 0 || var_list.number == 0)
    {
        searchForLimitsAndNames(date_from, date_to, &var_list);
        fprintf(stderr, "date_from='%s', date_to='%s', vars=%d\n", date_from, date_to, var_list.number);
    }

    printf("Content-Type: application/json; charset=UTF-8\n");
    printf("\n");
    printf("{\n");
    printf("  \"query\": {\n");
    printf("    \"QUERY_STRING\": \"%s\",\n",query_string);
    printf("    \"from\": \"%s\",\n",date_from);
    printf("    \"to\": \"%s\",\n",date_to);
    printf("    \"variables\": [ ");
    for (v=0;v<var_list.number;v++)
    {
        if (v > 0)
            printf(", ");
        printf("\"%s\"", var_list.name[v]);
    }
    printf(" ]\n");
    printf("    }\n");

    if (specifiedVariables)
    {
        searchForValues(date_from, date_to, &var_list);//////delta qui
    }
    printf("}\n");

    return 0;
}

void searchForValues(char *date_from, char *date_to, struct name_list *var_list)
{
    // int delta=DELTA;
  ///---------------------------
    fprintf(stderr, "searching for variables values in logs:\n");
    fprintf(stderr, "\tfrom: %s\n", date_from);
    fprintf(stderr, "\tto: %s\n", date_to);
  ///---------------------------
    struct dirent **entries = NULL;
    FILE *fp = NULL;
    char buffer[BUFF_SIZE];
    int n,i,v;

     strncpy(tx_datetime, date_from, DATE_LENGHT-1);

    //fa una scan della cartella e ordina in modo alfabetico
    n = scandir(FILEPATH,&entries,0,alphasort);

    if (n < 0)
    {
        fprintf(stderr, "\twrong path\n");
        goto exit_function;
    }
    for (i = 0; i < n; ++i)
    {
        char file_date[DATE_LENGHT];
        char pathname[FILENAME_MAX];
        unsigned year = 0;
        unsigned mon = 0;
        unsigned day = 0;
        unsigned hours = 0;
        unsigned minutes = 0;
        unsigned seconds = 0;

        if (strcmp(entries[i]->d_name,".")==0 || strcmp(entries[i]->d_name,"..")==0)
            continue;

        // recupero i tempi dal nome del file
        sscanf(entries[i]->d_name,"%u_%u_%u_%u_%u_%u.log", &year, &mon, &day, &hours, &minutes, &seconds);


        // escludo i log fuori dall'intervallo di tempo dato
        sprintf(file_date, "%04u-%02u-%02uT%02u:%02u:%02u", year, mon, day, hours, minutes, seconds);
        char next_file_date[DATE_LENGHT];

        if (i < (n - 1))
        {
            unsigned xyear = 0;
            unsigned xmon = 0;
            unsigned xday = 0;
            unsigned xhours = 0;
            unsigned xminutes = 0;
            unsigned xseconds = 0;

            sscanf(entries[i + 1]->d_name,"%u_%u_%u_%u_%u_%u.log", &xyear, &xmon, &xday, &xhours, &xminutes, &xseconds);
            sprintf(next_file_date, "%04u-%02u-%02uT%02u:%02u:%02u", xyear, xmon, xday, xhours, xminutes, xseconds);
        } else {
            // l'ultimo file presente, quindi consideriamo solo fino a mezzanotte
            sprintf(next_file_date, "%04u-%02u-%02uT%02u:%02u:%02u", year, mon, day+1, 00, 00, 00); // day+1 solo per strcmp()
        }
///---------------------------
        int isFirstFile = 0;
        if (strcmp(file_date, date_from) <= 0)
        {
            if (strcmp(next_file_date, date_from) <= 0)
                // fprintf(stderr, "\tskipping too old log '%s'\n", pathname);
                continue; // log ancora troppo vecchi, continuo
            isFirstFile = 1; // primo file di log da considerare
        }

        int isLastFile = 0;
        if (strcmp(date_to, next_file_date) < 0) {
            if (strcmp(date_to, file_date) < 0)
                // fprintf(stderr, "\tskipping too new log '%s'\n", pathname);
                break; // log troppo recenti, smetto
            isLastFile = 1; // ultimo file di log da considerare
        }
//-----------------------------
        // lettura dei file
        sprintf(pathname, "%s/%s",FILEPATH, entries[i]->d_name);
        fp = fopen(pathname,"r");
        if (fp == NULL)
        {
            fprintf(stderr, "\tcannot open file '%s'\n", pathname);
            continue;
        }
        // read the header
        if (fgets(buffer, BUFF_SIZE, fp) == NULL)
        {
            fprintf(stderr, "\tcannot read header from file '%s'\n", pathname);
            goto close_file;
        }
        fprintf(stderr, "\t%s\n", pathname);

        char *token = NULL;
        char *savedptr = NULL;

        token = strtok_csv(buffer, SEPARATOR, &savedptr);
        if (token == NULL || token[0] == '\0' || strcmp(token, "date") != 0)
        {
            fprintf(stderr, "\t\tmissing 'date', found '%s'\n", token);
            goto close_file;
        }
        token = strtok_csv(NULL, SEPARATOR, &savedptr);
        if (token == NULL || token[0] == '\0' || strcmp(token, "time") != 0)
        {
            fprintf(stderr, "\t\tmissing 'time', found '%s'\n", token);
            goto close_file;
        }
///---------------------------
        // parsing variable names
        // associo gli indici validi per questo file di log
        int column = 1; // dopo date e time
        int indexes = 0;
        for (v=0;v<var_list->number;++v)
        {
            // azzero gli indici (da altre righe)
            var_list->index[v] = 0;
        }
///---------------------------
        while ((token = strtok_csv(NULL, SEPARATOR, &savedptr)) != NULL)
        {
            int found = 0;

            if (token[0] == '\0' || strlen(token) > TAG_LEN) {
                fprintf(stderr, "\t\twrong variable '%s'\n", token);
                break;
            }
            for (v=0;v<var_list->number;v++)
            {
                if (strcmp(var_list->name[v], token) == 0)
                {
                    found = 1;
                    break;
                }
            }
            ///---------------------------
            // marco l'indice usato in questo log file
            if (found)
            {
                var_list->index[v] = column;
                ++indexes;
            }
            ++column;
                ///---------------------------
        }

        // ok, done with header
            ///---------------------------
        if (indexes == 0) {
            fprintf(stderr, "\t\tno occurencies found\n");
            goto close_file;
        }

        // read rows
        while (fgets(buffer, BUFF_SIZE, fp) != NULL)
        {
            if (searchForValuesInRow(buffer, var_list, date_from, date_to, isFirstFile, isLastFile))//,tx_datetime,delta))//////delta qui
            {
                // skip the other rows


                break;
            }


        }

         ///---------------------------
        // done with log file
    close_file:
        fclose(fp);
    }
exit_function:
    if (entries)
    {
        for (i=0;i<n;i++)
            free(entries[i]);
        free(entries);
    }
}

//Data Reader
int searchForValuesInRow(char* buffer, struct name_list *var_list, char* date_from, char* date_to,
                         int isFirstFile, int isLastFile)//,char *tx_datetime ,unsigned delta)
{
    int v;
    char row_datetime[DATE_LENGHT];
    //char *skip_datetime="\0";

    //delta=DELTA;
    int first_value;


    char *token = NULL;
    char *savedptr = NULL;

    token = strtok_csv(buffer, SEPARATOR, &savedptr);
    if (token == NULL || token[0] == '\0')
    {
        fprintf(stderr, "\t\tmissing 'date', found '%s'\n", token);
        return -1; // skip data row
    }
    strncpy(row_datetime, token, DATE_LENGHT-1);
    row_datetime[4] = '-';
    row_datetime[7] = '-';
    strncat(row_datetime, "T", DATE_LENGHT);
    // FIXME: controllare che date coincida con quella del file stesso

    //strcpy(tmp_datetime,row_datetime);
    //strcpy(skip_datetime[DATE_LENGHT],dateConvert(tmp_datetime,delta));



    token = strtok_csv(NULL, SEPARATOR, &savedptr);
    if (token == NULL || token[0] == '\0')
    {
        fprintf(stderr, "\t\tmissing 'time', found '%s'\n", token);
        return -1; // skip data row
    }
    strncat(row_datetime, token, DATE_LENGHT);

    // escludo le righe troppo vecchie e troppo recenti

    if (isFirstFile && strcmp(row_datetime, date_from) < 0)
    {
        return 0; // continue
    }

    if (isLastFile && strcmp(date_to, row_datetime) < 0)
    {
        return 1; // skip file
    }

    // parsing variable values
    int column = 1; // dopo date e time
    first_value = 1;



  if(delta==1){
        strcpy(tx_datetime,row_datetime);
    }


   if((strcmp(row_datetime,tx_datetime)>=0)){
    while ((token = strtok_csv(NULL, SEPARATOR, &savedptr)) != NULL) //////////////////qui delta
    {
        if (token[0] == '\0' || strlen(token) > TAG_LEN)
        {
            fprintf(stderr, "\t\twrong variable '%s'\n", token);
            break;
        }

        for (v=0; v < var_list->number; ++v)
        {
            if (var_list->index[v] == column )
            {

                if (first_value)
                {  ///////////////////////// qui delta skip

                    // alla prima colonna buona scrivo l'intestazione
                    printf(",\n");
                    printf("\"%s\": [", row_datetime);
                    first_value = 0;
                } else {
                    printf(",");
                }

               // printf("   \"%s\": ", var_list->name[v]);
                if (strcasecmp(token,"Nan")==0)
                {
                    // normalizziamo la stringa per i NaN
                    printf("\"NaN\"");

                }

                else// print anche dei "-"
                {
                    printf("%s", token);

                }

               //strcpy(tx_datetime,row_datetime);

               //strcpy(tx_datetime,row_datetime);
                break; // next column

               }
        }
        ++column;

    }
    do{
           deltaAdder(tx_datetime,delta);
      }
      while(strcmp(tx_datetime,row_datetime)<0);
  }



    if (! first_value)
    {
        // chiusura solo se abbiamo scritto qualcosa
        printf("] \n");
// { \"variables\}":
    }

    return 0; // continue

}

void deltaAdder(char* date,unsigned delta)
{
    unsigned x;
    unsigned old_sec,old_min,old_hour;
    struct tm time_struct;

    sscanf(date,"%u-%u-%uT%u:%u:%u",&time_struct.tm_year,&time_struct.tm_mon,&time_struct.tm_mday,
           &time_struct.tm_hour,&time_struct.tm_min,&time_struct.tm_sec);

    time_struct.tm_sec=time_struct.tm_sec+delta;
    old_sec=time_struct.tm_sec;
    old_min=time_struct.tm_min;
    old_hour=time_struct.tm_hour;
    time_struct.tm_year=time_struct.tm_year-1900;
    time_struct.tm_mon=time_struct.tm_mon-1;

    if(time_struct.tm_sec>=60){
        x=time_struct.tm_sec/60;
        time_struct.tm_min=time_struct.tm_min + x;
        time_struct.tm_sec=time_struct.tm_sec-(x*60);


        if(time_struct.tm_min>=60){
            x=time_struct.tm_min/60;

            time_struct.tm_min=time_struct.tm_min-(x*60);

            time_struct.tm_hour=time_struct.tm_hour + x;

            if(time_struct.tm_hour>=24){

                time_struct.tm_sec=old_sec;
                time_struct.tm_min=old_min;
                time_struct.tm_hour=old_hour;

                if(mktime(&time_struct)==-1)
                    fprintf(stderr, "date-time conversion error:\n");
            }
        }

    }
   /* sprintf(tmpdate,"%04u-%02u-%02uT%02u:%02u:%02u",time_struct.tm_year+1900,time_struct.tm_mon+1,time_struct.tm_mday,
            time_struct.tm_hour,time_struct.tm_min,time_struct.tm_sec);*/
    //strftime(tmpdate,DATE_LENGHT,"%Y-%m-%dT%H:%M:%S",&time_struct);
    //oppure
   strftime(tx_datetime,DATE_LENGHT,"%FT%T",&time_struct);

}



void searchForLimitsAndNames(char *date_from, char *date_to, struct name_list *var_list)
{
    ///---------------------------
    int searching_for_first_log = (strlen(date_from) == 0);
    int searching_for_last_log = (strlen(date_to) == 0);
    int searching_for_variable_names = (var_list->number == 0);

    fprintf(stderr, "searching for variables names in logs:\n");
    ///---------------------------

    struct dirent **entries = NULL;
    FILE *fp = NULL;
    char buffer[BUFF_SIZE];
    int n,i,v;

    //fa una scan della cartella e ordina in modo alfabetico
    n = scandir(FILEPATH,&entries,0,alphasort);

    if (n < 0)
    {
        fprintf(stderr, "\twrong path\n");
        goto exit_function;
    }
    for (i = 0; i < n; ++i)
    {
        char file_date[DATE_LENGHT];
        char pathname[FILENAME_MAX];
        unsigned year = 0;
        unsigned mon = 0;
        unsigned day = 0;
        unsigned hours = 0;
        unsigned minutes = 0;
        unsigned seconds = 0;

        if(strcmp(entries[i]->d_name,".")==0 || strcmp(entries[i]->d_name,"..")==0)
            continue; // "." and ".."

        // recupero i tempi dal nome del file
        sscanf(entries[i]->d_name,"%u_%u_%u_%u_%u_%u.log", &year, &mon, &day, &hours, &minutes, &seconds);
///---------------------------
        // eventualmente recupero i limiti di tempo dai nomi dei file
        if (i == 2 && searching_for_first_log)
        {
            sprintf(date_from,"%04d-%02d-%02dT%02d:%02d:%02d", year, mon, day, hours, minutes, seconds);
            if (!searching_for_last_log && !searching_for_variable_names)
                break;
        }
        if (i == n-1 && searching_for_last_log)
        {
            sprintf(date_to,"%04u-%02u-%02uT%02u:%02u:%02u", year, mon, day, 23, 59, 59);
            if (!searching_for_variable_names)
                break;
        }

        // leggo gli header solo se necessario
        if (!searching_for_variable_names)
            continue;
///---------------------------
        // escludo i log fuori dall'intervallo di tempo dato
        sprintf(file_date, "%04u-%02u-%02uT%02u:%02u:%02u", year, mon, day, hours, minutes, seconds);
        char next_file_date[DATE_LENGHT];
        if (i < (n - 1))
        {
            unsigned xyear = 0;
            unsigned xmon = 0;
            unsigned xday = 0;
            unsigned xhours = 0;
            unsigned xminutes = 0;
            unsigned xseconds = 0;
///---------------------------
            sscanf(entries[i + 1]->d_name,"%u_%u_%u_%u_%u_%u.log", &xyear, &xmon, &xday, &xhours, &xminutes, &xseconds);
            sprintf(next_file_date, "%04u-%02u-%02uT%02u:%02u:%02u", xyear, xmon, xday, xhours, xminutes, xseconds);
        } else {
            // l'ultimo file presente, quindi consideriamo solo fino a mezzanotte
            sprintf(next_file_date, "%04u-%02u-%02uT%02u:%02u:%02u", year, mon, day+1, 00, 00, 00); // day+1 solo per strcmp()
        }
        if (strcmp(file_date, date_from) < 0 && strcmp(next_file_date, date_from) < 0)
        {
            // fprintf(stderr, "\tskipping too old log '%s'\n", pathname);
            continue; // log ancora troppo vecchi, continuo
        }
        if (!searching_for_last_log && strcmp(file_date, date_to) > 0)
        {
            // fprintf(stderr, "\tskipping too new log '%s'\n", pathname);
            break; // log troppo recenti, smetto
        }
///---------------------------
        // lettura dei file
        sprintf(pathname, "%s/%s", FILEPATH , entries[i]->d_name);
        fp = fopen(pathname,"r");
        if (fp == NULL)
        {
            fprintf(stderr, "\tcannot open file '%s'\n", pathname);
            continue;
        }
        // read the header
        if (fgets(buffer, BUFF_SIZE, fp) == NULL)
        {
            fprintf(stderr, "\tcannot read header from file '%s'\n", pathname);
            goto close_file;
        }
        fprintf(stderr, "\t%s\n", pathname);

        char *token = NULL;
        char *savedptr = NULL;

        token = strtok_csv(buffer, SEPARATOR, &savedptr);
        if (token == NULL || token[0] == '\0' || strcmp(token, "date") != 0)
        {
            fprintf(stderr, "\t\tmissing 'date', found '%s'\n", token);
            goto close_file;
        }
        token = strtok_csv(NULL, SEPARATOR, &savedptr);
        if (token == NULL || token[0] == '\0' || strcmp(token, "time") != 0)
        {
            fprintf(stderr, "\t\tmissing 'time', found '%s'\n", token);
            goto close_file;
        }

        // parsing variable names
        // ignoriamo colonne e indici
        while ((token = strtok_csv(NULL, SEPARATOR, &savedptr)) != NULL)
        {
            int found = 0;

            if (token[0] == '\0' || strlen(token) > TAG_LEN) {
                fprintf(stderr, "\t\twrong variable '%s'\n", token);
                break;
            }
            for (v=0;v<var_list->number;v++)
            {
                if (strcmp(var_list->name[v], token) == 0)
                {
                    found = 1;
                    break;
                }
            }
       ///---------------------------
            // aggiungo le nuove variabili
            if (! found)
            {
                if (var_list->number < VAR_COUNT)
                {
                    strncpy(var_list->name[var_list->number], token, TAG_LEN-1);
                    fprintf(stderr, "\t\tvariable[%d]='%s'\n", var_list->number, var_list->name[var_list->number]);
                    ++var_list->number;
                }
                else
                {
                    fprintf(stderr, "\t\ttoo many variables: cannot add '%s'\n", token);
                    break;
                }
            }
        }
        ///---------------------------
        // ok, done with header

        // skip rows

        // done with log file
    close_file:
        fclose(fp);
    }
exit_function:
    if (entries)
    {
        for (i=0;i<n;i++)
            free(entries[i]);
        free(entries);
    }
    fprintf(stderr, "\tfound %d variables\n", var_list->number);
}


int usage(void)//HTML
{
    int n, i;
    struct dirent **entries;


    printf("Content-Type: Text/HTML; charset=UTF-8\n\n");
    printf("<!DOCTYPE html>\n<html><head>\n</head>");
    printf("\n<body><h3>Syntax:</h3>");
    printf("<ul>");
    printf("<li>get_log.cgi?<b>from=</b><u>YYYY-MM-DDThh:mm:ss</u><b>&to=</b><u>YYYY-MM-DDThh:mm:ss</u><b>&delta_s=</b><u>Seconds</u><b>&vars=</b><u>VariableNames</u></p>");
    printf("</ul>");
    printf("<h3>Examples:</h3>");
    printf("<ul>");
    printf("<li>get_log.cgi?<b>from=</b>2018-11-23T17:13:00<b>&to</b>=2018-11-25T17:28:00<b>&delta_s=</b>300<b>&vars=</b>Variable_A,Variable_B</li>");
    printf("<li>get_log.cgi?<b>from=</b>2018-11-23T17:13:00<b>&to</b>=2018-11-25T17:28:00<b>&vars=</b>Variable_A,Variable_B</li>");
    printf("<li>get_log.cgi?<b>from=</b>2018-11-23T17:13:00<b>&vars=</b>Variable_A,Variable_B</li>");
    printf("<li>get_log.cgi?<b>to=</b>2018-11-25T17:28:00<b>&vars=</b>Variable_A,Variable_B</li>");
    printf("<li>get_log.cgi?<b>from=</b>*<b>&to=</b>*<b>&vars=</b>Variable_A,Variable_B</li>");
    printf("<li>get_log.cgi?<b>vars=</b>* (only variable names)</li>");
    printf("</ul>");
    printf("<h3>Log Files:</h3>");

    entries = NULL;
    n = scandir(FILEPATH,&entries,0,alphasort);
    if (n < 0)
    {
        fprintf(stderr, "\twrong path\n");
        goto exit_function;
    }
    printf("<ol>\n");
    for (i=0; i < n; i++)
    {
        if(strcmp(entries[i]->d_name,".")==0 || strcmp(entries[i]->d_name,"..")==0)
        {
            continue;
        }

        char date_from[DATE_LENGHT]="\0";
        char date_to[DATE_LENGHT]="\0";
        unsigned year = 0;
        unsigned mon = 0;
        unsigned day = 0;
        unsigned hours = 0;
        unsigned minutes = 0;
        unsigned seconds = 0;
        int log_errors = 0;

        sscanf(entries[i]->d_name,"%u_%u_%u_%u_%u_%u.log", &year, &mon, &day, &hours, &minutes, &seconds);
        sprintf(date_from,"%04d-%02d-%02dT%02d:%02d:%02d", year, mon, day, hours, minutes, seconds);

        if (i < (n - 1))
        {
            unsigned xyear = 0;
            unsigned xmon = 0;
            unsigned xday = 0;
            unsigned xhours = 0;
            unsigned xminutes = 0;
            unsigned xseconds = 0;

            sscanf(entries[i + 1]->d_name,"%u_%u_%u_%u_%u_%u.log", &xyear, &xmon, &xday, &xhours, &xminutes, &xseconds);
            if (year == xyear && mon == xmon && day == xday)
            {
                // stesso giorno: mettiamo come limite un secondo prima del log successivo
                if (xseconds > 0)
                    xseconds -= 1;
                else {
                    xseconds = 59;
                    if (xminutes > 0)
                        xminutes -=1;
                    else {
                        xminutes = 59;
                        if (xhours > 0)
                            xhours -= 1;
                        else {
                            // errore: abbiamo due log che iniziano a 00:00:00
                            // forziamo comunque la lettura del file "i"
                            log_errors = 1;
                            xhours = 23;
                        }
                    }
                }
            } else {
                // altro giorno: mettiamo come limite la mezzanotte del giorno stesso
                xyear = year;
                xmon = mon;
                xday = day;
                xhours = 23;
                xseconds = 59;
                xminutes = 59;
            }
            sprintf(date_to, "%04u-%02u-%02uT%02u:%02u:%02u", xyear, xmon, xday, xhours, xminutes, xseconds);
        } else {
            // l'ultimo file presente, quindi consideriamo solo fino a mezzanotte
            sprintf(date_to, "%04u-%02u-%02uT%02u:%02u:%02u", year, mon, day, 23, 59, 59);
        }

        printf("<li><a href=\"get_log.cgi?from=%s&to=%s&vars=*\">%s</a>", date_from, date_to, entries[i]->d_name);
        if (log_errors)
            printf(" <i>log errors</i>");
        printf("\n");
    }
    printf("</ol>\n");

exit_function:
    if (entries)
    {
        for (i=0;i<n;i++)
            free(entries[i]);
        free(entries);
    }
    printf("<p></p></body></html>");
    return 0;
}

char *strtok_csv(char *string, const char *separators, char **savedptr)
{
    char *p, *s;

    if (separators == NULL || savedptr == NULL) {
        return NULL;
    }
    if (string == NULL) {
        p = *savedptr;
        if (p == NULL) {
            return NULL;
        }
    } else {
        p = string;
    }

    s = strstr(p, separators);
    if (s == NULL) {
        *savedptr = NULL;
        s = p + strlen(p);
    }
    else
    {
        *s = 0;
        *savedptr = s + 1;
    }

    // remove spaces at head
    while (p < s && isspace(*p)) {
        ++p;
    }
    // remove spaces at tail
    --s;
    while (s > p && isspace(*s)) {
        *s = 0;
        --s;
    }
    return p;
}

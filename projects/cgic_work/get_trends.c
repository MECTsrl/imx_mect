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
#define TREND_COUNT 100
#define TAG_LEN 32

#define SEPARATOR ";"
#define TRENDPATH "/local/data/trends" //"/local/data/trends"
#define CUSTOMTRENDPATH "/local/data/customtrend" // "/local/data/trends"


struct name_list {
    int number;
    char name[TREND_COUNT][TAG_LEN];
    int index[TREND_COUNT];
};

int usage(void); //HTML
char *strtok_csv(char *string, const char *separators, char **savedptr);


int main()
{
    char *query_string = NULL;
    struct name_list trend_list;
    char *ptr = NULL;
    int v;

    // azzeramento
    trend_list.number = 0;
    for (v=0;v<TREND_COUNT;v++)
    {
        trend_list.name[v][0] = '\0';
    }
    query_string = getenv("QUERY_STRING");


    // DEBUG ////////////////////////
    //stdout = freopen("trends.json", "w", stdout);
    //query_string = "trend=trend1.csv,trend2.csv,trend3.csv";
    //query_string = "trend=*";
    // /////////////////////////////

   /* if (query_string == NULL)
    {
        return usage();//HTML page
    }
    fprintf(stderr, "QUERY_STRING='%s'\n", query_string);
    */
    /////////////////////////////////
    if (query_string != NULL)
        ptr = strstr(query_string,"trend=");

    if (ptr == NULL || ptr[6] == '*') {

        fprintf(stderr, "Print all trends'\n");
        struct dirent **entries = NULL;
        int n,i;

        n = scandir(CUSTOMTRENDPATH,&entries,0,alphasort);

        if (n < 0)
        {
            fprintf(stderr, "\twrong path \n");
            goto print_query;
        }

        for (i = 0; i < n; ++i)
        {
            if (strcmp(entries[i]->d_name,".")==0 || strcmp(entries[i]->d_name,"..")==0)
                continue;

            // lettura dir
            if (trend_list.number < TREND_COUNT)
            {
                strncpy(trend_list.name[trend_list.number], entries[i]->d_name, TAG_LEN-1);
                ++trend_list.number;
            }
         }
    }
   /* else if (ptr != NULL && ptr[6] != '*' && ptr[5] != '\0')
    {
        // nomi trends letti dalla query
        char buffer[BUFF_SIZE];
        char *r = NULL;

        strncpy(buffer, &ptr[6], BUFF_SIZE-1);
        ptr = strtok_r(buffer, ",", &r);
        if (ptr != NULL)
        {
            do
            {
                if (trend_list.number < TREND_COUNT)
                {
                    strncpy(trend_list.name[trend_list.number], ptr, TAG_LEN-1);
                    ++trend_list.number;
                }
            }
            while ((ptr = strtok_r(NULL, ",", &r)) != NULL);
        }
    }*/


    /////////////////////////////////
print_query:
    printf("Content-Type: application/json; charset=UTF-8\n");
    printf("\n");
    printf("{\n");
    printf("  \"query\": {\n");
    printf("    \"QUERY_STRING\": \"%s\",\n",query_string);
    printf("    \"trends\": [ ");
    for (v=0;v<trend_list.number;v++)
    {
        if (v > 0)
            printf(", ");
        printf("\"%s\"", trend_list.name[v]);
    }
    printf(" ]\n");
    printf("    }\n");

    // ricerca trends
    if(trend_list.number != 0) {
        trendExplorer(trend_list);
        printf("\n]");
    }
    printf("\n}\n");

    return 0;
}

void trendExplorer(struct name_list *trend_list)
{
  fprintf(stderr, "searching for trends...\n");

  struct dirent **entries = NULL;
  FILE *fp = NULL;
  char buffer[BUFF_SIZE];
  int firstLine = 0;

  int n,i;

  n = scandir(CUSTOMTRENDPATH,&entries,0,alphasort);

  if (n < 0)
  {
      fprintf(stderr, "\twrong path \n");
      goto exit_function;
  }

  printf(",\n");
  printf("\"trends\": [\n{");
  for (i = 0; i < n; ++i)
  {
      char pathname[FILENAME_MAX];

      if (strcmp(entries[i]->d_name,".")==0 || strcmp(entries[i]->d_name,"..")==0)
          continue;


      // lettura dei file
      sprintf(pathname, "%s/%s",CUSTOMTRENDPATH, entries[i]->d_name);
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

      if (buffer == NULL || token == '\0' || strcmp(token, "L") != 0)
      {
          fprintf(stderr, "\t\twrong trend:'%s' header format \n", pathname);
          goto close_file;

      } else {
          // ok, done with header
          // read rows
          if(i > 2) {
              printf("\n,{");
          }
          printf("\"filename\": \"%s\" ,", entries[i]->d_name);
          printf("\"track\": [ ");

          while (fgets(buffer, BUFF_SIZE, fp) != NULL)
          {
              char *tokenFile = NULL;
              char *savedptrFile = NULL;
              char bufferFile[BUFF_SIZE];
              int counter = 0;

              printf("\n");
              if(firstLine) {
                printf(",{");
              } else {
                printf("{");
              }

              strcpy(bufferFile,buffer);
              tokenFile = strtok_csv(bufferFile, SEPARATOR, &savedptrFile);

              if(tokenFile != NULL || tokenFile != "\0" ) {
                  printf("\"enabled\": %d,", atoi(tokenFile));
              } else {
                  printf("\"enabled\": 0,");
              }

              while ((tokenFile = strtok_csv(NULL, SEPARATOR, &savedptrFile)) != NULL)
              {
                  if(counter == 0) {
                      printf("\"id\": \"%s\",", tokenFile);
                  } else if(counter == 1) {
                      printf("\"color\": \"%s\",", tokenFile);
                  } else if(counter == 2) {
                      printf("\"min\": \"%s\",",tokenFile);
                  } else if(counter == 3) {
                      printf("\"max\": \"%s\",",tokenFile);
                  } else if(counter == 4) {
                      printf("\"name\": \"%s\"", tokenFile);
                  } else {
                      break;
                  }
                  counter++;
              }
              printf("}");
              firstLine = 1;
          }
          printf("\n]}");

      }
    close_file:
        fclose(fp);
        firstLine = 0;
  }

exit_function:
    if (entries)
    {
        for (i=0;i<n;i++)
            free(entries[i]);
        free(entries);
    }
}


int usage(void)//HTML
{
    int n, i;
    struct dirent **entries;

    printf("Content-Type: Text/HTML; charset=UTF-8\n\n");
    printf("<!DOCTYPE html>\n<html><head>\n</head>");
    printf("\n<body><h3>Syntax:</h3>");
    printf("<ul>");
    printf("<li>get_trends.cgi?<b>trend=</b><u>trend_file_name.csv</u></p>");
    printf("<li>get_trends.cgi?<b>trend=</b><u>*</u></p>");
    printf("</ul>");

    printf("<h3>Trends :</h3>");
    entries = NULL;
    n = scandir(CUSTOMTRENDPATH,&entries,0,alphasort);
    if (n < 0)
    {
        fprintf(stderr, "\twrong path\n");
        goto custom_trend_func;
    }
    printf("<ol>\n");
    for (i=0; i < n; i++)
    {
        if(strcmp(entries[i]->d_name,".")==0 || strcmp(entries[i]->d_name,"..")==0)
        {
            continue;
        }

        printf("<li><a href=\"get_trends.cgi?trend=%s\">%s</a>", entries[i]->d_name, entries[i]->d_name);
        printf("\n");
    }
    printf("</ol>\n");


custom_trend_func:
    printf("<h3>Custom Trends :</h3>");
    entries = NULL;
    n = scandir(CUSTOMTRENDPATH,&entries,0,alphasort);
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

        printf("<li><a href=\"get_trends.cgi?trend=%s\">%s</a>", entries[i]->d_name, entries[i]->d_name);
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

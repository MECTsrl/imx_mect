#include <QtGui/QApplication>
#include <QWSServer>
#include <getopt.h>
#include <stdio.h>
#include "splash.h"
#define VERSION "0.1"

char picture[256] = "";
char text[256] = "";
char fontname[256] = "";
char fontsize[256] = "";
char color[256] = "";
char bgcolor[256] = "";

/* Long options */
static struct option long_options[] = {
    {"version", no_argument,              NULL, 'v'},
    {"picture", required_argument,        NULL, 'p'},
    {"text",    required_argument,        NULL, 't'},
    {"font",    required_argument,        NULL, 'f'},
    {"dimension",  required_argument,        NULL, 'd'},
    {"color",   required_argument,        NULL, 'c'},
    {"bgcolor", required_argument,        NULL, 'b'},
    {"qt", no_argument,        NULL, 'q'},
    {"qt", no_argument,        NULL, 'w'},
    {"qt", no_argument,        NULL, 's'},
    {NULL,      no_argument,              NULL,  0}
};

/*
 * Short options.
 * FIXME: KEEP THEIR LETTERS IN SYNC WITH THE RETURN VALUE
 * FROM THE LONG OPTIONS!
 */
static char short_options[] = "vptfdcbqws";

static int application_options(int argc, char *argv[])
{
    int option_index = 0;
    int c = 0;

    if (argc <= 0)
        return 0;

    if (argv == NULL)
        return 1;

    while ((c = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch (c) {
        case 'v':
            printf("%s version: %s\n", argv[0], VERSION);
            exit(0);
            break;
        case 'p':
            if (optarg)
            {
                fprintf(stderr, "%c with arg %s\n", c, optarg);
                printf("picture: %s\n", optarg);
                strcpy(picture, optarg);
            }
            break;
        case 't':
            if (optarg)
            {
                fprintf(stderr, "%c  with arg %s\n", c, optarg);
                printf("text: %s\n", optarg);
                strcpy(text, optarg);
            }
            break;
        case 'f':
            if (optarg)
            {
                fprintf(stderr, "%c  with arg %s\n", c, optarg);
                printf("font: %s\n", optarg);
                strcpy(fontname, optarg);
            }
            break;
        case 'd':
            if (optarg)
            {
                fprintf(stderr, "%c  with arg %s\n", c, optarg);
                printf("font size: %s\n", optarg);
                strcpy(fontsize, optarg);
            }
            break;
        case 'c':
            if (optarg)
            {
                fprintf(stderr, "%c  with arg %s\n", c, optarg);
                printf("rgbcolor: %s\n", optarg);
                strcpy(color, optarg);
            }
            break;
        case 'b':
            if (optarg)
            {
                fprintf(stderr, "%c  with arg %s\n", c, optarg);
                printf("rgbbgcolor: %s\n", optarg);
                strcpy(bgcolor, optarg);
            }
            break;
        case 'q':
            break;
        case 'w':
            break;
        case 's':
            break;
        default:
            fprintf(stderr, "%c unknown arg %s\n", c, optarg);
            break;
        }
    }

    return 0;
}

/**
 * @brief main
 */
int main(int argc, char *argv[])
{
    if (application_options(argc, argv) != 0) {
        fprintf(stderr, "%s: command line option error.\n", __func__);

        return 1;
    }

    /* print the version */
    fprintf(stderr, "#######################\n");
    fprintf(stderr, "# Version: %10s #\n", VERSION);
    fprintf(stderr, "#######################\n");

    QApplication a(argc, argv);

    /* set the cursor as invisible */
    QWSServer::setCursorVisible(false);

    splash w;
    w.showFullScreen();
    
    return a.exec();
}

/* @(#) $Id$ */

/* Copyright (C) 2006 Daniel B. Cid <dcid@ossec.net>
 * All rights reserved.
 *
 * This program is a free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License (version 2) as published by the FSF - Free Software
 * Foundation
 */
       

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "os_regex/os_regex.h"

#define OSSECCONF   "ossec.conf"
#define OS_MAXSTR   1024

int total;

int fileexist(char *file)
{
    FILE *fp;

    /* Opening file */
    fp = fopen(file, "r");
    if(!fp)
        return(0);

    fclose(fp);
    return(1);
}

int dogrep(char *file, char *str)
{
    char line[OS_MAXSTR +1];
    FILE *fp;

    /* Opening file */
    fp = fopen(file, "r");
    if(!fp)
        return(0);

    /* Clearing memory */
    memset(line, '\0', OS_MAXSTR +1);

    /* Reading file and looking for str */ 
    while(fgets(line, OS_MAXSTR, fp) != NULL)
    {
        if(OS_Match(str, line))
        {
            fclose(fp);
            return(1);
        }
    }

    fclose(fp);
    return(0);
}



/* Check is syscheck is present in the config */
int config_file(char *name, char *file)
{
    int add = 0;
    FILE *fp;

    if(!fileexist(file))
    {
        printf("%s: Log file not existent: '%s'.\n", name, file);
        return(0);
    }

    if(dogrep(OSSECCONF, file))
    {
        printf("%s: Log file already configured: '%s'.\n", 
                    name, file);
        return(0);
    }
    
    
    /* Add iis config config */
    fp = fopen(OSSECCONF, "a");
    if(!fp)
    {
        printf("%s: Unable to edit configuration file.\n", name);
        return(0); 
    }
   
    printf("%s: Adding log file to be monitored: '%s'.\n", name,file);
    printf("%s: Continue? (y/n):", name);
    while(1)
    {
        char u_buffer[256];
        memset(u_buffer, '\0', 256);
        if((fgets(u_buffer, 254, stdin) == NULL) &&
            (strlen(u_buffer) < 250))
        {
            if((u_buffer[0] == 'y') || (u_buffer[0] == 'Y'))
            {
                add = 1;
                break;
            }
            else if((u_buffer[0] == 'n') || (u_buffer[0] == 'N'))
            {
                add = 0;
                break;
            }
        }
    }
   
    if(add == 0)
    {
        printf("%s: Action not taken.\n", name);
        fclose(fp);
        return(0);
    }
    
    fprintf(fp, "\r\n" 
    "\r\n"    
    "<!-- Extra log file -->\r\n"
    "<ossec_config>\r\n"
    "  <localfile>\r\n"
    "    <location>%s</location>"
    "    <log_format>syslog</log_format>\r\n"
    "  </localfile>\r\n"
    "</ossec_config>\r\n\r\n", file);


    printf("%s: Action completed.\n", name);
    fclose(fp);

    return(0);
                    
}

/* Setup windows after install */
int main(int argc, char **argv)
{
    int i = 0;

    time_t tm;
    struct tm *p;
        
    
    if(argc < 3)
    {
        printf("%s: Invalid syntax.\n", argv[0]);
        printf("Try: '%s <directory> <file_name>'\n\n", argv[0]);
    }
    
    else if(chdir(argv[1]) != 0)
    {
        printf("%s: Invalid directory: '%s'.\n", argv[0], argv[1]);
    }
    
    /* Checking if ossec was installed already */
    else if(!fileexist(OSSECCONF))
    {
        printf("%s: Unable to find ossec config: '%s'.\n", argv[0], OSSECCONF);
    }

    else
    {
        config_file(argv[0], argv[2]);
    }
    
    system("pause");
    
    return(0);
}
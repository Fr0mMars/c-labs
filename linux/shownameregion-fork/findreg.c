#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "findreg.h"

//#define DEBUGMODEFIND

int findreg(char *buf, char *reg_num, char *reg_name)
{

    char *tmp_pointer = NULL;
    unsigned int i, j = 0;

    tmp_pointer = strstr(((const char *)buf), ((const char *)reg_num));

    #ifdef DEBUGMODEFIND
        printf("%p", tmp_pointer);
    #endif

    if (tmp_pointer == NULL)
    {
        #ifdef DEBUGMODEFIND
        printf("reg_num: %s\n", reg_num);
        #endif
        char tmp_answer[32] = "There is no region for number: ";
        strcat(reg_name, tmp_answer);
        strcat(reg_name, reg_num);
        #ifdef DEBUGMODEFIND
        printf("%s\n", reg_name);
        #endif
        return EXIT_SUCCESS;
    }
    else
    {
        i = tmp_pointer - buf + 1 + strlen(reg_num);

        while (buf[i] != 10)
        {
            reg_name[j] = buf[i];
            j++;
            i++;
        } 
        reg_name[j] = 0;
        
    }

    #ifdef DEBUGMODEFIND
        printf("%s", reg_name);
    #endif

    return EXIT_SUCCESS;
}

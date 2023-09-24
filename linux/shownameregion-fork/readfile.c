#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "readfile.h"

//#define DEBUGMODEREAD

int readfile(char *file_address, char *buf, size_t buf_size)
{
    size_t len;
    FILE *f = NULL;

    if ((f = fopen(file_address, "r")) == NULL)
    {
        fprintf(stderr, "Cannot open file: %d\n", errno);
        return EXIT_FAILURE;
    }
    while ((len = fread(buf, sizeof(char), buf_size - 1, f)) > 0)
    {
        if (ferror(f))
        {
            printf("File read error: %d\n", errno);
        }
        for (int i = 0; i < len; i++)
            if (0 == buf[i])
            {
                buf[i] = 10;
            }
        buf[len] = 0;
        #ifdef DEBUGMODEREAD
        printf("%s", buf);
        #endif
    }

    fclose(f);

    return EXIT_SUCCESS;
}

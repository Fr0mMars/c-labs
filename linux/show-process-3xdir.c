#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

#define PROCESS "bash"
#define BUF_SIZE 256

int main(int argc, char **argv)
{
    int count = 0;

    DIR *d = NULL;
    struct dirent *dirs;

    d = opendir("/proc");
    if (d == NULL)
    {
        ("opendir error");
        exit(-1);
    }
    
    while (dirs = readdir(d))
    {
        if ((isdigit(*dirs->d_name)))
        {

            char buf[BUF_SIZE] = "/proc/";
            strcat(buf, dirs->d_name);
            strcat(buf, "/comm");

            FILE *f = NULL;

            if ((f = fopen(buf, "r")) == NULL)
            {
                printf("Cannot open file %s.\n", buf);
                break;
            }

            buf[0] = 0;

            while (!feof(f))
            {
                fscanf(f, "%255s", buf);
                if (strcmp(PROCESS, buf) == 0)
                {
                    count++;
                    break;
                }
            }

            fclose(f);
        }
    }

    closedir(d);

    if (count > 0)
    {
        printf("The number of %s process: %d.\n", PROCESS, count);
    }
    else
        printf("Process not found.\n");

    return 0;
}

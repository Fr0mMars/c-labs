#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 256

int main(int argc, char *argv[])
{
    int PID;
    char buf[BUF_SIZE];

    FILE *f = NULL;
    if ((f = fopen("/proc/self/status", "r")) == NULL)
    {
        printf("Cannot open file.\n");
        exit(-1);
    }

    while (!feof(f))
    {
        if (fscanf(f, "%s", buf) > 0)
        {

            if (strcmp("Pid:", buf) == 0)
            {
                fscanf(f, "%d", &PID);
                printf("Pid: %d\n", PID);
                break;
            }
        }
    }

    fclose(f);

    return 0;
}
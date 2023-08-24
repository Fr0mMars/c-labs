#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int PID = -1;
    char buf[256];

    FILE *f = NULL;

    if ((f = fopen("/proc/self/status", "r")) == NULL)
    {
        printf("Cannot open file.\n");
        return -1;
    }

    while (!feof(f))
    {
        int TmpPID;
        fscanf(f, "%255s %d\n", buf, &TmpPID);
        if (strcmp("Pid:", buf) == 0)
        {
            PID = TmpPID;
            printf("Pid: %d\n", PID);
            break;
        }
    }

    fclose(f);

    if (PID == -1)
    {
        printf("PID not found.\n");
    }
    return 0;
}
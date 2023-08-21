#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 0x100
#define PARAMETER "PPid"

int main(int argc, char *argv[])
{

    char buf[BUF_SIZE];
    char *parameter = NULL;
    FILE *f = NULL;
    if (NULL == f)
    {
        if ((f = fopen("/proc/self/status", "r")) == NULL)
        {
            printf("Cannot open file.\n");
            exit(1);
        }
        while (!feof(f))
        {
            if (fgets(buf, BUF_SIZE - 1, f))
            {
                parameter = strstr(buf, PARAMETER);
                if (parameter != NULL)
                {
                    printf("%s", parameter);
                    break;
                }
            }
        }
          if (ferror(f))
        {
            printf("File read error.\n");
        }
        else if (NULL == parameter)
        {
            printf("There is no %s \n", PARAMETER);
        }
        else
            printf("End of search.\n");
        fclose(f);
    }
    return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 256
#define PARAMETER "PPid"

int main(int argc, char *argv[])
{

    char buf[BUF_SIZE];
    char *parameter = NULL;
    int parameter_value_int;
    FILE *f = NULL;

    if ((f = fopen("/proc/self/status", "r")) == NULL)
    {
        printf("Cannot open file.\n");
        exit(-1);
    }
    while (!feof(f))
    {
        if (fgets(buf, BUF_SIZE, f))
        {
            parameter = strstr(buf, PARAMETER);
            if (parameter != NULL)
            {
                sscanf(parameter, "%*s %d", &parameter_value_int);

                if (parameter_value_int != 0)
                {
                    printf("%d\n", parameter_value_int);
                }

                break;
            }
        }
    }

    if (NULL == parameter)
    {
        printf("There is no %s \n", PARAMETER);
    }

    fclose(f);

    return 0;
}
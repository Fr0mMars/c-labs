#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 256
#define PARAMETER "PPid"

int main(int argc, char *argv[])
{

    char buf[BUF_SIZE];
    char *parameter;
    char *parameter_value;
    int parameter_value_int;
    char nums[] = "0123456789";
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
                size_t start = strcspn(parameter, nums);
                parameter_value = &parameter[start];
                parameter_value_int = atoi(parameter_value);
                if (parameter_value_int != 0)
                {
                    printf("%d\n", parameter_value_int);
                }
                else
                    printf("Error with atoi");
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
    fclose(f);
    return 0;
}

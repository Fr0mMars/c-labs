#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int len;
    long file_size;
    char *buf = NULL;
    FILE *f = NULL;
    
        if ((f = fopen("/proc/self/status", "r")) == NULL)
        {
            printf("Cannot open file.\n");
            exit(1);
        }

        fseek(f, 0, SEEK_END);
        file_size = ftell(f);

        if (NULL == buf)
        {
            buf = malloc(file_size);
            if (NULL == buf)
            {
                printf("Memmory error!");
                exit(1);
            }
        }

        fseek(f, 0, SEEK_END);

        while (!feof(f))
        {
            if ((len = fscanf(f, "%c", buf)) > 0)
            {
                printf("%s", buf);
            }
        }

        free(buf);
        buf = NULL;

        if (feof(f))
        {
            printf("Premature end of file.\n");
        }
        else
            printf("File read error.\n");
        fclose(f);
    
    return 0;
}

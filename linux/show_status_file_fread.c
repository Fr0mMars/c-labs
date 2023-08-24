#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 256

int main(int argc, char *argv[])
{
    int len;
    char buf[BUF_SIZE];
    FILE *f = NULL;

    if ((f = fopen("/proc/self/status", "r")) == NULL)
    {
        printf("Cannot open file.\n");
        exit(-1);
    }
    while ((len = fread(buf, sizeof(char), BUF_SIZE - 1, f)) > 0)
    {
        for (int i = 0; i < len; i++)
            if (0 == buf[i])
            {
                buf[i] = 10;
            }
        buf[len] = 0;
        printf("%s", buf);
    }
    if (feof(f))
    {
        printf("Premature end of file.\n");
    }

    fclose(f);

    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define PROCESS "bash"

int sel(const struct dirent *d)
{
    int rv;

    for (int i = 0; i < 256; i++)
    {

        if (d->d_name[i] == 0)
        {
            return 1;
        }
        if (d->d_name[i] < '0' || d->d_name[i] > '9')
        {
            return 0;
        }
    }

    return 0;
}

int main(int argc, char **argv)
{
    int i, n;
    int count = 0;
    struct dirent **dirs;

    n = scandir("/proc", &dirs, sel, alphasort);
    if (n < 0)
    {
        perror("scandir");
        exit(-1);
    }
    else
    {
        for (i = 0; i < n; i++)
        {

            // printf("%s \n", dirs[i]->d_name);

            char buf[256] = "/proc/";
            strcat(buf, dirs[i]->d_name);
            strcat(buf, "/comm");

            // printf("%s \n", buf);

            FILE *f = NULL;

            if ((f = fopen(buf, "r")) == NULL)
            {
                printf("Cannot open file %s.\n", buf);
                break;
            }

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

        if (count > 0)
        {
            printf("The number of %s process: %d.\n", PROCESS, count);
        }
        else
            printf("Process not found.\n");
    }

    free(dirs);

    return 0;
}

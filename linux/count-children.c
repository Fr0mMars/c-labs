#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 256

int get_childs(int process_number)
{
    int count = 0;

    char dir_name[BUF_SIZE];
    snprintf(dir_name, sizeof(dir_name), "%d", process_number);

    char path[BUF_SIZE] = "/proc/";
    strcat(path, dir_name);
    strcat(path, "/task/");
    strcat(path, dir_name);
    strcat(path, "/children");

    FILE *f = NULL;

    if ((f = fopen(path, "r")) == NULL)
    {
        return 0;
    }

    else
    {
        while (!feof(f))
        {
            char Pid[BUF_SIZE];
            if (fgets(Pid, BUF_SIZE, f))
            {
                count++;
                count += get_childs(atoi(Pid));
            }
        }

        fclose(f);
    }
    return count;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("You need to use at least one and only one parametr\n");
        exit(-1);
    }

    int process_number = atoi(argv[1]);
    int num = get_childs(process_number) + 1;
    printf("%d\n", num);

    return 0;
}
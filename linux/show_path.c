#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 256
#define TGID "Tgid"
#define PID "Pid"
#define PPID "PPid"

int get_parametr_value(char *parameter_name, char *dir_name)
{
    int parameter = -1;
    char buf[BUF_SIZE];

    char path[256] = "/proc/";
    strcat(path, dir_name);
    strcat(path, "/status");
    // printf("%s - path\n", path);
    FILE *f = NULL;

    if ((f = fopen(path, "r")) == NULL)
    {
        printf("Cannot open file.\n");
        exit(-1);
    }

    while (!feof(f))
    {
        int tmp_parameter;
        char tmp_parameter_name[BUF_SIZE];
        strncpy(tmp_parameter_name, parameter_name, BUF_SIZE);
        strcat(tmp_parameter_name, ":");
        // printf("%s - tmp_parameter_name\n", tmp_parameter_name);

        fscanf(f, "%255s %d\n", buf, &tmp_parameter);
        if (strcmp(tmp_parameter_name, buf) == 0)
        {
            parameter = tmp_parameter;
            fclose(f);
            return parameter;
        }
    }

    fclose(f);

    if (parameter == -1)
    {
        printf("%s not found.\n", parameter_name);
    }
    return -1;
}

int show_path(int n)
{
    if (n == 1)
    {
        printf("%d\n", 1);
        return 1;
    }

    else
    {
        char dir_name[BUF_SIZE];
        snprintf(dir_name, sizeof(dir_name), "%d", n);
        int Tgid = get_parametr_value(TGID, dir_name);
        int Pid = get_parametr_value(PID, dir_name);

        if (Pid == Tgid)
        {
            int PPid = get_parametr_value(PPID, dir_name);
            printf("%d\n", Pid);
            return show_path(PPid);
        }
        printf("%d\n", Pid);
        return show_path(Tgid);
    }
    return -1;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("You need to use ar least and only one parametr\n");
        exit(-1);
    }
    int parametr_value = get_parametr_value(PID, argv[1]);
    // printf("%d - parametr_value\n", parametr_value);
    if (parametr_value != -1)
    {
        show_path(parametr_value);
    }
    return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    /* создание нового процесса */
    
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork faild");
        exit(-1);
    }
    else if (pid != 0)
        exit(EXIT_SUCCESS);

    /* создание нового сеанса и группы процессов */

    if (setsid() == -1)
    {
        perror("setsid faild");
        exit(-1);
    }

    /* установка в качестве рабочего каталога корневого каталога */

    if (chdir("/") == -1)
    {
        perror("chdir faild");
        exit(-1);
    }

    /* закрытие открытых файлов и вывод Pid процесса-демона */

    printf("%d\n", getpid());
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);

    /* перенаправление дескрипторов файла 0,1,2 в /dev/null */

    open("/dev/null", O_RDWR); /* stdin */
    dup(0);                    /* stdout */
    dup(0);                    /* stderr */

    sleep(60);

    return 0;
}
/*
В задании требуется доработать демон, разработанный ранее.
Задача -- снабдить демон обработчиком сигнала SIGURG,
по приходу которого демон должен завершать свою работу.
*/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void sigurg_function()
{
    exit(EXIT_SUCCESS);
}

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

    struct sigaction sigurg_action;
    memset(&sigurg_action, 0, sizeof(sigurg_action));
    sigurg_action.sa_handler = sigurg_function;

    sigaction(SIGURG, &sigurg_action, 0);

    while (1)
        sleep(60);

    return EXIT_SUCCESS;
}
/*Разработать приложение, умеющее обрабатывать сигналы
SIGUSR1 ,SIGUSR2, SIGTERM.
После старта Ваше приложение должно по приходу одного из сигналов
SIGUSR1,  SIGUSR2 выполнять суммирование числа срабатываний каждого из сигналов,
а после прихода сигнала SIGTERM, требуется вывести в стандартный поток вывода 2 числа,
разделенных пробелом, соответствующих количеству обработанных сигналов SIGUSR1, SIGUSR2, и завершить программу.
Вывод оканчивается символом конца строки.*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

volatile sig_atomic_t sum_sigusr1, sum_sigusr2 = 0;

void sigterm_function()
{
    printf("%d %d\n", sum_sigusr1, sum_sigusr2);
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    sigset_t sset;
    int sig;

    struct sigaction sigterm_action;
    memset(&sigterm_action, 0, sizeof(sigterm_action));
    sigterm_action.sa_handler = sigterm_function;

    sigaction(SIGTERM, &sigterm_action, 0);

    sigfillset(&sset);
    sigdelset(&sset, SIGTERM);
    sigprocmask(SIG_SETMASK, &sset, 0);
    while (!sigwait(&sset, &sig))
    {
        if (sig == 10) {
            sum_sigusr1++;
        }
         if (sig == 12) {
            sum_sigusr2++;
        }
    }
    return EXIT_SUCCESS;
}

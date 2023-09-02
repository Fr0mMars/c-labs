/*
Некоторая утилита генерирует довольно большой вывод,
а вам требуется всего-лишь посчитать количество символов '0' в этом выводе.
Утилита при запуске принимает 1 параметр. Вам требуется разработать программу, которая вызывает указанную утилиту,
с заданным параметром и подсчитывает количество символов '0' в ее выводе.
Ваша программа принимает на вход 2 параметра -- имя утилиты, в текущем каталоге и ее параметр.
Ваша программа должна после подсчета вывести найденное число '0' в отдельной строке,
заканчивающейся символом конца строки.
*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define BUF_SIZE 256

int main(int argc, char *argv[])
{
    FILE *f = NULL;
    int count = 0;
    int flag = 1;
    int i, symbol;
    char prog_with_param[BUF_SIZE];

    if (argc != 3)
    {
        printf("Use: ./solution someprog param\n");
        exit(-1);
    }

    snprintf(prog_with_param, sizeof prog_with_param, "%s %s", argv[1], argv[2]);
    f = popen(prog_with_param, "r");
    if (f == NULL)
    {
        perror("Error: popen\n");
        exit(-1);
    }

    while ((symbol = fgetc(f)) != EOF)
    {
        if (1 == flag)
        {
            if (feof(f))
            {
                perror("Error: wrong parameter\n");
                exit(-1);
            }
            else
            {
                flag = 0;
            }
        }
        if (48 == symbol)
        {
            count++;
        }
    }
    pclose(f);
    printf("%d\n", count);
    return 0;
}

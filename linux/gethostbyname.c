/*
Разработайте утилиту командной строки, 
принимающую на вход имя хоста и печатающую в стандартный поток вывода список IP-адресов, 
ассоциированных с данным именем.
*/

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char *argv[])
{

    int i = 0;

    if (argc != 2)
    {
        printf("You need to use at least one and only one parameter\n");
        return EXIT_FAILURE;
    }

    struct hostent *host = gethostbyname(argv[1]);
    if (host == NULL)
    {
        fprintf(stderr, "Unable to resolve hostname %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    while (NULL != host->h_addr_list[i])
    {
        struct in_addr *a = (struct in_addr *)host->h_addr_list[i];
        printf("%s\n", inet_ntoa(*a));
        i++;
    }
    return EXIT_SUCCESS;
}
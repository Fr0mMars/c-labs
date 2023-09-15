/*
Разработайте утилиту командной строки, 
принимающую на вход имя хоста и печатающую в стандартный поток вывода список IP-адресов, 
ассоциированных с данным именем.
*/

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("You need to use at least one and only one parameter\n");
        return EXIT_FAILURE;
    }

    int func_res;
    struct addrinfo *result, *tmp_result = NULL;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    func_res = getaddrinfo(argv[1], NULL, &hints, &result);
    if (func_res != 0)
    {
        perror("getaddrinfo error\n");
        return EXIT_FAILURE;
    }
    if (result == NULL)
    {
        fprintf(stderr, "Unable to resolve hostname %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    for (tmp_result = result; tmp_result != NULL; tmp_result = tmp_result->ai_next)
    {
        char *ip_add = inet_ntoa(((struct sockaddr_in *)tmp_result->ai_addr)->sin_addr);
        printf("%s\n", ip_add);
    }

    return EXIT_SUCCESS;
}
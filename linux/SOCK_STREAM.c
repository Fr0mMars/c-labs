/*
Разработайте TCP сервер, предназначенный для сортировки символов в строке.
Сервер получает на вход строки, оканчивающиеся символом '\0',
сортирует в них символы в порядке убывания ASCII-кодов и отсылает обратно на клиент,
в виде строки заканчивающейся '\0'.
Завершение работы сервера происходит после получения строки, содержащей только 'OFF'.

При старте сервер получает на вход номер порта в качестве параметра командной строки.
bind производится на адресе 127.0.0.1
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define BUF_SIZE 1024 * 5

int compare(const void *x1, const void *x2)
{
    return ((*(char *)x2) - (*(char *)x1));
}

int main(int argc, char *argv[])
{

    int tcp_socket, tmp_socket, port, clen;
    char buf[BUF_SIZE];
    struct sockaddr_in serv_addr, cli_addr;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port_number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    (void)argv;

    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (socket < 0)
    {
        printf("socket() failed: %d\n", errno);
        return EXIT_FAILURE;
    }

    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    port = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    // inet_aton("127.0.0.1", &serv_addr.sin_addr.s_addr);
    serv_addr.sin_port = htons(port);

    if (bind(tcp_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("bind() failed: %d\n", errno);
        return EXIT_FAILURE;
    }
    listen(tcp_socket, 1);
    clen = sizeof(cli_addr);
    tmp_socket = accept(tcp_socket, (struct sockaddr *)&cli_addr, &clen);
    if (tmp_socket < 0)
    {
        printf("accept() failed: %d\n", errno);
        return EXIT_FAILURE;
    }

    while (true)
    {
        memset(buf, 0, BUF_SIZE);
        int length = recv(tmp_socket, buf, BUF_SIZE - 1, 0);
        if (-1 == length)
        {
            printf("recv from socket failed: %d\n", errno);
        }
        buf[length] = 0;
        if (strncmp(buf, "OFF\n", 4) == 0)
        {
            break;
        }
        qsort(buf, (size_t)length, sizeof(char), compare);
        if (send(tmp_socket, buf, length, 0) == -1)
        { 
            printf("send() failed: %d\n", errno);
        }
    }

    close(tmp_socket);
    close(tcp_socket);

    return EXIT_SUCCESS;
}
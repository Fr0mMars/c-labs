/*
Разработайте UDP сервер для логирования (сбора и записи) сообщений.
Сервер при запуске принимает параметр -- номер порта, на котором будут приниматься запросы.
Каждый запрос приходящий к серверу - строка, не превышающая размер 5K.
Задача сервера -- выводить приходящие строки в стандартный поток ввода-вывода,
завершающиеся символом конца строки.

Сервер завершает работу, когда получает строку содержащую только текст 'OFF',
и заканчивающуюся символом перевода строки '\n'.

Сервер использует локальный адрес 127.0.0.1
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

#define BUF_SIZE (5 * 1024) + 1

int main(int argc, char *argv[])
{

    int socket_local, port;
    char buf[BUF_SIZE];
    struct sockaddr_in serv_addr;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port_number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    (void)argv;

    socket_local = socket(AF_INET, SOCK_DGRAM, 0);

    if (socket < 0)
    {
        printf("socket() failed: %d\n", errno);
        return EXIT_FAILURE;
    }

    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    port = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    // inet_aton("127.0.0.1", &serv_addr.sin_addr);
    serv_addr.sin_port = htons(port);

    if (bind(socket_local, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("bind() failed: %d\n", errno);
        return EXIT_FAILURE;
    }

    while (true)
    {
        ssize_t length = read(socket_local, buf, BUF_SIZE);
        if (-1 == length)
        {
            printf("read from socket failed: %d\n", errno);
        }
        buf[length] = 0;
        if (strncmp(buf, "OFF\n", 4) == 0)
        {
            break;
        }
        printf("%s\n", buf);
    }
    close(socket_local);
    return EXIT_SUCCESS;
}

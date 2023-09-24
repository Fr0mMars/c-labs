#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <signal.h>

#include "readfile.h"
#include "findreg.h"

#define BUF_SIZE 1024 * 5
// #define DEBUGMODEMAIN

char *buf_file = NULL;

void sigurg_function()
{
    free(buf_file);
    buf_file = NULL;
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return EXIT_FAILURE;
    }
    (void)argv;

    buf_file = (char *)malloc(BUF_SIZE);
    if (buf_file != NULL)
    {

        int tcp_socket, tmp_socket, port;
        struct sockaddr_in serv_addr, cli_addr;

        readfile(argv[1], buf_file, BUF_SIZE - 1);

#ifdef DEBUGMODEMAIN
        printf("%s", buf_file);
#endif

        tcp_socket = socket(AF_INET, SOCK_STREAM, 0);

        if (tcp_socket < 0)
        {
            fprintf(stderr, "socket() failed: %d\n", errno);
            return EXIT_FAILURE;
        }

        memset((char *)&serv_addr, 0, sizeof(serv_addr));
        port = 5555;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        serv_addr.sin_port = htons(port);

        if (bind(tcp_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            fprintf(stderr, "bind() failed: %d\n", errno);
            return EXIT_FAILURE;
        }

        listen(tcp_socket, 1);

        while (true)
        {
            int clen = sizeof(cli_addr);
            memset((char *)&cli_addr, 0, sizeof(cli_addr));
            tmp_socket = accept(tcp_socket, (struct sockaddr *)&cli_addr, &clen);
            if (tmp_socket < 0)
            {
                fprintf(stderr, "accept() failed: %d\n", errno);
                return EXIT_FAILURE;
            }

            switch (fork())
            {
            case -1:
                fprintf(stderr, "fork() failed: %d\n", errno);
                break;

            case 0:
                close(tcp_socket);
                while (true)
                {
                    char num[4];
                    char reg_name[256];
                    memset(num, 0, 4);
                    memset(reg_name, 0, 4);
                    int length = recv(tmp_socket, num, 3, 0);
                    if (-1 == length)
                    {
                        fprintf(stderr, "recv from socket failed: %d\n", errno);
                        break;
                    }
                    num[length] = 0;

                    findreg(buf_file, num, reg_name);
                    #ifdef DEBUGMODEMAIN
                    printf("%s", reg_name);
                    #endif

                    if (send(tmp_socket, reg_name, sizeof(reg_name), 0) == -1)
                    {
                        fprintf(stderr, "send() failed: %d\n", errno);
                    }
                    break;
                }
                close(tmp_socket);
                return EXIT_SUCCESS;

            default:
                close(tmp_socket);
            }
        }
        close(tcp_socket);
    }
    else
    {
        fprintf(stderr, "malloc error: %d\n", errno);
        return EXIT_FAILURE;
    }

    struct sigaction sigurg_action;
    memset(&sigurg_action, 0, sizeof(sigurg_action));
    sigurg_action.sa_handler = sigurg_function;
    sigaction(SIGINT, &sigurg_action, 0);

    free(buf_file);
    buf_file = NULL;



    return EXIT_SUCCESS;
}
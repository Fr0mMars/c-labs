#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define BUF_SIZE 256

int main(int argc, char *argv[])
{
    int sock, port;
    struct sockaddr_in serv_addr;
    char buf[BUF_SIZE];

    if (argc != 2) 
    {
       fprintf(stderr,"Usage: %s <region-number>\n", argv[0]);
       return EXIT_FAILURE;
    }
    char *reg_num = argv[1];
    port = 5555;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
      printf("socket() failed: %d", errno);
      return EXIT_FAILURE;
    }
    
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    serv_addr.sin_port = htons(port);
    if (connect(sock, (const struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) 
    {
      printf("connect() failed: %d", errno);
      return EXIT_FAILURE;
    }
    printf(">");
    //memset(buf, 0, BUF_SIZE);
    //strncpy(buf, reg_num, sizeof(reg_num));
    if (send(sock, reg_num, sizeof(reg_num), 0) == -1)
        {
            fprintf(stderr, "send() failed: %d\n", errno);
        }
    memset(buf, 0, BUF_SIZE);
    if (recv(sock, buf, BUF_SIZE-1, 0) == -1)
        {
            fprintf(stderr, "recv() failed: %d\n", errno);
        }
    printf("%s\n",buf);
    close(sock);
    return EXIT_SUCCESS;
}

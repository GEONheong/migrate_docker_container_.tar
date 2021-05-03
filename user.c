#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define SERVERIP "127.0.0.1"

int main(int argc, char *argv[])
{
    int sock;
    int con_len;
    struct sockaddr_in con_addr;
    char sendMsg[256];
    //char *sendMsg = "migrate crazy_orange 1 2";
    char recvMsg[100];

    con_len = sizeof(con_addr);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("sock error");
        exit(1);
    }

    con_addr.sin_family = AF_INET;
    con_addr.sin_addr.s_addr = inet_addr(SERVERIP);
    con_addr.sin_port = htons(atoi(argv[1]));

    if ((connect(sock, (struct sockaddr *)&con_addr, con_len)) == -1)
    {
        perror("connect error");
        exit(1);
    }
    else
    {
        printf("controller connect\n");
    }

    printf("Input Command : ");
    gets(sendMsg);
    send(sock, sendMsg, strlen(sendMsg) + 1, 0);
    printf("sendMsg : %s\n", sendMsg);
    recv(sock, recvMsg, sizeof(recvMsg), 0);
    printf("recvMsg : %s\n", recvMsg);

    close(sock);

    return 0;
}
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>

typedef struct {
    int id;
    char msg[10000];
} client;

client clients[1024];
int current_id = 0;
int maxfd = 0;

fd_set read_set;
fd_set write_set;
fd_set current;

char send_buffer[10000];
char recv_buffer[10000];

void putstr(int fd, char *str) {
    int i = 0;
    while(str[i])
        write(fd, &str[i++], 1);
}

void err(char *msg) {
    if (!msg)
        putstr(2, "Fatal error\n");
    else
        putstr(2, msg);
    exit(1);
}

void broadcast(int sender, char *msg, int sockfd) {
    for (int fd = 0; fd <= maxfd; fd++) {
        if (FD_ISSET(fd, &current) && fd != sockfd && fd != sender)
            send(fd, msg, strlen(msg), 0);
    }
}

void remove_client(int fd, int sockfd) {
    sprintf(send_buffer, "server: client %d just left\n", clients[fd].id);
    broadcast(fd, send_buffer, sockfd);
    FD_CLR(fd, &current);
    close(fd);
}

int main(int argc, char** argv) {
    if (argc != 2)
        err("Wrong number of arguments\n");
    int sockfd, connfd;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        err(NULL);
    FD_ZERO(&current);
    FD_SET(sockfd, &current);
    maxfd = sockfd;

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(2130706433);
    servaddr.sin_port = htons(atoi(argv[1]));

    if (bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) != 0)
        err(NULL);

    if (listen(sockfd, 10) != 0)
        err(NULL);
    
    while(1) {
        read_set = current;
        if (select(maxfd + 1, &read_set, NULL, NULL, NULL) == -1)
            err(NULL);
        for(int fd = 0; fd <= maxfd; fd++) {
            if (FD_ISSET(fd, &read_set)) {
                if (fd == sockfd) {
                    struct sockaddr_in cli;
                    bzero(&cli, sizeof(cli));
                    socklen_t len = sizeof(cli);
                    connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
                    if (connfd < 0)
                        err(NULL);
                    if (connfd > maxfd)
                        maxfd = connfd;
                    clients[connfd].id = current_id;
                    bzero(clients[connfd].msg, 10000);
                    current_id++;
                    FD_SET(connfd, &current);
                    sprintf(send_buffer, "server: client %d just arrived\n", clients[connfd].id);
                    // Broadcast, except to new client
                    broadcast(connfd, send_buffer, sockfd);
                } else {
                    int ret = recv(fd, recv_buffer, 10000, 0);
                    if (ret <= 0) {
                        remove_client(fd, sockfd);
                    } else {
                        int j = strlen(clients[fd].msg);
                        for(int i = 0; i < ret; i++, j++) {
                            clients[fd].msg[j] = recv_buffer[i];
                            if (clients[fd].msg[j] == '\n') {
                                clients[fd].msg[j] = '\0';
                                sprintf(send_buffer, "client %d: %s\n", clients[fd].id, clients[fd].msg);
                                // Broadcast, except to remetente
                                broadcast(fd, send_buffer, sockfd);
                                bzero(clients[fd].msg, 10000);
                                j = -1;
                            }
                        }
                    }
                }
            }
        }
    }
}
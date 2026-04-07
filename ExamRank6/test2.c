#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>

fd_set cur;
int maxfd = 0;
int ids = 0;
int cid[1024];
int clenmsg[1024];
char buf[4096];
char tmp[4096];
char msg[1024][4096];

void die(char *s) {
    write(2, s, strlen(s));
    exit(1);
}

void bcast(int skip, int skipserver) {
    for (int fd = 0; fd <= maxfd; fd++) {
        if (FD_ISSET(fd, &cur) && fd != skip && fd != skipserver)
            send(fd, buf, strlen(buf), 0);
    }
}

int main(int argc, char **argv) {
    if (argc != 2)
        die("Fatal error\n");

    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0)
        die("Fatal error\n");
    //bind
    struct sockaddr_in sa;
    bzero(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(atoi(argv[1]));
    sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (bind(server, (const struct sockaddr *)&sa, sizeof(sa))) {
        close(server);
        die("Fatal error\n");
    }
    //listen
    if (listen(server, 10)) {
        close(server);
        die("Fatal error\n");
    }
    FD_ZERO(&cur);
    FD_SET(server, &cur);
    maxfd = server;
    while(1) {
        fd_set snapshot = cur;
        if (select(maxfd + 1, &snapshot, 0, 0, 0) == -1) {
            for(int i = 0; i <= maxfd; i++) {
                if (FD_ISSET(i, &snapshot))
                    close(i);
                exit(0);
            }
        }
        for(int fd = 0; fd <= maxfd; fd++) {
            if (!FD_ISSET(fd, &snapshot)) continue;
            if (fd == server) {
                int c = accept(fd, 0,0);
                if (c < 0)
                    die("Fatal error\n");
                if (c > maxfd) maxfd = c;
                cid[c] = ids++;
                clenmsg[c] = 0;
                FD_SET(c, &cur);
                sprintf(buf, "server: client %d just arrived\n", cid[c]);
                bcast(c, server);
            } else {
                int r = recv(fd, tmp, sizeof(tmp), 0);
                if (r <= 0) {
                    sprintf(buf, "server: client %d just left\n", cid[fd]);
                    bcast(fd, server);
                    FD_CLR(fd, &cur);
                    close(fd);
                } else {
                    int j = clenmsg[fd];
                    for(int i = 0; i < r; i++) {
                        msg[fd][j] = tmp[i];
                        if (tmp[i] == '\n') {
                            msg[fd][i] = '\0';
                            sprintf(buf, "client %d: %s\n", cid[fd], msg[fd]);
                            bcast(fd, server);
                            j = 0;
                        } else {
                            j++;
                        }
                    }
                    clenmsg[fd] = j;
                }
            }
        }
    }
}
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

int     maxfd, ids;
fd_set  cur;
char    buf[110000];
char    tmp[110001];
char    msg[1024][110000];
int     cid[1024], mlen[1024];

void    die(char *s) { write(2, s, strlen(s)); exit(1); }

void    bcast(int skip, int srv) {
    for (int i = 0; i <= maxfd; i++)
        if (FD_ISSET(i, &cur) && i != skip && i != srv)
            send(i, buf, strlen(buf), 0);
}
int main(int argc, char **argv) {
    if (argc != 2)
        die("Wrong number of arguments\n");

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
                mlen[c] = 0;
                FD_SET(c, &cur);
                sprintf(buf, "server: client %d just arrived\n", cid[c]);
                bcast(c, server);
            } else {
                int r = recv(fd, tmp, 110000, 0);
                if (r <= 0) {
                    sprintf(buf, "server: client %d just left\n", cid[fd]);
                    bcast(fd, server);
                    FD_CLR(fd, &cur);
                    close(fd);
                } else {
                    int j = mlen[fd];
                    for (int i = 0; i < r; i++) {
                        msg[fd][j] = tmp[i];
                        if (tmp[i] == '\n') {
                            msg[fd][j] = '\0';
                            sprintf(buf, "client %d: ", cid[fd]);
                            bcast(fd, server);
                            sprintf(buf, "%s\n", msg[fd]);
                            bcast(fd, server);
                            j = 0;
                        } else j++;
                    }
                    mlen[fd] = j;
                }
            }
        }
    }
}
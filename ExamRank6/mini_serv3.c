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
char    buf[4096];
char    tmp[4096];
char    msg[1024][4096];
int     mid[1024], mlen[1024];

void    die(char *s) { write(2, s, strlen(s)); exit(1); }

void    bcast(int skip, int srv) {
    for (int i = 0; i <= maxfd; i++)
        if (FD_ISSET(i, &cur) && i != skip && i != srv)
            send(i, buf, strlen(buf), 0);
}

int main(int ac, char **av) {
    if (ac != 2) die("Wrong number of arguments\n");

    int srv = socket(AF_INET, SOCK_STREAM, 0);
    if (srv < 0) die("Fatal error\n");

    struct sockaddr_in sa;
    bzero(&sa, sizeof(sa));
    sa.sin_family      = AF_INET;
    sa.sin_addr.s_addr = htonl(0x7F000001);
    sa.sin_port        = htons(atoi(av[1]));

    if (bind(srv, (struct sockaddr*)&sa, sizeof(sa))) die("Fatal error\n");
    if (listen(srv, 10)) die("Fatal error\n");

    FD_ZERO(&cur);
    FD_SET(srv, &cur);
    maxfd = srv;

    while (1) {
        fd_set rd = cur;
        if (select(maxfd + 1, &rd, 0, 0, 0) == -1) {
            if (errno == EINTR) {
                for (int i = 0; i <= maxfd; i++)
                    if (FD_ISSET(i, &cur)) close(i);
                exit(0);
            }
        }
        for (int fd = 0; fd <= maxfd; fd++) {
            if (!FD_ISSET(fd, &rd)) continue;
            if (fd == srv) {
                int c = accept(srv, 0, 0);
                if (c < 0) die("Fatal error\n");
                if (c > maxfd) maxfd = c;
                mid[c]  = ids++;
                mlen[c] = 0;
                FD_SET(c, &cur);
                sprintf(buf, "server: client %d just arrived\n", mid[c]);
                bcast(c, srv);
            } else {
                int r = recv(fd, tmp, sizeof(tmp), 0);
                if (r <= 0) {
                    sprintf(buf, "server: client %d just left\n", mid[fd]);
                    bcast(fd, srv);
                    FD_CLR(fd, &cur);
                    close(fd);
                } else {
                    int j = mlen[fd];
                    for (int i = 0; i < r; i++) {
                        msg[fd][j] = tmp[i];
                        if (tmp[i] == '\n') {
                            msg[fd][j] = '\0';
                            sprintf(buf, "client %d: %s\n", mid[fd], msg[fd]);
                            bcast(fd, srv);
                            j = 0;
                        } else j++;
                    }
                    mlen[fd] = j;
                }
            }
        }
    }
}
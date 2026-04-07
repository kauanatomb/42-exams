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
char buf[4096];
char tmp[4096];
char *msg[1024];

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

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
                FD_SET(c, &cur);
                sprintf(buf, "server: client %d just arrived\n", cid[c]);
                bcast(c, server);
            } else {
                int r = recv(fd, tmp, sizeof(tmp), 0);
                if (r <= 0) {
                    sprintf(buf, "server: client %d just left\n", cid[fd]);
                    bcast(fd, server);
                    FD_CLR(fd, &cur);
                    free(msg[fd]);
                    msg[fd] = NULL;
                    close(fd);
                } else {
                    tmp[r] = '\0';
                    msg[fd] = str_join(msg[fd], tmp);
                    char *line;
                    while (extract_message(&msg[fd], &line)) {
                        sprintf(buf, "client %d: %s", cid[fd], line);
                        bcast(fd, server);
                        free(line);
                    }
                }
            }
        }
    }
}
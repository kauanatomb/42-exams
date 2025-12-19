#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void fill_board(char *board, int w, int h) {
    int x = 0, y = 0;
    int draw = 0;
    char c;

    while(read(0, &c, 1) == 1) {
        if (c == 'w' && y > 0) y--;
        else if (c == 's' && y < h - 1) y++;
        else if (c == 'a' && x > 0) x--;
        else if (c == 'd' && x < w - 1) x++;
        else if (c == 'x') draw = !draw;

        if (draw)
            board[y * w + x] = 'O';
    }
}

int count_neighbors(char *b, int w, int h, int x, int y) {
    int c = 0;
    for(int dy = -1; dy <= 1; dy++) {
        for(int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0)
                continue;
            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && ny >= 0 && nx < w && ny < h)
                if (b[ny * w + nx] == 'O')
                    c++;
        }
    }
    return c;
}

void step(char *b, char *n, int w, int h) {
    for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
            int alive = (b[y * w + x] == 'O');
            int nb = count_neighbors(b, w, h, x, y);
            if (alive && (nb == 2 || nb == 3))
                n[y* w + x] = 'O';
            else if (!alive && nb == 3)
                n[y* w + x] = 'O';
            else
                n[y * w + x] = ' ';
        }
    }
}

void print_board(char *b, int w, int h) {
    for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++)
            putchar(b[y * w + x]);
        putchar('\n');
    }
}

int main(int argc, char **argv) {
    if (argc != 4)
        return 1;
    int w = atoi(argv[1]);
    int h = atoi(argv[2]);
    int it = atoi(argv[3]);

    char *board = calloc(w * h, 1);
    char *next = malloc(w * h);

    if (!board || !next)
        return 1;

    for(int i = 0; i < w * h; i++)
        board[i] = ' ';
    fill_board(board, w, h);

    for(int i = 0; i < it; i++) {
        step(board, next, w, h);
        char *tmp = board;
        board = next;
        next = tmp;
    }
    print_board(board, w, h);

    free(board);
    free(next);
    return 0;
}
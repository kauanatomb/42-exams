#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

// board in 1D - practical

void fill_board(char *board, int w, int h) {
    int j = 0, i = 0;
    int draw = 0;
    char c;

    while(read(0, &c, 1) == 1) {
        if (c == 'w' && i > 0) i--;
        else if (c == 's' && i < h - 1) i++;
        else if (c == 'a' && j > 0) j--;
        else if (c == 'd' && j < w - 1) j++;
        else if (c == 'x') draw = !draw;

        if (draw)
            board[i * w + j] = 'O';
    }
}

int count_neighbors(char *b, int w, int h, int j, int i) {
    int c = 0;
    for(int di = -1; di <= 1; di++) {
        for(int dj = -1; dj <= 1; dj++) {
            if (dj == 0 && di == 0)
                continue;
            int ni = i + di;
            int nj = j + dj;
            if (nj >= 0 && ni >= 0 && nj < w && ni < h)
                if (b[ni * w + nj] == 'O')
                    c++;
        }
    }
    return c;
}

void step(char *b, char *n, int w, int h) {
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            int alive = (b[i * w + j] == 'O');
            int nb = count_neighbors(b, w, h, j, i);
            if (alive && (nb == 2 || nb == 3))
                n[i * w + j] = 'O';
            else if (!alive && nb == 3)
                n[i * w + j] = 'O';
            else
                n[i * w + j] = ' ';
        }
    }
}

void print_board(char *b, int w, int h) {
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++)
            putchar(b[i * w + j]);
        putchar('\n');
    }
}

int main(int argc, char **argv) {
    if (argc != 4)
        return 1;
    int w = atoi(argv[1]);
    int h = atoi(argv[2]);
    int it = atoi(argv[3]);

    char *board = calloc(w * h, sizeof(char));
    if (!board)
        return 1;
    char *next = calloc(w * h, sizeof(char));
    if (!next)
        return free(board), 1;

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
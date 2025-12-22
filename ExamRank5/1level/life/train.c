#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void fill_board(char *board, int h, int w) {
    int i =0, j = 0, draw = 0;
    char c;
    while(read(0, &c, 1) == 1) {
        if (c == 'w' && i > 0) i--;
        else if (c == 'a' && j > 0) j--;
        else if (c == 's' && i < h -1) i++;
        else if (c == 'd' && j < w -1) j++;
        else if (c == 'x') draw = !draw;

        if (draw)
            board[i * w + j] = 'O';
    }
}

void print_board(char *b, int h, int w) {
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            putchar(b[i * w + j]);
        }
        putchar('\n');
    }
}

int count_neighbours(char *b, int h, int w, int i, int j) {
    int c = 0;
    for(int di = -1; di <= 1; di++) {
        for(int dj = -1; dj <= 1; dj++) {
            if (di == 0 && dj == 0)
                continue;
            int ni = i + di;
            int nj = j + dj;
            if (ni >= 0 && nj >= 0 && ni < h && nj < w) {
                if (b[ni *w + nj] == 'O')
                    c++;
            }
        }
    }
    return c;
}

void step(char *board, int h, int w, char *next) {
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            int alive = board[i * w + j] == 'O';
            int nb = count_neighbours(board, h, w, i, j);
            if (alive && (nb == 2 || nb == 3))
                next[i * w + j] = 'O';
            else if (!alive && nb == 3)
                next[i * w + j] = 'O';
            else
                next[i * w + j] = ' ';
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 4)
        return 1;
    int w = atoi(argv[1]);
    int h = atoi(argv[2]);
    int it = atoi(argv[3]);

    char *board = calloc(h * w, sizeof(char));
    if (!board)
        return 1;
    char *next = calloc(h * w, sizeof(char));
    if(!next)
        return free(board), 1;
    for(int k = 0; k < w * h; k++)
        board[k] = ' ';
    fill_board(board, h, w);
    for(int k = 0; k < it; k++) {
        step(board, h, w, next);
        char *tmp = board;
        board = next;
        next = tmp;
    }
    print_board(board, h, w);
    free(board);
    free(next);
    return 0;
}
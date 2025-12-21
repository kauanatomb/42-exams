#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

// board in 2D - more to allocate, increase complexibility

int count_neighbors(char **b, int w, int h, int i, int j)
{
    int count = 0;

    for (int di = -1; di <= 1; di++)
        for (int dj = -1; dj <= 1; dj++)
        {
            if (di == 0 && dj == 0)
                continue;

            int ni = i + di;
            int nj = j + dj;

            if (ni >= 0 && nj >= 0 && ni < h && nj < w)
                if (b[ni][nj] == 'O')
                    count++;
        }
    return count;
}


void fill_board(char **board, int w, int h)
{
    int j = 0, i = 0;
    int draw = 0;
    char c;

    while (read(0, &c, 1) == 1)
    {
        if (c == 'w' && i > 0) i--;
        else if (c == 's' && i < h - 1) i++;
        else if (c == 'a' && j > 0) j--;
        else if (c == 'd' && j < w - 1) j++;
        else if (c == 'x') draw = !draw;

        if (draw)
            board[i][j] = 'O';
    }
}

void step(char **b, char **n, int w, int h) {
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            int alive = (b[i][j] == 'O');
            int nb = count_neighbors(b, w, h, i, j);
            if (alive && (nb == 2 || nb == 3))
                n[i][j] = 'O';
            else if (!alive && nb == 3)
                n[i][j] = 'O';
            else
                n[i][j] = ' ';
        }
    }
}

void print_board(char **b, int w, int h) {
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++)
            putchar(b[i][j]);
        putchar('\n');
    }
}

int error_and_free(char **board, char **next, int height, int is_error) {
    if (board) {
        for(int i = 0; i < height; i++) {
            if (board[i])
                free(board[i]);
            if (next && next[i])
                free(next[i]);
        }
        free(board);
    }
    if (next) free(next);
    if (is_error)
        return 1;
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 4)
        return 1;
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int iteration = atoi(argv[3]);
    char **board = NULL;
    char **next = NULL;

    board = calloc(height, sizeof(char *));
    if (!board)
        return 1;
    next = calloc(height, sizeof(char *));
    if (!next)
        return error_and_free(board, next, height, 1);
    for(int i = 0; i < height; i++) {
        board[i] = calloc(width, sizeof(char));
        if (!board[i])
            return error_and_free(board, next, height, 1);
        next[i] = calloc(width, sizeof(char));
        if (!next[i])
            return error_and_free(board, next, height, 1);
        for(int j = 0; j < width; j++)
            board[i][j] = ' ';
    }

    fill_board(board, width, height);

    for(int i = 0; i < iteration; i++) {
        step(board, next, width, height);
        char **tmp = board;
        board = next;
        next = tmp;
    }
    print_board(board, width, height);

    return error_and_free(board, next, height, 0);
}
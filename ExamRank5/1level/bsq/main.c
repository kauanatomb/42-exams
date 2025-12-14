#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min3(int a, int b, int c) {
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

int main(int argc, char **argv) {
    FILE *file = stdin;
    // deal with more than one map
    if (argc > 1) {
        file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "map error\n");
            return 1;
        }
    }

    // header
    int height;
    char empty, obstacle, full;
    if (fscanf(file, "%d %c %c %c\n", &height, &empty, &obstacle, &full) != 4 || height <= 0) {
        fprintf(stderr, "map error\n");
        return 1;
    }
    // TODO : have header rules here

    // width first line
    char *line = NULL;
    size_t len = 0;

    if (getline(&line, &len, file) == -1) { fprintf(stderr, "map error\n"); return 1; }
    int width = strlen(line);
    if (line[width-1] == '\n') line[--width] = 0;

    // allocate
    int *dp = calloc(width, sizeof(int));
    if (!dp) return 1;
    char **map = malloc(height * sizeof(char*));
    if (!map) return 1;

    int best_size = 0, best_i = 0, best_j = 0;

    for (int i = 0; i < height; i++) {
        if (i > 0) {
            if (getline(&line, &len, file) == -1)
                return 1;
            int read = strlen(line);
            if (line[read - 1] == '\n') line[--read] = 0;
            if (read != width)
                return 1;
        }

        map[i] = malloc(width + 1);
        if (!map[i]) return 1;
        strcpy(map[i], line); // allowed?

        // dp algorithm
        int prev_diag = 0;
        for (int j = 0; j < width; j++) {
            int temp = dp[j];
            if (map[i][j] == obstacle)
                dp[j] = 0;
            else if (i == 0 || j == 0)
                dp[j] = 1;
            else
                dp[j] = 1 + min3(dp[j], dp[j-1], prev_diag);

            if (dp[j] > best_size) {
                best_size = dp[j];
                best_i = i;
                best_j = j;
            }
            prev_diag = temp;
        }
    }

    // full square
    for (int i = best_i - best_size + 1; i <= best_i; i++)
        for (int j = best_j - best_size + 1; j <= best_j; j++)
            map[i][j] = full;

    // print
    for (int i = 0; i < height; i++) {
        printf("%s\n", map[i]);
        free(map[i]);
    }

    free(map);
    free(dp);
    free(line);
    if (file != stdin) fclose(file);

    return 0;
}

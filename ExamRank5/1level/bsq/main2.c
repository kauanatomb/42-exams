#include <stdio.h>
#include <stdlib.h>

int map_error() {
    fprintf(stderr, "map error\n");
    return 1;
}

int msg_error() {
    fprintf(stderr, "Error: malloc\n");
    return 1;
}

int process_header(FILE *file, int* height, char* full, char* empty, char *obstacle) {
    int read = fscanf(file, "%d%c%c%c\n", height, empty, obstacle, full);
    if (read != 4 || *height <= 0)
        return 1;
    if (*full == *obstacle || *full == *empty || *obstacle == *empty)
        return 1;
    if (*full < 32 || *full > 126 || *empty < 32 || *empty > 126 || *obstacle < 32 || *obstacle > 126)
        return 1;
    return 0;
}

int error_and_free(char **map, int **dp, int height, char *line, int is_map) {
    if (map) {
        for(int i = 0; i < height; i++) {
            if (map[i])
                free(map[i]);
            if (dp && dp[i])
                free(dp[i]);
        }
    }
    if (map) free(map);
    if (dp) free(dp);
    if (line) free(line);
    if (is_map)
        return map_error();
    else
        return msg_error();
}

int min3(int a, int b, int c) {
    int min = a;
    if (min > b) min = b;
    if (min > c) min = c;
    return min;
}

void full_map(char **map, int best_size, int best_i, int best_j, char full) {
    for(int i = best_i - best_size + 1; i <= best_i; i++)
        for(int j = best_j - best_size + 1; j <= best_j; j++)
            map[i][j] = full;
}

void printmap_and_free(char **map, int **dp, int height) {
    for(int i = 0; i < height; i++) {
        fprintf(stdout, "%s\n", map[i]);
        free(map[i]);
        free(dp[i]);
    }
}

int process_map(FILE *file) {
    int height;
    char full, empty, obstacle;
    char **map;
    int **dp;
    char *line = NULL;
    size_t cap = 0;
    int width = -1;
    int best_size = 0, best_i = 0, best_j = 0;

    if (process_header(file, &height, &full, &empty, &obstacle))
        return map_error();
    
    map = calloc(height, sizeof(char *));
    if (!map)
        return msg_error();
    dp = calloc(height, sizeof(int *));
    if (!dp)
        return error_and_free(map, dp, height, line, 0);
    
    for(int i = 0; i < height; i++) {
        ssize_t read = getline(&line, &cap, file);
        if (read <= 0)
            return error_and_free(map, dp, height, line, 0);
        if (line[read -1] != '\n')
            return error_and_free(map, dp, height, line, 1);
        line[read -1] = 0;
        --read;
        if (width == -1)
            width = read;
        else if (width != read)
            return error_and_free(map, dp, height, line, 1);
        map[i] = calloc(width + 1, sizeof(char));
        if (!map[i])
            return error_and_free(map, dp, height, line, 0);
        dp[i] = calloc(width, sizeof(int));
        if (!dp[i])
            return error_and_free(map, dp, height, line, 0);
        
        for(int k = 0; k < width; k++)
            map[i][k] = line[k];
        for(int j = 0; j < width; j++) {
            if (map[i][j] != empty && map[i][j] != obstacle)
                return error_and_free(map, dp, height, line, 1);
            if (map[i][j] == obstacle)
                dp[i][j] = 0;
            else if (i == 0 || j == 0)
                dp[i][j] = 1;
            else
                dp[i][j] = 1 + min3(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]);
            
            if (dp[i][j] > best_size) {
                best_size = dp[i][j];
                best_i = i;
                best_j = j;
            }
        }
    }
    full_map(map, best_size, best_i, best_j, full);
    printmap_and_free(map, dp, height);

    free(map);
    free(dp);
    free(line);
    return 0;
}

int main (int argc, char **argv) {
    if (argc == 1) {
        if (process_map(stdin))
            return 1;
    }
    else {
        FILE *file = fopen(argv[1], "r");
        if (!file)
            return map_error();
        process_map(file);
        fclose(file);
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	min3(int a, int b, int c)
{
	int m = a;
	if (b < m) m = b;
	if (c < m) m = c;
	return m;
}

static int	map_error(void)
{
	fprintf(stderr, "map error\n");
	return 1;
}

static int	msg_error(void)
{
	fprintf(stderr, "Error: malloc or get next line\n");
	return 1;
}

static int	map_error_and_free(char **map, int size, int **dp, char *line, int is_map)
{
    if (map)
    {
        for (int i = 0; i < size; i++)
        {
            if (map[i])
                free(map[i]);
			if (dp && dp[i])
				free(dp[i]);
        }    
        free(map);
    }
    if (dp) free(dp);
    if (line) free(line);
	if (is_map)
		return map_error();
	else
		return msg_error();
}

int validate_header(FILE *file, int *height, char *obstacle, char *full, char *empty)
{
    if (fscanf(file, "%d%c%c%c\n",
			height, empty, obstacle, full) != 4 || *height <= 0)
            return 1;
    if (*full > 126 || *full < 32)
        return 1;
    if (*obstacle > 126 || *obstacle < 32)
        return 1;
    if (*empty > 126 || *empty < 32)
        return 1;
    if (*full == *obstacle || *full == *empty || *obstacle == *empty)
        return 1;
    return 0;
}

void draw_square_on_map(char **map, char full, int best_i, int best_size, int best_j) {
	for (int i = best_i - best_size + 1; i <= best_i; i++)
		for (int j = best_j - best_size + 1; j <= best_j; j++)
			map[i][j] = full;
}

void print_map_and_free(char **map, int **dp, int height) {
	for (int i = 0; i < height; i++)
	{
		fprintf(stdout, "%s\n", map[i]);
		free(map[i]);
		free(dp[i]);
	}
}

int process_map(FILE *file)
{
	int height;
    char obstacle, full, empty;
    char **map = NULL;
    int **dp = NULL;
    char *line = NULL;
    size_t cap = 0;
    int width = -1;
    int best_size = 0, best_i = 0, best_j = 0;

    if (validate_header(file, &height, &obstacle, &full, &empty))
        return map_error();

    map = calloc(height, sizeof(char *));
	if (!map)
		return msg_error();

	dp = calloc(height, sizeof(int *));
	if (!dp)
		return map_error_and_free(map, height, dp, line, 0); // malloc

	/* main loop: read + validate + dp */
	for (int i = 0; i < height; i++)
	{
		ssize_t n = getline(&line, &cap, file);
		if (n <= 0)
			return map_error_and_free(map, height, dp, line, 0); // get next line

		if (line[n - 1] != '\n')
            return map_error_and_free(map, height, dp, line, 1);
        else
			line[--n] = 0;

		if (width == -1)
			width = n;
		else if (n != width)
			return map_error_and_free(map, height, dp, line, 1);
		dp[i] = calloc(width, sizeof(int));
		if (!dp[i])
			return map_error_and_free(map, height, dp, line, 0); // malloc

		map[i] = malloc(width + 1);
		if (!map[i])
			return map_error_and_free(map, height, dp, line, 0); // malloc
		for (int k = 0; k <= width; k++)
    		map[i][k] = line[k];

		for (int j = 0; j < width; j++)
		{
			if (map[i][j] != obstacle && map[i][j] != empty)
                return map_error_and_free(map, height, dp, line, 1);
			else if (map[i][j] == obstacle)
				dp[i][j] = 0;
			else if (i == 0 || j == 0)
				dp[i][j] = 1;
            else
				dp[i][j] = 1 + min3(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]);

			if (dp[i][j] > best_size)
			{
				best_size = dp[i][j];
				best_i = i;
				best_j = j;
			}
		}
	}

	draw_square_on_map(map, full, best_i, best_size, best_j);

	print_map_and_free(map, dp, height);

	free(map);
	free(dp);
	free(line);
	return 0;
}

int	main(int argc, char **argv)
{
    if (argc == 1)
    {
        if (process_map(stdin))
            return 1;
        return 0;
    }
	FILE *file = fopen(argv[1], "r");
	if (!file)
		return map_error();
	else {
		process_map(file);
		fclose(file);
	}
	return 0;
}


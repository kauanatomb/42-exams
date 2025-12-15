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

static int	map_error_and_free(char **map, int size, int *dp, char *line)
{
    if (map)
    {
        for (int i = 0; i < size; i++)
        {
            if (map[i])
                free(map[i]);
        }    
        free(map);
    }
    if (dp) free(dp);
    if (line) free(line);
	return map_error();
}

int validate_header(FILE *file, int *height, char *obstacle, char *full, char *empty)
{
    if (fscanf(file, "%d %c %c %c\n",
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

int process_map(FILE *file)
{
	int height;
    char obstacle, full, empty;
    char **map = NULL;
    int *dp = NULL;
    char *line = NULL;
    size_t cap = 0;
    int width = -1;
    int best_size = 0, best_i = 0, best_j = 0;

    if (validate_header(file, &height, &obstacle, &full, &empty))
        return map_error();

    map = calloc(height, sizeof(char *));
	if (!map)
		return 1;

	/* main loop: read + validate + dp */
	for (int i = 0; i < height; i++)
	{
		ssize_t n = getline(&line, &cap, file);
		if (n <= 0)
			return map_error_and_free(map, height, dp, line);

		if (line[n - 1] != '\n')
            return map_error_and_free(map, height, dp, line);
        else
			line[--n] = 0;

		if (width == -1)
		{
			width = n;
			dp = calloc(width, sizeof(int));
			if (!dp)
				return map_error_and_free(map, height, dp, line);
		}
		else if (n != width)
			return map_error_and_free(map, height, dp, line);

		map[i] = malloc(width + 1);
		if (!map[i])
			return map_error_and_free(map, height, dp, line);
		memcpy(map[i], line, width + 1);

		int prev_diag = 0;
		for (int j = 0; j < width; j++)
		{
			int tmp = dp[j];

			if (map[i][j] != obstacle && map[i][j] != empty)
                return map_error_and_free(map, height, dp, line);
			else if (map[i][j] == obstacle)
				dp[j] = 0;
			else if (i == 0 || j == 0)
				dp[j] = 1;
            else
				dp[j] = 1 + min3(dp[j], dp[j - 1], prev_diag);

			if (dp[j] > best_size)
			{
				best_size = dp[j];
				best_i = i;
				best_j = j;
			}
			prev_diag = tmp;
		}
	}

	/* draw square */
	for (int i = best_i - best_size + 1; i <= best_i; i++)
		for (int j = best_j - best_size + 1; j <= best_j; j++)
			map[i][j] = full;

	/* output */
	for (int i = 0; i < height; i++)
	{
		fprintf(stdout, "%s\n", map[i]);
		free(map[i]);
	}

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
	for (int i = 1; i < argc; i++)
	{
		FILE *file = fopen(argv[i], "r");
		if (!file)
			map_error();
		else
		{
			process_map(file);
			fclose(file);
		}
		if (i < argc - 1)
			fprintf(stdout, "\n");
	}
	return 0;
}


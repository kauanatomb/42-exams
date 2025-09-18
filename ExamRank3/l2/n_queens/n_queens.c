#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	abs(int a) { return (a < 0) ? -a : a; }

int	is_safe(int *board, int col, int row)
{
    int prev = 0;
	while (prev < col)
	{
		if (board[prev] == row || abs(board[prev] - row) == col - prev)
			return (0);
        prev++;
	}
	return (1);
}

void	print_board(int *board, int n)
{
    int i = 0;
	while (i < n)
	{
		if (i > 0)
            printf(" ");
		printf("%d", board[i]);
        i++;
	}
    printf("\n");
}

void	backtrack(int *board, int col, int n)
{
	if (col == n)
	{
		print_board(board, n);
		return ;
	}
    int row = 0;
	while (row < n)
	{
		if (is_safe(board, col, row))
		{
			board[col] = row;
			backtrack(board, col + 1, n);
		}
        row++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	int	n = atoi(argv[1]);
	if (n < 1)
		return (0);
	int	*board = malloc(sizeof(int) * n);
	if (!board)
		return (1);
	backtrack(board, 0, n);
	free(board);
    return 0;
}

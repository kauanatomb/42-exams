/*
Write a program that will take one and only one argument s. Your program 
will then read from stdin and write all the cocntent read in stdout except 
that every occurance of s must be repalced by * as many as the length of s. 
Your program will be tested with random buffer sizes using a custom
read function therefore the buffer being set in your program will be filled with 
a different number of chars each new call.

For example:

./filter hello
sed 's/hello*****g'

*/
/*

more generally your program must be the equivallent of the shell script filter.sh 
present in this directory you can compare your program with it. 
In case of error during a read or a malloc you must write 
"Error: " followed by the error message in stderr and return 1. 
If the program is called without arguments or with an empty argument or with multiple
arguments it must return 1.

For exampl this should work:

$> echo 'abcdefaaaabcdabcabcdabc' | ./filter abc | cat -e
***defaaa***de******d***$

$> echo 'ababcabababc' | ./filter ababc | cat -e
*****ab*****$
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

# define BUF_SIZE 4

int	match_str(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if (*str2 == '\0')
		return (1);
	return (0);
}

void	print_starts(int size)
{
	while (size--)
		write(1, "*", 1);
}

int	main(int argc, char *argv[])
{
	if (argc != 2 || argv[1][0] == '\0')
		return (1);
	char	buf[BUF_SIZE];
	char	*leftover = NULL;
	int		needle_len = strlen(argv[1]);
	int		rd;

	while ((rd = read(0, buf, BUF_SIZE)) > 0)
	{
		int left_len = leftover ? strlen(leftover) : 0;
		int total = left_len + rd;
		char	*tmp = malloc(total + 1);
		if (!tmp)
		{
			fprintf(stderr, "Error %s\n", strerror(errno));
			free(leftover);
			return (1);
		}
		if (leftover)
		{
			memcpy(tmp, leftover, left_len);
			free(leftover);
		}
		memcpy(tmp + left_len, buf, rd);
		tmp[total] = '\0';
		printf("tmp: %s\n", tmp);

		int i = 0;
		while (i <= total - needle_len)
		{
			if (match_str(&tmp[i], argv[1]))
			{
				print_starts(needle_len);
				i += needle_len;
			}
			else
				write(1, &tmp[i++], 1);
		}
		leftover = malloc(total + 1 - i);
		if (!leftover)
		{
			fprintf(stderr, "Error %s\n", strerror(errno));
			free(tmp);
			return (1);
		}
		memcpy(leftover, &tmp[i], total - i);
		leftover[total - i] = '\0';
		free(tmp);
		printf("leftover: %s\n", leftover);
	}
	return (0);
}
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define BUF_SIZE 32

int	match_str(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s2 == '\0');
}

void print_stars(int n)
{
	while (n--)
		write(1, "*", 1);
}

int main(int ac, char **av)
{
	if (ac != 2 || av[1][0] == '\0')
		return (1);

	char	buf[BUF_SIZE];
	char	*left = NULL;
	int		nlen = strlen(av[1]);
	int		rd;

	while ((rd = read(0, buf, BUF_SIZE)) > 0)
	{
		int	left_len = left ? strlen(left) : 0;
		int	total = left_len + rd;
		char	*tmp = malloc(total + 1);
		if (!tmp)
		{
			fprintf(stderr, "Error: %s\n", strerror(errno));
			free(left);
			return (1);
		}
		if (left)
		{
			memcpy(tmp, left, left_len);
			free(left);
		}
		memcpy(tmp + left_len, buf, rd);
		tmp[total] = '\0';

		int	i = 0;
		while (i <= total - nlen)
		{
			if (match_str(&tmp[i], av[1]))
			{
				print_stars(nlen);
				i += nlen;
			}
			else
				write(1, &tmp[i++], 1);
		}
		// guarda o final potencialmente incompleto
		left = malloc(total - i + 1);
		if (!left)
		{
			fprintf(stderr, "Error: %s\n", strerror(errno));
			free(tmp);
			return (1);
		}
		memcpy(left, &tmp[i], total - i);
		left[total - i] = '\0';
		free(tmp);
	}
	if (rd < 0)
	{
		fprintf(stderr, "Error: %s\n", strerror(errno));
		free(left);
		return (1);
	}
	if (left)
	{
		int i = 0;
		int	len = strlen(left);
		while (i <= len - nlen)
		{
			if (match_str(&left[i], av[1]))
			{
				print_stars(nlen);
				i += nlen;
			}
			else
				write(1, &left[i++], 1);
		}
		write(1, left + i, len - i);
		free(left);
	}
	return (0);
}



/*
Write a function that takes a string, splits it into words, and returns them as
a NULL-terminated array of strings.

A "word" is defined as a part of a string delimited either by spaces/tabs/new
lines, or by the start/end of the string.

Your function must be declared as follows:

char    **ft_split(char *str);
*/
#include <stdlib.h>
#include <stdio.h>
int	count_words(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		while ((*str >= 8 && *str <= 13) || *str == ' ')
			str++;
		if (*str)
		{
			count++;
			while (*str && !((*str >= 8 && *str <= 13) || *str == ' '))
				str++;
		}
	}
	return (count);
}

void    *ft_free(char **strs, int size)
{
    int i = 0;

    while (i < size)
        free(strs[i++]);
    free(strs);
    return (NULL);
}

char	*fill_word(char *start, int size)
{
	int i = 0;
	char *str = malloc(size + 1);
	if (!str)
		return (NULL);
	while (i < size)
	{
		str[i] = start[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char    **ft_split(char *str)
{
	char *start;
	int		i = 0;
    if (!str)
        return (NULL);
    char **result;
	result = malloc((count_words(str) + 1) * sizeof(char *));
    if (!result)
        return (NULL);
	
    while (*str)
    {
	while ((*str >= 8 && *str <= 13) || *str == ' ')
		str++;
	if (*str)
	{
		start = str;
		while (*str && !((*str >= 8 && *str <= 13) || *str == ' '))
			str++;
		result[i] = fill_word(start, str - start);
		if (!result[i])
			ft_free(result, i);
		i++;
	}
    }
	result[i] = NULL;
    return (result);
}

int main()
{
	int i = 0;
	char **result = ft_split(" hello	world ");
	if (!result)
		return (0);
	while (result[i])
		printf("%s\n", result[i++]);
	ft_free(result, i);
	return (0);
}

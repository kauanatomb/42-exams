/*
Write a function that takes a string, splits it into words, and returns them as
a NULL-terminated array of strings.

A "word" is defined as a part of a string delimited either by spaces/tabs/new
lines, or by the start/end of the string.

Your function must be declared as follows:

char    **ft_split(char *str);
*/

int	count_words(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
		{
			count++;
			while (*str && *str != c)
				str++;
		}
	}
	return (count);
}

void    **ft_free(char **strs, int size)
{
    int i = 0;

    while (i < size)
        free(strs[i++]);
    free(strs);
    return (NULL);
}

char    **ft_split(char *str)
{
    if (!str)
        return (NULL);
    char    **result = malloc((count_words(str) + 1) * sizeof(char *));
    if (!result)
        return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktombola <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:44:29 by ktombola          #+#    #+#             */
/*   Updated: 2025/06/16 18:05:22 by ktombola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
*/
#include <stdlib.h>

int	is_space(char c)
{
	return ((c >= 8 && c <= 13) || c == ' ');
}

int	counter(char *str)
{
	int i = 0;
	while (*str)
	{
		while (is_space(*str) && *str)
			str++;
		if (*str)
		{
			while (!is_space(*str) && *str)
				str++;
			i++;
		}
	}
	return (i);
}

char	*fill_words(char *start, int size)
{
	int i = 0;
	char *str = malloc(size + 1);
	if (!str)
		return (NULL);
	while (size > i)
	{
		str[i] = start[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	*free_result(char **str, int size)
{
	int i = 0;
	while (i < size)
	{
		free(str[i++]);
	}
	free(str);
	return (NULL);
}

char	**ft_split_whitespaces(char *str)
{
	if (!str)
		return (NULL);
	int count_words = counter(str);
	char **result = malloc((count_words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	int i = 0;
	char *start;
	while (*str)
	{
		while (is_space(*str) && *str)
			str++;
		start = str;
		if (*str)
		{
			while (!is_space(*str) && *str)
				str++;
			result[i] = fill_words(start, str - start);
			if (!result[i])
				return (free_result(result, i));
			i++;
		}
	}
	result[i] = NULL;
	return (result);
}
/*
int main()
{
	char **result = ft_split_whitespaces("Kauana 		tomb da Sil");
	if (!result)
		return (0);
	int i = 0;
	while (result[i])
	{
		printf("%s\n", result[i++]);
	}
	free_result(result, i);
	return (0);
}
*/

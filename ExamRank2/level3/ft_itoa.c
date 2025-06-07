/**
 * @brief Converts an integer into its corresponding ASCII string representation.
 *
 * This function allocates a new null-terminated string representing 
 * the given integer `n`. Handles negative numbers and zero correctly.
 *
 * Memory for the resulting string is obtained with malloc(3) 
 * and must be freed by the caller.
 * @param n The integer to convert.
 * @return A pointer to the newly allocated string, or NULL if the 
 * allocation fails.
 */
#include <stdio.h>
#include <stdlib.h>

static int	count_int(long n);

char	*ft_itoa(int n)
{
	int	len;
	long	nbr;
	char	*res;
	int		i;

	nbr = n;
	len = count_int(nbr);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	res[len] = '\0';
	if (nbr == 0)
		res[0] = '0';
	if (nbr < 0)
	{
		nbr = -nbr;
		res[0] = '-';
	}
	i = len - 1;
	while (nbr > 0)
	{
		res[i--] = ((nbr % 10) + '0');
		nbr = nbr / 10;
	}
	return (res);
}

static int	count_int(long n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

int main(void)
{
    int num = -12345;
    char *result = ft_itoa(num);
    if (result)
    {
        printf("The integer %d as a string is: %s\n", num, result);
        free(result);
    }
    return 0;
}
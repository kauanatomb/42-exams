/*
Write a function that converts the string argument str (base N <= 16)
to an integer (base 10) and returns it.

The characters recognized in the input are: 0123456789abcdef
Those are, of course, to be trimmed according to the requested base. For
example, base 4 recognizes "0123" and base 16 recognizes "0123456789abcdef".

Uppercase letters must also be recognized: "12fdb3" is the same as "12FDB3".

Minus signs ('-') are interpreted only if they are the first character of the
string.

Your function must be declared as follows:

int	ft_atoi_base(const char *str, int str_base);
*/

int	ft_atoi_base(const char *str, int str_base)
{
	int			result = 0;
	int			sign = 1;
	char		c;

	if (!str || str_base < 2 || str_base > 16)
		return (0);

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;

	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;

	while (*str)
	{
		c = *str;
		if (c >= 'A' && c <= 'F')
			c += 32;

		int val;
		if (c >= '0' && c <= '9')
			val = c - '0';
		else if (c >= 'a' && c <= 'f')
			val = 10 + (c - 'a');
		else
			break;

		if (val >= str_base)
			break;

		result = result * str_base + val;
		str++;
	}
	return (result * sign);
}

#include <stdio.h>
#include <limits.h>
int main(void)
{
    printf("%d\n", ft_atoi_base("   -1a", 16));
    printf("%d\n", ft_atoi_base("1011", 2));
    printf("%d\n", ft_atoi_base("77", 8));
    printf("%d\n", ft_atoi_base("123", 4));
    printf("%d\n", ft_atoi_base("   +FF", 16));
    printf("%d\n", ft_atoi_base("G1", 16));
    return (0);
}

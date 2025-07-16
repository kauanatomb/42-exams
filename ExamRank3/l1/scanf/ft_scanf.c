#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int read_f;
    while ((read_f = fgetc(f)) != EOF)
    {
        if (!isspace(read_f))
        {
            ungetc(read_f, f);
            break ;
        }
    }
    return (1);
}

int match_char(FILE *f, char c)
{
    int read_f = fgetc(f);
    if (read_f == EOF)
        return (-1);
    if ((char)read_f == c)
        return (1);
    if (read_f != EOF)
        ungetc(read_f, f);
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
    int read_f = fgetc(f);
    if (read_f == EOF)
        return (-1);
    char *c = va_arg(ap, char *);
    *c = (char)read_f;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
    int read_f = fgetc(f);
    int res = 0;
    int sign = 1;
    if (read_f == EOF)
        return (-1);
    if (read_f == '+' || read_f == '-')
    {
        if (read_f == '-')
            sign = -1;
        read_f = fgetc(f);
    }
    if (!isdigit(read_f))
    {
        if (read_f != EOF)
            ungetc(read_f, f);
        return (-1);
    }
    while (isdigit(read_f))
    {
        res = res * 10 + (read_f - '0');
        read_f = fgetc(f);
    }
    if (read_f != EOF)
        ungetc(read_f, f);
    int *nbr = va_arg(ap, int *);
    *nbr = res * sign;
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
    int read_f = fgetc(f);
    char *str = va_arg(ap, char *);
    int i = 0;
    if (read_f == EOF)
        return (-1);
    while (read_f != EOF && !isspace(read_f))
    {
        str[i++] = (char)read_f;
        read_f = fgetc(f);
    }
    str[i] = '\0';
    if (i == 0)
        return (-1);
    ungetc(read_f, f);
    return (1);
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list ap;
    va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}

int main()
{
    int age;
    char word[100];
    char letter;

    ft_scanf("%c has %d of %s", &letter, &age, word);
    printf("%c, %d, %s", letter, age, word);
}
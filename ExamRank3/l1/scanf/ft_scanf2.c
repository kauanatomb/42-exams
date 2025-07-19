#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c;
    int found_space = 0;
    
    // Skip all whitespace characters
    while ((c = fgetc(f)) != EOF)
    {
        if (isspace(c))
        {
            found_space = 1;
        }
        else
        {
            // Put back the non-space character
            ungetc(c, f);
            break;
        }
    }
    
    if (c == EOF && !found_space)
        return -1;
    
    return 0;
}

int match_char(FILE *f, char c)
{
    int input_char = fgetc(f);
    
    if (input_char == EOF)
        return -1;
    
    if (input_char == c)
        return 1;
    
    // Character doesn't match, put it back
    ungetc(input_char, f);
    return 0;
}

int scan_char(FILE *f, va_list ap)
{
    char *ptr = va_arg(ap, char *);
    int c = fgetc(f);
    
    if (c == EOF)
        return -1;
    
    *ptr = (char)c;
    return 1;
}

int scan_int(FILE *f, va_list ap)
{
    int *ptr = va_arg(ap, int *);
    int c;
    int sign = 1;
    int num = 0;
    int has_digits = 0;
    
    // Handle optional sign
    c = fgetc(f);
    if (c == '+' || c == '-')
    {
        if (c == '-')
            sign = -1;
        c = fgetc(f);
    }
    
    // Read digits
    while (c != EOF && isdigit(c))
    {
        num = num * 10 + (c - '0');
        has_digits = 1;
        c = fgetc(f);
    }
    
    // Put back the non-digit character
    if (c != EOF)
        ungetc(c, f);
    
    if (!has_digits)
        return -1;
    
    *ptr = num * sign;
    return 1;
}

int scan_string(FILE *f, va_list ap)
{
    char *ptr = va_arg(ap, char *);
    int c;
    int count = 0;
    
    // Read non-whitespace characters
    while ((c = fgetc(f)) != EOF && !isspace(c))
    {
        ptr[count] = (char)c;
        count++;
    }
    
    // Put back the whitespace or EOF
    if (c != EOF)
        ungetc(c, f);
    
    if (count == 0)
        return -1;
    
    // Null-terminate the string
    ptr[count] = '\0';
    return 1;
}

int match_conv(FILE *f, const char **format, va_list ap)
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
    int ret;
    
    va_start(ap, format);
    ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    
    return ret;
}

int main()
{
    int age;
    char c;
    // char s[100];

    ft_scanf("%c has %d", &c, &age);
    printf("%c, %d", c, age);
    return 0;
}
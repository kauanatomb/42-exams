/*

Write a function that returns the length of a string.

Your function must be declared as follows:

int	ft_strlen(char *str);
*/
int	ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

int main(void)
{
    int res = ft_strlen("Hello word!");
    return (res);
}
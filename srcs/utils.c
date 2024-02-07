#include "../includes/utils.h"
#include "../includes/lem-in.h"

int ft_atoi(const char *nptr)
{
    int i;
    int result;
    int neg;

    neg = 1;
    i = 0;
    result = 0;
    while (nptr[i] >= '0' && nptr[i] <= '9')
    {
        result = result * 10;
        result = result + nptr[i] - '0';
        i++;
    }
    if (nptr[i] != '\n' && nptr[i] != '\0')
        return -1;
    return (result * neg);
}

int ft_strcomp(char *src, char *dst)
{
    int i = 0;
    while (src[i] || src[i] != '\n')
    {
        if (!dst[i] && src[i] == '\n')
            return 1;
        if (src[i] != dst[i])
            return 0;
        i++;
    }
    if (ft_strlen(dst) != i)
        return 0;
    return 1;
}

int ft_strlen(char *str)
{
    if (str == NULL)
        return 0;
    int i = 0;
    while (str[i])
        i++;
    return i;
}

char *ft_str_cat(char *src, char *dst)
{
    int len;
    len = ft_strlen(src) + ft_strlen(dst);
    char *output = malloc(sizeof(char) * (len + 1));
    int i = 0;
    if(!dst)
        return NULL;
    while (dst[i])
    {
        output[i] = dst[i];
        i++;
    }
    int j = i;
    i = 0;
    while (src[i])
    {
        output[j + i] = src[i];
        i++;
    }
    output[len] = '\0';
    free(dst);
    return output;
}

int ft_strcmp(char *src, char *dst)
{
    int i = 0;
    while (src[i] && dst[i])
    {
        if (src[i] != dst[i])
            return 0;
        i++;
    }
    if (ft_strlen(dst) != i || (src[i] != '\n' && src[i] != '\0'))
        return 0;
    return 1;
}
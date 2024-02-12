#include "../includes/includes.h"

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



size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		srclen;
	char	*str;

	str = (char *)src;
	i = 0;
	srclen = ft_strlen(str);
	if (size == 0)
		return (srclen);
	while (src[i] && i < size - 1)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = 0;
	return (srclen);
}


void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*tab;
	int		i;
	int		len;

	if (nmemb > 2147483647 || size > 2147483647 || size * nmemb > 2147483647)
		return (0);
	len = (nmemb * size);
	i = 0;
	tab = malloc(len);
	if (!tab)
		return (0);
	while (i < len)
	{
		tab[i] = 0;
		i++;
	}
	return (tab);
}



void	*ft_memset(void *s, int c, size_t n)
{
	int		i;
	char	*temp;

	temp = s;
	i = 0;
	while (n-- != 0)
		temp[i++] = c;
	return (s);
}


void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}


static char	*ft_populate(char *tab, int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		tab[0] = '-';
		i++;
	}
	while (n > 0)
	{
		tab[i] = n % 10 + '0';
		n /= 10;
		i++;
	}
	tab[i] = 0;
	return (tab);
}

static int	ft_len(int n)
{
	int	neg;
	int	i;

	neg = 0;
	i = 1;
	if (n == 0)
		i++;
	if (n < 0)
	{
		n *= -1;
		neg++;
	}
	while ((unsigned int)n > 0)
	{
		n /= 10;
		i++;
	}
	return (i + neg);
}

static char	*ft_echange(char *tab, int n)
{
	char	temp;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(tab) - 1;
	if (n < 0)
		i++;
	while (i < j)
	{
		temp = tab[j];
		tab[j] = tab[i];
		tab[i] = temp;
		j--;
		i++;
	}
	return (tab);
}

char	*ft_itoa(int n)
{
	char	*tab;
	int		len;

	len = ft_len(n);
	tab = ft_calloc(sizeof(char), len);
	if (!tab)
		return (NULL);
	if (n == -2147483648)
	{
		ft_strlcpy(tab, "-2147483648", 12);
		return (tab);
	}
	if (!tab)
		return (NULL);
	ft_populate(tab, n);
	ft_echange(tab, n);
	if (tab[0] == 0)
		tab[0] = '0';
	return (tab);
}

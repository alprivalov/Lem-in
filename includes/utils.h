
#ifndef UTILS_H
#define UTILS_H
#include "includes.h"

int ft_strlen(char *str);
int ft_strcmp(char *src, char *dst);
char *ft_str_cat(char *src, char *dst);
int ft_strcomp(char *src, char *dst);
int ft_atoi(const char *nptr);
void outputBuffer(char * str);
char	*ft_itoa(int n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif
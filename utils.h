
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 5

#define ROOM 1
#define LINK 2

#define START 10
#define END 11
#define COMMENT 12

#define GET_ID_LINK_END 20
#define GET_ID_LINK_BEGIN 21
#define GET_ID_ROOM 22

#define ERROR_UNDEFINED 200
#define ERROR_NODE_NOT_FOUND 201
#define ERROR_NODE_WRONG_NAME 202
#define ERROR_CANNOT_READ_FD 203

int ft_strlen(char *str);
int ft_strcmp(char *src, char *dst);
char *ft_str_cat(char *src, char *dst);
int ft_strcomp(char *src, char *dst);
int ft_atoi(const char *nptr);

#endif
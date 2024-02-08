#ifndef PARSING_H
#define PARSING_H

#include "includes.h"
int ft_find_number_of(char *src, char c);
int getType(char *buff);
void reAllocStruct(t_node ***node, int size, t_node *createdNode);
int getLenTill(char *buff, char c, int *index);
char *getIdTill(char *buff, int *index, char c);
int getPosTill(char *buff, int *index, char c);
char *getBufferFromFd(char *fileName);
void initStructs(t_node ***node,int fd_Type,t_vars *global);
void exitError(int Error);
#endif
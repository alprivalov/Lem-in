

#ifndef LEM_IN_H
#define LEM_IN_H


#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>
#include "mlx.h"
#define BUFFER_SIZE 5

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

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


#endif
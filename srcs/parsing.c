#include "../includes/includes.h"

void exitError(int Error)
{
    //If there isn’t enough data to process normally you must display ERROR
    printf("Error : %d\n", Error);
    exit(Error);
}

int ft_find_number_of(char *src, char c)
{
    int i = 0;
    int number = 0;
    while (src[i] && src[i] != '\n')
    {
        if (src[i] == c)
            number++;
        i++;
    }
    return number;
}

int getType(char *buff)
{
    int len = ft_strlen(buff);
    int space = ft_find_number_of(buff, ' ');
    int dash = ft_find_number_of(buff, '-');
    if (space == 2 && dash == 0)
        return ROOM;
    if (dash == 1 && space == 0)
        return LINK;
    return ERROR_UNDEFINED;
}

void reAllocStruct(t_node ***node, int size, t_node *createdNode)
{
    t_node **new_node = malloc(sizeof(t_node *) * (size + 2));
    for (int i = 0; i < size; i++)
    {
        new_node[i] = (*node)[i];
    }
    new_node[size] = createdNode;
    new_node[size + 1] = 0;
    free((*node));
    (*node) = new_node;
}

int getLenTill(char *buff, char c, int *index)
{
    int i = 0;
    while (buff[i] && buff[i] != c)
    {
        i++;
        (*index)++;
    }
    (*index)++;
    return i;
}

char *getIdTill(char *buff, int *index, char c)
{
    int i = 0;
    char *output;
    int len = getLenTill(buff, c, index);
    output = malloc(sizeof(char) * (len + 1));
    output[len] = '\0';
    while (buff[i] && buff[i] != c)
    {
        output[i] = buff[i];
        i++;
    }
    if (output && (output[0] == 'L' || output[0] == '#'))
        exitError(ERROR_NODE_WRONG_NAME);
    output[i] = '\0';
    return output;
}

int getPosTill(char *buff, int *index, char c)
{
    int i = 0;
    char *tmp;
    int len = getLenTill(buff, c, index);
    tmp = malloc(sizeof(char) * (len + 2));
    while (buff[i] && buff[i] != c)
    {
        tmp[i] = buff[i];
        i++;
    }
    tmp[i] = '\0';

    int output = ft_atoi(tmp);
    if (tmp)
        free(tmp);
    return output;
}

char *getBufferFromFd(char *fileName)
{
    char * tmp_buffer;
    char *fd_buffer = malloc(0);
    int bytesRead;
    int fd = open(fileName, O_RDWR);
    if (fd == -1)
        exitError(ERROR_CANNOT_READ_FD);
    tmp_buffer = malloc(sizeof(char ) * BUFFER_SIZE);
    bytesRead = read(fd, tmp_buffer, sizeof(tmp_buffer));
    while (bytesRead)
    {
        fd_buffer = ft_str_cat(tmp_buffer, fd_buffer);
        tmp_buffer[BUFFER_SIZE] = '\0';
        free(tmp_buffer);
        tmp_buffer = malloc(sizeof(char ) * BUFFER_SIZE);
        bytesRead = read(fd, tmp_buffer, sizeof(tmp_buffer));
    }
    fd_buffer[ft_strlen(fd_buffer)] = '\0';
    free(tmp_buffer);
    return fd_buffer;
}

char *getBufferFromFdSTDIN()
{
    char * tmp_buffer;
    char *fd_buffer = malloc(0);
    int bytesRead;
    bytesRead = read(STDIN_FILENO, tmp_buffer, sizeof(tmp_buffer));
    if (bytesRead < 0)
        exitError(ERROR_CANNOT_READ_FD);
    tmp_buffer = malloc(sizeof(char ) * BUFFER_SIZE);
    while (bytesRead)
    {
        fd_buffer = ft_str_cat(tmp_buffer, fd_buffer);
        tmp_buffer[BUFFER_SIZE] = '\0';
        free(tmp_buffer);
        tmp_buffer = malloc(sizeof(char ) * BUFFER_SIZE);
        bytesRead = read(STDIN_FILENO, tmp_buffer, sizeof(tmp_buffer));
    }
    fd_buffer[ft_strlen(fd_buffer)] = '\0';
    free(tmp_buffer);
    return fd_buffer;
}

void initStructs(t_node ***node, int fd_Type,t_vars *global)
{
    int i = 0;
    char *fd_buffer = NULL;
    t_node **links = NULL;
    if (fd_Type == LEM)
    {
        fd_buffer = getBufferFromFd("../maps/subject.map");
        outputBuffer(fd_buffer);
        // \/ a ne pas oublier d'enlever \/ 
        write(1,"\n",1);
    }
    else
        fd_buffer = getBufferFromFdSTDIN();
    char commentType;
    int type;
    int numberOfNodes = 0;
    int lenBuffer = ft_strlen(fd_buffer);
    (*global).nbAnt = getPosTill(fd_buffer,&i,'\n');
    if (!fd_buffer)
        exitError(0);
    while (i < lenBuffer && fd_buffer[i])
    {
        if (fd_buffer[i] == '#')
        {
            // searching for start data:
            if (ft_strcmp(fd_buffer + i, "##start") && commentType != 'S')
            {
                commentType = 'S';
                getLenTill(fd_buffer + i, '\n', &i);
            }
            // searching for end data:
            else if (ft_strcmp(fd_buffer + i, "##end") && commentType != 'E')
            {
                commentType = 'E';
                getLenTill(fd_buffer + i, '\n', &i);
            }
            // searching for comment data:
            else
                getLenTill(fd_buffer + i, '\n', &i);
        }
        type = getType(fd_buffer + i);
        if (type == ROOM)
        {
            char *id = getIdTill(fd_buffer + i, &i, ' ');
            int x = getPosTill(fd_buffer + i, &i, ' ');
            int y = getPosTill(fd_buffer + i, &i, '\n');
            // printf("room : %s %d %d \ttype: %c\n", id, x, y, commentType);
            t_node *createdNode = create_new_node(x, y, id, commentType);
            reAllocStruct(node, numberOfNodes, createdNode);
            numberOfNodes++;
        }
        else if (type == LINK)
        {
            char *id_begin = getIdTill(fd_buffer + i, &i, '-');
            char *id_end = getIdTill(fd_buffer + i, &i, '\n');
            t_node *begin_node = find_node(node, id_begin);
            t_node *end_node = find_node(node, id_end);
            // printf("Link : %s-%s \ttype: %c\n", id_begin, id_end, commentType);
            free(id_begin);
            free(id_end);
            if (begin_node == NULL || end_node == NULL)
                exitError(ERROR_NODE_NOT_FOUND);
            link_node(begin_node, end_node);
        }
        else
            i++;
        commentType = 'C';

    }
    if(fd_buffer)
    free(fd_buffer);
}

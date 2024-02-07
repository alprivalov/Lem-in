#include "../includes/lem-in.h"
#include "../includes/utils.h"

typedef struct s_node
{
    int x;
    int y;
    char *id;
    char type;
    struct s_node **linked_nodes;
} t_node;

t_node *create_new_node(int x, int y, char *id, char type)
{
    t_node *new_node = malloc(sizeof(t_node));
    new_node->id = id;
    new_node->type = type;
    new_node->x = x;
    new_node->y = y;
    new_node->linked_nodes = NULL;
    return (new_node);
}


void exitError(int Error)
{
    printf("Error : %d\n", Error);
    exit(Error);
}

int get_linked_node_len(t_node **linked_nodes)
{
    int i;

    i = 0;
    if (linked_nodes)
    {
        while (linked_nodes[i])
            i++;
    }
    return (i);
}

void add_link(t_node *src_node, t_node *add_node)
{
    int i = 0;
    if (!src_node->linked_nodes)
    {
        src_node->linked_nodes = malloc(sizeof(t_node *) * 2);
        src_node->linked_nodes[0] = add_node;
        src_node->linked_nodes[1] = NULL;
    }
    else
    {
        t_node **new_src_node_link = malloc(sizeof(t_node *) * (get_linked_node_len(src_node->linked_nodes) + 2));
        while (src_node->linked_nodes[i])
        {
            new_src_node_link[i] = src_node->linked_nodes[i];
            i++;
        }
        new_src_node_link[i] = add_node;
        new_src_node_link[i + 1] = NULL;
        free(src_node->linked_nodes);
        src_node->linked_nodes = NULL;
        src_node->linked_nodes = new_src_node_link;
    }
}

void link_node(t_node *first_node, t_node *second_node)
{
    add_link(first_node, second_node);
    add_link(second_node, first_node);
}

t_node *find_node(t_node ***nodes, char *id)
{
    int i = 0;
    while ((*nodes)[i])
    {
        if (ft_strcmp((*nodes)[i]->id, id) == 1)
            return ((*nodes)[i]);
        i++;
    }
    return (NULL);
}

void create_node_map(char ***link, t_node ***nodes)
{
    int i = 0;

    while (link[i])
    {
        t_node *first_link = find_node(nodes, link[i][0]);
        t_node *second_link = find_node(nodes, link[i][1]);
        if (!first_link || !second_link)
            exitError(ERROR_NODE_NOT_FOUND);
        link_node(first_link, second_link);
    }
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
    int len = getLenTill(buff, c,index);
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
    int len = getLenTill(buff, c,index);
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

void initStructs(t_node ***node, char *buff)
{
    int i = 0;
    t_node **links = NULL;

    char commentType;
    int type;
    int numberOfNodes = 0;
    int lenBuffer = ft_strlen(buff);
    if (!buff)
        exitError(0);
    while (i < lenBuffer && buff[i] )
    {
        if (buff[i] == '#')
        {
            // searching for start data:
            if (ft_strcmp(buff + i, "##start"))
            {
                commentType = 'S';
                getLenTill(buff + i, '\n',&i);
                printf("start\n");
            }
            // searching for end data:
            else if (ft_strcmp(buff + i, "##end"))
            {
                commentType = 'E';
                getLenTill(buff + i, '\n',&i);
                printf("end\n");
            }
            // searching for comment data:
            else
            {
                commentType = 'C';
                getLenTill(buff + i, '\n',&i);
                printf("comment\n");
            }
        }
        type = getType(buff + i);
        if (type == ROOM)
        {
            char *id = getIdTill(buff + i, &i, ' ');
            int x = getPosTill(buff + i, &i, ' ');
            int y = getPosTill(buff + i, &i, '\n');
            printf("room : %s %d %d \ttype: %c\n",  id,x,y,commentType);
            t_node *createdNode = create_new_node(x, y, id, commentType);
            reAllocStruct(node, numberOfNodes, createdNode);
            numberOfNodes++;
        }
        else if (type == LINK)
        {
            char *id_begin = getIdTill(buff + i, &i, '-');
            char *id_end = getIdTill(buff + i, &i, '\n');
            t_node *begin_node = find_node(node, id_begin);
            t_node *end_node = find_node(node, id_end);
            printf("Link : %s-%s \ttype: %c\n", id_begin,id_end, commentType);
            free(id_begin);
            free(id_end);
            if (begin_node == NULL || end_node == NULL)
                exitError(ERROR_NODE_NOT_FOUND);
            link_node(begin_node, end_node);
        }
        else
            i++;
    }
}

char *getBufferFromFd(char *fileName)
{
    char tmp_buffer[BUFFER_SIZE + 1];
    char *fd_buffer = malloc(0);
    int bytesRead;
    int fd = open(fileName, O_RDWR);
    if (fd == -1)
        exitError(ERROR_CANNOT_READ_FD);
    tmp_buffer[BUFFER_SIZE + 1] = '\0';
    bytesRead = read(fd, tmp_buffer, sizeof(tmp_buffer));
    while (bytesRead)
    {
        fd_buffer = ft_str_cat(tmp_buffer, fd_buffer);
        bytesRead = read(fd, tmp_buffer, sizeof(tmp_buffer));
    }
    fd_buffer[ft_strlen(fd_buffer)] = '\0';
    return fd_buffer;   
}


int main(int ac, char **av)
{
    t_node **nodes = NULL;
    char *fd_buffer = getBufferFromFd("../maps/subject.map");
    initStructs(&nodes, fd_buffer);
    for(int i = 0; nodes[i];i++){
        free(nodes[i]->id);
        free(nodes[i]->linked_nodes);
        free(nodes[i]);
    }
    free(nodes);
    free(fd_buffer);
}

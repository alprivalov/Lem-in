#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define ROOM 1
#define LINK 2
#define ERROR 0

#define START 10
#define END 11
#define COMMENT 12

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

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
    {
        i++;
    }
    return i;
}

int get_linked_node_len(t_node **linked_nodes)
{
    int i;

    i = 0;
    if (linked_nodes)
    {
        while (linked_nodes[i])
        {
            ++linked_nodes;
            i++;
        }
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
        t_node **new_src_node_link = malloc(sizeof(t_node *) * (get_linked_node_len(src_node->linked_nodes) + 1));
        while (src_node->linked_nodes[i])
        {
            new_src_node_link[i] = src_node->linked_nodes[i];
            i++;
        }
        new_src_node_link[i] = add_node;
        new_src_node_link[i + 1] = NULL;
        free(src_node->linked_nodes);
        src_node->linked_nodes = new_src_node_link;
    }
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

void link_node(t_node *first_node, t_node *second_node)
{
    add_link(first_node, second_node);
    add_link(second_node, first_node);
}

t_node *find_node(t_node **nodes, char *id)
{
    int i = 0;
    while (nodes[i])
    {
        if (ft_strcomp(nodes[i]->id, id) == 0)
            return (nodes[i]);
    }
    return (NULL);
}

t_node *create_node_map(char ***link, t_node **nodes)
{
    int i = 0;

    while (link[i])
    {
        t_node *first_link = find_node(nodes, link[i][0]);
        t_node *second_link = find_node(nodes, link[i][1]);
        if (!first_link || !second_link)
            return (NULL);
        link_node(first_link, second_link);
    }
}

char *ft_str_cat(char *src, char *dst)
{
    int len;
    len = ft_strlen(src) + ft_strlen(dst);
    char *output = malloc(sizeof(char) * (len + 1));
    int i = 0;
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
    if (ft_strlen(dst) != i || src[i] != '\n')
        return 0;
    return 1;
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
    {
        return ROOM;
    }
    if (dash == 1 && space == 0)
    {
        return LINK;
    }
    return ERROR;
}

int get_comment_lenght(char *buff)
{
    int len = ft_strlen(buff);
    int i;
    for (i = 0; i < len; i++)
    {
        if (buff[i] == '\n')
        {
            return i;
        }
    }
    return i;
}

void exitError(int Error)
{
    printf("Error : %d\n", Error);
    exit(Error);
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
    if(!(*node))
        free((*node));
    (*node) = new_node;
}

int getLenBackSlash(char *buff)
{
    int i = 0;
    while (buff[i] && buff[i] != '\n')
        i++;
    return i;
}

int getLenSpace(char *buff)
{
    int i = 0;
    while (buff[i] && buff[i] != ' ')
        i++;
    return i;
}
char *getId(char *buff, int *index)
{
    int i = 0;
    char *output;
    int len = getLenSpace(buff);
    output = malloc(sizeof(char) * (len + 2));
    while (buff[i] && buff[i] != ' ')
    {
        output[i] = buff[i];
        i++;
        (*index)++;
    }
    (*index)++;
    output[i] = '\0';
    return output;
}

int getX(char *buff, int *index)
{
    int i = 0;
    char *tmp;
    int len = getLenSpace(buff);
    tmp = malloc(sizeof(char) * (len + 2));
    while (buff[i] && buff[i] != ' ')
    {
        tmp[i] = buff[i];
        i++;
        (*index)++;
    }
    tmp[i] = '\0';
    (*index)++;
    int output = ft_atoi(tmp);
    if (tmp)
        free(tmp);
    return output;
}

int getY(char *buff, int *index)
{
    int i = 0;
    char *tmp;
    int len = getLenBackSlash(buff);
    tmp = malloc(sizeof(char) * (len + 2));
    while (buff[i] && buff[i] != '\n')
    {
        tmp[i] = buff[i];
        i++;
        (*index)++;
    }
    tmp[i] = '\0';
    (*index)++;

    int output = ft_atoi(tmp);
    if (tmp)
        free(tmp);
    return output;
}

void initStruct(t_node **node, char *buff)
{
    int i = 0;
    char **links;
    char commentType;
    int type;
    int size_array = 0;
    if (!buff)
        exitError(0);
    while (buff[i])
    {
        if (buff[i] == '#')
        {
            // searching for start data:
            if (buff[i + 1] && buff[i + 1] == '#' && ft_strcmp(buff + i, "##start"))
            {
                commentType = 'S';
                i += ft_strlen("##start") + 1;
                printf("start: %d\n", i);
            }
            // searching for end data:
            else if (buff[i + 1] && buff[i + 1] == '#' && ft_strcmp(buff + i, "##end"))
            {
                commentType = 'E';
                i += ft_strlen("##end") + 1;
                printf("end: %d\n", i);
            }
            // searching for comment data:
            else
            {
                commentType = 'C';
                i += get_comment_lenght(buff + i) + 2;
                printf("comment , i : %d\n", i);
            }
        }
        type = getType(buff + i);
        if (type == ROOM)
        {
            char *id = getId(buff + i, &i);
            int x = getX(buff + i, &i);
            int y = getY(buff + i, &i);
            t_node * createdNode = create_new_node(x,y,id,commentType);
            reAllocStruct(&node, size_array,createdNode);
            size_array++;
        }

        i++;
    }
}

int main()
{
    t_node **rooms = NULL;

    int i = 0;
    int bytesRead;

    char *buff;
    char tmp_buffer[BUFFER_SIZE + 1];
    char *fileName = "subject.map";
    buff = malloc(0);
    int fd = open(fileName, O_RDWR);
    bytesRead = read(fd, tmp_buffer, sizeof(tmp_buffer));
    while (bytesRead)
    {
        buff = ft_str_cat(tmp_buffer, buff);
        bytesRead = read(fd, tmp_buffer, sizeof(tmp_buffer));
    }
    initStruct(rooms, buff);
}

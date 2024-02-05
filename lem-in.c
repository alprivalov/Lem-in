#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 5

typedef struct s_node
{
    int x;
    int y;
    int id;
    char type;
    struct s_node **linked_nodes;
} t_node;

t_node *create_new_node(int x, int y, int id, char type)
{
    t_node *new_node = malloc(sizeof(t_node));
    new_node->id = id;
    new_node->type = type;
    new_node->x = x;
    new_node->y = y;
    new_node->linked_nodes = NULL;
    return new_node;
}

// int get_linked_node_len(t_node linked_nodes)
// {
//     int i;

//     i = 0;
//     while (linked_nodes)
//     {
//         ++linked_nodes;
//         i++;
//     }
//     return (i);
// }

// t_nodelink_node(t_node first_node, t_nodesecond_node)
// {
//     int new_first_node_link = maget_linked_node_len(first_node->linked_nodes);
//     int new_second_node_link = get_linked_node_len(second_node->linked_nodes);

//     if (first_node->linked_nodes)
//     {

//     }
// }

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
    {
        i++;
    }
    return i;
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

int ft_strcomp(char *src, char *dst)
{
    int i = 0;
    while (src[i] || src[i] != '\n')
    {
        if(!dst[i] && src[i] == '\n')
            return 1;
        if (src[i] != dst[i])
            return 0;
        i++;
    }
    if (ft_strlen(dst) != i)
        return 0;
    return 1;
}

t_node *initStruct(char *buff)
{
    int i = 0;

    if (!buff)
        exit(0);
    while (buff[i])
    {
        if (buff[i] == '#')
        {
            if (ft_strcomp(buff + i, "#comment"))
            {
                printf("comment\n");
            }
            if (buff[i + 1] && buff[i + 1] == '#' && ft_strcomp(buff + i, "##start"))
            {
                printf("start\n");
            }
            if (buff[i + 1] && buff[i + 1] == '#' && ft_strcomp(buff + i, "##end"))
            {
                printf("end\n");
            }
        }
        else
        {
        }
        i++;
    }
}

int main()
{

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

    t_node *Game = initStruct(buff);
    printf("%s\n", buff);
    // int number_of_ants;
    // FILE *fichier = NULL;
    // int caractereActuel = 0;

    // fichier = fopen("../subject.map", "r");

    // if (fichier != NULL)
    // {
    //     caractereActuel = fgetc(fichier); // On lit le caractère
    //     while (caractereActuel != EOF)
    //     {
    //         printf("%c", caractereActuel);    // On l'affiche
    //         caractereActuel = fgetc(fichier); // On lit le caractère
    //     }

    //     fclose(fichier);
    // }
    // else
    // {
    //     // On affiche un message d'erreur si on veut
    //     printf("Impossible d'ouvrir le fichier test.txt");
    // }
}

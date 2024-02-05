#include <stdio.h>
#include <stdlib.h>

typedef struct s_node
{
    int x;
    int y;
    char *id;
    char type;
    struct s_node **linked_nodes;
} t_node;

t_node *create_new_node(int x,int y, char *id, char type)
{
    t_node* new_node = malloc(sizeof(t_node));
    new_node->id = id;
    new_node->type = type;
    new_node->x = x;
    new_node->y = y;
    new_node->linked_nodes = NULL;
    return(new_node);
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
        src_node->linked_nodes = malloc(sizeof(t_node*) * 2);
        src_node->linked_nodes[0] = add_node;
        src_node->linked_nodes[1] = NULL;
    }
    else
    {
        t_node  **new_src_node_link = malloc(sizeof(t_node*) * (get_linked_node_len(src_node->linked_nodes) + 1));
        while(src_node->linked_nodes[i])
        {
            new_src_node_link[i] = src_node->linked_nodes[i];
            i++;
        }
        new_src_node_link[i] = add_node;
        new_src_node_link[i+1] = NULL;
        free (src_node->linked_nodes);
        src_node->linked_nodes = new_src_node_link;
    }
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

void link_node(t_node *first_node, t_node *second_node)
{
    add_link(first_node, second_node);
    add_link(second_node, first_node);
}

t_node *find_node(t_node **nodes, char *id)
{
    int i = 0;
    while(nodes[i])
    {
        if (ft_strcomp(nodes[i]->id, id) == 0)
            return (nodes[i]);
    }
    return(NULL);
}

t_node ** add_start_nodes(t_node **start_nodes, t_node *add_node)
{
    t_node **new_start_nodes = NULL;
    int i = 0;

    if (!start_nodes)
    {
        new_start_nodes = malloc(sizeof(t_node*) * 2);
        new_start_nodes[0] = add_node;
        new_start_nodes[1] = NULL;
    }
    else
    {
        new_start_nodes = malloc(sizeof(t_node*) * (get_linked_node_len(start_nodes)+2));
        while(start_nodes[i])
        {
            new_start_nodes[i] = start_nodes[i];
            i++;
        }
        new_start_nodes[i] = add_node;
        new_start_nodes[i + 1] = NULL;
        free(start_nodes);
    }
    return (new_start_nodes);
}

t_node ** create_node_map(char **link, t_node **nodes)
{
    int i = 0;
    t_node **start_nodes = NULL;

    while (link[i])
    {
        t_node *first_link = find_node(nodes, link[i][0]);
        t_node *second_link = find_node(nodes, link[i][1]);
        if (!first_link || !second_link)
            return(NULL);
    }
    i = 0;
    while (nodes[i])
    {
       if (nodes[i]->type == 'S')
        start_nodes = add_start_nodes(start_nodes, nodes[i]);
    }
    return(start_nodes);
}

int main()
{

    int number_of_ants;
    FILE *fichier = NULL;
    int caractereActuel = 0;

    fichier = fopen("../subject.map", "r");

    if (fichier != NULL)
    {
        caractereActuel = fgetc(fichier); // On lit le caractère
        while (caractereActuel != EOF)
        {
            printf("%c", caractereActuel);    // On l'affiche
            caractereActuel = fgetc(fichier); // On lit le caractère
        }

        fclose(fichier);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier test.txt");
    }
}

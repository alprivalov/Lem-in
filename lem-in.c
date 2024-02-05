#include <stdio.h>
#include <stdlib.h>

typedef struct s_node
{
    int x;
    int y;
    int id;
    char type;
    struct s_node **linked_nodes;
} t_node;

t_node *create_new_node(int x,int y, int id, char type)
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
        t_node  **new_first_node_link = malloc(sizeof(t_node*) * (get_linked_node_len(src_node->linked_nodes) + 1));
        while(src_node->linked_nodes[i])
        {
            new_first_node_link[i] = src_node->linked_nodes[i];
            i++;
        }
        new_first_node_link[i] = add_node;
        new_first_node_link[i+1] = NULL;
    }
}

void link_node(t_node *first_node, t_node *second_node)
{
    add_link(first_node, second_node);
    add_link(second_node, first_node);
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

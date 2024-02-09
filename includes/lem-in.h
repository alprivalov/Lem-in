

#ifndef LEM_IN_H
#define LEM_IN_H

#include "includes.h"


typedef struct s_ant t_ant;
typedef struct s_node
{
    int x;
    int y;
    char *id;
    int weigth;
    int color;
    char type;
    int defWeight;
    struct s_node **linked_nodes;
    t_ant ** ants;
} t_node;



typedef struct s_ant
{
    t_node ** node_found;
    int id;
    t_node * location;
    int nbNodeFound;
} t_ant;


typedef struct s_window
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_window;


typedef struct s_display
{
    void *mlx;
    void *win;
    int min_dist;
    int min_y;
    int min_x;
    int max_y;
    int max_x;
    int off_set_dist;
    int off_set_x;
    int off_set_y;
} t_display;

typedef struct s_vars
{
    int nbAnt;
    int nbNode;
} t_vars;


typedef struct s_vec
{
    int x;
    int y;
} t_vec;

t_node *create_new_node(int x, int y, char *id, char type);
int get_linked_node_len(t_node **linked_nodes);
void add_link(t_node *src_node, t_node *add_node);
void link_node(t_node *first_node, t_node *second_node);
t_node *find_node(t_node ***nodes, char *id);
void create_node_map(char ***link, t_node ***nodes);
void printNodes(t_node **node);
void ft_mlx_pixel_put(t_window *vars, int x, int y, int color);
void ft_draw_circle(int x, int y, int r, int line_width, t_window *window, int color);
void ft_draw_circle_color(int x, int y, int r, int line_width, t_window *window, int color);
void DDA(t_window window, int aX, int aY, int cX, int cY, int len, int border, int color_start, int color_end);
int ft_close_key(int keycode, t_display *vars);
int ft_move_keycode(int keycode, t_display *vars);
int ft_close_mouse(t_display *vars);
#endif
#include "../includes/includes.h"

t_node *create_new_node(int x, int y, char *id, char type)
{
    t_node *new_node = malloc(sizeof(t_node));
    new_node->id = id;
    new_node->type = type;
    new_node->x = x;
    new_node->y = y;
    new_node->linked_nodes = NULL;
    new_node->ants = NULL;
    return (new_node);
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

int ft_blend(int color1, int color2, float r1, float r2)
{
    unsigned char RGB[3];

    RGB[0] = (unsigned char)(((color1 >> 16) & 0xFF) * r1 + ((color2 >> 16) & 0xFF) * r2);
    RGB[1] = (unsigned char)(((color1 >> 8) & 0xFF) * r1 + ((color2 >> 8) & 0xFF) * r2);
    RGB[2] = (unsigned char)(((color1) & 0xFF) * r1 + ((color2) & 0xFF) * r2);

    return ((RGB[0] << 16) + (RGB[1] << 8) + RGB[2]);
}

void printNodes(t_node **node)
{
    for (int i = 0; node[i]; i++)
    {
        printf("node : %s\tlinks : ", node[i]->id);
        for (int j = 0; node[i]->linked_nodes[j]; j++)
        {
            printf(" %s", node[i]->linked_nodes[j]->id);
        }
        printf("\t type: %c", node[i]->type);
        printf("\t weight: %d", node[i]->weigth);
        printf("\t color: %d\n", node[i]->color);
    }
}

void ft_mlx_pixel_put(t_window *vars, int x, int y, int color)
{
    char *dst;

    dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
    if (x >= 0 && y >= 0 && x <= WINDOW_WIDTH && y <= WINDOW_HEIGHT)
        *(unsigned int *)dst = color;
}

void ft_draw_circle(int x, int y, int r, int line_width, t_window *window, int color)
{
    int round_area_start_x = x - r;
    int round_area_start_y = y - r;
    int round_area_end_x = x + r;
    int round_area_end_y = y + r;

    for (int i = round_area_start_x; i < round_area_end_x; i++)
        for (int j = round_area_start_y; j < round_area_end_y; j++)
            if (!(i < 0 || i > 1920 || j < 0 || j > 1080) && ((i - x) * (i - x)) + ((j - y) * (j - y)) < r * r)
                ft_mlx_pixel_put(window, i, j, 0x00000000FF);
    if (line_width <= r)
        for (int i = round_area_start_x; i < round_area_end_x; i++)
            for (int j = round_area_start_y; j < round_area_end_y; j++)
                if (!(i < 0 || i > 1920 || j < 0 || j > 1080) && ((i - x) * (i - x)) + ((j - y) * (j - y)) < (r - line_width) * (r - line_width))
                    ft_mlx_pixel_put(window, i, j, color);
}

void ft_draw_circle_color(int x, int y, int r, int line_width, t_window *window, int color)
{
    int round_area_start_x = x - r;
    int round_area_start_y = y - r;
    int round_area_end_x = x + r;
    int round_area_end_y = y + r;

    for (int i = round_area_start_x; i < round_area_end_x; i++)
        for (int j = round_area_start_y; j < round_area_end_y; j++)
            if (!(i < 0 || i > 1920 || j < 0 || j > 1080) && ((i - x) * (i - x)) + ((j - y) * (j - y)) < (r - line_width) * (r - line_width))
                ft_mlx_pixel_put(window, i, j, color);
}

void DDA(t_window window, int aX, int aY, int cX, int cY, int len, int border, int color_start, int color_end)
{
    // calculate dx & dy
    int dx = cX - aX;
    int dy = cY - aY;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    // calculate increment in x & y for each steps
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;

    // Put pixel for each step
    float X = aX;
    float Y = aY;
    for (int i = 0; i <= steps; i++)
    {
        // printf("%f",)

        double ratio_start = (double)(i) / steps;
        double ratio_end = 1.0 - (double)(i) / steps;
        // printf("%f , %f\n", ratio_start, ratio_end);

        ft_draw_circle(X, Y, len, border, &window, ft_blend(color_start, color_end, ratio_start, ratio_end));
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
    }
}

int ft_close_key(int keycode, t_display *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
    return 0;
}

int ft_move_keycode(int keycode, t_display *vars)
{
    if (keycode == 65307)
        ft_close_key(keycode, vars);
    return 0;
}

int ft_close_mouse(t_display *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
    return 0;
}

void init_vars(t_node ***nodes, t_display *vars)
{
    vars->min_dist = 900000000;
    vars->min_y = 900000000;
    vars->min_x = 900000000;
    vars->max_y = -900000000;
    vars->max_x = -900000000;
    vars->off_set_dist = 50;
    for (int i = 0; (*nodes)[i]; i++)
    {
        for (int j = 0; (*nodes)[j]; j++)
        {
            if ((*nodes)[i] != (*nodes)[j] && ((*nodes)[i]->x - (*nodes)[j]->x) * ((*nodes)[i]->x - (*nodes)[j]->x) != 0 && ((*nodes)[i]->y - (*nodes)[j]->y) * ((*nodes)[i]->y - (*nodes)[j]->y) != 0)
            {
                if (((*nodes)[i]->x - (*nodes)[j]->x) * ((*nodes)[i]->x - (*nodes)[j]->x) < vars->min_dist)
                    vars->min_dist = ((*nodes)[i]->x - (*nodes)[j]->x) * ((*nodes)[i]->x - (*nodes)[j]->x);
                if (((*nodes)[i]->y - (*nodes)[j]->y) * ((*nodes)[i]->y - (*nodes)[j]->y) < vars->min_dist)
                    vars->min_dist = ((*nodes)[i]->y - (*nodes)[j]->y) * ((*nodes)[i]->y - (*nodes)[j]->y);
            }
        }
    }
    vars->min_dist = sqrt(vars->min_dist);
    printf("%d\n", vars->min_dist);
    for (int i = 0; (*nodes)[i]; i++)
    {
        (*nodes)[i]->x = (*nodes)[i]->x / vars->min_dist * vars->off_set_dist;
        (*nodes)[i]->y = (*nodes)[i]->y / vars->min_dist * vars->off_set_dist;
    }
    for (int i = 0; (*nodes)[i]; i++)
    {
        if ((*nodes)[i]->x < vars->min_x)
            vars->min_x = (*nodes)[i]->x;
        if ((*nodes)[i]->y < vars->min_y)
            vars->min_y = (*nodes)[i]->y;
    }
    for (int i = 0; (*nodes)[i]; i++)
    {
        (*nodes)[i]->x -= vars->min_x;
        (*nodes)[i]->y -= vars->min_y;
    }
    for (int i = 0; (*nodes)[i]; i++)
    {
        if ((*nodes)[i]->x > vars->max_x)
            vars->max_x = (*nodes)[i]->x;
        if ((*nodes)[i]->y > vars->max_y)
            vars->max_y = (*nodes)[i]->y;
    }
    for (int i = 0; (*nodes)[i]; i++)
    {
        (*nodes)[i]->x += (1920 - vars->max_x) / 2;
        (*nodes)[i]->y += (1080 - vars->max_y) / 2;
        (*nodes)[i]->weigth = 0;
        (*nodes)[i]->defWeight = 0;
    }
}

void initNodeColor(t_node **node)
{
    int minWeight = 999999999;
    int maxWeight = 0;

    for (int i = 0; node[i]; i++)
    {
        if (node[i]->defWeight > maxWeight)
            maxWeight = node[i]->defWeight;
        if (node[i]->defWeight < minWeight)
            minWeight = node[i]->defWeight;
    }
    for (int i = 0; node[i]; i++)
    {
        float ratio = (maxWeight != minWeight) ? (float)(node[i]->defWeight - minWeight) / (float)(maxWeight - minWeight) : 1.0;

        float ratioInv = 1.0 - ratio;
        node[i]->color = ft_blend(16711680, 0x0000FF00, ratio, ratioInv);
    }
}

void display_mlx(t_node **node, t_display vars, t_window window)
{
    initNodeColor(node);
    for (int i = 0; node[i]; i++)
    {
        ft_draw_circle(node[i]->x, node[i]->y, vars.off_set_dist / 2 * 0.9, vars.off_set_dist / 2 * 0.1, &window, 0x000000FF);
        for (int j = 0; node[i]->linked_nodes[j]; j++)
        {
            DDA(window, node[i]->x, node[i]->y, node[i]->linked_nodes[j]->x, node[i]->linked_nodes[j]->y, 10, 10, 0x000000FF, 0x000000FF);
            if (node[i]->weigth == 0 || node[i]->linked_nodes[j]->weigth == 0)
                DDA(window, node[i]->x, node[i]->y, node[i]->linked_nodes[j]->x, node[i]->linked_nodes[j]->y, 7, 0, 0xFFFFFFFF, 0xFFFFFFFF);
            else
                DDA(window, node[i]->x, node[i]->y, node[i]->linked_nodes[j]->x, node[i]->linked_nodes[j]->y, 7, 0, node[i]->linked_nodes[j]->color, node[i]->color);
        }
    }

    for (int i = 0; node[i]; i++)
    {
        if (node[i]->weigth == 0)
            ft_draw_circle_color(node[i]->x, node[i]->y, vars.off_set_dist / 2 * 0.9, vars.off_set_dist / 2 * 0.1, &window, 0xFFFFFFFF);
        else
            ft_draw_circle_color(node[i]->x, node[i]->y, vars.off_set_dist / 2 * 0.9, vars.off_set_dist / 2 * 0.1, &window, node[i]->color);
    }

    mlx_put_image_to_window(vars.mlx, vars.win, window.img, 0, 0xFFFFFFFF);
    for (int i = 0; node[i]; i++)
        mlx_string_put(vars.mlx, vars.win, node[i]->x, node[i]->y, 0, ft_itoa(node[i]->defWeight));
}

void BFS(t_node **node, t_window window, t_display vars)
{
    int weigth = 1;
    int state = 1;

    while (state)
    {
        usleep(100000);
        state = 0;
        for (int i = 0; node[i]; i++)
        {

            if (node[i]->weigth == weigth)
            {
                for (int j = 0; node[i]->linked_nodes[j]; j++)
                {
                    if (node[i]->linked_nodes[j]->weigth == 0)
                    {
                        node[i]->linked_nodes[j]->weigth = weigth + 1;
                        state = 1;
                    }
                }
            }
        }
        weigth++;
    }
    for (int i = 0; node[i]; i++)
    {
        if (node[i]->weigth == 1)
        {
            for (int j = 0; node[j]; j++)
            {
                if (node[j]->type == 'S' || node[j]->type == 'E')
                {
                    node[i]->defWeight += node[j]->weigth;
                }
            }
        }
    }

    display_mlx(node, vars, window);
}

t_node *endNode(t_node **node)
{
    for (int i = 0; node[i]; i++)
    {
        if (node[i]->type == 'E')
            return node[i];
    }
    exitError(ERROR_NODE_NOT_FOUND);
    return NULL;
}

t_node *beginNode(t_node **node)
{
    for (int i = 0; node[i]; i++)
    {
        if (node[i]->type == 'S')
            return node[i];
    }
    exitError(ERROR_NODE_NOT_FOUND);
    return NULL;
}

bool finish(t_ant **ants, t_node **node, t_vars global)
{
    t_node *node_end = endNode(node);
    int nb_finished = 0;
    for (int j = 0; ants[j]; j++)
    {
        if (ft_strcmp(ants[j]->location->id, node_end->id))
            nb_finished++;
    }
    if (nb_finished == global.nbAnt)
        return true;
    return false;
}

bool is_ant_finish(t_ant *ants, t_node *node_end)
{
    if (ft_strcmp(ants->location->id, node_end->id))
        return true;
    return false;
}

void moveAnt(t_node *node, t_ant *ant)
{
    char *tmp = ant->location->id;
    int nbant = 0;
    if (node->ants && node->ants[0] != NULL && node->type != 'E')
    {
        printf("ant: %d cant move to %s cause  %d\n", ant->id, node->id, node->ants[0]->id);
        return;
    }
    while (ant->location->ants[nbant])
        nbant++;
    t_ant **tmpAnts = malloc(sizeof(t_ant *) * (nbant + 1));
    int j = 0;
    for (int i = 0; i < nbant; i++)
    {
        if (ant->location->ants[i]->id != ant->id)
        {
            tmpAnts[j] = ant->location->ants[i];
            j++;
        }
    }
    tmpAnts[nbant - 1] = NULL;
    free(ant->location->ants);
    ant->location->ants = tmpAnts;

    node->ants[0] = ant;
    node->defWeight++;

    ant->location->defWeight--;

    ant->location = node;

    ant->node_found[ant->nbNodeFound + 1] = node;
    ant->node_found[ant->nbNodeFound + 2] = NULL;
    ant->nbNodeFound++;
    printf("ant : %d from :%s to :%s\n", ant->id, tmp, ant->location->id);
}
// a changer en dijkstra
t_node *getNearestNode(t_ant *ant, t_node **node, t_node *end)
{
    if (ft_strcmp(ant->location->id, end->id))
        return NULL;
    
    bool tmpfound = false;
    int j = 0;
    int len = 10000;
    int target[len];
    for (int i = 0; i < len; i++)
        target[i] = -1;

    int goodNode = 0;
    for (int i = 0; ant->location->linked_nodes[i]; i++)
    {
        j = 0;
        while (ant->node_found[j])
        {
            if (ft_strcmp(ant->location->linked_nodes[i]->id, ant->node_found[j]->id) || (ant->location->linked_nodes[i]->ants[0] != NULL && ant->location->linked_nodes[i]->type != 'E'))
                tmpfound = true;
            j++;
        }
        if (tmpfound == true)
            tmpfound = false;
        else
        {
            target[goodNode] = i;
            goodNode++;
        }
    }

    if (!goodNode)
        return NULL;

    t_node **tmpnode = malloc(sizeof(t_node *) * goodNode + 1);
    tmpnode[goodNode] = NULL;
    for (int i = 0; i < goodNode; i++)
        tmpnode[i] = ant->location->linked_nodes[target[i]];
    int minweight = 9000000;
    t_node *bestNode;
    for (int i = 0; tmpnode[i]; i++)
    {
        if (tmpnode[i]->type == 'E')
        {
            bestNode = tmpnode[i];
            free(tmpnode);
            return bestNode;
        }
        if (tmpnode[i]->defWeight < minweight)
        {
            minweight = tmpnode[i]->defWeight;
            bestNode = tmpnode[i];
        }
    }

    free(tmpnode);
    return bestNode;
}
//
void initAnts(t_ant ***ant, t_vars global, t_node **node)
{
    t_node *start = beginNode(node);
    (*ant) = malloc(sizeof(t_ant *) * (global.nbAnt + 1));
    for (int i = 0; node[i]; i++)
    {
        node[i]->ants = malloc(sizeof(t_ant *) * (global.nbAnt + 1));
        node[i]->ants[global.nbAnt] = NULL;
    }
    for (int i = 0; i < global.nbAnt; i++)
    {
        (*ant)[i] = malloc(sizeof(t_ant));
        (*ant)[i]->id = i + 1;
        (*ant)[i]->location = start;
        (*ant)[i]->node_found = malloc(sizeof(t_node *) * (global.nbNode + 2));
        (*ant)[i]->node_found[global.nbNode] = NULL;
        (*ant)[i]->node_found[0] = start;
        (*ant)[i]->nbNodeFound = 0;
        start->ants[i] = (*ant)[i];
    }
    ant[global.nbAnt] = NULL;
}

int main(int ac, char **av)
{
    t_display display;
    t_vars global;
    t_window window;
    t_node **node = NULL;
    t_ant **ant = NULL;

    initStructs(&node, LEM, &global);
    initAnts(&ant,global,node);
    t_node *end = endNode(node);

    display.mlx = mlx_init();
    display.win = mlx_new_window(display.mlx, 1920, 1080, "Hello world!");
    window.img = mlx_new_image(display.mlx, 1920, 1080);
    window.addr = mlx_get_data_addr(window.img, &window.bits_per_pixel, &window.line_length,
                                    &window.endian);

    init_vars(&node, &display);

    for (int i = 0; node[i]; i++)
    {
        for (int j = 0; node[j]; j++)
        {
            node[j]->weigth = 0;
        }
        node[i]->weigth = 1;
        BFS(node, window, display);
    }

    int round = 0;
    while (!finish(ant, node, global))
    {
        printf("round : %d\n", round++);
        for (int i = 0; i < global.nbAnt; i++)
        {
            t_node *nearestNode = getNearestNode(ant[i], node, end);
            if (nearestNode != NULL)
                moveAnt(nearestNode, ant[i]);
            usleep(100000);
            display_mlx(node, display, window);
        }
    }
    // printNodes(node);
    exitGood(ant, window, display, node);
    mlx_hook(display.win, 2, 1L << 0, ft_move_keycode, &display);
    mlx_hook(display.win, 17, 1L << 2, ft_close_mouse, &display);
    mlx_loop(display.mlx);
}

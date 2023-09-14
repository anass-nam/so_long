#include "so_long.h"


static void move(t_game *so_long, int h, int w)
{
    int ph;
    int pw;

    if (so_long->map->data[h][w] == COLL)
        so_long->collectible--;
    ph = so_long->pos_p->y;
    pw = so_long->pos_p->x;
    if (so_long->map->data[ph][pw] != EXIT)
        so_long->map->data[ph][pw] = EMPTY;
    so_long->map->data[h][w] = PLAYER;
    so_long->pos_p->y = h;
    so_long->pos_p->x = w;
    put_image(so_long->gui, EMPTY, pw, ph);
    put_image(so_long->gui, so_long->map->data[ph][pw], pw, ph);
    put_image(so_long->gui, EMPTY, w, h);
    put_image(so_long->gui, PLAYER, w, h);
}

static void finish(t_game *so_long)
{
    int eh;
    int ew;

    if (so_long->collectible == 0)
        exit_err2(so_long, NULL);
    eh = so_long->pos_e->y;
    ew = so_long->pos_e->x;
    put_image(so_long->gui, EMPTY, so_long->pos_p->x, so_long->pos_p->y);
    put_image(so_long->gui, EMPTY, ew, eh);
    put_image(so_long->gui, EXIT, ew, eh);
    put_image(so_long->gui, PLAYER, ew, eh);
    so_long->pos_p->y = eh;
    so_long->pos_p->x = ew;
}

static void moveto(t_game *so_long, int h, int w)
{
    if (so_long->map->data[so_long->pos_p->y + h][so_long->pos_p->x + w] == WALL)
        return ;
    else if (so_long->map->data[so_long->pos_p->y + h][so_long->pos_p->x + w] == COLL)
        move(so_long, so_long->pos_p->y + h, so_long->pos_p->x + w);
    else if (so_long->map->data[so_long->pos_p->y + h][so_long->pos_p->x + w] == EXIT)
        finish(so_long);
    else 
        move(so_long, so_long->pos_p->y + h, so_long->pos_p->x + w);
}

int  key_hook(int key, void *ptr)
{
    if (key == 53)
        exit_err2((t_game *)ptr, NULL);
    else if (key == 13)
        moveto((t_game *)ptr, -1, 0);
    else if (key == 0)
        moveto((t_game *)ptr, 0, -1);
    else if (key == 1)
        moveto((t_game *)ptr, 1, 0);
    else if (key == 2)
        moveto((t_game *)ptr, 0, 1);
    return (0);
}

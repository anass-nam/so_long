#include "so_long.h"

static void destroy_image(t_mlx *mlx, char *err)
{
    if (mlx->wall)
        mlx_destroy_image(mlx->mlx, mlx->wall);
    else if (mlx->empty)
        mlx_destroy_image(mlx->mlx, mlx->empty);
    else if (mlx->player)
        mlx_destroy_image(mlx->mlx, mlx->player);
    else if (mlx->collectible)
        mlx_destroy_image(mlx->mlx, mlx->collectible);
    else if (mlx->exit)
        mlx_destroy_image(mlx->mlx, mlx->exit);
    mlx_destroy_window(mlx->mlx, mlx->window);
    if (err)
        ft_putendl_fd(err, STDERR_FILENO);
}

static void put_image(t_mlx *gui, char c, int x, int y)
{
    mlx_put_image_to_window(gui->mlx, gui->window, gui->empty, x * 32, y * 32);
    if (c == WALL)
        mlx_put_image_to_window(gui->mlx, gui->window, gui->wall, x * 32, y * 32);
    else if (c == PLAYER)
        mlx_put_image_to_window(gui->mlx, gui->window, gui->player, x * 32, y * 32);
    else if (c == COLL)
        mlx_put_image_to_window(gui->mlx, gui->window, gui->collectible, x * 32, y * 32);
    else if (c == EXIT)
        mlx_put_image_to_window(gui->mlx, gui->window, gui->exit, x * 32, y * 32);
}

static bool set_xpms(t_mlx *gui)
{
    int h;
    int w;

    gui->wall = mlx_xpm_file_to_image(gui->mlx, "./assets/wall.xpm", &w, &h);
    gui->empty = mlx_xpm_file_to_image(gui->mlx, "./assets/empty.xpm", &w, &h);
    gui->player = mlx_xpm_file_to_image(gui->mlx, "./assets/player.xpm", &w, &h);
    gui->collectible = mlx_xpm_file_to_image(gui->mlx, "./assets/collectible.xpm", &w, &h);
    gui->exit = mlx_xpm_file_to_image(gui->mlx, "./assets/exit.xpm", &w, &h);
    if (gui->wall == NULL || gui->empty == NULL || gui->player == NULL || gui->collectible == NULL || gui->exit == NULL)
    {
        destroy_image(gui, "\033[1;101m ERROR!\033[0m\ncan't get xpm file");
        return (false);
    }
    return (true);
}

static void swap(char *a, char *b)
{
    (*a) ^= (*b);
    (*b) ^= (*a);
    (*a) ^= (*b);
}

static void moveto(t_game *so_long, int h, int w)
{
    int x;
    int y;
    int nx;
    int ny;

    x = so_long->pos_p->x;
    y = so_long->pos_p->y;
    nx = so_long->pos_p->x + w;
    ny = so_long->pos_p->y + h;
    if (so_long->map->data[ny][nx] != WALL)
    {
        swap(&(so_long->map->data[y][x]), &(so_long->map->data[ny][nx]));
        if (so_long->map->data[y][x] == COLL)
            so_long->map->data[y][x] = EMPTY;
        
        so_long->pos_p->x = nx;
        so_long->pos_p->y = ny;
        put_image(so_long->gui, so_long->map->data[y][x], x, y);
        put_image(so_long->gui, so_long->map->data[ny][nx], nx, ny);
    }
}

static int  key_hook(int key, void *ptr)
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

void    render_so_long(t_game *so_long)
{
    int x;
    int y;

    x = 32 * so_long->map->w;
    y = 32 * so_long->map->h;
    so_long->gui->mlx = mlx_init();
    if (so_long->gui->mlx == NULL)
        exit_err2(so_long, "\033[1;101m ERROR!\033[0m\ncan't open a window");
    so_long->gui->window = mlx_new_window(so_long->gui->mlx, x, y, "So_long");
    if (!so_long->gui->window || (!so_long->gui->wall && !set_xpms(so_long->gui)))
        exit_err2(so_long, "");
    x = -1;
    while (++x < so_long->map->w)
    {
        y = -1;
        while (++y < so_long->map->h)
            put_image(so_long->gui, so_long->map->data[y][x], x, y);
    }
    mlx_key_hook(so_long->gui->window, key_hook, so_long);
    mlx_loop(so_long->gui->mlx);
    exit_err2(so_long, NULL);
}
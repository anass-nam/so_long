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

static void put_image(t_mlx *mlx, char c, int x, int y)
{
    if (c == WALL)
        mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->wall, x * 32, y * 32);
    else if (c == EMPTY)
        mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->empty, x * 32, y * 32);
    else if (c == PLAYER)
        mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->player, x * 32, y * 32);
    else if (c == COLL)
        mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->collectible, x * 32, y * 32);
    else if (c == EXIT)
        mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->exit, x * 32, y * 32);
}

static bool set_xpms(t_mlx *mlx)
{
    int h;
    int w;

    mlx->wall = mlx_xpm_file_to_image(mlx->mlx, "./assets/wall.xpm", &w, &h);
    mlx->empty = mlx_xpm_file_to_image(mlx->mlx, "./assets/empty.xpm", &w, &h);
    mlx->player = mlx_xpm_file_to_image(mlx->mlx, "./assets/player.xpm", &w, &h);
    mlx->collectible = mlx_xpm_file_to_image(mlx->mlx, "./assets/collectible.xpm", &w, &h);
    mlx->exit = mlx_xpm_file_to_image(mlx->mlx, "./assets/exit.xpm", &w, &h);
    if (mlx->wall == NULL || mlx->empty == NULL || mlx->player == NULL || mlx->collectible == NULL || mlx->exit == NULL)
    {
        destroy_image(mlx, "\033[1;101m ERROR!\033[0m\ncan't get xpm file");
        return (false);
    }
    return (true);
}

static void moveto(t_game *so_long, int h, int w)
{
    int x;
    int y;
    int nx;
    int ny;

    if (so_long->map->data[ny][nx] != WALL)
    {
        x = so_long->pos_p->x;
        y = so_long->pos_p->y;
        nx = so_long->pos_p->x + w;
        ny = so_long->pos_p->y + h;
        so_long->map->data[y][x] ^= so_long->map->data[ny][nx];
        so_long->map->data[y][x] ^= so_long->map->data[ny][nx];
        so_long->map->data[y][x] ^= so_long->map->data[ny][nx];
        so_long->pos_p->x = nx;
        so_long->pos_p->y = ny;
        put_image(so_long->gui->mlx, so_long->map->data[y][x], x, y);
        put_image(so_long->gui->mlx, so_long->map->data[ny][nx], nx, ny);
    }
}

static int  key_hook(int key, void *ptr)
{
    if (key == 65307)
        exit_err2((t_game *)ptr, NULL);
    else if (key == 119)
        moveto((t_game *)ptr, -1, 0);
    else if (key == 97)
        moveto((t_game *)ptr, 0, -1);
    else if (key == 115)
        moveto((t_game *)ptr, 1, 0);
    else if (key == 100)
        moveto((t_game *)ptr, 0, 1);
    return (0);
}

void    render_so_long(t_game *so_long)
{
    int x;
    int y;
    int sx;
    int sy;

    sx = 32 * so_long->map->w;
    sy = 32 * so_long->map->h;
    so_long->gui->mlx = mlx_init();
    if (so_long->gui->mlx == NULL)
        exit_err2(so_long, "\033[1;101m ERROR!\033[0m\ncan't open a window");
    so_long->gui->window = mlx_new_window(so_long->gui->mlx, sx, sy, "So_long");
    if (!set_xpms(so_long->gui))
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
}
#include "so_long.h"

typedef struct s_mlx
{
    void    *mlx;
    void    *window;
    void    *wall;
    void    *empty;
    void    *player;
    void    *collectible;
    void    *exit;
}       t_mlx;

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

static void set_xpms(t_mlx *mlx)
{
    int h;
    int w;

    mlx->wall = mlx_xpm_file_to_image(mlx->mlx, "./assets/wall.xpm", &w, &h);
    if (mlx->wall == NULL)
        destroy_image(mlx, "ERROR: can't get xpm file");
    mlx->empty = mlx_xpm_file_to_image(mlx->mlx, "./assets/empty.xpm", &w, &h);
    if (mlx->empty == NULL)
        destroy_image(mlx, "ERROR: can't get xpm file");
    mlx->player = mlx_xpm_file_to_image(mlx->mlx, "./assets/player.xpm", &w, &h);
    if (mlx->player == NULL)
        destroy_image(mlx, "ERROR: can't get xpm file");
    mlx->collectible = mlx_xpm_file_to_image(mlx->mlx, "./assets/collectible.xpm", &w, &h);
    if (mlx->collectible == NULL)
        destroy_image(mlx, "ERROR: can't get xpm file");
    mlx->exit = mlx_xpm_file_to_image(mlx->mlx, "./assets/exit.xpm", &w, &h);
    if (mlx->exit == NULL)
        destroy_image(mlx, "ERROR: can't get xpm file");
}

void    render_so_long(t_game *g)
{
    t_mlx   so_long;
    int     x;
    int     y;

    so_long.mlx = mlx_init();
    so_long.window = mlx_new_window(so_long.mlx, 32 * g->map->w, 32 * g->map->h, "So_long");
    set_xpms(&so_long);
    x = -1;
    while (++x < g->map->w)
    {
        y = -1;
        while (++y < g->map->h)
            put_image(&so_long, g->map->data[y][x], x, y);
    }
    
    mlx_loop(so_long.mlx);
}
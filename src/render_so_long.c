#include "so_long.h"

void    render_so_long(t_game *game)
{
    void    *mlx;
    void    *window;

    mlx = mlx_init();
    window = mlx_new_window(mlx, 32 * game->map->w, 32 * game->map->h, "So_long");
    mlx_loop(mlx);
}
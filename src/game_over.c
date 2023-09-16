#include "so_long.h"

static void	destroy_images(t_mlx *gui)
{
	if (gui->wall)
		mlx_destroy_image(gui->mlx, gui->wall);
	if (gui->empty)
		mlx_destroy_image(gui->mlx, gui->empty);
	if (gui->player)
		mlx_destroy_image(gui->mlx, gui->player);
	if (gui->collectible)
		mlx_destroy_image(gui->mlx, gui->collectible);
	if (gui->exit)
		mlx_destroy_image(gui->mlx, gui->exit);
}

static void	destroy_display(void *mlx)
{
	if (mlx)
	{
		mlx_destroy_display(mlx);
		free(mlx);
	}
}

void	game_over(t_game *so_long, char option, char *msg)
{
	if (option & D_MAP)
		ft_free2d((void **)(so_long->map->data));
	if (option & D_IMG)
		destroy_images(so_long->gui);
	if (option & D_WIN && so_long->gui->window)
		mlx_destroy_window(so_long->gui->mlx, so_long->gui->window);
	if (option & D_MLX)
		destroy_display(so_long->gui->mlx);
	if (option & M_ERR)
		ft_putendl_fd(msg, STDERR_FILENO);
	else if (option & M_PER)
		perror(msg);
	else if (msg)
		ft_putendl_fd(msg, STDOUT_FILENO);
	if (option & E_ERR)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
#include "so_long.h"

static void	destroy_images(void *mlx, t_img *img)
{
	if (img->wall)
		mlx_destroy_image(mlx, img->wall);
	if (img->empty)
		mlx_destroy_image(mlx, img->empty);
	if (img->player)
		mlx_destroy_image(mlx, img->player);
	if (img->collectible)
		mlx_destroy_image(mlx, img->collectible);
	if (img->exit)
		mlx_destroy_image(mlx, img->exit);
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
		ft_free2d((void **)(so_long->map->content));
	if (option & D_IMG)
		destroy_images(so_long->mlx, so_long->assets);
	if (option & D_WIN && so_long->window)
		mlx_destroy_window(so_long->mlx, so_long->window);
	if (option & D_MLX)
		destroy_display(so_long->mlx);
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
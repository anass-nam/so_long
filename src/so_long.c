/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 22:17:30 by anammal           #+#    #+#             */
/*   Updated: 2023/09/16 22:17:32 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move(t_game *so_long, int h, int w)
{
	int	ph;
	int	pw;

	if (so_long->map->content[h][w] == COLL)
		so_long->map->collectible--;
	ph = so_long->map->player.y;
	pw = so_long->map->player.x;
	if (so_long->map->content[ph][pw] != EXIT)
		so_long->map->content[ph][pw] = EMPTY;
	so_long->map->content[h][w] = PLAYER;
	so_long->map->player.y = h;
	so_long->map->player.x = w;
	put_image(so_long, EMPTY, pw, ph);
	put_image(so_long, so_long->map->content[ph][pw], pw, ph);
	put_image(so_long, EMPTY, w, h);
	put_image(so_long, PLAYER, w, h);
}

static void	finish(t_game *so_long)
{
	int	eh;
	int	ew;

	if (so_long->map->collectible == 0)
		game_over(so_long, D_MLX | D_WIN | D_IMG | D_MAP | E_SUC, M_YW);
	eh = so_long->map->exit.y;
	ew = so_long->map->exit.x;
	put_image(so_long, EMPTY, so_long->map->player.x, so_long->map->player.y);
	put_image(so_long, EMPTY, ew, eh);
	put_image(so_long, EXIT, ew, eh);
	put_image(so_long, PLAYER, ew, eh);
	so_long->map->player.y = eh;
	so_long->map->player.x = ew;
}

static void	moveto(t_game *so_long, int h, int w)
{
	char	**map;
	t_point	p_pos;

	map = so_long->map->content;
	p_pos.x = so_long->map->player.x;
	p_pos.y = so_long->map->player.y;
	if (map[p_pos.y + h][p_pos.x + w] == WALL)
		return ;
	else if (map[p_pos.y + h][p_pos.x + w] == COLL)
		move(so_long, p_pos.y + h, p_pos.x + w);
	else if (map[p_pos.y + h][p_pos.x + w] == EXIT)
		finish(so_long);
	else
		move(so_long, p_pos.y + h, p_pos.x + w);
	ft_putstr_fd("> current move : ", STDOUT_FILENO);
	ft_putnbr_fd(++so_long->move_c, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static int	key_hook(int key, void *ptr)
{
	if (key == 53)
		game_over((t_game *)ptr, D_ALL | E_SUC, M_GO);
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

void	play_so_long(t_game *so_long)
{
	int	x;
	int	y;

	x = -1;
	while (++x < so_long->map->max.x)
	{
		y = -1;
		while (++y < so_long->map->max.y)
			put_image(so_long, so_long->map->content[y][x], x, y);
	}
	mlx_hook(so_long->window, 17, 0, gameover, so_long);
	mlx_hook(so_long->window, 2, 0, key_hook, so_long);
	mlx_loop(so_long->mlx);
}

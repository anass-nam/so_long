/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:13:12 by anammal           #+#    #+#             */
/*   Updated: 2023/09/11 13:13:21 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_err(char *err_msg)
{
	if (err_msg)
		ft_putendl_fd(err_msg, STDERR_FILENO);
	else
		perror("\033[1;101mERROR!\033[0m");
	exit(EXIT_FAILURE);
}

void	exit_err2(t_game *so_long, char *err_msg)
{
	ft_free2d((void **)so_long->map->data);
	mlx_destroy_image(so_long->gui->mlx, so_long->gui->wall);
	mlx_destroy_image(so_long->gui->mlx, so_long->gui->empty);
	mlx_destroy_image(so_long->gui->mlx, so_long->gui->player);
	mlx_destroy_image(so_long->gui->mlx, so_long->gui->collectible);
	mlx_destroy_image(so_long->gui->mlx, so_long->gui->exit);
	mlx_destroy_window(so_long->gui->mlx, so_long->gui->window);
	mlx_destroy_display(so_long->gui->mlx);
	free(so_long->gui->mlx);
	if (err_msg)
		exit_err(err_msg);
	exit(EXIT_SUCCESS);
}


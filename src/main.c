/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:16:31 by anammal           #+#    #+#             */
/*   Updated: 2023/09/11 13:16:35 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_map_ext(int ac, char const *map_file)
{
	int	len;

	len = 0;
	if (ac > 1)
		len = ft_strlen(map_file);
	if (len < 4 || ft_strncmp(map_file + len - 4, ".ber", 4))
		exit_err("\033[1;101m ERROR!\033[0m\ninvalid map file name");
}

int	main(int ac, char const **av)
{
	t_game	so_long;
	t_map	map;
	t_point	player;
	t_point	exit;
	t_mlx	gui;

	check_map_ext(ac, av[1]);
	ft_bzero(&so_long, sizeof so_long);
	ft_bzero(&map, sizeof map);
	so_long.map = &map;
	ft_bzero(&player, sizeof player);
	so_long.pos_p = &player;
	ft_bzero(&exit, sizeof exit);
	so_long.pos_e = &exit;
	ft_bzero(&gui, sizeof gui);
	so_long.gui = &gui;
	init_so_long(av[1], &so_long);
	render_so_long(&so_long);
	return (0);
}


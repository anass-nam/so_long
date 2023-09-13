/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:16:56 by anammal           #+#    #+#             */
/*   Updated: 2023/09/11 13:17:00 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>

# define EMPTY 48
# define WALL 49
# define COLL 67
# define EXIT 69
# define PLAYER 80

typedef struct s_map
{
	char	**data;
	int		w;
	int		h;
}			t_map;

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

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

typedef struct s_game
{
	t_map	*map;
	t_point	*pos_p;
	t_point	*pos_e;
	t_mlx	*gui;
	int		player;
	int		exit;
	int		collectible;
}			t_game;

void	init_so_long(char const *map_file, t_game *game);
bool	parse_map(t_game *game, t_list *list);
void    render_so_long(t_game *game);
//	exit handler functions
void	exit_err(char *err_msg);
void	exit_err2(t_game *so_long, char *err_msg);

#endif

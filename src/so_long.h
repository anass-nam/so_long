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

# define D_MAP 0x1	// free the map
# define D_IMG 0x2	// destroy images
# define D_WIN 0x4	// destroy the window
# define D_MLX 0x8	// destroy mlx
# define M_ERR 0x10	// print error msg to stderr
# define M_PER 0x20	// print error msg to stderr using errno
# define E_ERR 0x40	// exit with failure status

# define M_EXT "ERROR!\nso_long: usage: ./so_long path/to/map*.ber"
# define M_IMP "ERROR!\nso_long: map: invalid map"
# define M_NVP "ERROR!\nso_long: map: no valid path"
# define M_XPM "ERROR!\nso_long failed to access assets"
# define M_MEM "ERROR!\nso_long failed to get enough memory"
# define M_GO "GAME OVER !!"
# define M_YW "You WON !!"

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
	int		move_c;
}			t_game;

void	init_so_long(char const *map_file, t_game *game);
bool	parse_map(t_game *game, t_list *list);
void    render_so_long(t_game *game);
int  	key_hook(int key, void *ptr);
void	put_image(t_mlx *gui, char c, int x, int y);
//	exit handler functions
void	exit_err(char *err_msg);
void	exit_err2(t_game *so_long, char *err_msg);

#endif

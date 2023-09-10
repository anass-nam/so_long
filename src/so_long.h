#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>

# define EMPTY '0'
# define WALL '1'
# define COLL 'C'
# define EXIT 'E'
# define PLAYER 'P'

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

typedef struct s_game
{
	t_map	*map;
	t_point	*pos_p;
	t_point	*pos_e;
	int		player;
	int		exit;
	int		collectible;
}			t_game;

void	init_so_long(char const *map_file, t_game *game);
bool	parse_map(t_game *game, t_list *list);
//	exit handler functions
void	exit_err(char const *err_msg);
// void	exit_err_heap(void	*ptr, void (*f)(void *));
// void	exit_err_heap2(t_list **ptr);

#endif
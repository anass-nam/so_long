#include "so_long.h"

static void	set_pos(t_point *p, int *count, int x, int y)
{
	p->x = x;
	p->y = y;
	(*count)++;
}

static bool	isnotvalid(char c, int h, int w, int hi, int wi)
{
	if (c == EMPTY || c == WALL || c == COLL || c == EXIT || c == PLAYER)
	{
		if (((wi == 0 || wi == w - (2 - (wi == h - 1)) || hi == 0 || hi == h - 1) && c != WALL))
			return (true);
		return (false);
	}
	return (true);
}

static bool	parse_map_line(t_game *game, char *l, int h, int w, int hi)
{
	int	i;

	i = 0;
	while (l[i])
	{
		if (i == w - (1 - (hi == h - 1)))
			l[i] = '\0';
		else if (isnotvalid(l[i], h, w, hi, i))
			return (false);
		else if (l[i] == PLAYER)
			set_pos(game->pos_p, &(game->player), i, hi);
		else if (l[i] == EXIT)
			set_pos(game->pos_e, &(game->exit), i, hi);
		else if (l[i] == COLL)
			game->collectible++;
		i++;
	}
	if (i != w - (hi == h - 1))
		return (false);
	return (true);
}

bool	parse_map(t_game *game, t_list *list)
{
	int	i;

	game->map->h = ft_lstsize(list);
	game->map->w = ft_strlen(list->content);
	game->map->data = (char **)malloc(game->map->h * sizeof(char *));
	if (game->map->data == NULL)
		return (false);
	game->player = 0;
	game->exit = 0;
	game->collectible = 0;
	i = 0;
	while (list)
	{
		if (parse_map_line(game, list->content, game->map->h, game->map->w, i) == false)
			return (false);
		game->map->data[i] = list->content;
		list = list->next;
		i++;
	}
	if (game->player != 1 || game->exit != 1 || !game->collectible)
		return (false);
	game->map->w--;
	return (true);
}
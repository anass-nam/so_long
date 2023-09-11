/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:16:42 by anammal           #+#    #+#             */
/*   Updated: 2023/09/11 13:16:48 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	set_pos(t_point *p, int *count, int x, int y)
{
	p->x = x;
	p->y = y;
	(*count)++;
}

static bool	isnotvalid(char c, int h, int w, t_point p)
{
	if (c == EMPTY || c == WALL || c == COLL || c == EXIT || c == PLAYER)
	{
		if (((p.x == 0 || p.x == w - (2 - (p.x == h - 1)) 
					|| p.y == 0 || p.y == h - 1) && c != WALL))
			return (true);
		return (false);
	}
	return (true);
}

static bool	parse_map_line(t_game *game, char *l, int i)
{
	t_point	pos;

	pos.x = 0;
	pos.y = i;
	while (l[pos.x])
	{
		if (pos.x == game->map->w - (1 - (pos.y == game->map->h - 1)))
			l[pos.x] = '\0';
		else if (isnotvalid(l[pos.x], game->map->h, game->map->w, pos))
			return (false);
		else if (l[pos.x] == PLAYER)
			set_pos(game->pos_p, &(game->player), pos.x, pos.y);
		else if (l[pos.x] == EXIT)
			set_pos(game->pos_e, &(game->exit), pos.x, pos.y);
		else if (l[pos.x] == COLL)
			game->collectible++;
		pos.x++;
	}
	if (pos.x != game->map->w - (pos.y == game->map->h - 1))
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
		if (parse_map_line(game, list->content, i) == false)
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

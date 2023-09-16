#include "so_long.h"

static void	set_pos(t_point *p, int x, int y)
{
	if (p->x == 0)
	{
		p->x = x;
		p->y = y;
	}
	else
		p->x = -1;
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

static bool	parse_map_line(t_game *so_long, char *l, int i)
{
	t_point	pos;

	pos.x = 0;
	pos.y = i;
	while (l[pos.x])
	{
		if (pos.x == so_long->map->max.x - (1 - (pos.y == so_long->map->max.y - 1)))
			l[pos.x] = '\0';
		else if (isnotvalid(l[pos.x], so_long->map->max.y, so_long->map->max.x, pos))
			return (false);
		else if (l[pos.x] == PLAYER)
			set_pos(&(so_long->map->player), pos.x, pos.y);
		else if (l[pos.x] == EXIT)
			set_pos(&(so_long->map->exit), pos.x, pos.y);
		else if (l[pos.x] == COLL)
			so_long->map->collectible++;
		pos.x++;
	}
	if (pos.x != so_long->map->max.x - (pos.y == so_long->map->max.y - 1))
		return (false);
	return (true);
}

bool	parse_map(t_game *so_long, t_list *list)
{
	int	i;

	so_long->map->max.x = ft_strlen(list->content);
	so_long->map->max.y = ft_lstsize(list);
	so_long->map->content = (char **)ft_calloc(so_long->map->max.y + 1, sizeof(char *));
	if (so_long->map->content == NULL)
		return (false);
	i = 0;
	while (list)
	{
		if (parse_map_line(so_long, list->content, i) == false)
			return (false);
		so_long->map->content[i] = list->content;
		list = list->next;
		i++;
	}
	if (so_long->map->player.x < 1 || so_long->map->exit.x < 1 || !so_long->map->collectible)
		return (false);
	so_long->map->max.x--;
	return (true);
}
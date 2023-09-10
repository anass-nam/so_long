#include "so_long.h"

static void	free_nodes(t_list **list)
{
	t_list	*next;

	while (*list)
	{
		next = (*list)->next;
		free(*list);
		*list = next;	
	}
}

static t_list	*read_map(int fd)
{
	t_list	*list;
	t_list	*new;
	char	*line;

	list = NULL;
	line = "";
	while (line)
	{
		line = get_next_line(fd);
		if (line)
		{
			new = ft_lstnew(line);
			if (new == NULL)
				return (free(line), ft_lstclear(&list, free), NULL);
			ft_lstadd_back(&list, new);
		}
	}
	return (list);
}

static void	flood_fill(char **map, int x, int y, int *count)
{
	if (map[y][x] != WALL)
	{
		if (map[y][x] == COLL || map[y][x] == EXIT)
			(*count)++;
		map[y][x] = WALL;
		flood_fill(map, x - 1, y, count);
		flood_fill(map, x + 1, y, count);
		flood_fill(map, x, y - 1, count);
		flood_fill(map, x, y + 1, count);
	}
}

static bool check_valid_path(t_game *game)
{
	char	**tmp;
	int		i;

	tmp = (char **)ft_calloc(game->map->h + 1, sizeof(char *));
	if (tmp == NULL)
		return (false);
	i = 0;
	while (i < game->map->h)
	{
		tmp[i] = ft_strdup(game->map->data[i]);
		if (tmp[i++] == NULL)
			return (ft_free2d((void **)tmp), false);
	}
	i = 0;
	flood_fill(tmp, game->pos_p->x, game->pos_p->y, &i);
	ft_free2d((void **)tmp);
	if (i - 1 != game->collectible)
		return (false);
	return (true);
}

void	init_so_long(char const *map_file, t_game *game)
{
	int		fd;
	t_list	*map;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		exit_err(NULL);
	map = read_map(fd);
	close(fd);
	if (map == NULL)
		exit_err("ERROR: unable to get the map");
	if (!parse_map(game, map) || !check_valid_path(game))
	{
		ft_lstclear(&map, free);
		free(game->map->data);
		exit_err("ERROR: invalid map");
	}
	free_nodes(&map);
}
#include "so_long.h"

void wp(void *s) { ft_putstr_fd((char *)s, STDOUT_FILENO);}

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

static void	parse_map(t_game *game, t_list **list)
{

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
	ft_lstiter(map, wp);
	parse_map(game, &map);
}
#include "so_long.h"

static t_map	**read_map(int fd)
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
			if (new)
				
			ft_lstadd_back(&list, new);

		}
	}
	
}

void	init_so_long(char const *map_file, t_game *game)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		exit_err(NULL);
	game->map = read_map(map_file);
}
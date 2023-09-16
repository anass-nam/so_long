#include "so_long.h"

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



void	init_so_long(t_game *so_long, char const *file)
{
	int		fd;
	t_list	*map;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		game_over(NULL, M_PER | E_ERR, M_OPN);
	map = read_map(fd);
	close(fd);
	if (map == NULL)
		game_over(NULL, M_ERR | E_ERR, M_MEM);

}
#include "so_long.h"

static void	check_map_ext(int ac, char const *map_file)
{
	int	len;

	len = 0;
	if (ac > 1)
		len = ft_strlen(map_file);
	if (len < 4 || ft_strncmp(map_file + len - 4, ".ber", 4))
		exit_err("ERROR: invalid map file name");
}

int main(int ac, char const **av)
{
	t_game	game;

	check_map_ext(ac, av[1]);
	init_so_long(av[1], &game);
	// render map on window (mlx)
	return 0;
}

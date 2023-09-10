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
	t_map	map;
	t_point	player;
	t_point	exit;

	game.map = &map;
	game.pos_p = &player;
	game.pos_e = &exit;
	check_map_ext(ac, av[1]);
	init_so_long(av[1], &game);
	// for (size_t i = 0; i < map.h; i++)
	// {
	// 	ft_putendl_fd(map.data[i], STDOUT_FILENO);
	// 	free(map.data[i]);
	// }
	// free(map.data);
	// printf("map (h = %d | w = %d)\npos_p (y = %d | x = %d)\npos_e (y = %d | x = %d)\ncount_c = %d\n", map.h, map.w, player.y, player.x, exit.y, exit.x, game.collectible);
	
	return 0;
}

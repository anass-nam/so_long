#include "so_long.h"

void	move_player(t_game *so, int x, int y)
{
	t_point	p;
	t_point	e;
	
	p.x = so->map->player.x;
	p.y = so->map->player.y;
	e.x = so->map->exit.x;
	e.y = so->map->exit.y;
	if (so->map->content[y][x] == EXIT && !so->map->collectible)
		game_over(so, D_ALL | E_SUC, M_YW);
	else if (so->map->content[y][x] == COLL)
	{
		so->map->content[y][x] = EMPTY;
		so->map->collectible--;
	}
	so->map->player.x = x;
	so->map->player.y = y;
	put_image(so, EMPTY, p.x, p.y);
	put_image(so, EXIT, e.x, e.y);
	put_image(so, PLAYER, x, y);
}
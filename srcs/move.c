#include "so_long.h"
#include "get_next_line.h"

int	key_hook(int keycode, t_info *info)
{
	int origin_x;
	int	origin_y;

	origin_x = info->hero_x;
	origin_y = info->hero_y;
	if (keycode == 53)
		destroy_window_exit(info);
	else if (keycode == 2)
		info->hero_y += 1;
	else if (keycode == 0)
		info->hero_y -= 1;
	else if (keycode == 13)
		info->hero_x -= 1;
	else if (keycode == 1)
		info->hero_x += 1;
	else
		return (0);
	move(info, origin_x, origin_y);
	return (0);
}

void	move(t_info *info, int origin_x, int origin_y)
{
	if (MSB(info->map[info->hero_x][info->hero_y]) == '1')
	{
		info->hero_x = origin_x;
		info->hero_y = origin_y;
		return ;
	}
	if (MSB(info->map[info->hero_x][info->hero_y]) == 'E' && info->c_cnt == 0)
		destroy_window_exit(info);
	if (MSB(info->map[info->hero_x][info->hero_y]) == 'C')
		info->map[info->hero_x][info->hero_y] = '0';
	mlx_clear_window(info->mlx, info->mlx_win);
	info->move_cnt++;
	init_map(info);
	ft_printf("collect_cur -> %d\n", info->c_cnt);
	ft_printf("%d\n", info->move_cnt);
}
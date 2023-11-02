#include "so_long.h"
#include "get_next_line.h"

void	move(t_info *info, int origin_x, int origin_y)
{
	if (info->map[info->hero_x][info->hero_y] == '1')
	{
		info->hero_x = origin_x;
		info->hero_y = origin_y;
		return ;
	}
	if (info->map[info->hero_x][info->hero_y] == 'E' && info->c_cnt == 0)
		destroy_window_exit(info);
	if (info->map[info->hero_x][info->hero_y] == 'C')
		info->map[info->hero_x][info->hero_y] = '0';
	mlx_clear_window(info->mlx, info->mlx_win);
	info->move_cnt++;
	init_map(info);
	ft_printf("collect_cur -> %d\n", info->c_cnt);
	ft_printf("%d\n", info->move_cnt);
}
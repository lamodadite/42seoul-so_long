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

void init_image(t_info *info)
{
	info->img_hero = mlx_xpm_file_to_image(info->mlx, "./textures/hero.xpm", &info->img_size, &info->img_size);
	info->img_wall = mlx_xpm_file_to_image(info->mlx, "./textures/wall.xpm", &info->img_size, &info->img_size);
	info->img_exit = mlx_xpm_file_to_image(info->mlx, "./textures/exit.xpm", &info->img_size, &info->img_size);
	info->img_collect = mlx_xpm_file_to_image(info->mlx, "./textures/collect.xpm", &info->img_size, &info->img_size);
	info->img_empty = mlx_xpm_file_to_image(info->mlx, "./textures/empty.xpm", &info->img_size, &info->img_size);
}

void	init_mlx(t_info *info)
{
	info->mlx = mlx_init();
	info->mlx_win = mlx_new_window(info->mlx, info->map_width * TILE_SIZE, info->map_height * TILE_SIZE, "so_long");
}

int	main(int ac, char **av)
{
	t_info info;

	if (ac != 2)
		error_exit(ARG_ERROR);
	// map valid check & load
	load_map(&info, av[1]);
	init_mlx(&info);
	init_image(&info);
	init_map(&info);
	mlx_key_hook(info.mlx_win, key_hook, &info);
	mlx_loop(info.mlx);
	return (0);
}
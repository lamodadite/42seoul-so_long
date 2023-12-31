/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:20:41 by jongmlee          #+#    #+#             */
/*   Updated: 2023/11/06 19:41:56 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_image(t_info *info)
{
	info->img_hero = mlx_xpm_file_to_image(info->mlx, "./textures/hero.xpm",
			&info->img_size, &info->img_size);
	info->img_wall = mlx_xpm_file_to_image(info->mlx, "./textures/wall.xpm",
			&info->img_size, &info->img_size);
	info->img_exit = mlx_xpm_file_to_image(info->mlx, "./textures/exit.xpm",
			&info->img_size, &info->img_size);
	info->img_collect = mlx_xpm_file_to_image(info->mlx, "./textures/coin.xpm",
			&info->img_size, &info->img_size);
	info->img_empty = mlx_xpm_file_to_image(info->mlx, "./textures/empty.xpm",
			&info->img_size, &info->img_size);
}

void	init_mlx(t_info *info)
{
	info->mlx = mlx_init();
	info->mlx_win = mlx_new_window(info->mlx, info->map_w * TILE_SIZE,
			info->map_h * TILE_SIZE, "so_long");
}

int	close_window(void *param)
{
	free_map(param, 0);
	exit(0);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 2)
		error_exit(ARG_ERROR);
	load_map(&info, av[1]);
	check_map(&info);
	init_mlx(&info);
	init_image(&info);
	init_map(&info);
	mlx_key_hook(info.mlx_win, key_hook, &info);
	mlx_hook(info.mlx_win, 17, 0, close_window, &info);
	mlx_loop(info.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:20:01 by jongmlee          #+#    #+#             */
/*   Updated: 2023/11/06 18:34:08 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"

void	get_map_size(t_info *info, char *map_path)
{
	char	*first_line;
	int		fd;

	fd = open(map_path, O_RDONLY);
	first_line = get_next_line(fd);
	info->map_w = ft_strlen(first_line) - 1;
	while (first_line != NULL)
	{
		info->map_h += 1;
		free(first_line);
		first_line = get_next_line(fd);
	}
	free(first_line);
	close(fd);
}

void	load_map(t_info *info, char *map_path)
{
	int		fd;
	int		i;

	i = -1;
	check_extension(map_path);
	get_map_size(info, map_path);
	info->map = (char **)malloc(info->map_h * sizeof(char *));
	if (info->map == NULL)
		error_exit(MALLOC_ERROR);
	fd = open(map_path, O_RDONLY);
	while (++i < info->map_h)
	{
		info->map[i] = get_next_line(fd);
		if (info->map[i] == NULL)
			free_error_exit(MALLOC_ERROR, info, i);
	}
	check_rectangle(info);
	close(fd);
}

void	init_map(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	info->c_cnt = 0;
	while (++i < info->map_h)
	{
		j = -1;
		while (++j < info->map_w)
		{
			mlx_put_image_to_window(info->mlx, info->mlx_win, info->img_empty,
				j * TILE_SIZE, i * TILE_SIZE);
			if (info->map[i][j] != 0)
				put_element(info, i, j);
		}
	}
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->img_hero,
		info->hero_y * TILE_SIZE, info->hero_x * TILE_SIZE);
}

void	put_element(t_info *info, int x, int y)
{
	if (msb(info->map[x][y]) == '1')
		mlx_put_image_to_window(info->mlx, info->mlx_win, info->img_wall,
			y * TILE_SIZE, x * TILE_SIZE);
	else if (msb(info->map[x][y]) == 'C')
	{
		info->c_cnt++;
		mlx_put_image_to_window(info->mlx, info->mlx_win, info->img_collect,
			y * TILE_SIZE, x * TILE_SIZE);
	}
	else if (msb(info->map[x][y]) == 'E')
		mlx_put_image_to_window(info->mlx, info->mlx_win, info->img_exit,
			y * TILE_SIZE, x * TILE_SIZE);
	else if (msb(info->map[x][y]) == 'P' &&
		info->hero_x == 0 && info->hero_y == 0)
	{
		info->hero_x = x;
		info->hero_y = y;
	}
	else if (msb(info->map[x][y]) != '0' && msb(info->map[x][y]) != 'P')
		free_error_exit(MAP_ERROR, info, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:31:49 by jongmlee          #+#    #+#             */
/*   Updated: 2023/11/03 14:33:47 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_info *info, int idx)
{
	int	i;
	int	map_cnt;

	i = -1;
	map_cnt = info->map_h;
	if (idx != 0)
		map_cnt = idx;
	while (++i < map_cnt)
	{
		free(info->map[i]);
		info->map[i] = NULL;
	}
	free(info->map);
	info->map = NULL;
}

void	free_error_exit(char *message, t_info *info, int idx)
{
	free_map(info, idx);
	error_exit(message);
}

void	error_exit(char *message)
{
	ft_printf("Error\n");
	ft_printf("%s\n", message);
	exit(0);
}

void	destroy_window_exit(t_info *info)
{
	mlx_destroy_window(info->mlx, info->mlx_win);
	exit(0);
}

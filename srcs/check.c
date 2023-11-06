/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:31:37 by jongmlee          #+#    #+#             */
/*   Updated: 2023/11/06 18:26:49 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_path(t_info *info)
{
	t_point	*stack;
	t_point	cur;

	stack = malloc(info->map_w * info->map_h * sizeof(t_point));
	if (stack == NULL)
		free_error_exit(MALLOC_ERROR, info, 0);
	push(stack, info, info->hero_x, info->hero_y);
	while (info->top != 0)
	{
		cur = stack[info->top - 1];
		info->top--;
		if (info->flag == 1 && info->c_cnt == 0)
		{
			free(stack);
			return ;
		}
		push(stack, info, cur.x + 1, cur.y);
		push(stack, info, cur.x - 1, cur.y);
		push(stack, info, cur.x, cur.y + 1);
		push(stack, info, cur.x, cur.y - 1);
	}
	free(stack);
	free_error_exit(MAP_ERROR, info, 0);
}

void	check_map(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (++i < info->map_h)
	{
		j = -1;
		while (++j < info->map_w)
		{
			if ((!i || i == info->map_h - 1 || !j || j == info->map_w - 1)
				&& msb(info->map[i][j]) != '1')
				free_error_exit(MAP_ERROR, info, 0);
			if (msb(info->map[i][j]) == 'P')
			{
				info->hero_x = i;
				info->hero_y = j;
				info->p_cnt++;
			}
			info->e_cnt += (msb(info->map[i][j]) == 'E');
			info->c_cnt += (msb(info->map[i][j]) == 'C');
		}
	}
	if (info->e_cnt > 1 || info->p_cnt > 1 || info->c_cnt < 1)
		free_error_exit(MAP_ERROR, info, 0);
	check_path(info);
}

void	check_rectangle(t_info *info)
{
	int	i;
	int	len;

	i = -1;
	while (++i < info->map_h)
	{
		len = ft_strlen(info->map[i]);
		if (i == info->map_h - 1)
		{
			if (len == info->map_w)
				continue ;
			if (len - 1 == info->map_w && info->map[i][len - 1] == '\n')
				continue ;
			free_error_exit(MAP_ERROR, info, 0);
		}
		if (len - 1 != info->map_w)
		{
			free_error_exit(MAP_ERROR, info, 0);
			return ;
		}
	}
}

void	check_extension(char *map_path)
{
	int		i;
	int		j;
	char	*extension;

	i = 0;
	j = 0;
	while (map_path[i] != '\0')
		i++;
	if (i < 4)
		error_exit(MAP_ERROR);
	extension = EXTENSION_NAME;
	while (j < 4)
	{
		if (map_path[i - 4] != extension[j])
		{
			error_exit(MAP_ERROR);
			return ;
		}
		i++;
		j++;
	}
}

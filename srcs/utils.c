/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:21:18 by jongmlee          #+#    #+#             */
/*   Updated: 2023/11/03 14:33:52 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (*s != '\0')
	{
		s++;
		i++;
	}
	return (i);
}

void	push(t_point *stack, t_info *info, int x, int y)
{
	if (msb(info->map[x][y]) == '1' || (info->map[x][y] & MSB_VAL) != 0)
		return ;
	if (msb(info->map[x][y]) == 'C')
		info->c_cnt--;
	if (msb(info->map[x][y]) == 'E')
		info->flag = 1;
	stack[info->top].x = x;
	stack[info->top].y = y;
	info->map[x][y] |= MSB_VAL;
	info->top += 1;
}

char	msb(char var)
{
	return (var & ~MSB_VAL);
}

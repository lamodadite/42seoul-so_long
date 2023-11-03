#include "so_long.h"
#include "get_next_line.h"

void	check_path(t_info *info)
{
	t_point	*stack;
	t_point	cur;

	stack = malloc(info->map_w * info->map_h * sizeof(t_point));
	if (stack == NULL)
		error_exit(MALLOC_ERROR);
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
	error_exit(MAP_ERROR);
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
			if ((!i || i == info->map_h - 1) && MSB(info->map[i][j]) != '1')
				error_exit(MAP_ERROR);
			if ((!j || j == info->map_w - 1) && MSB(info->map[i][j]) != '1')
				error_exit(MAP_ERROR);
			if (MSB(info->map[i][j]) == 'P')
			{
				info->hero_x = i;
				info->hero_y = j;
				info->p_cnt++;
			}
			info->e_cnt += (MSB(info->map[i][j]) == 'E');
			info->c_cnt += (MSB(info->map[i][j]) == 'C');
		}
	}
	if (info->e_cnt > 1 || info->p_cnt > 1 || info->c_cnt < 1)
		error_exit(MAP_ERROR);
	check_path(info);
}

void	check_rectangle(t_info *info)
{
	int i;
	int	len;

	i = -1;
	while (++i < info->map_h)
	{
		len = ft_strlen(info->map[i]);
		if (i == info->map_h - 1)
		{
			if (len == info->map_w && info->map[i][len - 1] == '\n')
				continue;
			if (len == info->map_w + 1 && info->map[i][len - 1] != '\n')
			{
				error_exit(MAP_ERROR);
				return;
			}
		}
        else if (len - 1 != info->map_w)
		{
			ft_printf("%d\n", i);
            error_exit(MAP_ERROR);
            return;
        }
	}
}

void	load_map(t_info *info, char *map_path)
{
	char	*first_line;
	int		fd;
	int		i;

	i = -1;
	fd = open(map_path, O_RDONLY);
	first_line = get_next_line(fd);
	info->map_h = 1;
	info->map_w = ft_strlen(first_line) - 1;
	while (get_next_line(fd) != NULL)
		info->map_h += 1;
	close(fd);
	info->map = (char **)malloc(info->map_h * sizeof(char *));
	if (info->map == NULL)
		error_exit(MALLOC_ERROR);
	fd = open(map_path, O_RDONLY);
	while (++i < info->map_h)
		info->map[i] = get_next_line(fd);
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
	if (MSB(info->map[x][y]) == '1')
		mlx_put_image_to_window(info->mlx, info->mlx_win, info->img_wall,
			y * TILE_SIZE, x * TILE_SIZE);
	else if (MSB(info->map[x][y]) == 'C')
	{
		info->c_cnt++;
		mlx_put_image_to_window(info->mlx, info->mlx_win, info->img_collect,
			y * TILE_SIZE, x * TILE_SIZE);
	}
	else if (MSB(info->map[x][y]) == 'E')
		mlx_put_image_to_window(info->mlx, info->mlx_win, info->img_exit,
			y * TILE_SIZE, x * TILE_SIZE);
	else if (MSB(info->map[x][y]) == 'P' &&
		info->hero_x == 0 && info->hero_y == 0)
	{
		info->hero_x = x;
		info->hero_y = y;
	}
	else if (MSB(info->map[x][y]) != '0' && MSB(info->map[x][y]) != 'P')
		error_exit(MAP_ERROR);
}

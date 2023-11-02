#include "so_long.h"
#include "get_next_line.h"

void	load_map(t_info *info, char *map_path)
{
	char	*first_line;
	int		fd;
	int		i;
	
	i = -1;
	fd = open(map_path, O_RDONLY);
	first_line = get_next_line(fd);
	info->map_height = 1;
	info->map_width = ft_strlen(first_line) - 1;
	while (get_next_line(fd) != NULL)
		info->map_height += 1;
	close(fd);
	info->map = (char **)malloc(info->map_height * sizeof(char *));
	if (info->map == NULL)
		error_exit(MALLOC_ERROR);
	fd = open(map_path, O_RDONLY);	
	while (++i < info->map_height)
		info->map[i] = get_next_line(fd);
	close(fd);
}

void	init_map(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	info->c_cnt = 0;
	while (++i < info->map_height)
	{
		j = -1;
		while (++j < info->map_width)
		{
			mlx_put_image_to_window(info->mlx, info->mlx_win, info->img_empty, j * TILE_SIZE, i * TILE_SIZE);
			if (info->map[i][j] != 0)
				put_element(info, i , j);
		}
	}
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->img_hero, info->hero_y * TILE_SIZE, info->hero_x * TILE_SIZE);
}

void	put_element(t_info *info, int x, int y)
{
	if (info->map[x][y] == '1')
		mlx_put_image_to_window(info->mlx, info->mlx_win, info->img_wall, y * TILE_SIZE, x * TILE_SIZE);
	else if (info->map[x][y] == 'C')
	{
		info->c_cnt++;
		mlx_put_image_to_window(info->mlx, info->mlx_win, info->img_collect, y * TILE_SIZE, x * TILE_SIZE);
	}
	else if (info->map[x][y] == 'E')
		mlx_put_image_to_window(info->mlx, info->mlx_win, info->img_exit, y * TILE_SIZE, x * TILE_SIZE);
	else if (info->map[x][y] == 'P' && info->hero_x == 0 && info->hero_y == 0)
	{
		info->hero_x = x;
		info->hero_y = y;
	}
}
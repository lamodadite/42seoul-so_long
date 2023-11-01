#include "so_long.h"
#include "get_next_line.h"

void	init_map(t_info *info);

int	key_hook(int keycode, t_info *info)
{
	int origin_x;
	int	origin_y;

	origin_x = info->hero_x;
	origin_y = info->hero_y;
	if (keycode == 53)
	{
		mlx_destroy_window(info->mlx, info->mlx_win);
		exit(0);
	}
	else if (keycode == 2)
		info->hero_y += 1;
	else if (keycode == 0)
		info->hero_y -= 1;
	else if (keycode == 13)
		info->hero_x -= 1;
	else if (keycode == 1)
		info->hero_x += 1;
	if (info->map[info->hero_x][info->hero_y] == '1')
	{
		info->hero_x = origin_x;
		info->hero_y = origin_y;
	}
	else if (info->map[info->hero_x][info->hero_y] == 'C')
	{
		info->map[info->hero_x][info->hero_y] = '0';
		mlx_clear_window(info->mlx, info->mlx_win);
		info->move_cnt++;
		ft_printf("collect_cur -> %d\n", info->collect_cnt);
		ft_printf("%d\n", info->move_cnt);
		init_map(info);
	}
	else if (info->map[info->hero_x][info->hero_y] == 'E' && info->collect_cnt == 0)
	{
		mlx_destroy_window(info->mlx, info->mlx_win);
		exit(0);
	}
	else
	{
		mlx_clear_window(info->mlx, info->mlx_win);
		info->move_cnt++;
		ft_printf("collect_cur -> %d\n", info->collect_cnt);
		ft_printf("%d\n", info->move_cnt);
		init_map(info);
	}
	return (0);
}

void	put_element(t_info *info, int x, int y)
{
	if (info->map[x][y] == '1')
		mlx_put_image_to_window(info->mlx, info->mlx_win, info->img_wall, y * TILE_SIZE, x * TILE_SIZE);
	else if (info->map[x][y] == 'C')
	{
		info->collect_cnt++;
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

void	init_map(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	info->collect_cnt = 0;
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

void init(char *map_path, t_info *info)
{
	int	fd;
	char	*first_line;
	int i;
 
	i = -1;
	// map load
	fd = open(map_path, O_RDONLY);
	first_line = get_next_line(fd);
	info->map_height = 1;
	info->map_width = ft_strlen(first_line) - 1;
	while (get_next_line(fd) != NULL)
		info->map_height += 1;
	close(fd);
	info->map = (char **)malloc(info->map_height * sizeof(char *));
	if (info->map == NULL)
		exit(0); // malloc fail
	fd = open(map_path, O_RDONLY);	
	while (++i < info->map_height)
		info->map[i] = get_next_line(fd);
		// malloc 실패할 경우 지금까지 만든 map 전부 free 해야함
	close(fd);
	// mlx init
	info->mlx = mlx_init();
	// mlx-window init
	info->mlx_win = mlx_new_window(info->mlx, info->map_width * TILE_SIZE, info->map_height * TILE_SIZE, "so_long");
	// img init
	info->img_hero = mlx_xpm_file_to_image(info->mlx, "./textures/hero.xpm", &info->img_size, &info->img_size);
	info->img_wall = mlx_xpm_file_to_image(info->mlx, "./textures/wall.xpm", &info->img_size, &info->img_size);
	info->img_exit = mlx_xpm_file_to_image(info->mlx, "./textures/exit.xpm", &info->img_size, &info->img_size);
	info->img_collect = mlx_xpm_file_to_image(info->mlx, "./textures/collect.xpm", &info->img_size, &info->img_size);
	info->img_empty = mlx_xpm_file_to_image(info->mlx, "./textures/empty.xpm", &info->img_size, &info->img_size);
	// put images to window
	init_map(info);
	// set keyhook
	mlx_key_hook(info->mlx_win, key_hook, info);
}

int	main(int ac, char **av)
{
	t_info info;

	if (ac != 2)
	{
		perror("Error\n");
		exit(0);
	}
	// map valid check & load
	init(av[1], &info);
	mlx_loop(info.mlx);
	return (0);
}
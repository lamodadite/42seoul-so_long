#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# define TILE_SIZE 64

typedef struct s_info
{
	char	**map;
	char	*map_path;
	int		map_width;
	int		map_height;
	int		img_size;
	void	*mlx;
	void	*mlx_win;
	void	*img_hero;
	void	*img_wall;
	void	*img_exit;
	void	*img_collect;
	void	*img_empty;
	int		hero_x;
	int		hero_y;
	int		collect_max;
	int		collect_cur;
	int		move_cnt;
}	t_info;

size_t	ft_strlen(const char *s);
int	ft_printf(const char *str, ...);
void	init_map(t_info *info);

#endif
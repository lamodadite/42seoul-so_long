#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# define TILE_SIZE 64
# define MALLOC_ERROR "malloc failed"
# define ARG_ERROR "invalid argument"


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
	int		c_cnt;
	int		move_cnt;
}	t_info;

size_t	ft_strlen(const char *s);
void	init_map(t_info *info);
void	init_mlx(t_info *info);
void	destroy_window_exit(t_info *info);
void	error_exit(char *message);
void	load_map(t_info *info, char *map_path);
void 	init_image(t_info *info);
void	put_element(t_info *info, int x, int y);
void	move(t_info *info, int origin_x, int origin_y);
int		ft_printf(const char *str, ...);
int		key_hook(int keycode, t_info *info);


#endif
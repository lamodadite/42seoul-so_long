/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:20:57 by jongmlee          #+#    #+#             */
/*   Updated: 2023/11/06 17:00:04 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define MSB_VAL 0x80
# define TILE_SIZE 64
# define MALLOC_ERROR "malloc failed"
# define ARG_ERROR "invalid argument"
# define MAP_ERROR "invalid map"
# define EXTENSION_NAME ".ber"

typedef struct s_info
{
	char	**map;
	char	*map_path;
	int		map_w;
	int		map_h;
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
	int		e_cnt;
	int		p_cnt;
	int		flag;
	int		move_cnt;
	int		top;
}	t_info;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

size_t	ft_strlen(const char *s);
void	init_map(t_info *info);
void	init_mlx(t_info *info);
void	destroy_window_exit(t_info *info);
void	error_exit(char *message);
void	load_map(t_info *info, char *map_path);
void	init_image(t_info *info);
void	put_element(t_info *info, int x, int y);
void	move(t_info *info, int origin_x, int origin_y);
int		ft_printf(const char *str, ...);
int		key_hook(int keycode, t_info *info);
void	check_map(t_info *info);
void	push(t_point *stack, t_info *info, int x, int y);
void	check_rectangle(t_info *info);
char	msb(char var);
void	free_error_exit(char *message, t_info *info, int i);
void	free_map(t_info *info, int idx);
void	check_extension(char *map_path);

#endif
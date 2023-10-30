#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	int			x;
	int			y;
	int			img_width;
	int			img_height;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_vars;

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode == 2)
	{
		mlx_clear_window(vars->mlx, vars->win);
		vars->x += vars->img_width;
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, vars->x, vars->y);
	}
	else if (keycode == 0)
	{
		mlx_clear_window(vars->mlx, vars->win);
		vars->x -= vars->img_width;
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, vars->x, vars->y);
	}
	else if (keycode == 13)
	{
		mlx_clear_window(vars->mlx, vars->win);
		vars->y -= vars->img_height;
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, vars->x, vars->y);
	}
	else if (keycode == 1)
	{
		mlx_clear_window(vars->mlx, vars->win);
		vars->y += vars->img_height;
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, vars->x, vars->y);
	}
	return (0);
}

int	main(void)
{
	t_vars	vars;
	char	*relative_path = "./images.xpm";

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1440, 1080, "mario");
	vars.img = mlx_xpm_file_to_image(vars.mlx, relative_path, &vars.img_width, &vars.img_height);
	//img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, vars.x, vars.y);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
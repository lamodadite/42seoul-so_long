#include "so_long.h"
#include "get_next_line.h"

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
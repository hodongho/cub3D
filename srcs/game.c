/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: littley <littley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:08:00 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/07 18:28:15 by littley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->img = mlx_xpm_file_to_image(info->var.mlx, path,
			&img->width, &img->height);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp,
			&img->line_length, &img->endian);
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			texture[img->width * y + x] = img->addr[img->width * y + x];
	}
	mlx_destroy_image(info->var.mlx, img->img);
}

void	set_info(t_info *info)
{
	int		i;
	int		j;
	t_img	img;

	info->var.width = 1200;
	info->var.height = 700;
	info->move_speed = 0.2;
	i = -1;
	info->buff = ft_calloc(info->var.height, sizeof(int *));
	while (++i < info->var.height)
		info->buff[i] = ft_calloc(info->var.width, sizeof(int));
	j = -1;
	info->texture = ft_calloc(4, sizeof(int *));
	while (++j < 4)
		info->texture[j] = ft_calloc(P_HEIGHT * P_WIDTH, sizeof(int));
	load_image(info, info->texture[0], info->ea_path, &img);
	load_image(info, info->texture[1], info->we_path, &img);
	load_image(info, info->texture[2], info->so_path, &img);
	load_image(info, info->texture[3], info->no_path, &img);
}

int	mouse_move(t_info *info)
{
	const int	std_x = info->var.width / 2;
	int			x;
	int			y;

	mlx_mouse_get_pos(info->var.mlx, info->var.win, &x, &y);
	if (y < 0 || y > info->var.height)
		return (0);
	if (x > std_x + info->var.width / 10)
		press_left_right(KEY_RIGHT, info, 0.025);
	else if (x < std_x - info->var.width / 10)
		press_left_right(KEY_LEFT, info, 0.025);
	return (0);
}

int	main_loop(t_info *info)
{
	draw_cell_floor(info, &info->main);
	ray_casting(info, &info->ray);
	draw_game(info);
	mouse_move(info);
	if (info->map_sw)
		minimap(info);
	return (0);
}

int	into_game(t_info *info)
{
	info->var.mlx = mlx_init();
	set_info(info);
	set_info_dir(info);
	info->var.win = mlx_new_window(info->var.mlx,
			info->var.width, info->var.height, "cub3d");
	info->main.img = mlx_new_image(info->var.mlx,
			info->var.width, info->var.height);
	info->main.addr = (int *)mlx_get_data_addr(info->main.img, &info->main.bpp,
			&info->main.line_length, &info->main.endian);
	mlx_loop_hook(info->var.mlx, &main_loop, info);
	mlx_hook(info->var.win, PRESS, 0, &key_press, info);
	mlx_hook(info->var.win, RED_BUTTON, 0, &exit_hook, &info->var);
	mlx_loop(info->var.mlx);
	return (0);
}

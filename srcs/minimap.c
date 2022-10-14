/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:17:18 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/13 15:31:40 by yehyun           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_size(t_dlist *map, int *m_width, int *m_height)
{
	t_dlist	*tmp;
	int		tmp_width;

	*m_width = 0;
	*m_height = 0;
	tmp = map;
	while (tmp->next)
	{
		tmp_width = tmp->width;
		if (*m_width < tmp_width)
			*m_width = tmp_width;
		tmp = tmp->next;
	}
	*m_width *= MM_SIZE;
	*m_height = (tmp->height + 1) * MM_SIZE;
}

void	draw_pixel(t_img *minimap, int i, int j, int color)
{
	int	w_cnt;
	int	h_cnt;
	int	cnt;

	h_cnt = MM_SIZE;
	i *= MM_SIZE;
	j *= MM_SIZE;
	while (h_cnt)
	{
		cnt = 0;
		w_cnt = MM_SIZE;
		while (w_cnt)
		{
			minimap->addr[i * minimap->width + j + cnt] = color;
			cnt++;
			w_cnt--;
		}
		i++;
		h_cnt--;
	}
}

void	draw_pixel_pos(t_img *minimap, int i, int j)
{
	int	w_cnt;
	int	h_cnt;
	int	cnt;

	h_cnt = MM_SIZE;
	i *= MM_SIZE;
	j *= MM_SIZE;
	while (h_cnt)
	{
		cnt = 0;
		w_cnt = MM_SIZE;
		while (w_cnt)
		{
			if (!(w_cnt < 6 || w_cnt > MM_SIZE - 5
					|| h_cnt < 6 || h_cnt > MM_SIZE - 5))
				minimap->addr[i * minimap->width + j + cnt] = 0x60FFFF00;
			cnt++;
			w_cnt--;
		}
		i++;
		h_cnt--;
	}
}

void	draw_minimap(t_info *info, t_img *minimap, int i, int j)
{
	draw_pixel(minimap, i, j, 0xFF000000);
	if (j < info->map->width && info->map->line[j] != ' ')
	{
		if (info->map->line[j] == '0')
			draw_pixel(minimap, i, j, 0xA0FFFFFF);
		else if (info->map->line[j] == '1')
			draw_pixel(minimap, i, j, 0xA0000000);
		else if (info->map->line[j] == 'C' || info->map->line[j] == 'c')
			draw_pixel(minimap, i, j, 0xA0FF0000);
		else if (info->map->line[j] == 'O')
			draw_pixel(minimap, i, j, 0xA000FF00);
		else if (info->map->line[j] == 'X'
			&& info->access_cnt + 1 == info->sprite_cnt)
			draw_pixel(minimap, i, j, 0xA00000FF);
		if (i == (int)info->p_y && j == (int)info->p_x)
			draw_pixel_pos(minimap, i, j);
	}
}

int	minimap(t_info *info)
{
	t_img	minimap;
	t_dlist	*origin;
	int		i;
	int		j;

	ft_memset(&minimap, 0, sizeof(t_img));
	set_size(info->map, &minimap.width, &minimap.height);
	minimap.img = mlx_new_image(info->mlx, minimap.width, minimap.height);
	minimap.addr = (int *)mlx_get_data_addr(minimap.img, \
					&minimap.bpp, &minimap.line_length, &minimap.endian);
	origin = info->map;
	i = -1;
	while (++i < minimap.height / MM_SIZE)
	{
		j = -1;
		while (++j < minimap.width / MM_SIZE)
			draw_minimap(info, &minimap, i, j);
		info->map = info->map->next;
	}
	info->map = origin;
	mlx_put_image_to_window(info->mlx, info->win, minimap.img, \
					(W_WIDTH - minimap.width) / 2, \
					(W_HEIGHT - minimap.height) / 2);
	mlx_destroy_image(info->mlx, minimap.img);
	return (0);
}

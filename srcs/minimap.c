/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:17:18 by yehyun            #+#    #+#             */
/*   Updated: 2022/10/07 17:01:43 by yehyun           ###   ########seoul.kr  */
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

void	draw_minimap(t_info *info, t_dlist *map, t_img *minimap)
{
	int	i;
	int	j;

	i = -1;
	while (++i < minimap->height / MM_SIZE)
	{
		j = -1;
		while (++j < minimap->width / MM_SIZE)
		{
			if (j < map->width && map->line[j] != ' ')
			{
				if (map->line[j] == '1')
					draw_pixel(minimap, i, j, 0xA0000000);
				else if (map->line[j] == '0')
					draw_pixel(minimap, i, j, 0xA0FFFFFF);
				if (i == (int)info->p_y && j == (int)info->p_x)
					draw_pixel(minimap, i, j, 0xA0FF0000);
			}
			else
				draw_pixel(minimap, i, j, 0xFF000000);
		}
		map = map->next;
	}
}

int	minimap(t_info *info)
{
	t_img	minimap;

	ft_memset(&minimap, 0, sizeof(t_img));
	set_size(info->map, &minimap.width, &minimap.height);
	minimap.img = mlx_new_image(info->var.mlx, minimap.width, minimap.height);
	minimap.addr = (int *)mlx_get_data_addr(minimap.img, \
					&minimap.bpp, &minimap.line_length, &minimap.endian);
	draw_minimap(info, info->map, &minimap);
	mlx_put_image_to_window(info->var.mlx, info->var.win, \
					minimap.img, \
					(info->var.width - minimap.width) / 2, \
					(info->var.height - minimap.height) / 2);
	return (0);
}

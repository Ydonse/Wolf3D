/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:20:14 by ydonse            #+#    #+#             */
/*   Updated: 2019/05/15 11:04:30 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_square(t_main *s, t_dpos orig, t_dpos dest, t_image *wall)
{
	t_position	coord;
	int			perx;
	int			pery;
	int			pix_tex;

	coord.x = orig.x;
	while (coord.x < dest.x)
	{
		coord.y = orig.y;
		perx = (int)(percent(coord.x - orig.x, dest.x - orig.x) * 100);
		while (coord.y < dest.y)
		{
			coord.y++;
			pery = (int)(percent(coord.y - orig.y, dest.y - orig.y) * 100);
			pix_tex = (int)(pery * wall->h / 100.0) * wall->w
			+ (int)(perx * wall->w / 100.0);
			if (pix_tex >= 0 && pix_tex < (wall->h * wall->w))
				set_pixel(s->sdl->map, wall->tex[pix_tex], coord);
		}
		coord.x++;
	}
}

void	get_case_color(t_main *s, t_dpos orig, t_dpos dest, t_case pos)
{
	if (pos.type == 'm')
		draw_square(s, orig, dest, s->areas[0].wall_n);
	else if (pos.type == '.' || (pos.type == 'p' && pos.block == 0))
	{
		s->sdl->map->color_tmp = 0xB0B0B0FF;
		draw_rect(s->sdl->map, orig, dest);
	}
	else if (pos.type == 'j')
	{
		s->sdl->map->color_tmp = 0xA0A0A0FF;
		draw_rect(s->sdl->map, orig, dest);
	}
	else if (pos.type == 'p' && pos.block == 1)
	{
		draw_square(s, orig, dest, s->door);
	}
	else if (pos.type == 't')
	{
		s->sdl->map->color_tmp = 0xB0B0B0FF;
		draw_rect(s->sdl->map, orig, dest);
		draw_square(s, orig, dest, s->coupe);
	}
}

void	draw_black(t_main *s)
{
	t_position xy;

	xy.x = -1;
	while (xy.x++ < WIDTH)
	{
		xy.y = -1;
		while (xy.y++ < HEIGHT)
			set_pixel(s->sdl->map, 0x000000FF, xy);
	}
}

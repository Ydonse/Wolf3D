/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:20:14 by ydonse            #+#    #+#             */
/*   Updated: 2019/05/03 18:26:36 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	get_case_color(t_main *s, t_position orig, t_position dest, char type)
{
	if (type == 'm')
	{
		int i;
		int j;
		t_position	coord;
		int perx;
		int pery;

		orig.x = orig.x < 0 ? 0 : orig.x;
		orig.y = orig.y < 0 ? 0 : orig.y;
		dest.x = dest.x > WIDTH ? WIDTH : dest.x;
		dest.y = dest.y > HEIGHT ? HEIGHT : dest.y;
		i = orig.x;
		while (i < dest.x)
		{
			j = orig.y;
			while (j < dest.y)
			{
				coord.x = i;
				coord.y = j++;
				perx = (int)(percent(coord.x - orig.x, dest.x - orig.x) * 100);
				pery = (int)(percent(coord.y - orig.y, dest.y - orig.y) * 100);
				// printf("percent x = %d\n", perx);
				// printf("percent y = %d\n", pery);
				// printf("percent y = %d\n", pery * s->wall->h / 100 - 1);
				// printf("percent = %d\n", (int)per * (s->wall->w * s->wall->h) / 100);
				// set_pixel(s->sdl->map, SKY, coord);
				set_pixel(s->sdl->map, s->wall->tex[(pery * s->wall->h / 100) * s->wall->w - 1 + (perx * s->wall->w / 100) - 1], coord);
			}
			i++;
		}
	}
	else if (type == '.')
	{
		s->sdl->map->color_tmp = 0xB0B0B0FF;
		draw_rect(s->sdl, s->sdl->map, orig, dest);
	}
	else if (type == 'j')
	{
		s->sdl->map->color_tmp = 0xA0A0A0FF;
		draw_rect(s->sdl, s->sdl->map, orig, dest);
	}
	else if (type == 'p')
	{
		s->sdl->map->color_tmp = 0xCD7006FF;
		draw_rect(s->sdl, s->sdl->map, orig, dest);
	}
}

void	draw_black(t_main *s)
{
	t_position xy;

	xy.x = -1;
	while (xy.x++ < WIDTH)
	{
		xy.y = -1;
		while (xy.y++ < s->sdl->y_o)
			set_pixel(s->sdl->map, 0x000000FF, xy);
	}
	xy.x = -1;
	while (xy.x++ < s->sdl->x_o)
	{
		xy.y = -1;
		while (xy.y++ < HEIGHT)
			set_pixel(s->sdl->map, 0x000000FF, xy);
	}
	xy.y = -1;
	while (xy.x++ < WIDTH)
	{
		xy.y = HEIGHT - s->sdl->y_o - 1;
		while (xy.y++ < HEIGHT)
			set_pixel(s->sdl->map, 0x000000FF, xy);
	}
	xy.x = WIDTH - s->sdl->x_o - 1;
	while (xy.x++ < WIDTH)
	{
		xy.y = -1;
		while (xy.y++ < HEIGHT)
			set_pixel(s->sdl->map, 0x000000FF, xy);
	}
}

void	draw_minimap(t_main *s)
{
	t_position orig;
	t_position dest;
	int i;
	int j;

	i = -1;
	j = 0;
	while (++i < s->height)
	{
		while (j < s->width)
		{
			orig.x = SPACE * j + s->sdl->x_o;
			orig.y = SPACE * i + s->sdl->y_o;
			dest.x = orig.x + SPACE;
			dest.y = orig.y + SPACE;
			get_case_color(s, orig, dest, s->map[i][j++].type);
		}
		j = 0;
	}
	draw_player(s, s->sdl);
	raycast_visualization(s);
	draw_black(s);
	update_image(s, s->sdl->map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:20:14 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/26 11:15:39 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "wolf3d.h"

void	get_case_color(t_main *s, t_position orig, t_position dest, char type)
{
	if (type == 'm')
	{
		s->sdl->map->color_tmp = 0x9a5444FF;
		draw_rect(s->sdl, s->sdl->map, orig, dest);
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
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:20:14 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/25 17:19:32 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_minimap(t_main *s)
{
	t_position orig;
	t_position dest;
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < s->height)
	{
		while (j < s->width)
		{
			orig.x = SPACE * j + s->sdl->x_o;
			orig.y = SPACE * i + s->sdl->y_o;
			dest.x = orig.x + SPACE;
			dest.y = orig.y + SPACE;
			if (s->map[i][j].type == 'm')
			{
				s->sdl->map->color_tmp = 0x9a5444FF;
				draw_rect(s->sdl, s->sdl->map, orig, dest);
			}
			else if (s->map[i][j].type == '.')
			{
				s->sdl->map->color_tmp = 0xB0B0B0FF;
				draw_rect(s->sdl, s->sdl->map, orig, dest);
			}
			else if (s->map[i][j].type == 'j')
			{
				s->sdl->map->color_tmp = 0xA0A0A0FF;
				draw_rect(s->sdl, s->sdl->map, orig, dest);
			}
			j++;
		}
		// ft_putchar('\n');
		j = 0;
		i++;
	}
}

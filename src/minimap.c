/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:20:14 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/25 16:49:13 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_minimap(t_main *s)
{
	int o = 50;
	t_position orig = {50 ,50};
	t_position dest = {750 ,750};
	// t_position orig = {WIDTH / 2 - (SPACE * s->width) ,HEIGHT / 2 - (SPACE * s->height)};
	// t_position dest = {750 ,750};
	int i;
	int j;

	i = 0;
	j = 0;
	// s->sdl->map->color_tmp = 0x2222FFFF;
	// draw_rect(s->sdl, s->sdl->map, orig, dest);
	while (i < s->height)
	{
		while (j < s->width)
		{
			if (s->map[i][j].type == 'm')
			{
				// ft_putstr("true ");
				orig.x = SPACE * j;
				orig.y = SPACE * i;
				dest.x = orig.x + SPACE;
				dest.y = orig.y + SPACE;
				s->sdl->map->color_tmp = 0xFFFFFFFF;
				draw_rect(s->sdl, s->sdl->map, orig, dest);
			}
			else if (s->map[i][j].type == '.')
			{
				// ft_putstr("true ");
				orig.x = SPACE * j;
				orig.y = SPACE * i;
				dest.x = orig.x + SPACE;
				dest.y = orig.y + SPACE;
				s->sdl->map->color_tmp = 0x00000000;
				draw_rect(s->sdl, s->sdl->map, orig, dest);
			}
			j++;
		}
		// ft_putchar('\n');
		j = 0;
		i++;
	}
}

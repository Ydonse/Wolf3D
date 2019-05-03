/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:58:12 by malluin           #+#    #+#             */
/*   Updated: 2019/05/03 18:07:22 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_print_map(t_main	*s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < s->height)
	{
		while (j < s->width)
		{
			ft_putchar(s->map[i][j].type);
			ft_putchar(s->map[i][j].zone);
			ft_putnbr(s->map[i][j].block);
			ft_putchar(' ');
			j++;
		}
		i++;
		ft_putchar('\n');
		j = 0;
	}
}

void	set_pixel_debug(t_sdl *sdl, t_dpos coord)
{
	if (coord.x >=0 && coord.x < WIDTH && coord.y >= 0 && coord.y < HEIGHT)
	{
		sdl->map->content[(int)(sdl->x_o + coord.x * SPACE + (sdl->y_o + coord.y * SPACE) * WIDTH)] = 0x000000FF;
	}
}

void	draw_debug_rect(t_sdl *sdl, t_texture *text, Uint32 color, t_dpos orig)
{
	int		i;
	int		j;
	t_position	coord;
	t_dpos		dest;

	orig.x = sdl->x_o + orig.x * SPACE;
	orig.y = sdl->y_o + orig.y * SPACE;
	orig.x -= 3;
	orig.y -= 3;
	dest.x = orig.x + 6;
	dest.y = orig.y + 6;

	i = orig.x;
	while (i < dest.x)
	{
		j = orig.y;
		while (j < dest.y)
		{
			coord.x = i;
			coord.y = j++;
			// printf("x = %d, y = %d\n", coord.x, coord.y);
			set_pixel(text, color, coord);
		}
		i++;
	}
}

// t_position orig;
// t_position dest;
// int i;
// int j;
//
// i = -1;
// j = 0;
// while (++i < s->height)
// {
// 	while (j < s->width)
// 	{
// 		orig.x = SPACE * j + s->sdl->x_o;
// 		orig.y = SPACE * i + s->sdl->y_o;
// 		dest.x = orig.x + SPACE;
// 		dest.y = orig.y + SPACE;
// 		get_case_color(s, orig, dest, s->map[i][j++].type);
// 	}
// 	j = 0;
// }

// while (j < s->width)
// {
// 	orig.x = SPACE * j + s->sdl->x_o;
// 	orig.y = SPACE * i + s->sdl->y_o;
// 	dest.x = orig.x + SPACE;
// 	dest.y = orig.y + SPACE;
// 	get_case_color(s, orig, dest, s->map[i][j++].type);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:20:14 by ydonse            #+#    #+#             */
/*   Updated: 2019/05/10 18:13:42 by ydonse           ###   ########.fr       */
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
	else if (pos.type == '.')
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
	else if (pos.type == 'p' && pos.block == 0)
	{
		s->sdl->map->color_tmp = 0xB0B0B0FF;
		draw_rect(s->sdl->map, orig, dest);
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
	t_dpos orig;
	t_dpos dest;
	int			i;
	int			j;
	double			debut_x;
	double			debut_y;
	int			bloc_x;
	int			bloc_y;

	debut_x = (WIDTH / SPACE) / 2;
	debut_y = (HEIGHT / SPACE) / 2;

	bloc_y = s->player_pos.y < debut_y ? 0 : (int)(s->player_pos.y - debut_y);
	bloc_x = s->player_pos.x < debut_x ? 0 : (int)(s->player_pos.x - debut_x);
	i = 0;
	j = 0;
	// printf("debut_x = %d, debut_y = %d, position player y = %f\n", debut_x, debut_y, s->player_pos.y);
	while (bloc_y < s->height)
	{
		while (bloc_x < s->width)
		{
			orig.x = SPACE * j;
			orig.y = SPACE * i;
			dest.x = orig.x + SPACE;
			dest.y = orig.y + SPACE;

			get_case_color(s, orig, dest, s->map[bloc_y][bloc_x++]);
			j++;
		}
		j = 0;
		bloc_x = s->player_pos.x < debut_x ? 0 : (int)(s->player_pos.x - debut_x);
		bloc_y++;
		i++;
	}
	draw_player(s, s->sdl, s->player_pos.x < debut_x ? s->player_pos.x : s->player_pos.x - (s->player_pos.x - debut_x), s->player_pos.y < debut_y ? s->player_pos.y : s->player_pos.y - (s->player_pos.y - debut_y));
	raycast_visualization(s);
	draw_black(s);
	update_image(s, s->sdl->map);
}

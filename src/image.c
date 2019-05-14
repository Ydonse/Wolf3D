/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 10:19:27 by ydonse            #+#    #+#             */
/*   Updated: 2019/05/13 13:44:05 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	set_pixel(t_texture *text, Uint32 color, t_position coord)
{
	if (coord.x >= 0 && coord.x < WIDTH && coord.y >= 0 && coord.y < HEIGHT)
	{
		text->content[coord.x + coord.y * WIDTH] = color;
	}
}

void	draw_interface(t_main *s)
{
	t_position	coord;
	int			j;
	t_dpos orig;
	double		perx;
	double		pery;

	orig.x = 0;
	orig.y = HEIGHT - s->interface->h;
	coord.y = 0;
	coord.x = 0;
	j = 0;
	while (coord.x < WIDTH)
	{
		j = orig.y;
		perx = (double)coord.x / (double)WIDTH;
		while (j < HEIGHT)
		{
			coord.y = j++;
			pery = (percent(coord.y - orig.y, HEIGHT - orig.y));
			set_pixel(s->sdl->game, s->interface->tex
			[(int)(pery * (double)s->interface->h * s->interface->w
			+ (perx * (double)s->interface->w))], coord);
		}
		coord.x++;
	}
}

void	draw_weapon(t_main *s, double perx, short orig_x, short orig_y)
{
	t_position	coord;
	double		pery;
	t_dpos dest;
	int			pix_tex;

	dest.x = WIDTH / 2 + (s->weapon.image[s->weapon.current]->w / 2);
	dest.y = HEIGHT - s->interface->h;
	coord.x = orig_x;
	while (coord.x < dest.x)
	{
		coord.y = orig_y;
		perx = (int)(percent(coord.x - orig_x, dest.x - orig_x) * 100);
		while (coord.y < dest.y)
		{
			coord.y++;
			pery = (int)(percent(coord.y - orig_y, dest.y - orig_y) * 100);
			pix_tex = (int)(pery * s->weapon.image[s->weapon.current]->h
			/ 100.0) * s->weapon.image[s->weapon.current]->w
			+ (int)(perx * s->weapon.image[s->weapon.current]->w / 100.0);
			if (s->weapon.image[s->weapon.current]->tex[pix_tex] != 0x98008800)
				set_pixel(s->sdl->game, s->weapon.image
				[s->weapon.current]->tex[pix_tex], coord);
		}
		coord.x++;
	}
}

void	draw_rect(t_texture *text, t_dpos orig, t_dpos dest)
{
	int			i;
	int			j;
	t_position	coord;

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
			set_pixel(text, text->color_tmp, coord);
		}
		i++;
	}
}

void	draw_player(t_main *s, t_sdl *sdl, double bloc_x, double bloc_y)
{
	t_dpos orig;
	t_dpos dest;

	orig.x = (bloc_x - PLAYER_SIZE / 2) * SPACE;
	dest.x = (bloc_x + PLAYER_SIZE / 2) * SPACE;
	orig.y = (bloc_y - PLAYER_SIZE / 2) * SPACE;
	dest.y = (bloc_y + PLAYER_SIZE / 2) * SPACE;
	// printf("ori x = %f, ori y = %f, position player x = %f\n", orig.x, orig.y, s->player_pos.x);
	// printf("bloc x = %f, bloc y = %f, position player x = %f\n", bloc_x, bloc_y, s->player_pos.x);
	sdl->map->color_tmp = 0xFF0000FF;
	draw_rect(sdl->map, orig, dest);
}

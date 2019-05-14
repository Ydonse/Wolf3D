/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:20:14 by ydonse            #+#    #+#             */
/*   Updated: 2019/05/14 18:55:39 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	initialize_minimap(t_main *s)
{
	s->min.bloc_y = s->player_pos.y < HALF_Y ? 0 : (int)(s->player_pos.y
		- HALF_Y);
	s->min.bloc_y = s->min.bloc_y >= s->height - (HEIGHT / SPACE)
	&& s->player_pos.y > s->height - HALF_Y - 1 ? s->height
	- (HEIGHT / SPACE) : s->min.bloc_y;
	s->min.bloc_y_cp = s->min.bloc_y;
	s->min.bloc_x = s->player_pos.x < HALF_X ? 0 : (int)(s->player_pos.x
	- HALF_X);
	s->min.bloc_x = s->min.bloc_x >= s->width - (WIDTH / SPACE)
	&& s->player_pos.x > s->width - HALF_X - 1 ? s->width
	- (WIDTH / SPACE) : s->min.bloc_x;
	s->min.per_pos_x = s->player_pos.x - (int)s->player_pos.x;
	s->min.per_pos_y = s->player_pos.y - (int)s->player_pos.y;
}

void	get_x_coord(t_main *s, int j)
{
	if (s->player_pos.x < HALF_X || (s->player_pos.x >= HALF_X
		&& s->player_pos.x >= s->width - HALF_X - 1))
	{
		s->min.orig.x = SPACE * j;
		s->min.dest.x = s->min.orig.x + SPACE;
	}
	else if (s->player_pos.x >= HALF_X && s->player_pos.x < s->width
		- HALF_X - 1)
	{
		if (j == 0)
		{
			s->min.orig.x = j - SPACE + ((1 - s->min.per_pos_x) * SPACE);
			s->min.dest.x = (s->min.orig.x + SPACE);
		}
		else if (j != 0)
		{
			s->min.orig.x = SPACE * j - (s->min.per_pos_x * SPACE);
			s->min.dest.x = s->min.orig.x + SPACE;
		}
	}
}

void	get_y_coord(t_main *s, int i)
{
	if (s->player_pos.y < HALF_Y || (s->player_pos.y
		>= HALF_Y && s->player_pos.y >= s->height - HALF_Y - 1))
	{
		s->min.orig.y = SPACE * i;
		s->min.dest.y = s->min.orig.y + SPACE;
	}
	else if (s->player_pos.y >= HALF_Y && s->player_pos.y
		< s->height - HALF_Y - 1)
	{
		if (i == 0)
		{
			s->min.orig.y = i - SPACE + ((1 - s->min.per_pos_y) * SPACE);
			s->min.dest.y = (s->min.orig.y + SPACE);
		}
		else if (i != 0)
		{
			s->min.orig.y = SPACE * i - (s->min.per_pos_y * SPACE);
			s->min.dest.y = s->min.orig.y + SPACE;
		}
	}
}

void	draw_background(t_main *s, int i, int j)
{
	while (s->min.bloc_y_cp < s->height)
	{
		while (s->min.bloc_x < s->width)
		{
			get_x_coord(s, j);
			get_y_coord(s, i);
			get_case_color(s, s->min.orig, s->min.dest,
			s->map[s->min.bloc_y][s->min.bloc_x++]);
			j++;
		}
		j = 0;
		s->min.bloc_x = s->player_pos.x < HALF_X ? 0 : (int)(s->player_pos.x
		- HALF_X);
		s->min.bloc_x = s->min.bloc_x >= s->width
		- (WIDTH / SPACE) && s->player_pos.x > s->width - HALF_X - 1 ? s->width
		- (WIDTH / SPACE) : s->min.bloc_x;
		s->min.bloc_y++;
		s->min.bloc_y_cp++;
		i++;
	}
}

void	draw_minimap(t_main *s, int i, int j)
{
	double new_player_pos_x;
	double new_player_pos_y;

	draw_black(s);
	initialize_minimap(s);
	draw_background(s, i, j);
	new_player_pos_x = s->player_pos.x - HALF_X <= 0 ? s->player_pos.x
	: s->player_pos.x - (s->player_pos.x - HALF_X);
	new_player_pos_y = s->player_pos.y - HALF_Y <= 0 ? s->player_pos.y
	: s->player_pos.y - (s->player_pos.y - HALF_Y);
	if (s->player_pos.x > s->width - HALF_X - 1)
		new_player_pos_x = WIDTH / SPACE - (s->width - s->player_pos.x);
	if (s->player_pos.y > s->height - HALF_Y)
		new_player_pos_y = HEIGHT / SPACE - (s->height - s->player_pos.y);
	draw_player(s, s->sdl, new_player_pos_x, new_player_pos_y);
	raycast_visualization(s);
	update_image(s, s->sdl->map);
}

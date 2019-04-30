/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:12:40 by malluin           #+#    #+#             */
/*   Updated: 2019/04/30 18:04:54 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		keyboard_controls(t_main *s, int key)
{
	// t_position orig = {0,0};
	// t_position dest = {WIDTH,HEIGHT};
		if (key == SDLK_ESCAPE)
			return (0);
		else if (key == SDLK_e)
			open_door(s);
		else if (key == SDLK_m)
			s->active_map = !s->active_map;
	return (1);
}

Uint32	darken_color(Uint32 color, int perc)
{
	int		r;
	int		g;
	int		b;

	perc = perc > 100 ? 100 : perc;
	perc = perc < 0 ? 0 : perc;
	r = color >> 24 & 0xFF;
	g = color >> 16 & 0xFF;
	b = color >> 8 & 0xFF;
	r = (r * (100 - perc)) / 100;
	g = (g * (100 - perc)) / 100;
	b = (b * (100 - perc)) / 100;
	// printf("%08x  ",color);
	color = (r << 24) | (g << 16) | (b << 8) | 0x000000FF;
	// printf("%08x\n",color);
	return (color);
}

void	draw_wall_slice(t_main *s, double dist, int x)
{
	int			projected_h;
	int			i;
	int			bwall;
	int			ewall;
	t_position	pix;
	Uint32		color;

	i = 0;
	projected_h = ((double)s->proj_distance / dist);
	bwall = s->viewline - projected_h / 2;
	ewall = s->viewline + projected_h / 2;
	bwall = bwall <= 0 ? 0 : bwall;
	ewall = ewall > HEIGHT ? HEIGHT : ewall;
	pix.x = x;
	color = SKY;
	while (i < bwall)
	{
		pix.y = i++;
		set_pixel(s->sdl->game, color, pix);
	}
	color = WALL;
	while (bwall < ewall)
	{
		pix.y = bwall++;
		set_pixel(s->sdl->game, darken_color(color, (int)(dist * 100.0 / 8.0)), pix);
	}
	color = GROUND;
	while (ewall < HEIGHT)
	{
		pix.y = ewall++;
		set_pixel(s->sdl->game, color, pix);
	}
}

void	raycast_visualization(t_main *s)
{
	double	angle;
	double	dist;
	double correc;
	int		i;

	i = 0;
	angle = s->p_angle + s->fov / 2.0;
	correc = raycast(s, s->p_angle);
	while (i < PROJ_WIDTH)
	{
		dist = raycast(s, angle);
		if (dist <= 0)
			printf("FAIL angle:%f val:%f\n", angle, dist);
		dist *= cos(to_rad((double)s->p_angle - angle));
		if (dist > 0)
			draw_wall_slice(s, dist, i);
		angle -= s->fov / (double)PROJ_WIDTH;
		i++;
	}
	// printf("angle fin: %f\n", angle);
}

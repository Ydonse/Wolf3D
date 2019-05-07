/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:12:40 by malluin           #+#    #+#             */
/*   Updated: 2019/05/07 14:09:17 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

Uint32	darken_color(Uint32 color, double perc)
{
	int		r;
	int		g;
	int		b;

	if (perc <= 1.0)
		return (color);
	perc = perc > 100.0 ? 100.0 : perc;
	perc = perc < 0.0 ? 0.0 : perc;
	r = color >> 24 & 0xFF;
	g = color >> 16 & 0xFF;
	b = color >> 8 & 0xFF;
	r = (r * (100.0 - perc)) / 100;
	g = (g * (100.0 - perc)) / 100;
	b = (b * (100.0 - perc)) / 100;
	color = (r << 24) | (g << 16) | (b << 8) | 0x000000FF;
	return (color);
}

void	draw_tex_slice(t_main *s, t_ray ray, t_slice sl, double dist)
{
	double		pery;
	double		perx;

	if (ray.orientation == 'N' || ray.orientation == 'S')
		perx = (ray.dpos.x - (int)ray.dpos.x);
	else if (ray.orientation == 'E' || ray.orientation == 'W')
		perx = (ray.dpos.y - (int)ray.dpos.y);
	else
		return;
	dist *= 12.5;
	while (sl.pix.y < HEIGHT)
	{
		pery = (double)(sl.pix.y - sl.bwall) / (double)(sl.ewall - sl.bwall);
		sl.color = sl.tex->tex[(int)(pery * s->door->h) * s->door->w
			+ (int)(perx * s->door->w)];
		set_pixel(s->sdl->game, darken_color(sl.color, dist), sl.pix);
		sl.pix.y++;
	}
}

t_image	*choose_texture(t_main *s, t_ray ray)
{
	if (ray.type == 'p')
		return (s->door);
	else
	{
		if (ray.orientation == 'N')
			return (s->areas[ray.zone].wall_n);
		else if (ray.orientation == 'W')
			return (s->areas[ray.zone].wall_w);
		else if (ray.orientation == 'E')
			return (s->areas[ray.zone].wall_e);
		else
			return (s->areas[ray.zone].wall_s);
	}
}

void	draw_wall_slice(t_main *s, t_ray ray, double dist, int x)
{
	int			projected_h;
	t_slice		sl;

	dist = dist <= 0.01 ? 0.01 : dist;
	projected_h = ((double)s->proj_distance / dist);
	sl.bwall = s->viewline - projected_h / 2;
	sl.ewall = s->viewline + projected_h / 2;
	sl.pix.x = x;
	sl.pix.y = -1;
	sl.color = SKY;
	while (++(sl.pix.y) < sl.bwall && sl.pix.y < HEIGHT)
		set_pixel(s->sdl->game, sl.color, sl.pix);
	sl.tex = choose_texture(s, ray);
	draw_tex_slice(s, ray, sl, dist);
	sl.ewall = sl.ewall > HEIGHT ? HEIGHT : sl.ewall;
	sl.ewall = sl.ewall < 0 ? 0 : sl.ewall;
	sl.color = GROUND;
	dist *= 12.5;
	while (sl.ewall < HEIGHT)
	{
		sl.pix.y = sl.ewall++;
		dist *= 0.987;
		set_pixel(s->sdl->game, darken_color(sl.color, dist), sl.pix);
	}
}

void	raycast_visualization(t_main *s)
{
	double	angle;
	double	dist;
	double 	correc;
	int		i;
	t_ray	ray;

	i = 0;
	angle = s->p_angle + s->fov / 2.0;
	ray = raycast(s, s->p_angle);
	correc = ray.dist;
	while (i < PROJ_WIDTH)
	{
		ray = raycast(s, angle);
		dist = ray.dist;
		dist *= cos(to_rad((double)s->p_angle - angle));
		if (dist > 0 && s->active_map == 0)
			draw_wall_slice(s, ray, dist, i);
		angle -= s->fov / (double)PROJ_WIDTH;
		i++;
	}
	// printf("angle fin: %f\n", angle);
}

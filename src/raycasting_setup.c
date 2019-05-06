/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:12:40 by malluin           #+#    #+#             */
/*   Updated: 2019/05/06 19:07:49 by malluin          ###   ########.fr       */
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

void	draw_tex_slice(t_main *s, t_ray ray, t_position *pix, int ewall, double dist, int b)
{
	Uint32		color;
	double		pery;
	double		perx;

	color = MIXSW;
	if (ray.orientation == 'N' || ray.orientation == 'S')
		perx = (ray.dpos.x - (int)ray.dpos.x);
	else if (ray.orientation == 'E' || ray.orientation == 'W')
		perx = (ray.dpos.y - (int)ray.dpos.y);
	else
		return;
	while (pix->y < ewall)
	{
		pery = (double)(pix->y - b) / (double)(ewall - b);
		color = s->wall->tex[(int)(pery * s->wall->h) * s->wall->w
			+ (int)(perx * s->wall->w)];
		set_pixel(s->sdl->game, darken_color(color, (dist * 100.0 / 8.0)), *pix);
		pix->y++;
		color = WALL;
	}
}

void	draw_wall_slice(t_main *s, t_ray ray, double dist, int x)
{
	int			projected_h;
	int			bwall;
	int			ewall;
	t_position	pix;
	Uint32		color;

	dist = dist <= 0.01 ? 0.01 : dist;
	projected_h = ((double)s->proj_distance / dist);
	bwall = s->viewline - projected_h / 2;
	ewall = s->viewline + projected_h / 2;
	// bwall = bwall <= 0 ? 0 : bwall;
	pix.x = x;
	pix.y = -1;
	color = SKY;
	while (++(pix.y) < bwall)
		set_pixel(s->sdl->game, color, pix);

	draw_tex_slice(s, ray, &pix, ewall, dist, bwall);
	ewall = ewall > HEIGHT ? HEIGHT : ewall;
	color = GROUND;
	while (ewall < HEIGHT)
	{
		pix.y = ewall++;
		dist *= 0.987;
		set_pixel(s->sdl->game, darken_color(color, (dist * 100.0 / 8.0)), pix);
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

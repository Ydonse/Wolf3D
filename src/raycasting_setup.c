/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:12:40 by malluin           #+#    #+#             */
/*   Updated: 2019/05/09 13:44:40 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

Uint32	darken_color(Uint32 color, double perc)
{
	int		r;
	int		g;
	int		b;

	if (perc >= 0.995)
		return (color);
	perc = perc <= 0.01 ? 0.01 : perc;
	r = color >> 24 & 0xFF;
	g = color >> 16 & 0xFF;
	b = color >> 8 & 0xFF;
	r *= perc;
	g *= perc;
	b *= perc;
	color = (r << 24) | (g << 16) | (b << 8);
	return (color);
}

void	draw_ground_sky(t_main *s, int x)
{
	t_position	pix;

	pix.x = x;
	pix.y = -1;
	while (++pix.y < s->viewline)
		set_pixel(s->sdl->game, SKY, pix);
	set_pixel(s->sdl->game, GROUND, pix);
	while (++pix.y < HEIGHT - s->interface->h)
		set_pixel(s->sdl->game, GROUND, pix);
}

void	raycast_visualization(t_main *s)
{
	double	angle;
	double	dist;
	double	correc;
	int		i;
	t_ray	ray;

	i = 0;
	angle = s->p_angle + s->fov / 2.0;
	ray = raycast(s, s->p_angle);
	correc = ray.dist;
	while (i < PROJ_WIDTH)
	{
		ray = raycast(s, angle);
		ray.angle = angle;
		dist = ray.dist;
		dist *= cos(to_rad((double)s->p_angle - angle));
		if (dist > 0 && s->active_map == 0)
			draw_wall_slice(s, ray, dist, i);
		else
			draw_ground_sky(s, i);
		angle -= s->fov / (double)PROJ_WIDTH;
		i++;
	}
	draw_weapon(s);
}

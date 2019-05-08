/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:12:40 by malluin           #+#    #+#             */
/*   Updated: 2019/05/08 17:58:58 by malluin          ###   ########.fr       */
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

void	draw_tex_slice(t_main *s, t_ray ray, t_slice sl, double dist)
{
	double		pery;
	double		perx;
	int			px_tex;
	double		diff;

	if (ray.orientation == 'N' || ray.orientation == 'S')
		perx = (ray.dpos.x - (int)ray.dpos.x);
	else if (ray.orientation == 'E' || ray.orientation == 'W')
		perx = (ray.dpos.y - (int)ray.dpos.y);
	else
		return ;
	dist = 1 - (dist * 0.125);
	diff = sl.ewall - sl.bwall;
	pery = 0;
	while (sl.pix.y < HEIGHT - s->interface->h)
	{
		if (pery == 0 || (int)((double)(sl.pix.y - sl.bwall) / diff * s->door->h) > (int)(pery * s->door->h))
		{
			pery = (double)(sl.pix.y - sl.bwall) / diff;
			px_tex = (int)(pery * s->door->h) * s->door->w + (int)(perx * s->door->w);
			if (px_tex >= 0 && px_tex < sl.tex->h * sl.tex->w)
				sl.color = sl.tex->tex[px_tex];
		}
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

void	draw_skybox(t_main *s, t_ray ray, t_slice sl, int x)
{
	double angle;
	double pery;
	int		px_tex;

	angle = ray.angle;
	angle = angle > 360.0 ? angle - 360.0 : angle;
	angle = angle < 0 ? angle + 360.0 : angle;
	angle = (angle / 360.0);
	while (sl.pix.y < sl.bwall && sl.pix.y < HEIGHT - s->interface->h)
	{
		pery = (double)(sl.pix.y - s->viewline / 8) / (double)(HEIGHT * 1.5) + 0.2;
		pery = pery > 1.0 ? 1.0 : pery;
		pery = pery < 0.0 ? 0.0 : pery;
		// printf("x: %f y:%f\n", angle, pery);
		px_tex = (int)((angle * s->skybox->w) + s->skybox->w * (int)(s->skybox->h * pery));
		if (px_tex < s->skybox->w * s->skybox->h && px_tex >= 0)
			sl.color = s->skybox->tex[px_tex];
		// else
		// {
		// 	printf("x: %f y:%f\n", angle, pery);
		// 	printf("%d\n", px_tex);
		// 	}
		set_pixel(s->sdl->game, sl.color, sl.pix);
		sl.pix.y++;
	}
}

void	draw_wall_slice(t_main *s, t_ray ray, double dist, int x)
{
	int			projected_h;
	t_slice		sl;

	dist = dist <= 0.01 ? 0.01 : dist;
	projected_h = ((double)s->proj_distance / dist) / 2.0;
	dist = dist > 14 ? 14 : dist;
	dist = dist > 6 ? dist - (dist - 6) * 0.6 : dist;
	sl.bwall = s->viewline - projected_h;
	sl.ewall = s->viewline + projected_h;
	sl.pix.x = x;
	sl.pix.y = 0;
	// sl.color = SKY;
	// while (++(sl.pix.y) < sl.bwall && sl.pix.y < HEIGHT - s->interface->h)
	// 	set_pixel(s->sdl->game, sl.color, sl.pix);
	draw_skybox(s, ray, sl, x);
	sl.pix.y = sl.bwall;
	sl.tex = choose_texture(s, ray);
	draw_tex_slice(s, ray, sl, dist);
	if (sl.ewall > HEIGHT - s->interface->h)
		sl.ewall = HEIGHT - s->interface->h;
	sl.ewall = sl.ewall < 0 ? 0 : sl.ewall;
	sl.color = GROUND;
	dist *= 0.125;
	while (sl.ewall < HEIGHT - s->interface->h)
	{
		sl.pix.y = sl.ewall++;
		dist *= 0.987;
		set_pixel(s->sdl->game, darken_color(sl.color, 1 - dist), sl.pix);
	}
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

	// printf("angle fin: %f\n", angle);
}

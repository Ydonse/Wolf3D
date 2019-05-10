/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 13:25:49 by malluin           #+#    #+#             */
/*   Updated: 2019/05/10 13:28:57 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_tex_slice(t_main *s, t_ray ray, t_slice sl, double dist)
{
	double		pery;
	double		perx;
	int			px_tex;
	double		diff;

	perx = (ray.orientation == 'N' || ray.orientation == 'S') ? (ray.dpos.x
			- (int)ray.dpos.x) : (ray.dpos.y - (int)ray.dpos.y);
	dist = 1 - (dist * 0.125);
	diff = sl.ewall - sl.bwall;
	pery = 0;
	while (sl.pix.y < HEIGHT - s->interface->h && sl.pix.y < sl.ewall)
	{
		if (pery == 0 || (int)((sl.pix.y - sl.bwall) / diff
			* sl.tex->h) > (pery * sl.tex->h))
		{
			pery = (double)(sl.pix.y - sl.bwall) / diff;
			px_tex = (int)(pery * sl.tex->h) * sl.tex->w + (perx * sl.tex->w);
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

void	draw_skybox(t_main *s, t_ray ray, t_slice sl)
{
	double	angle;
	double	pery;
	int		px_tex;

	angle = ray.angle;
	angle = angle > 360.0 ? angle - 360.0 : angle;
	angle = angle < 0 ? angle + 360.0 : angle;
	angle = (angle / 360.0);
	sl.pix.y = -1;
	while (++(sl.pix.y) < sl.bwall && sl.pix.y < HEIGHT - s->interface->h)
	{
		pery = (double)(sl.pix.y - s->viewline + HEIGHT * 1.5) / (HEIGHT * 2.2);
		pery = pery > 1.0 ? 1.0 : pery;
		pery = pery < 0.0 ? 0.0 : pery;
		px_tex = (int)((angle * s->skybox->w) + s->skybox->w
			* (int)(s->skybox->h * pery));
		if (px_tex < s->skybox->w * s->skybox->h && px_tex >= 0)
			sl.color = s->skybox->tex[px_tex];
		set_pixel(s->sdl->game, sl.color, sl.pix);
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
	draw_skybox(s, ray, sl);
	sl.pix.y = sl.bwall < 0 ? 0 : sl.bwall;
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

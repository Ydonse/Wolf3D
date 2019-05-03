/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 11:55:41 by malluin           #+#    #+#             */
/*   Updated: 2019/05/03 18:33:45 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_ray	fill_ray(t_main *s, double x, double y, t_ray ray)
{
	if (x < 0 || x >= (double)s->width || y < 0
		|| y >= (double)s->height)
	{
		ray.res = -1;
		return (ray);
	}
	ray.type = s->map[(int)y][(int)x].type;
	ray.object.x = (int)x;
	ray.object.y = (int)y;
	if (s->map[(int)y][(int)x].block == 0)
		return (ray);
	ray.res = 1;
	return (ray);
}

t_ray	check_entity_h(t_main *s, t_dpos point, double r_angle, t_ray ray)
{
	ray.type = 0;
	ray.res = 0;
	if (r_angle > 180 && r_angle < 360)
	{
		ray = fill_ray(s, point.x, point.y, ray);
		if (ray.res == 1)
			draw_debug_rect(s->sdl, s->sdl->map, 0xFF0000FF, point);
	}
	else if (r_angle > 0 && r_angle < 180)
	{
		ray = fill_ray(s, point.x, point.y - 1, ray);
		if (ray.res == 1)
			draw_debug_rect(s->sdl, s->sdl->map, 0xFF0000FF, point);
	}
	return (ray);
}

t_ray		check_entity_v(t_main *s, t_dpos point, double r_angle, t_ray ray)
{
	ray.type = 0;
	ray.res = 0;
	if ((r_angle >= 0 && r_angle < 90) || (r_angle > 270 && r_angle < 360))
	{
		ray = fill_ray(s, point.x, point.y, ray);
		if (ray.res == 1)
			draw_debug_rect(s->sdl, s->sdl->map, 0x00FF00FF, point);
	}
	else if (r_angle > 90 && r_angle < 270)
	{
		ray = fill_ray(s, point.x - 1, point.y, ray);
		if (ray.res == 1)
			draw_debug_rect(s->sdl, s->sdl->map, 0x00FF00FF, point);
	}
	return (ray);
}

t_ray	raycast_hor(t_main *s, t_dpos fp, double r_angle, t_ray ray)
{
	char	sens;
	t_dpos 	b;
	double	xa;

	if (r_angle == 0 || r_angle == 180 || r_angle == 360)
	{
		ray.dist = 0;
		return (ray);
	}
	sens = (r_angle > 0 && r_angle < 180) ? -1 : 1;
	fp.y = (double)((int) s->player_pos.y + (sens == 1));
	fp.x = (s->player_pos.y - fp.y) / tan(to_rad(r_angle)) + s->player_pos.x;
	ray = check_entity_h(s, fp, r_angle, ray);
	if (ray.res == 1)
	{
		ray.dist = norme(s->player_pos, fp);
		return (ray);
	}
	else if (ray.res == -1)
		return (ray);
	while (1)
	{
		xa = 1.0 / tan(to_rad(r_angle));
		b.y = fp.y + sens;
		b.x = fp.x + xa * -sens;
		if (b.y < 0 || b.y > (double)s->height || b.x < 0 || b.x > (double)s->width)
			break;
		ray = check_entity_h(s, b, r_angle, ray);
		if (ray.res == 1)
		{
			ray.dist = norme(s->player_pos, b);
			return (ray);
		}
		else if (ray.res == -1)
			break;
		sens = sens < 0 ? sens - 1 : sens + 1;
	}
	ray.dist = 0;
	return (ray);
}

t_ray	raycast_ver(t_main *s, t_dpos fp, double r_angle, t_ray ray)
{
	char	sens;
	t_dpos	b;
	double	ya;

	if (r_angle == 90 || r_angle == 270)
	{
		ray.dist = 0;
		return (ray);
	}
	sens = (r_angle >= 0 && r_angle < 90) || (r_angle > 270 && r_angle < 360) ? 1 : -1;
	fp.x = (int) s->player_pos.x + (sens == 1);
	fp.y = s->player_pos.y +  (s->player_pos.x - fp.x ) * tan(to_rad(r_angle));
	ray = check_entity_v(s, fp, r_angle, ray);
	if (ray.res == 1)
	{
		ray.dist = norme(s->player_pos, fp);
		return (ray);
	}
	else if (ray.res == -1)
		return (ray);
	while (1)
	{
		ya = tan(to_rad(r_angle));
		b.x = fp.x + sens;
		b.y = fp.y + ya * -sens;
		if (b.y < 0 || b.y > (double)s->height || b.x < 0 || b.x > (double)s->width)
			break;
		// printf("%f %f\n", b.x, b.y);
		ray = check_entity_v(s, b, r_angle, ray);
		if (ray.res == 1)
		{
			ray.dist = norme(s->player_pos, b);
			return (ray);
		}
		else if (ray.res == -1)
			break;
		sens = sens <= 0 ? sens - 1 : sens + 1;
	}
	ray.dist = 0;
	return (ray);
}

t_ray	raycast(t_main *s, double r_angle)
{
	t_dpos	collision;
	t_ray	vertical;
	t_ray	horiz;

	collision.x = 0;
	collision.y = 0;
	horiz.dist = 0;
	vertical.dist = 0;
	r_angle = fmod(r_angle + 360.0, 360.0);
	horiz = raycast_hor(s, collision, r_angle, horiz);
	vertical = raycast_ver(s, collision, r_angle, vertical);
	if ((!(horiz.dist <= 0) && horiz.dist < vertical.dist) || vertical.dist <= 0)
		return (horiz);
	else
		return (vertical);
}

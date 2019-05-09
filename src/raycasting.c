/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 11:55:41 by malluin           #+#    #+#             */
/*   Updated: 2019/05/09 13:49:21 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_ray	raycast_hor(t_main *s, t_dpos fp, double r_angle, t_ray ray)
{
	char	sens;

	if (r_angle == 0 || r_angle == 180 || r_angle == 360)
	{
		ray.dist = 0;
		return (ray);
	}
	sens = (r_angle > 0 && r_angle < 180) ? -1 : 1;
	fp.y = (double)((int)s->player_pos.y + (sens == 1));
	fp.x = (s->player_pos.y - fp.y) / tan(to_rad(r_angle)) + s->player_pos.x;
	ray = check_entity_h(s, fp, r_angle, ray);
	if (ray.res == 1)
	{
		ray.dist = norme(s->player_pos, fp);
		return (ray);
	}
	else if (ray.res == -1)
		return (ray);
	ray = get_raycast_dist_h(s, ray, r_angle, fp);
	return (ray);
}

t_ray	raycast_ver(t_main *s, t_dpos fp, double r_angle, t_ray ray)
{
	char	sens;

	if (r_angle == 90 || r_angle == 270)
	{
		ray.dist = 0;
		return (ray);
	}
	sens = (r_angle >= 0 && r_angle < 90) || (r_angle > 270
			&& r_angle < 360) ? 1 : -1;
	fp.x = (int)s->player_pos.x + (sens == 1);
	fp.y = s->player_pos.y + (s->player_pos.x - fp.x) * tan(to_rad(r_angle));
	ray = check_entity_v(s, fp, r_angle, ray);
	if (ray.res == 1)
	{
		ray.dist = norme(s->player_pos, fp);
		return (ray);
	}
	else if (ray.res == -1)
		return (ray);
	ray = get_raycast_dist_v(s, ray, r_angle, fp);
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
	if ((!(horiz.dist <= 0) && horiz.dist < vertical.dist)
		|| vertical.dist <= 0)
	{
		draw_debug_rect(s->sdl, s->sdl->map, 0xf47742FF, horiz.dpos);
		return (horiz);
	}
	else
	{
		draw_debug_rect(s->sdl, s->sdl->map, 0xFF0000FF, vertical.dpos);
		return (vertical);
	}
}

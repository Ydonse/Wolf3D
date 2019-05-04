/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 11:55:41 by malluin           #+#    #+#             */
/*   Updated: 2019/05/04 21:20:02 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_ray	fill_ray(t_main *s, t_dpos pos, t_position bpos, t_ray ray)
{
	if (pos.x < 0 || pos.x >= (double)s->width || pos.y < 0
		|| pos.y >= (double)s->height)
	{
		ray.res = -1;
		return (ray);
	}
	ray.type = s->map[bpos.y][bpos.x].type;
	ray.dpos.x = pos.x;
	ray.dpos.y = pos.y;
	ray.object.x = bpos.x;
	ray.object.y = bpos.y;
	if (s->map[bpos.y][bpos.x].block == 0)
		return (ray);
	ray.res = 1;
	return (ray);
}

t_ray	check_entity_h(t_main *s, t_dpos point, double r_angle, t_ray ray)
{
	t_position	block_pos;

	ray.type = 0;
	ray.res = 0;
	if (r_angle > 180 && r_angle < 360)
	{
		block_pos.x = (int)point.x;
		block_pos.y = (int)point.y;
		ray = fill_ray(s, point, block_pos, ray);
	}
	else if (r_angle > 0 && r_angle < 180)
	{
		block_pos.x = (int)point.x;
		block_pos.y = (int)(point.y - 1);
		ray = fill_ray(s, point, block_pos, ray);
	}
	return (ray);
}

t_ray		check_entity_v(t_main *s, t_dpos point, double r_angle, t_ray ray)
{
	t_position	block_pos;

	ray.type = 0;
	ray.res = 0;
	if ((r_angle >= 0 && r_angle < 90) || (r_angle > 270 && r_angle < 360))
	{
		block_pos.x = (int)point.x;
		block_pos.y = (int)point.y;
		ray = fill_ray(s, point, block_pos, ray);
	}
	else if (r_angle > 90 && r_angle < 270)
	{
		block_pos.x = (int)(point.x - 1);
		block_pos.y = (int)point.y;
		ray = fill_ray(s, point, block_pos, ray);
	}
	return (ray);
}

t_ray	get_raycast_dist_v(t_main *s, t_ray ray, double r_a, t_dpos fp)
{
	t_dpos	b;
	double	ya;
	char	sens;

	sens = (r_a >= 0 && r_a < 90) || (r_a > 270 && r_a < 360) ? 1 : -1;
	while (1)
	{
		ya = tan(to_rad(r_a));
		b.x = fp.x + sens;
		b.y = fp.y + ya * -sens;
		if (b.y < 0 || b.y > (double)s->height
		|| b.x < 0 || b.x > (double)s->width)
			break;
		ray = check_entity_v(s, b, r_a, ray);
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

t_ray	get_raycast_dist_h(t_main *s, t_ray ray, double r_angle, t_dpos fp)
{
	t_dpos	b;
	double	xa;
	char	sens;

	sens = (r_angle > 0 && r_angle < 180) ? -1 : 1;
	while (1)
	{
		xa = 1.0 / tan(to_rad(r_angle));
		b.y = fp.y + sens;
		b.x = fp.x + xa * -sens;
		if (b.y < 0 || b.y > (double)s->height || b.x < 0
		|| b.x > (double)s->width)
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
	ray = get_raycast_dist_h(s, ray, r_angle, fp);
	// while (1)
	// {
	// 	xa = 1.0 / tan(to_rad(r_angle));
	// 	b.y = fp.y + sens;
	// 	b.x = fp.x + xa * -sens;
	// 	if (b.y < 0 || b.y > (double)s->height || b.x < 0 || b.x > (double)s->width)
	// 		break;
	// 	ray = check_entity_h(s, b, r_angle, ray);
	// 	if (ray.res == 1)
	// 	{
	// 		ray.dist = norme(s->player_pos, b);
	// 		return (ray);
	// 	}
	// 	else if (ray.res == -1)
	// 		break;
	// 	sens = sens < 0 ? sens - 1 : sens + 1;
	// }
	// ray.dist = 0;
	return (ray);
}

t_ray	raycast_ver(t_main *s, t_dpos fp, double r_angle, t_ray ray)
{
	char	sens;
	// t_dpos	b;
	// double	ya;

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
	ray = get_raycast_dist_v(s, ray, r_angle, fp);
	// while (1)
	// {
	// 	ya = tan(to_rad(r_angle));
	// 	b.x = fp.x + sens;
	// 	b.y = fp.y + ya * -sens;
	// 	if (b.y < 0 || b.y > (double)s->height || b.x < 0 || b.x > (double)s->width)
	// 		break;
	// 	ray = check_entity_v(s, b, r_angle, ray);
	// 	if (ray.res == 1)
	// 	{
	// 		ray.dist = norme(s->player_pos, b);
	// 		return (ray);
	// 	}
	// 	else if (ray.res == -1)
	// 		break;
	// 	sens = sens <= 0 ? sens - 1 : sens + 1;
	// }
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

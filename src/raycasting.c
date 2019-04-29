/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 11:55:41 by malluin           #+#    #+#             */
/*   Updated: 2019/04/29 15:08:52 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	to_rad(double angle)
{
	return (angle * PI / 180.0);
}

int		raycast_hor(t_main *s, t_dpos collision, double r_angle)
{
	if (r_angle > 0 && r_angle < 180)
	{
		collision.y = (int) s->player_pos.y;
		collision.x = (s->player_pos.y - collision.y ) / tan(to_rad(r_angle)) + s->player_pos.x;
		printf("x%f y%f\n", collision.x, collision.y);
	}
	else if (r_angle > 180 && r_angle < 360)
	{
		collision.y = (int) s->player_pos.y + 1;
		collision.x = (s->player_pos.y - collision.y) / tan(to_rad(r_angle)) + s->player_pos.x;
	}
	draw_debug_rect(s->sdl, s->sdl->map, collision);
}

int		raycast_ver(t_main *s, t_dpos collision, double r_angle)
{
	if ((r_angle > 0 && r_angle < 90) || (r_angle > 270 && r_angle < 360))
	{
		collision.x = (int) s->player_pos.x + 1;
		collision.y = s->player_pos.y +  (s->player_pos.x - collision.x ) * tan(to_rad(r_angle));
		printf("x%f y%f\n", collision.x, collision.y);
	}
	else if (r_angle > 90 && r_angle < 270)
	{
		collision.x = (int) s->player_pos.x;
		collision.y = s->player_pos.y + (s->player_pos.x - collision.x ) * tan(to_rad(r_angle));
	}
	draw_debug_rect(s->sdl, s->sdl->map, collision);
}

int		raycast(t_main *s, double r_angle)
{
	t_dpos	collision;

	collision.x = 0;
	collision.y = 0;

	raycast_hor(s, collision, r_angle);
	raycast_ver(s, collision, r_angle);
}

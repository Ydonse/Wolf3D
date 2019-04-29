/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 11:55:41 by malluin           #+#    #+#             */
/*   Updated: 2019/04/29 15:29:39 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	to_rad(double angle)
{
	return (angle * PI / 180.0);
}

int		raycast_hor(t_main *s, t_dpos collision, double r_angle)
{
	char	sens;
	t_dpos 	b;
	double	xa;

	if (r_angle == 0 || r_angle == 180 || r_angle == 360)
		return (0);
	sens = (r_angle > 0 && r_angle < 180) ? -1 : 1;
	collision.y = (int) s->player_pos.y + (sens == 1);
	collision.x = (s->player_pos.y - collision.y) / tan(to_rad(r_angle)) + s->player_pos.x;
	xa = 1.0 / tan(to_rad(r_angle));
	b.y = collision.y + sens;
	b.x = collision.x + xa * -sens;
	draw_debug_rect(s->sdl, s->sdl->map, 0x00000FF, collision);
	draw_debug_rect(s->sdl, s->sdl->map, 0xFF0000FF, b);

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
	draw_debug_rect(s->sdl, s->sdl->map, SKY, collision);
}

int		raycast(t_main *s, double r_angle)
{
	t_dpos	collision;

	collision.x = 0;
	collision.y = 0;

	raycast_hor(s, collision, r_angle);
	// raycast_ver(s, collision, r_angle);
}

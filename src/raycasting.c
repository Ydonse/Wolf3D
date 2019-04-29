/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 11:55:41 by malluin           #+#    #+#             */
/*   Updated: 2019/04/29 17:15:35 by ydonse           ###   ########.fr       */
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
	draw_debug_rect(s->sdl, s->sdl->map, 0x00000FF, collision);
	while (1)
	{
		xa = 1.0 / tan(to_rad(r_angle));
		b.y = collision.y + sens;
		if (b.y < 0 || b.y > (double)s->height)
			break;
		b.x = collision.x + xa * -sens;
		draw_debug_rect(s->sdl, s->sdl->map, 0xFF0000FF, b);
		sens = sens < 0 ? sens - 1 : sens + 1;
	}

}

int		raycast_ver(t_main *s, t_dpos collision, double r_angle)
{
	char	sens;
	t_dpos	b;
	double	ya;

	// sens = 0;
		if (r_angle == 0 || r_angle == 90 || r_angle == 270)
			return (0);
	sens = (r_angle > 0 && r_angle < 90) || (r_angle > 270 && r_angle < 360) ? 1 : -1;
		collision.x = (int) s->player_pos.x + (sens == 1);
		collision.y = s->player_pos.y +  (s->player_pos.x - collision.x ) * tan(to_rad(r_angle));
		draw_debug_rect(s->sdl, s->sdl->map, SKY, collision);
	while (1)
	{
		ya = tan(to_rad(r_angle));
		b.x = collision.x + sens;
		if (b.x < 0 || b.x > (double)s->width)
			break;
		b.y = collision.y + ya * -sens;
		draw_debug_rect(s->sdl, s->sdl->map, SKY, b);
		sens = sens <= 0 ? sens - 1 : sens + 1;
	}

	// printf("y%f, Height = %d\n", collision.y, HEIGHT);
}

int		raycast(t_main *s, double r_angle)
{
	t_dpos	collision;

	collision.x = 0;
	collision.y = 0;

	raycast_hor(s, collision, r_angle);
	raycast_ver(s, collision, r_angle);
}

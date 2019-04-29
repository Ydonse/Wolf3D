/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 11:55:41 by malluin           #+#    #+#             */
/*   Updated: 2019/04/29 16:52:02 by ydonse           ###   ########.fr       */
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
	// sens < WIDTH / SPACE - (int)s->player_pos.x
	collision.y = (int) s->player_pos.y + (sens == 1);
	collision.x = (s->player_pos.y - collision.y) / tan(to_rad(r_angle)) + s->player_pos.x;
	draw_debug_rect(s->sdl, s->sdl->map, 0x00000FF, collision);
	while (1)
	{
		xa = 1.0 / tan(to_rad(r_angle));
		b.y = collision.y + sens;
		// printf("%d\n\n", s->height);
		if (b.y < 0 || b.y > (double)s->height)
			break;
		// printf("b.y = %f, width / space = %d\n", b.y, WIDTH / SPACE);
		b.x = collision.x + xa * -sens;
		draw_debug_rect(s->sdl, s->sdl->map, 0xFF0000FF, b);
		sens = sens < 0 ? sens - 1 : sens + 1;
	}

}

int		raycast_ver(t_main *s, t_dpos collision, double r_angle)
{
	int tmp;

	tmp = 1;
	if ((r_angle > 0 && r_angle < 90) || (r_angle > 270 && r_angle < 360))
	{
		while (tmp < WIDTH / SPACE - (int)s->player_pos.y)
		{
			collision.x = (int) s->player_pos.x + tmp;
			collision.y = s->player_pos.y +  (s->player_pos.x - collision.x ) * tan(to_rad(r_angle));
			draw_debug_rect(s->sdl, s->sdl->map, SKY, collision);
			tmp++;
		}
		// printf("x%f y%f\n", collision.x, collision.y);
	}
	tmp = 0;
	if (r_angle > 90 && r_angle < 270)
	{
		while (tmp > 0 + (int)s->player_pos.y)
		{
			collision.x = (int) s->player_pos.x - tmp;
			collision.y = s->player_pos.y + (s->player_pos.x - collision.x ) * tan(to_rad(r_angle));
			tmp--;
		}
	}
	draw_debug_rect(s->sdl, s->sdl->map, SKY, collision);
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

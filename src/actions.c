/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 09:43:56 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/30 14:16:26 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	move_player(t_main *s, double dir_x, double dir_y)
{
	t_dpos	target;

	// target.x = s->player_pos.x + dir_x;
	// target.y = s->player_pos.y + dir_y;
	target.x = s->player_pos.x + cos(to_rad(s->p_angle)) * s->move_speed;
	target.y = s->player_pos.y - sin(to_rad(s->p_angle)) * s->move_speed;
	printf("angle = %d, payer .x = %f, target.x = %f\n",s->p_angle, s->player_pos.x, target.x);
	printf("angle = %d, payer .y = %f, target.y = %f\n",s->p_angle, s->player_pos.y, target.y);
	if (check_collisions(s, target) == 0)
	{
		target.x = s->player_pos.x + (cos(to_rad(s->p_angle)) * s->move_speed / 2);
		target.y =  s->player_pos.y + (cos(to_rad(s->p_angle)) * s->move_speed / 2);
		if (check_collisions(s, target) == 0)
			return ;
	}
	target.x = target.x < 0 ? 0 : target.x;
	target.x = target.x > s->width ? s->width: target.x;
	target.y = target.y < 0 ? 0 : target.y;
	target.y = target.y > s->height ? s->height : target.y;
	s->player_pos.x = target.x;
	s->player_pos.y = target.y;
}

void	open_door(t_main *s)
{

}

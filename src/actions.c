/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 09:43:56 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/30 17:08:53 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	move_player(t_main *s, const Uint8 *keys, char sprint)
{
	t_dpos	target;
	double	speed;

	speed = s->move_speed + sprint * s->move_speed * 0.5;
	if ((keys[UP] || keys[DOWN]) && (keys[LEFT] || keys[RIGHT]))
		speed /= 2;
	target.x = s->player_pos.x;
	target.y = s->player_pos.y;
	if (keys[UP])
	{
		target.x += cos(to_rad(s->p_angle)) * speed;
		target.y -= sin(to_rad(s->p_angle)) * speed;
	}
	if (keys[DOWN])
	{
		target.x -= cos(to_rad(s->p_angle * -1)) * speed;
		target.y -= sin(to_rad(s->p_angle * -1)) * speed;
	}
	if (keys[LEFT])
	{
		target.x += cos(to_rad(s->p_angle + 90)) * speed;
		target.y -= sin(to_rad(s->p_angle + 90)) * speed;
	}
	if (keys[RIGHT])
	{
		target.x += cos(to_rad(s->p_angle - 90)) * speed;
		target.y -= sin(to_rad(s->p_angle - 90)) * speed;
	}
	if (check_collisions(s, target) == 0)
	{
		// target.x = s->player_pos.x + (cos(to_rad(s->p_angle)) * s->move_speed / 2);
		// target.y =  s->player_pos.y + (cos(to_rad(s->p_angle)) * s->move_speed / 2);
		// if (check_collisions(s, target) == 0)
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
	;
}

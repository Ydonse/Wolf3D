/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 09:43:56 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/30 18:06:11 by ydonse           ###   ########.fr       */
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
	if ((s->p_angle < 45 && s->p_angle >= 0) || (s->p_angle < 380 && s->p_angle >= 315))
	{
		if (s->map[(int)s->player_pos.y][(int)s->player_pos.x + 1].type == 'p'
		&& s->map[(int)s->player_pos.y][(int)s->player_pos.x + 1].block == 1)
			s->map[(int)s->player_pos.y][(int)s->player_pos.x + 1].block = 0;
	}
	else if(s->p_angle < 135 && s->p_angle > 45)
	{
		if (s->map[(int)s->player_pos.y - 1][(int)s->player_pos.x].type == 'p'
		&& s->map[(int)s->player_pos.y - 1][(int)s->player_pos.x].block == 1)
			s->map[(int)s->player_pos.y - 1][(int)s->player_pos.x].block = 0;
	}
	else if(s->p_angle < 225 && s->p_angle > 135)
	{
		if (s->map[(int)s->player_pos.y][(int)s->player_pos.x - 1].type == 'p'
		&& s->map[(int)s->player_pos.y][(int)s->player_pos.x - 1].block == 1)
			s->map[(int)s->player_pos.y][(int)s->player_pos.x - 1].block = 0;
	}
	else if(s->p_angle < 315 && s->p_angle > 225)
	{
		if (s->map[(int)s->player_pos.y + 1][(int)s->player_pos.x].type == 'p'
		&& s->map[(int)s->player_pos.y + 1][(int)s->player_pos.x].block == 1)
			s->map[(int)s->player_pos.y + 1][(int)s->player_pos.x].block = 0;
	}
}

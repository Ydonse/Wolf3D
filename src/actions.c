/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 09:43:56 by ydonse            #+#    #+#             */
/*   Updated: 2019/05/07 16:07:52 by malluin          ###   ########.fr       */
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

int		check_door(t_case **map, int x, int y)
{
	if (map[y][x].type == 'p' && map[y][x].block == 1)
		return (1);
	else
		return (0);
}

void	open_door(t_main *s)
{
	if (((s->p_angle < 45 && s->p_angle >= 0)
		|| (s->p_angle < 380 && s->p_angle>= 315))
		&& check_door(s->map, (int)s->player_pos.x + 1, (int)s->player_pos.y))
		{
			s->map[(int)s->player_pos.y][(int)s->player_pos.x + 1].block = 0;
			 Mix_PlayChannel(2, s->sdl->sounds.door, 0);
		}
	else if ((s->p_angle < 135 && s->p_angle > 45)
	&& check_door(s->map, (int)s->player_pos.x, (int)s->player_pos.y - 1))
	{
		s->map[(int)s->player_pos.y - 1][(int)s->player_pos.x].block = 0;
		Mix_PlayChannel(2, s->sdl->sounds.door, 0);
	}
	else if ((s->p_angle < 225 && s->p_angle > 135)
	&& check_door(s->map, (int)s->player_pos.x - 1, (int)s->player_pos.y))
	{
		s->map[(int)s->player_pos.y][(int)s->player_pos.x - 1].block = 0;
		Mix_PlayChannel(2, s->sdl->sounds.door, 0);
	}
	else if ((s->p_angle < 315 && s->p_angle > 225)
	&& check_door(s->map, (int)s->player_pos.x, (int)s->player_pos.y + 1))
	{
		s->map[(int)s->player_pos.y + 1][(int)s->player_pos.x].block = 0;
		Mix_PlayChannel(2, s->sdl->sounds.door, 0);
	}
}

void	turn_camera(t_main *s, const Uint8 *keys, char command)
{
	if (command)
	{
		s->p_angle -= (s->sdl->event.motion.xrel) / 10;
		s->p_angle = (s->p_angle + 360) % 360;
		s->viewline -= (s->sdl->event.motion.yrel);
		s->viewline = (s->viewline < - HEIGHT / 2 ? - HEIGHT / 2 : s->viewline);
		s->viewline = (s->viewline > HEIGHT * 1.5 ? HEIGHT * 1.5 : s->viewline);
		s->sdl->event.type = 0;
	}
	if (keys[LEFT_AR] || keys[RIGHT_AR])
		s->p_angle = (s->p_angle + (keys[LEFT_AR] - keys[RIGHT_AR])
		* ROTATE_SPEED + 360) % 360;
	if (keys[UP_AR] || keys[DOWN_AR])
	{
		s->viewline = (s->viewline + (keys[UP_AR] - keys[DOWN_AR])
		* ROTATE_SPEED * 5);
		s->viewline = (s->viewline < - HEIGHT / 2 ? - HEIGHT / 2 : s->viewline);
		s->viewline = (s->viewline > HEIGHT * 1.5 ? HEIGHT * 1.5 : s->viewline);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 09:43:56 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/29 11:03:15 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	move_player(t_main *s, double dir_x, double dir_y)
{
	t_dpos	target;

	target.x = s->player_pos.x + dir_x;
	target.y = s->player_pos.y + dir_y;
	if (check_collisions(s, target) == 0)
	{
		target.x = s->player_pos.x + dir_x / 2;
		target.y = s->player_pos.y + dir_y / 2;
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
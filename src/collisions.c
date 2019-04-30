/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:10:35 by malluin           #+#    #+#             */
/*   Updated: 2019/04/30 17:10:50 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		check_collisions(t_main *s, t_dpos target)
{
	t_dpos		corners[4];
	int			i;

	corners[0].x = target.x - PLAYER_SIZE / 2;
	corners[0].y = target.y - PLAYER_SIZE / 2;
	corners[1].x = target.x + PLAYER_SIZE / 2;
	corners[1].y = target.y - PLAYER_SIZE / 2;
	corners[2].x = target.x - PLAYER_SIZE / 2;
	corners[2].y = target.y + PLAYER_SIZE / 2;
	corners[3].x = target.x + PLAYER_SIZE / 2;
	corners[3].y = target.y + PLAYER_SIZE / 2;
	i = -1;
	while (++i < 4)
	{
		if (corners[i].x < 0 || corners[i].y < 0
			|| corners[i].x > s->width || corners[i].y > s->height)
			return (0);
		if (s->map[(int)corners[i].y][(int)corners[i].x].block == 1)
			return (0);
	}
	return (1);
}

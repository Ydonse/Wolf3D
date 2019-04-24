/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 11:54:34 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/24 15:14:22 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	check_up(t_main *s, int x, int y)
{
	if (y < s->height && s->map[y][x].valid == 0)
	{
		s->map[y][x].valid = 1;
		if (s->map[y][x].type == 'm')
			return (1);
		else
			return (check_next_case(s, x, y));
	}
	else if (y < s->height && s->map[y][x].valid == 1)
		return (1);
	else
		return (0);
}

int	check_down(t_main *s, int x, int y)
{
	if (y >= 0 && s->map[y][x].valid == 0)
	{
		s->map[y][x].valid = 1;
		if (s->map[y][x].type == 'm')
			return (1);
		else
			return (check_next_case(s, x, y));
	}
	else if (y >= 0 && s->map[y][x].valid == 1)
		return (1);
	else
		return (0);
}

int	check_right(t_main *s, int x, int y)
{
	if (x < s->width && s->map[y][x].valid == 0)
	{
		s->map[y][x].valid = 1;
		if (s->map[y][x].type == 'm')
			return (1);
		else
			return (check_next_case(s, x, y));
	}
	else if (x < s->width && s->map[y][x].valid == 1)
		return (1);
	else
		return (0);
}

int	check_left(t_main *s, int x, int y)
{
	if (x >= 0 && s->map[y][x].valid == 0)
	{
		s->map[y][x].valid = 1;
		if (s->map[y][x].type == 'm')
			return (1);
		else
			return (check_next_case(s, x, y));
	}
	else if (x >= 0 && s->map[y][x].valid == 1)
		return (1);
	else
		return (0);
}

int	check_next_case(t_main *s, int x, int y)
{
	if (check_up(s, x, y + 1) && check_down(s, x, y - 1)
	&& check_left(s, x - 1, y) && check_right(s, x + 1, y))
		return (1);
	return (0);
}

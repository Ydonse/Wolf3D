/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_trig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:45:53 by malluin           #+#    #+#             */
/*   Updated: 2019/04/30 17:12:03 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	to_rad(double angle)
{
	return (angle * PI / 180.0);
}

double	norme(t_dpos player, t_dpos point)
{
	double x;
	double y;

	x = point.x - player.x;
	y = point.y - player.y;
	return (sqrtf(x * x + y * y));
}

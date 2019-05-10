/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_trig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:45:53 by malluin           #+#    #+#             */
/*   Updated: 2019/05/10 13:46:32 by malluin          ###   ########.fr       */
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

double	percent(double value, double total)
{
	return (value / total);
}

void	pre_initialize_sdl(t_main *s)
{
	if (!(s->sdl = (t_sdl *)malloc(sizeof(t_sdl))))
		exit(-1);
	s->sdl->pwindow = NULL;
	s->sdl->prenderer = NULL;
	s->sdl->minimap = NULL;
	s->sdl->map = NULL;
	s->sdl->game = NULL;
	s->sdl->ui = NULL;
	s->sdl->musique = NULL;
}

int		ft_min_one(int a)
{
	if (a < 0 && a / 10 == 0 && a < -2)
		return (-1);
	else if (a > 0 && a / 10 == 0 && a > 2)
		return (1);
	else
		return (a / 20);
}

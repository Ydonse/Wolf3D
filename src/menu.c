/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:45:55 by ydonse            #+#    #+#             */
/*   Updated: 2019/05/08 16:27:43 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	display_menu(t_main *s, int i, int j)
{
	double		perx;
	double		pery;
	t_position	coord;
	int			pix_tex;

	s->menu = load_tga("images/menu.tga");
	while (i < WIDTH)
	{
		j = 0;
		coord.x = i;
		perx = (int)(percent(coord.x, WIDTH) * 100);
		while (j < HEIGHT)
		{
			coord.y = j++;
			pery = (int)(percent(coord.y, HEIGHT) * 100);
			pix_tex = (int)(pery * s->menu->h / 100.0) * s->menu->w + (int)(perx * s->menu->w / 100.0);
			set_pixel(s->sdl->game,s->menu->tex[pix_tex], coord);
		}
	}
}

int		handle_menu(t_main *s)
{
	display_menu(s, 0, 0);
	if (SDL_WaitEvent(&s->sdl->event) != 0)
	{
		if (s->sdl->event.type == SDL_QUIT)
			return (0);
		if (s->sdl->event.type == SDL_KEYDOWN && s->sdl->event.key.keysym.sym == SDLK_RETURN)
			return (1);
	}
	return (0);
}

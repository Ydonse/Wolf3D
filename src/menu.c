/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:45:55 by ydonse            #+#    #+#             */
/*   Updated: 2019/05/08 17:38:52 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	display_menu(t_main *s, int i, int j)
{
	double		perx;
	double		pery;
	t_position	coord;

	s->menu = load_tga("images/menu2.tga");
	coord.x = 0;
	coord.y = 0;
	printf("w =  = %d\n", s->menu->w);
	while (i < WIDTH)
	{
		j = 0;
		coord.x = i;
		perx = (double)coord.x / (double)WIDTH;
		// printf("perx = %lf\n", perx);
		while (j < HEIGHT)
		{
			coord.y = j++;
			pery = (double)coord.y / (double)HEIGHT;
			set_pixel(s->sdl->game,s->menu->tex[(int)(pery * (double)s->menu->h) * s->menu->w + (int)(perx * (double)s->menu->w)], coord);
		}
		i++;
	}
	update_image(s, s->sdl->game);
}

int		handle_menu(t_main *s)
{
	display_menu(s, 0, 0);
	while (SDL_WaitEvent(&s->sdl->event) != 0 && s->sdl->event.key.keysym.sym != SDLK_RETURN)
	{
		if (s->sdl->event.type == SDL_QUIT)
			return (0);
		if (s->sdl->event.type == SDL_KEYDOWN && s->sdl->event.key.keysym.sym == SDLK_RETURN)
			return (1);
	}
	return (1);
	// return (0);
}

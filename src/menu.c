/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:45:55 by ydonse            #+#    #+#             */
/*   Updated: 2019/05/15 16:44:53 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	display_menu(t_main *s, int i, int j)
{
	double		perx;
	double		pery;
	t_position	coord;
	int			px;

	coord.x = 0;
	coord.y = 0;
	while (i < WIDTH)
	{
		j = 0;
		coord.x = i;
		perx = (double)coord.x / (double)WIDTH;
		while (j < HEIGHT)
		{
			coord.y = j++;
			pery = (double)coord.y / (double)HEIGHT;
			px = (int)(pery * (double)s->menu->h) * s->menu->w + (int)
			(perx * (double)s->menu->w);
			if (px >= 0 && px < s->menu->w * s->menu->h)
				set_pixel(s->sdl->game, s->menu->tex[px], coord);
		}
		i++;
	}
	update_image(s, s->sdl->game);
}

void	play_music(t_main *s)
{
	s->sdl->musique = Mix_LoadMUS("musics/menu.wav");
	if (s->sdl->musique == NULL)
		ft_putstr("Error : music not loaded\n");
	else
		Mix_PlayMusic(s->sdl->musique, -1);
}

int		handle_menu(t_main *s)
{
	play_music(s);
	display_menu(s, 0, 0);
	while (1)
	{
		SDL_WaitEvent(&s->sdl->event);
		if (s->sdl->event.type == SDL_QUIT)
			return (0);
		else if (s->sdl->event.type == SDL_KEYDOWN)
		{
			if (s->sdl->event.key.keysym.sym == SDLK_RETURN)
				break ;
			else if (s->sdl->event.key.keysym.sym == SDLK_ESCAPE)
				return (0);
		}
		else
			continue ;
	}
	if (s->sdl->musique != NULL)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(s->sdl->musique);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 09:44:06 by ydonse            #+#    #+#             */
/*   Updated: 2019/05/09 13:56:03 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		keyboard_controls(t_main *s, int key)
{
		if (key == SDLK_ESCAPE)
			return (0);
		else if (key == SDLK_e)
			open_door(s);
		else if (key == SDLK_m)
		{
			s->active_map = !s->active_map;
			draw_interface(s);
		}
	return (1);
}

void	handle_keys(t_main *s)
{
	const Uint8 *keys;

	keys = SDL_GetKeyboardState(NULL);
	if (keys[LEFT] || keys[RIGHT] || keys[UP] || keys[DOWN])
		move_player(s, keys, keys[SPRINT]);
	if (keys[LEFT_AR] || keys[RIGHT_AR] || keys[UP_AR] || keys[DOWN_AR])
		turn_camera(s, keys, 0);
	if (s->sdl->event.type == SDL_MOUSEMOTION)
		turn_camera(s, keys, 1);
	if (s->active_map)
		draw_minimap(s);
	else
	{
		raycast_visualization(s);
		update_image(s, s->sdl->game);
		// update_image(s, s->sdl->ui);
	}
}

void	event_handler(t_main *s)
{
	int			game;
	time_t		fps;

	game = 1;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	fps = clock();
	draw_interface(s);
	while (game)
	{
		while ((SDL_PollEvent(&(s->sdl->event))) != 0)
		{
			if (s->sdl->event.type == SDL_QUIT)
				game = 0;
			if (s->sdl->event.type == SDL_MOUSEBUTTONDOWN && s->weapon.current == 0)
				 shoot(s);
			if (s->sdl->event.type == SDL_KEYDOWN && keyboard_controls(s, s->sdl->event.key.keysym.sym) == 0)
					game = 0;
		}
		handle_keys(s);
		printf("FPS: %f\n", 1.0 / ((clock() - fps) / 1000000.0));
		fps = clock();
	}
}

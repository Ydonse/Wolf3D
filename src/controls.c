/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 09:44:06 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/30 18:06:28 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	event_handler(t_main *s)
{
	const Uint8 *keys;
	int			game;
	time_t		fps;

	game = 1;

	keys = SDL_GetKeyboardState(NULL);
	fps = clock();
	while (game)
	{
		while ((SDL_PollEvent(&(s->sdl->event))) != 0)
		{
			if (s->sdl->event.type == SDL_QUIT)
				game = 0;
			if (s->sdl->event.type == SDL_KEYDOWN)
				if (keyboard_controls(s, s->sdl->event.key.keysym.sym) == 0)
					game = 0;
		}
		keys = SDL_GetKeyboardState(NULL);
		if (keys[LEFT] || keys[RIGHT] || keys[UP] || keys[DOWN])
			move_player(s, keys, keys[SPRINT]);
		if (keys[LEFT_AR] || keys[RIGHT_AR])
			s->p_angle = (s->p_angle + (keys[LEFT_AR] - keys[RIGHT_AR]) * ROTATE_SPEED + 360) % 360;
		if (keys[UP_AR] || keys[DOWN_AR])
		{
			s->viewline = (s->viewline + (keys[UP_AR] - keys[DOWN_AR]) * ROTATE_SPEED * 5);
			s->viewline = (s->viewline < - HEIGHT / 2 ? - HEIGHT / 2 : s->viewline);
			s->viewline = (s->viewline > HEIGHT * 1.5 ? HEIGHT * 1.5 : s->viewline);
			// printf("%d\n", s->p_angle);
		}
		if (s->active_map)
		{
			draw_minimap(s);
			draw_player(s, s->sdl);
			raycast_visualization(s);
			update_image(s, s->sdl->map);
		}
		else
		{
			raycast_visualization(s);
			update_image(s, s->sdl->game);
		}
		printf("FPS: %f\n", 1.0 / ((clock() - fps) / 1000000.0));
		fps = clock();
	}
}

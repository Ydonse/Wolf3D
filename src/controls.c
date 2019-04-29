/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 09:44:06 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/29 10:25:21 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		keyboard_controls(t_main *s, int key)
{
	t_position orig = {0,0};
	t_position dest = {WIDTH,HEIGHT};

	if (key == SDLK_ESCAPE)
		return (0);
	else if (key == SDLK_e)
		open_door(s);
	else if (key == SDLK_m)
	{
		s->active_map = !s->active_map;
		s->sdl->map->color_tmp = 0x000000FF;
		draw_rect(s->sdl, s->sdl->map, orig, dest);
		if (s->active_map)
			draw_minimap(s);
	}
	return (1);
}

void	event_handler(t_main *s)
{
	const Uint8 *keys;

	while (SDL_WaitEvent(&(s->sdl->event)))
	{
		keys = SDL_GetKeyboardState(NULL);
		if (s->sdl->event.type == SDL_QUIT)
			break ;
		else if (s->sdl->event.type == SDL_KEYDOWN)
		{
			if (keyboard_controls(s, s->sdl->event.key.keysym.sym) == 0)
				break;

				if (keys[LEFT] || keys[RIGHT] || keys[UP] || keys[DOWN])
				{
					move_player(s,
						s->move_speed * (keys[RIGHT] - keys[LEFT]) * (1 + 0.4 * (keys[SPRINT] == 1)),
						s->move_speed * (keys[DOWN] - keys[UP]) * (1 + 0.4 * (keys[SPRINT] == 1)));
						draw_minimap(s);
						draw_player(s, s->sdl);
				}
		}
		update_image(s);
		// printf("Player x:%f y:%f\n", s->player_pos.x, s->player_pos.y);
	}
}

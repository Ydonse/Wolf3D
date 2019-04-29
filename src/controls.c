/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 09:44:06 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/29 18:56:19 by malluin          ###   ########.fr       */
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

void	raycast_visualization(t_main *s)
{
	double	angle;
	int		i;

	i = 0;
	angle = s->p_angle - s->fov / 2.0;
	printf("angle debut: %f\n", angle);
	while (i < PROJ_WIDTH)
	{
		raycast(s, angle);
		angle += s->fov / (double)PROJ_WIDTH;
		i++;
	}
	printf("angle fin: %f\n", angle);
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
					s->move_speed * (keys[RIGHT] - keys[LEFT]) * (1 + 0.6 * (keys[SPRINT] == 1)),
					s->move_speed * (keys[DOWN] - keys[UP]) * (1 + 0.6 * (keys[SPRINT] == 1)));
				if (s->active_map)
				{
					draw_minimap(s);
					draw_player(s, s->sdl);
					raycast_visualization(s);
				}
			}
			if (keys[LEFT_AR] || keys[RIGHT_AR])
			{
				s->p_angle = (s->p_angle + (keys[LEFT_AR] - keys[RIGHT_AR]) * ROTATE_SPEED + 360) % 360;
				if (s->active_map)
				{
					draw_minimap(s);
					draw_player(s, s->sdl);
					raycast_visualization(s);
				}
			}
			printf("%d\n", s->p_angle);
		}
		update_image(s);
		// printf("Player x:%f y:%f\n", s->player_pos.x, s->player_pos.y);
	}
}

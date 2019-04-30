/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 09:44:06 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/30 15:55:04 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		keyboard_controls(t_main *s, int key)
{
	// t_position orig = {0,0};
	// t_position dest = {WIDTH,HEIGHT};
		if (key == SDLK_ESCAPE)
			return (0);
		else if (key == SDLK_e)
			open_door(s);
		else if (key == SDLK_m)
			s->active_map = !s->active_map;
	return (1);
}

void	draw_wall_slice(t_main *s, double dist, int x)
{
	int		projected_h;
	t_position	pix;
	if (dist <= 0)
	{
		printf("FAIL %f\n", dist);
		return ;
	}
	// printf("dist: %f proj distance %d\n", dist, s->proj_distance);
	projected_h = (int)((double)1.0 / dist * (double)s->proj_distance);
	// printf("wall height: %d\n", projected_h);

	int		i;
	int		bwall;
	int		ewall;

	bwall = s->viewline - projected_h / 2;
	ewall = s->viewline + projected_h / 2;
	bwall = bwall <= 0 ? 0 : bwall;
	ewall = ewall > HEIGHT ? HEIGHT : ewall;

	i = 0;
	pix.x = x;
	while (i < bwall)
	{
		pix.y = i;
		set_pixel(s->sdl, s->sdl->game, SKY, pix);
		i++;
	}
	while (bwall < ewall)
	{
		pix.y = bwall;
		set_pixel(s->sdl, s->sdl->game, WALL, pix);
		bwall++;
	}
	while (ewall < HEIGHT)
	{
		pix.y = ewall;
		set_pixel(s->sdl, s->sdl->game, GROUND, pix);
		ewall++;
	}
}

void	raycast_visualization(t_main *s)
{
	double	angle;
	double	dist;
	int		i;

	i = 0;
	angle = s->p_angle + s->fov / 2.0;
	// printf("angle debut: %f\n", angle);
	double correc;
	correc = raycast(s, s->p_angle);
	while (i < PROJ_WIDTH)
	{
		dist = raycast(s, angle);
		if (dist <= 0)
			printf("FAIL angle:%f val:%f\n", angle, dist);
		dist *= cos(to_rad((double)s->p_angle - angle));
		draw_wall_slice(s, dist, i);
		angle -= s->fov / (double)PROJ_WIDTH;
		i++;
	}
	if (s->active_map)
		update_image(s, s->sdl->map);
	// printf("angle fin: %f\n", angle);
}

void	event_handler(t_main *s)
{
	const Uint8 *keys;
	int			game;

	game = 1;

	keys = SDL_GetKeyboardState(NULL);
	while (game)
	{
		while ((SDL_PollEvent(&(s->sdl->event))) != 0)
			if (s->sdl->event.type == SDL_QUIT)
				game = 0;
		keys = SDL_GetKeyboardState(NULL);
		if (s->sdl->event.type == SDL_KEYDOWN || s->sdl->event.type == SDL_KEYUP)
		{
			if (s->sdl->event.type == SDL_KEYDOWN)
				if (keyboard_controls(s, s->sdl->event.key.keysym.sym) == 0)
					game = 0;
		}
		if (keys[LEFT] || keys[RIGHT] || keys[UP] || keys[DOWN])
			move_player(s, keys, keys[SPRINT]);
		if (keys[LEFT_AR] || keys[RIGHT_AR])
			s->p_angle = (s->p_angle + (keys[LEFT_AR] - keys[RIGHT_AR]) * ROTATE_SPEED + 360) % 360;
		if (keys[UP_AR] || keys[DOWN_AR])
		{
			s->viewline = (s->viewline + (keys[UP_AR] - keys[DOWN_AR]) * ROTATE_SPEED);
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
		// update_image(s, s->sdl->map);
		// printf("Player x:%f y:%f\n", s->player_pos.x, s->player_pos.y);
	}
}

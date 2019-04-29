/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 10:20:16 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/29 10:25:54 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"



void	ft_error_sdl(char *str)
{
	printf("%s (%s)\n", str, SDL_GetError());
	exit (-1);
}

void	set_pixel(t_sdl *sdl, t_texture *text, Uint32 color, t_position coord)
{
	if (coord.x < WIDTH && coord.y < HEIGHT)
	{
		text->content[coord.x + coord.y * WIDTH] = color;
	}
}

void	draw_rect(t_sdl *sdl, t_texture *text, t_position orig, t_position dest)
{
	int		i;
	int		j;
	t_position	coord;

	orig.x = orig.x < 0 ? 0 : orig.x;
	orig.y = orig.y < 0 ? 0 : orig.y;
	dest.x = dest.x > WIDTH ? WIDTH : dest.x;
	dest.y = dest.y > HEIGHT ? HEIGHT : dest.y;

	i = orig.x;
	while (i < dest.x)
	{
		j = orig.y;
		while (j < dest.y)
		{
			coord.x = i;
			coord.y = j++;
			set_pixel(sdl, text, text->color_tmp, coord);
		}
		i++;
	}
}

void	draw_player(t_main *s, t_sdl *sdl)
{
	t_position	orig;
	t_position	dest;

	orig.x = (s->player_pos.x - PLAYER_SIZE / 2) * SPACE + sdl->x_o;
	dest.x = (s->player_pos.x + PLAYER_SIZE / 2) * SPACE + sdl->x_o;
	orig.y = (s->player_pos.y - PLAYER_SIZE / 2) * SPACE + sdl->y_o;
	dest.y = (s->player_pos.y + PLAYER_SIZE / 2) * SPACE + sdl->y_o;
	sdl->map->color_tmp = 0xFF0000FF;
	draw_rect(sdl, sdl->map, orig, dest);
}

int		check_collisions(t_main *s, t_dpos target)
{
	t_dpos		corners[4];
	int			i;

	corners[0].x = target.x - PLAYER_SIZE / 2;
	corners[0].y = target.y - PLAYER_SIZE / 2;
	corners[1].x = target.x + PLAYER_SIZE / 2;
	corners[1].y = target.y - PLAYER_SIZE / 2;
	corners[2].x = target.x - PLAYER_SIZE / 2;
	corners[2].y = target.y + PLAYER_SIZE / 2;
	corners[3].x = target.x + PLAYER_SIZE / 2;
	corners[3].y = target.y + PLAYER_SIZE / 2;
	i = -1;
	while (++i < 4)
	{
		if (corners[i].x < 0 || corners[i].y < 0
			|| corners[i].x > s->width || corners[i].y > s->height)
			return (0);
		if (s->map[(int)corners[i].y][(int)corners[i].x].block == 1)
			return (0);
	}
	return (1);
}

int	main (int ac, char **av)
{
	t_main	*s;

	if (ac <= 1)
		return (1);
	s = initialize_main();
	parse_map(s, av[1]);
	initialize_sdl(s->sdl);
	s->sdl->x_o = WIDTH / 2 - ((SPACE * s->width) / 2);
	s->sdl->y_o = HEIGHT / 2 - ((SPACE * s->height) / 2);
	s->player_pos.x = (double) s->start_position.x + 0.5;
	s->player_pos.y = (double) s->start_position.y + 0.5;
	event_handler(s);
	return (1);
}

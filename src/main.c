/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 10:20:16 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/25 16:09:25 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_error_sdl(char *str)
{
	printf("%s (%s)\n", str, SDL_GetError());
	exit (-1);
}

t_main	*initialize_main(void)
{
	t_main	*s;

	if (!(s = (t_main *)malloc(sizeof(t_main))))
		exit(-1);
	if (!(s->sdl = (t_sdl *)malloc(sizeof(t_sdl))))
		exit(-1);
	if (!(s->sdl->minimap = (SDL_Surface *)malloc(sizeof(SDL_Surface))))
		exit(-1);
	s->width = 0;
	s->height = 0;
	s->map = NULL;
	s->move_speed = 0.1;
	return (s);
}

t_texture	*initialize_texture(t_sdl *sdl, int width, int height)
{
	t_texture	*text;

	if (!(text = (t_texture *)malloc(sizeof(t_texture))))
		return (NULL);
	if (!(text->content = (Uint32 *)malloc(width * height * sizeof(Uint32))))
		return (NULL);
	if (!(text->texture = SDL_CreateTexture(sdl->prenderer,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height)))
		return (NULL);
	text->color_tmp = 0x000000FF;
	return (text);
}

void	initialize_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		ft_error_sdl("Échec de l'initialisation de la SDL");
	if (!(sdl->pwindow = SDL_CreateWindow("Wolf3D", 100,
		100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)))
		ft_error_sdl("Échec de creation de la fenetre");
	if (!(sdl->prenderer = SDL_CreateRenderer(sdl->pwindow, -1,
		SDL_RENDERER_ACCELERATED)))
		ft_error_sdl("Échec de chargement du renderer");
	if (!(sdl->map = initialize_texture(sdl, WIDTH, HEIGHT)))
		exit(-1);
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

	i = orig.x;
	while (i < dest.x)
	{
		j = orig.y;
		while (j < dest.y)
		{
			coord.x = i;
			coord.y = j++;
			set_pixel(sdl, text, 0xFFFF00BB, coord);
		}
		i++;
	}
	SDL_SetRenderTarget(sdl->prenderer, text->texture);
	SDL_UpdateTexture(text->texture, NULL, text->content, WIDTH
		* sizeof(Uint32));
	SDL_SetRenderTarget(sdl->prenderer, NULL);
	SDL_RenderCopy(sdl->prenderer, text->texture, NULL, NULL);
	SDL_RenderPresent(sdl->prenderer);
}


void	move_player(t_main *s, t_sdl *sdl, double dir_x, double dir_y)
{
	t_dpos	target;

	target.x = s->player_pos.x + dir_x;
	target.y = s->player_pos.y + dir_y;
	target.x = target.x < 0 ? 0 : target.x;
	target.x = target.x > s->width - 1 ? s->width - 1 : target.x;
	target.y = target.y < 0 ? 0 : target.y;
	target.y = target.y > s->height - 1 ? s->height - 1 : target.y;
	s->player_pos.x = target.x;
	s->player_pos.y = target.y;
}

void	event_handler(t_main *s)
{
	t_position orig = {100 ,100};
	t_position dest = {500 ,500};

	draw_rect(s->sdl, s->sdl->map, orig, dest);

	const Uint8 *keys;

	while (SDL_WaitEvent(&(s->sdl->event)))
	{
		keys = SDL_GetKeyboardState(NULL);
		if (s->sdl->event.type == SDL_QUIT)
			break ;
		else if (s->sdl->event.type == SDL_KEYDOWN)
		{
			if (s->sdl->event.key.keysym.sym == SDLK_ESCAPE)
				break;
			if (keys[LEFT] || keys[RIGHT] || keys[UP] || keys[DOWN])
				move_player(s, s->sdl, s->move_speed * (keys[RIGHT]
				- keys[LEFT]), s->move_speed * (keys[DOWN] - keys[UP]));
		}
		printf("Player x:%f y:%f\n", s->player_pos.x, s->player_pos.y);
	}

}

int	main (int ac, char **av)
{
	t_main	*s;

	if (ac <= 1)
		return (1);
	s = initialize_main();
	parse_map(s, av[1]);
	initialize_sdl(s->sdl);
	ft_print_map(s);

	s->player_pos.x = (double) s->player_pos.x;
	s->player_pos.y = (double) s->player_pos.y;
	event_handler(s);
	return (1);
}

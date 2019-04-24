/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 10:20:16 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/24 13:36:21 by ydonse           ###   ########.fr       */
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
	s->width = 0;
	s->height = 0;
	s->map = NULL;
	return (s);
}

int	main (int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_main	*s;

	s = initialize_main();
	parse_map(s, argv[1]);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		ft_error_sdl("Échec de l'initialisation de la SDL");
	if (!(s->sdl->pwindow = SDL_CreateWindow("Wolf3D", 100,
		100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)))
		ft_error_sdl("Échec de creation de la fenetre");
	if (!(s->sdl->prenderer = SDL_CreateRenderer(s->sdl->pwindow,-1,
		SDL_RENDERER_ACCELERATED)))
		ft_error_sdl("Échec de chargement du renderer");
	int i = 0;
	int j = 0;
	while (i < s->height)
	{
		while (j < s->width)
		{
			ft_putchar(s->map[i][j].type);
			ft_putchar(s->map[i][j].zone);
			ft_putchar(' ');
			j++;
		}
		i++;
		ft_putchar('\n');
		j = 0;
	}
	while (SDL_WaitEvent(&(s->sdl->event)))
	{
		if (s->sdl->event.type == SDL_QUIT)
			break ;
		else if (s->sdl->event.type == SDL_KEYDOWN)
		{
			;
		}
	}
	return (1);
}

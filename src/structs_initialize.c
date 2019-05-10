/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_initialize.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 18:07:03 by malluin           #+#    #+#             */
/*   Updated: 2019/05/10 13:26:44 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			check_images(t_main *s)
{
	int		i;

	i = -1;
	while (++i < MAX_AREA)
	{
		if (!s->areas[i].wall_n || !s->areas[i].wall_s || !s->areas[i].wall_e
		|| !s->areas[i].wall_w)
			return (0);
	}
	if (!s->weapon.image[0] || !s->weapon.image[1] || !s->weapon.image[2])
		return (0);
	if (!s->door || !s->interface || !s->skybox)
		return (0);
	return (1);
}

t_main		*initialize_main(void)
{
	t_main	*s;

	if (!(s = (t_main *)malloc(sizeof(t_main))))
		exit(-1);
	pre_initialize_sdl(s);
	s->width = 0;
	s->height = 0;
	s->map = NULL;
	s->parsing_line = NULL;
	s->move_speed = 0.05;
	s->active_map = 0;
	s->fov = DEFAULT_FOV;
	s->p_angle = 0;
	s->proj_distance = (PROJ_WIDTH / 2) / tan((double)(s->fov / 2)
	* PI / 180.0);
	s->viewline = HEIGHT / 2;
	ft_bzero(s->areas, sizeof(s->areas));
	ft_bzero(s->weapon.image, sizeof(s->weapon.image));
	s->menu = NULL;
	s->skybox = NULL;
	s->door = NULL;
	s->interface = NULL;
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

void		load_images(t_main *s)
{
	s->areas[0].wall_n = load_tga("images/zone_0/wall_n.tga", 0, 0, 0);
	s->areas[0].wall_s = load_tga("images/zone_0/wall_s.tga", 0, 0, 0);
	s->areas[0].wall_e = load_tga("images/zone_0/wall_e.tga", 0, 0, 0);
	s->areas[0].wall_w = load_tga("images/zone_0/wall_w.tga", 0, 0, 0);
	s->areas[1].wall_n = load_tga("images/zone_1/wall_n.tga", 0, 0, 0);
	s->areas[1].wall_s = load_tga("images/zone_1/wall_s.tga", 0, 0, 0);
	s->areas[1].wall_e = load_tga("images/zone_1/wall_e.tga", 0, 0, 0);
	s->areas[1].wall_w = load_tga("images/zone_1/wall_w.tga", 0, 0, 0);
	s->areas[2].wall_n = load_tga("images/zone_2/wall_n.tga", 0, 0, 0);
	s->areas[2].wall_s = load_tga("images/zone_2/wall_s.tga", 0, 0, 0);
	s->areas[2].wall_e = load_tga("images/zone_2/wall_e.tga", 0, 0, 0);
	s->areas[2].wall_w = load_tga("images/zone_2/wall_w.tga", 0, 0, 0);
	s->areas[3].wall_n = load_tga("images/zone_3/wall_n.tga", 0, 0, 0);
	s->areas[3].wall_s = load_tga("images/zone_3/wall_s.tga", 0, 0, 0);
	s->areas[3].wall_e = load_tga("images/zone_3/wall_e.tga", 0, 0, 0);
	s->areas[3].wall_w = load_tga("images/zone_3/wall_w.tga", 0, 0, 0);
	s->weapon.image[0] = load_tga("images/gun_0.tga", 0, 0, 0);
	s->weapon.image[1] = load_tga("images/gun_1.tga", 0, 0, 0);
	s->weapon.image[2] = load_tga("images/gun_2.tga", 0, 0, 0);
	s->skybox = load_tga("images/skybox_stars.tga", 0, 0, 0);
	s->interface = load_tga("images/interface.tga", 0, 0, 0);
	s->door = load_tga("images/door.tga", 0, 0, 0);
	s->weapon.current = 0;
}

void		initialize_sdl(t_main *s, t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		ft_error_sdl("Échec de l'initialisation de la SDL");
	if (!(sdl->pwindow = SDL_CreateWindow("Wolf3D", 100,
		100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)))
		ft_error_sdl("Échec de creation de la fenetre");
	if (!(sdl->prenderer = SDL_CreateRenderer(sdl->pwindow, -1, 0)))
		ft_error_sdl("Échec de chargement du renderer");
	load_images(s);
	if (!check_images(s))
		exit(-1);
	if (!(sdl->map = initialize_texture(sdl, WIDTH, HEIGHT)))
		exit(-1);
	if (!(sdl->game = initialize_texture(sdl, WIDTH, HEIGHT)))
		exit(-1);
	if (!(sdl->ui = initialize_texture(sdl, s->interface->w, s->interface->h)))
		exit(-1);
	ft_memcpy(sdl->ui->content, s->interface->tex, s->interface->h
	* s->interface->w);
	if (!(s->sdl->minimap = (SDL_Surface *)malloc(sizeof(SDL_Surface))))
		exit(-1);
	sdl->x_o = WIDTH / 2 - ((SPACE * s->width) / 2);
	sdl->y_o = HEIGHT / 2 - ((SPACE * s->height) / 2);
	sdl->musique = NULL;
	create_sounds(sdl);
}

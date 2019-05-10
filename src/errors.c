/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:50:10 by ydonse            #+#    #+#             */
/*   Updated: 2019/05/10 12:13:50 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	free_images(t_main *s, int i)
{
	while (i < MAX_AREA)
	{
		ft_memdel(((void **)&s->areas[i].wall_n));
		ft_memdel(((void **)&s->areas[i].wall_s));
		ft_memdel(((void **)&s->areas[i].wall_e));
		ft_memdel(((void **)&s->areas[i].wall_w));
		i++;
	}
	ft_memdel(((void **)&s->skybox));
	ft_memdel(((void **)&s->weapon.image[0]));
	ft_memdel(((void **)&s->weapon.image[1]));
	ft_memdel(((void **)&s->weapon.image[2]));
	ft_memdel(((void **)&s->door));
	ft_memdel(((void **)&s->interface));
}

void	free_program(t_main *s)
{
	int i;

	i = 0;
	ft_strdel(&(s->parsing_line));
	if (s->map != NULL)
	{
		while (i < s->height)
			ft_memdel((void **)&s->map[i++]);
		ft_memdel((void **)&s->map);
	}
	if (s->sdl->musique != NULL)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(s->sdl->musique);
		Mix_CloseAudio();
	}
	free_images(s, 0);
	ft_memdel((void **)&s->sdl->pwindow);
	ft_memdel((void **)&s->sdl->prenderer);
	ft_memdel((void **)&s->sdl);
	ft_memdel((void **)&s);
}

void	display_error(int error_nb)
{
	if (error_nb == FILE_ERROR)
		ft_putstr("Error : The file cannot be opened\n");
	else if (error_nb == SIZE_ERROR)
		ft_putstr("Error : Map too small\n");
	else if (error_nb == SYNTAX_ERROR)
		ft_putstr("Error : Syntax error\n");
	else if (error_nb == MALLOC_ERROR)
		ft_putstr("Error : Malloc error\n");
	else if (error_nb == PLAYER_ERROR)
		ft_putstr("Error : One player position needed.\n");
	else if (error_nb == WALL_ERROR)
		ft_putstr("Error : Map must be limited by walls !\n");
}

void	handle_error(t_main *s, int error_nb)
{
	if (error_nb != 0)
		display_error(error_nb);
	free_program(s);
	exit(0);
}

void	ft_error_sdl(char *str)
{
	ft_putstr(str);
	ft_putchar(' ');
	ft_putstr(SDL_GetError());
	exit(-1);
}

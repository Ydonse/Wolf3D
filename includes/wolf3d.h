/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 10:04:29 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/23 11:58:31 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H

# include "libft.h"
# include <SDL2/SDL.h>

# define WIDTH 800
# define HEIGHT 800

typedef struct	s_sdl
{
	SDL_Window		*pwindow;
	SDL_Renderer	*prenderer;
	SDL_Event		event;
}				t_sdl;

typedef struct	s_main
{
	t_sdl			*sdl;
}				t_main;

#define WOLF3D_H
#endif

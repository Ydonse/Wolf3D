/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 10:04:29 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/23 17:33:59 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "libft.h"
# include <SDL2/SDL.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdlib.h>

# define WIDTH 800
# define HEIGHT 800
# define MIN_WIDTH 3
# define MIN_HEIGHT 3
# define OBJ_TYPE_NB 4
# define FILE_ERROR 1
# define SIZE_ERROR 2
# define SYNTAX_ERROR 3
# define MALLOC_ERROR 4
# define MAX_AREA 0

typedef struct		s_case
{
	char	type;
	char	zone;
}					t_case;

typedef struct		s_sdl
{
	SDL_Window		*pwindow;
	SDL_Renderer	*prenderer;
	SDL_Event		event;
}					t_sdl;

typedef struct		s_main
{
	t_sdl			*sdl;
	t_case			**map;
	int				width;
	int				height;
	char			*parsing_line;
}					t_main;

void				handle_error(t_main *s, int error_nb);
int					parse_map(t_main *s, char *file);
#endif

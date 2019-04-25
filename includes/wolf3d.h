/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 10:04:29 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/25 15:47:09 by malluin          ###   ########.fr       */
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
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 800
# define MIN_WIDTH 3
# define MIN_HEIGHT 3
# define FILE_ERROR 1
# define SIZE_ERROR 2
# define SYNTAX_ERROR 3
# define MALLOC_ERROR 4
# define PLAYER_ERROR 5
# define WALL_ERROR 6
# define MAX_AREA 0
# define OBJ "mp.tj"

# define LEFT	SDL_SCANCODE_LEFT
# define RIGHT	SDL_SCANCODE_RIGHT
# define UP		SDL_SCANCODE_UP
# define DOWN	SDL_SCANCODE_DOWN


typedef struct		s_position {
	short			x;
	short			y;
}					t_position;

typedef struct		s_dpos {
	double			x;
	double			y;
}					t_dpos;

typedef struct		s_case {
	char			type;
	char			zone;
	t_bool			valid;
}					t_case;

typedef struct		s_texture {
	Uint32			*content;
	SDL_Texture		*texture;
	Uint32			color_tmp;
}					t_texture;

typedef struct		s_sdl {
	SDL_Window		*pwindow;
	SDL_Renderer	*prenderer;
	SDL_Event		event;
	SDL_Surface 	*minimap;
	t_texture		*map;
}					t_sdl;

typedef struct		s_main {
	t_sdl			*sdl;
	t_case			**map;
	int				width;
	int				height;
	char			*parsing_line;
	t_position		start_position;
	t_dpos			player_pos;
	double			move_speed;
}					t_main;

void				handle_error(t_main *s, int error_nb);
int					parse_map(t_main *s, char *file);
int					check_next_case(t_main *s, int x, int y);
void				draw_minimap(t_main *s);

void				ft_print_map(t_main	*s);
#endif

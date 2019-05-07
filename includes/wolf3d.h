/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 10:04:29 by ydonse            #+#    #+#             */
/*   Updated: 2019/05/07 11:42:26 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "libft.h"
# include <SDL2/SDL.h>
# include <SDL2/SDL_mixer.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>

# define WIDTH 800
# define HEIGHT 600
# define SPACE 60
# define MIN_WIDTH 3
# define MIN_HEIGHT 3

# define FILE_ERROR 1
# define SIZE_ERROR 2
# define SYNTAX_ERROR 3
# define MALLOC_ERROR 4
# define PLAYER_ERROR 5
# define WALL_ERROR 6

# define SKY 0x69DBF5FF
# define MIXSW 0x82989DFF
# define WALL  0x9a5444FF
# define GROUND  0xB0B0B0FF
# define DOOR  0xBBBBBBFF

# define MAX_AREA 0
# define OBJ "mp.tj"

# define PLAYER_SIZE 0.25
# define BLOCK_SIZE 64
# define PLAYER_HEIGHT 32
# define DEFAULT_FOV 65
# define ROTATE_SPEED 2

# define PROJ_WIDTH 800
# define PROJ_HEIGHT 600

#define PI 3.14159265

# define LEFT_AR	SDL_SCANCODE_LEFT
# define RIGHT_AR	SDL_SCANCODE_RIGHT
# define UP_AR		SDL_SCANCODE_UP
# define DOWN_AR	SDL_SCANCODE_DOWN

# define LEFT	SDL_SCANCODE_A
# define RIGHT	SDL_SCANCODE_D
# define UP		SDL_SCANCODE_W
# define DOWN	SDL_SCANCODE_S

# define SPRINT	SDL_SCANCODE_LSHIFT

# define PARSE_BUFF_SIZE 64

typedef	struct 		s_sounds
{
	Mix_Chunk		*shot;
	Mix_Chunk		*door;
}					t_sounds;

typedef struct		s_position {
	short			x;
	short			y;
}					t_position;

typedef struct		s_dpos {
	double			x;
	double			y;
}					t_dpos;

typedef struct		s_ray {
	double			dist;
	char			type;
	char			orientation;
	t_position		object;
	t_dpos			dpos;
	short			res;
}					t_ray;

typedef struct		s_case {
	char			type;
	char			zone;
	char			block;
	t_bool			valid;
}					t_case;

typedef struct		s_texture {
	Uint32			*content;
	SDL_Texture		*texture;
	Uint32			color_tmp;
}					t_texture;

typedef struct		s_image {
	int				bits_color;
	int				bits_alpha;
	Uint32			*tex;
	int				w;
	int				h;
}					t_image;

typedef struct		s_slice {
	int				bwall;
	int				ewall;
	t_position		pix;
	Uint32			color;
}					t_slice;

typedef struct		s_sdl {
	SDL_Window		*pwindow;
	SDL_Renderer	*prenderer;
	SDL_Event		event;
	SDL_Surface 	*minimap;
	t_texture		*map;
	t_texture		*game;
	t_texture		*ui;
	int				x_o;
	int				y_o;
	t_sounds		sounds;
}					t_sdl;

typedef struct		s_main {
	t_sdl			*sdl;
	t_case			**map;
	int				width;
	int				height;
	char			*parsing_line;
	t_position		start_position;
	double			move_speed;
	t_dpos			player_pos;
	short			p_angle;
	char			active_map;
	short			fov;
	int				proj_distance;
	int				viewline;
	t_image			*wall;
	t_image			*door;
	t_image			*interface;
}					t_main;

void				handle_error(t_main *s, int error_nb);
int					parse_map(t_main *s, char *file);
int					check_next_case(t_main *s, int x, int y);
void				draw_minimap(t_main *s);
void				draw_player(t_main *s, t_sdl *sdl);
void				draw_rect(t_sdl *sdl, t_texture *text, t_position orig,
					t_position dest);

void				set_pixel(t_texture *text, Uint32 color, t_position coord);
void				update_image(t_main *s, t_texture *texture);
int					check_collisions(t_main *s, t_dpos target);

void				ft_print_map(t_main	*s);

void				ft_error_sdl(char *str);

//INITIALIZE
t_main				*initialize_main(void);
t_texture			*initialize_texture(t_sdl *sdl, int width, int height);
void				initialize_sdl(t_main *s, t_sdl *sdl);

//EVENTS

void				event_handler(t_main *s);
void				turn_camera(t_main *s, const Uint8 *keys, char command);
void				move_player(t_main *s, const Uint8 *keys, char sprint);



void				raycast_visualization(t_main *s);
t_ray				raycast(t_main *s, double r_angle);
void				set_pixel_debug(t_sdl *sdl, t_dpos coord);
void				draw_debug_rect(t_sdl *sdl, t_texture *text, Uint32 color, t_dpos orig);

double				to_rad(double angle);
double				norme(t_dpos player, t_dpos point);
double				percent(double value, double total);

//IMAGES

t_image				*load_tga(char *path);

//SOUNDS
void				create_sounds(t_sdl *sdl);




#endif

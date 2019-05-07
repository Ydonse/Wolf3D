/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 10:19:27 by ydonse            #+#    #+#             */
/*   Updated: 2019/05/07 18:25:01 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void update_image(t_main *s, t_texture *texture)
{
	SDL_SetRenderTarget(s->sdl->prenderer, texture->texture);
	SDL_UpdateTexture(texture->texture, NULL, texture->content, WIDTH
		* sizeof(Uint32));
	SDL_SetRenderTarget(s->sdl->prenderer, NULL);
	SDL_RenderCopy(s->sdl->prenderer, texture->texture, NULL, NULL);
	SDL_RenderPresent(s->sdl->prenderer);
}

void	set_pixel(t_texture *text, Uint32 color, t_position coord)
{
	if (coord.x >= 0 && coord.x < WIDTH && coord.y >= 0 && coord.y < HEIGHT)
	{
		text->content[coord.x + coord.y * WIDTH] = color;
	}
}

void	draw_interface (t_main *s)
{
	t_position coord;
	int i;
	int j;
	t_position orig;
	double perx;
	double pery;

	orig.x = 0;
	orig.y = HEIGHT - s->interface->h;
	coord.y = 0;
	coord.x = 0;
	i = 0;
	j = 0;
	while (i < WIDTH)
	{
		j = orig.y;
		coord.x = i;
		perx = (double)coord.x / (double)WIDTH;
		while (j < HEIGHT)
		{
			coord.y = j++;
			pery = (percent(coord.y - orig.y, HEIGHT - orig.y));
			// set_pixel(s->sdl->game, s->interface->tex[s->interface->h * s->interface->w - 1 + (s->interface->w) - 1], coord);
			set_pixel(s->sdl->game, s->interface->tex[(int)(pery * (double)s->interface->h * s->interface->w + (perx * (double)s->interface->w))], coord);
		}
		i++;
	}
}

void	draw_weapon (t_main *s)
{
	t_position coord;
	int i;
	int j;
	t_position orig;
	double perx;
	double pery;
	t_position dest;
	int		pix_tex;

	orig.x = WIDTH / 2 - (s->weapon->w / 2);
	orig.y = HEIGHT - s->interface->h - s->weapon->h;
	dest.x = WIDTH / 2 + (s->weapon->w / 2);
	dest.y = HEIGHT - s->interface->h;
	coord.y = 0;
	coord.x = 0;
	i = orig.x;
	j = 0;
	while (i < dest.x)
	{
		j = orig.y;
		coord.x = i;
		perx = (int)(percent(coord.x - orig.x, dest.x - orig.x) * 100);
		while (j < dest.y)
		{
			coord.y = j++;
			pery = (int)(percent(coord.y - orig.y, dest.y - orig.y) * 100);
			pix_tex = (int)(pery * s->weapon->h / 100.0) * s->weapon->w + (int)(perx * s->weapon->w / 100.0);

			// set_pixel(s->sdl->game, s->interface->tex[s->interface->h * s->interface->w - 1 + (s->interface->w) - 1], coord);
			if (s->weapon->tex[pix_tex] != 0x97ff8800)
				set_pixel(s->sdl->game, s->weapon->tex[pix_tex], coord);
		}
		i++;
	}
}

void	draw_rect(t_sdl *sdl, t_texture *text, t_position orig, t_position dest)
{
	int		i;
	int		j;
	t_position	coord;

	(void) sdl;
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
			set_pixel(text, text->color_tmp, coord);
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

// void	fill_texture(t_main *s, t_image *image, t_texture *texture)
// {
// 	int i;
// 	int j;
//
// 	i = 0;
// 	j = 0;
// 	while (i < image->h)
// 	{
// 		while (j < image->w)
// 		{
// 			texture->te
// 		}
// 	}
// }

// void	draw_interface(t_main *s)
// {
// 	t_position	orig;
// 	t_position	dest;
// 	int i;
// 	int j;
//
// 	i = 0;
// 	j = 0;
// }

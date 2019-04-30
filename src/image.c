/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 10:19:27 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/30 17:16:19 by malluin          ###   ########.fr       */
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
	if (coord.x > 0 && coord.x < WIDTH && coord.y > 0 && coord.y < HEIGHT)
	{
		text->content[coord.x + coord.y * WIDTH] = color;
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

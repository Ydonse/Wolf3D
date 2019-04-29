/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 10:19:27 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/29 10:20:59 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void update_image(t_main *s)
{
	SDL_SetRenderTarget(s->sdl->prenderer, s->sdl->map->texture);
	SDL_UpdateTexture(s->sdl->map->texture, NULL, s->sdl->map->content, WIDTH
		* sizeof(Uint32));
	SDL_SetRenderTarget(s->sdl->prenderer, NULL);
	SDL_RenderCopy(s->sdl->prenderer, s->sdl->map->texture, NULL, NULL);
	SDL_RenderPresent(s->sdl->prenderer);
}

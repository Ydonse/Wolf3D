/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 10:20:16 by ydonse            #+#    #+#             */
/*   Updated: 2019/05/09 18:05:21 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	update_image(t_main *s, t_texture *texture)
{
	SDL_SetRenderTarget(s->sdl->prenderer, texture->texture);
	SDL_UpdateTexture(texture->texture, NULL, texture->content, WIDTH
		* sizeof(Uint32));
	SDL_SetRenderTarget(s->sdl->prenderer, NULL);
	SDL_RenderCopy(s->sdl->prenderer, texture->texture, NULL, NULL);
	SDL_RenderPresent(s->sdl->prenderer);
}

int		check_walls(t_main *s, int x, int y)
{
	s->map[y][x].valid = 1;
	if (check_next_case(s, x, y))
		return (1);
	else
		return (0);
}

int		check_door(t_case **map, int x, int y)
{
	if (map[y][x].type == 'p' && map[y][x].block == 1)
		return (1);
	else
		return (0);
}

int		main(int ac, char **av)
{
	t_main	*s;

	if (ac <= 1)
		return (1);
	s = initialize_main();
	parse_map(s, av[1]);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)
	== -1)
		ft_putstr(Mix_GetError());
	initialize_sdl(s, s->sdl);
	s->player_pos.x = (double)s->start_position.x + 0.5;
	s->player_pos.y = (double)s->start_position.y + 0.5;
	if (!handle_menu(s))
		handle_error(s, 0);
	s->sdl->musique = Mix_LoadMUS("musics/game.wav");
	Mix_PlayMusic(s->sdl->musique, -1);
	event_handler(s);
	Mix_HaltMusic();
	Mix_CloseAudio();
	SDL_Quit();
	return (1);
}

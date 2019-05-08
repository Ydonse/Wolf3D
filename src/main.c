/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 10:20:16 by ydonse            #+#    #+#             */
/*   Updated: 2019/05/08 18:11:45 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	main (int ac, char **av)
{
	t_main	*s;

	if (ac <= 1)
		return (1);
	s = initialize_main();
	parse_map(s, av[1]);
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
		printf("%s", Mix_GetError());
	initialize_sdl(s, s->sdl);
	if (!handle_menu(s))
		free_program(s);
	s->player_pos.x = (double) s->start_position.x + 0.5;
	s->player_pos.y = (double) s->start_position.y + 0.5;
	if (!handle_menu(s))
		handle_error(s, 0);
	event_handler(s);
	Mix_CloseAudio();
	SDL_Quit();
	return (1);
}

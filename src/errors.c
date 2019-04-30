/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:50:10 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/30 17:11:19 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	free_program(t_main *s)
{
	int i;

	i = 0;
	ft_strdel(&(s->parsing_line));
	if (s->map != NULL)
	{
		while (i < s->height)
			free(s->map[i++]);
		free(s->map);
	}
	free(s->sdl);
	free(s);
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
	display_error(error_nb);
	free_program(s);
	exit(0);
}

void	ft_error_sdl(char *str)
{
	printf("%s (%s)\n", str, SDL_GetError());
	exit (-1);
}

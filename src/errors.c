/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:50:10 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/23 17:36:37 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	free_program(t_main *s)
{
	ft_strdel(&(s->parsing_line));
}

void	display_error(int error_nb)
{
	if (error_nb == FILE_ERROR)
		ft_putstr("Error : The file cannot be opened\n");
	else if(error_nb == SIZE_ERROR)
		ft_putstr("Error : Map too small\n");
	else if(error_nb == SYNTAX_ERROR)
		ft_putstr("Error : Syntax error\n");
	else if(error_nb == MALLOC_ERROR)
		ft_putstr("Error : Malloc error\n");
}

void	handle_error(t_main *s, int error_nb)
{
	display_error(error_nb);
	free_program(s);
	exit(0);
}

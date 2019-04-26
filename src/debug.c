/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:58:12 by malluin           #+#    #+#             */
/*   Updated: 2019/04/26 18:20:03 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_print_map(t_main	*s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < s->height)
	{
		while (j < s->width)
		{
			ft_putchar(s->map[i][j].type);
			ft_putchar(s->map[i][j].zone);
			ft_putnbr(s->map[i][j].block);
			ft_putchar(' ');
			j++;
		}
		i++;
		ft_putchar('\n');
		j = 0;
	}
}

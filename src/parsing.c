/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:58:00 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/23 18:04:09 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	fill_map(t_main *s, char **tab)
{
	static int 		i = 0;
	int 			j;
	int				k;

	j = 0;
	k = 0;
	if (!(s->map[i] = (t_case*)malloc(sizeof(t_case) * s->width)))
		handle_error(s, MALLOC_ERROR);
	while (tab[k])
	{
		s->map[i][k].type = tab[k][0];
		s->map[i][k].zone = tab[k][2];
		k++;
	}
	ft_free_tab_str(tab);
	i++;
}

void	check_valid_line(t_main *s, char **tab)
{
	int				i;
	int				j;
	t_bool			valid;
	static char		valid_letters[] = {
		'.', 'm', 'p', 't'};

	i = 0;
	j = 0;
	valid = 0;
	while (tab[i])
	{
		while (j < OBJ_TYPE_NB)
		{
			if (tab[i][0] == valid_letters[j++])
				valid = 1;
		}
		if (!valid || tab[i][1] != ',' || tab[i][2] < '0'
		|| tab[i++][2] > MAX_AREA + '0')
			{
				ft_free_tab_str(tab);
				handle_error(s, SYNTAX_ERROR);
			}
		j = 0;
		valid = 0;
	}
	ft_free_tab_str(tab);
	if (i != s->width && s->width != 0)
		handle_error(s, SYNTAX_ERROR);
	s->width = i;
}

void	check_file(t_main *s, int fd, char *file)
{
	int		line_nb;
	int		i;

	line_nb = 0;
	i = 0;
	while (get_next_line(fd, &(s->parsing_line)))
	{
		i++;
		if (!ft_isalpha(s->parsing_line[0]))
			handle_error(s, SYNTAX_ERROR);
		ft_strdel(&s->parsing_line);
	}
	if (i < MIN_HEIGHT)
		handle_error(s, SIZE_ERROR);
	s->height = i;
	close(fd);
	if ((fd = open(file, O_RDONLY)) < 1)
		handle_error(s, FILE_ERROR);
	while (get_next_line(fd, &(s->parsing_line)))
	{
		check_valid_line(s, ft_strsplit(s->parsing_line, ' '));
		ft_strdel(&(s->parsing_line));
	}
	close(fd);
}

int		parse_map(t_main *s, char *file)
{
	int fd;

	if ((fd = open(file, O_RDONLY)) < 1)
		handle_error(s, FILE_ERROR);
	check_file(s, fd, file);
	if ((fd = open(file, O_RDONLY)) < 1)
		handle_error(s, FILE_ERROR);
	if (!(s->map = (t_case**)malloc(sizeof(t_case*) * s->height)))
		handle_error(s, MALLOC_ERROR);
	while (get_next_line(fd, &(s->parsing_line)))
	{
		fill_map(s, ft_strsplit(s->parsing_line, ' '));
		ft_strdel(&(s->parsing_line));
	}
		return (1);
}

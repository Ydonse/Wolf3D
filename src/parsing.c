/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 12:58:00 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/24 15:13:25 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		check_walls(t_main *s, int x, int y)
{
	s->map[y][x].valid = 1;
	if (check_next_case(s, x, y))
		return (1);
	else
		return (0);
}

int		fill_map(t_main *s, char **tab, int i)
{
	static int		player = 0;
	int				k;

	k = 0;
	if (!(s->map[i] = (t_case*)malloc(sizeof(t_case) * s->width)))
	{
		ft_free_tab_str(tab);
		handle_error(s, MALLOC_ERROR);
	}
	while (tab[k])
	{
		s->map[i][k].type = tab[k][0];
		if (s->map[i][k].type == 'j')
		{
			s->player_position.x = k;
			s->player_position.y = i;
			player++;
		}
		s->map[i][k].zone = tab[k][2];
		s->map[i][k++].valid = 0;
	}
	ft_free_tab_str(tab);
	if (++i == s->width && player > 1)
		handle_error(s, PLAYER_ERROR);
	return (i);
}

void	check_valid_line(t_main *s, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!ft_strchr(OBJ, tab[i][0]) || tab[i][1] != ',' || tab[i][2] < '0'
		|| tab[i++][2] > MAX_AREA + '0')
		{
			ft_free_tab_str(tab);
			handle_error(s, SYNTAX_ERROR);
		}
	}
	ft_free_tab_str(tab);
	if (i != s->width && s->width != 0)
		handle_error(s, SYNTAX_ERROR);
	s->width = i;
}

void	check_file(t_main *s, int fd, char *file)
{
	int		i;

	i = 0;
	while (get_next_line(fd, &(s->parsing_line)))
	{
		i++;
		if (!ft_isalpha(s->parsing_line[0]))
			handle_error(s, SYNTAX_ERROR);
		ft_strdel(&(s->parsing_line));
	}
	ft_strdel(&(s->parsing_line));
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
	ft_strdel(&(s->parsing_line));
	close(fd);
}

int		parse_map(t_main *s, char *file)
{
	int fd;
	int i;

	i = 0;
	if ((fd = open(file, O_RDONLY)) < 1)
		handle_error(s, FILE_ERROR);
	check_file(s, fd, file);
	if ((fd = open(file, O_RDONLY)) < 1)
		handle_error(s, FILE_ERROR);
	if (!(s->map = (t_case**)malloc(sizeof(t_case*) * s->height)))
		handle_error(s, MALLOC_ERROR);
	while (get_next_line(fd, &(s->parsing_line)))
	{
		i = fill_map(s, ft_strsplit(s->parsing_line, ' '), i);
		ft_strdel(&(s->parsing_line));
	}
	if (!check_walls(s, s->player_position.x, s->player_position.y))
		handle_error(s, WALL_ERROR);
	return (1);
}

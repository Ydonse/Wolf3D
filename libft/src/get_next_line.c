/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmerding <fmerding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:30:35 by fmerding          #+#    #+#             */
/*   Updated: 2018/12/20 13:40:55 by fmerding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

t_gnlist	*ft_gnlistnew(int fd)
{
	t_gnlist	*new;
	int			i;

	if (!(new = (t_gnlist *)malloc(sizeof(t_gnlist))))
		return (NULL);
	if (!(new->save = ft_strnew(BUFF_SIZE)))
		return (NULL);
	new->fd = fd;
	new->next = NULL;
	i = read(fd, new->save, BUFF_SIZE);
	if (i == -1)
		return (NULL);
	return (new);
}

void		ft_save(t_gnlist *node, char **line, char *needle)
{
	char	*before;
	char	*after;
	char	*tmp;

	before = ft_strsub(node->save, 0, needle - node->save);
	after = ft_strsub(node->save, (needle - node->save) + 1,
	ft_strlen(node->save));
	tmp = *line;
	*line = ft_strjoin(*line, before);
	ft_memdel((void **)&(node->save));
	node->save = after;
	ft_memdel((void **)&tmp);
	ft_memdel((void **)&before);
}

int			ft_read(int fd, t_gnlist *node, char **line)
{
	char	*needle;
	char	*tmp;
	int		i;
	int		len;

	i = 1;
	while (i > 0)
	{
		if ((needle = ft_strchr(node->save, '\n')))
		{
			ft_save(node, line, needle);
			return (1);
		}
		tmp = *line;
		*line = ft_strjoin(*line, node->save);
		ft_memdel((void **)&tmp);
		len = ft_strlen(node->save);
		ft_memdel((void **)&(node->save));
		if (!(node->save = ft_strnew(BUFF_SIZE)))
			return (-1);
		i = read(fd, node->save, BUFF_SIZE);
		if (!len && !i)
			return (0);
	}
	return (1);
}

t_gnlist	*ft_findfd(t_gnlist *save, int fd)
{
	t_gnlist	*node;

	while (save)
	{
		if (save->fd == fd)
			return (save);
		if (!(save->next))
			break ;
		save = save->next;
	}
	if (!(node = ft_gnlistnew(fd)))
		return (NULL);
	save->next = node;
	return (node);
}

int			get_next_line(const int fd, char **line)
{
	int					i;
	static t_gnlist		*save;
	t_gnlist			*node;

	if (!line || fd < 0 || BUFF_SIZE < 1)
		return (-1);
	if (!save)
		if (!(save = ft_gnlistnew(fd)))
			return (-1);
	*line = ft_strdup("");
	if (!(node = ft_findfd(save, fd)))
		return (-1);
	if ((i = ft_read(fd, node, line) > 0))
		return (1);
	if (i == 0)
		return (0);
	return (-1);
}

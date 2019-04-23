/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 16:04:55 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/21 11:28:44 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	**nullvalue(void)
{
	char **str;

	if (!(str = malloc(sizeof(char*) * (0))))
		return (NULL);
	str[0] = NULL;
	return (str);
}

static int	countwords(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (s[i] != c && s[i])
		count++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
		{
			count++;
		}
		i++;
	}
	return (count);
}

static int	lenwords(char const *s, char c, int nb)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = 0;
	while (j < nb)
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			j++;
		i++;
	}
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len);
}

static void	cpy(char const *s, char c, char *str, int nb)
{
	int i;
	int j;
	int len;

	i = 0;
	j = -1;
	len = 0;
	if (s[i] != c)
		j++;
	while (s[i] && j < nb)
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			j++;
		i++;
	}
	j = 0;
	while (s[i] != c && s[i])
	{
		str[j] = s[i];
		j++;
		i++;
	}
	str[j] = '\0';
}

char		**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		count;
	int		len;
	int		word;

	if (!s)
		return (NULL);
	count = countwords(s, c);
	len = 0;
	word = 0;
	if (count == 0)
		return (str = nullvalue());
	if (!(str = malloc(sizeof(char*) * (count + 1))))
		return (NULL);
	str[count] = NULL;
	while (word < count)
	{
		len = lenwords(s, c, word);
		if (!(str[word] = malloc(sizeof(char) * (len + 1))))
			return (NULL);
		cpy(s, c, str[word], word);
		word++;
	}
	return (str);
}

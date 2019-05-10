/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tga.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:40:18 by malluin           #+#    #+#             */
/*   Updated: 2019/05/10 12:26:47 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_image	*initialize_image(void)
{
	t_image	*image;

	image = NULL;
	if (!(image = (t_image *)malloc(sizeof(t_image))))
		return (0);
	image->w = 0;
	image->h = 0;
	image->tex = NULL;
	image->bits_color = 0;
	image->bits_alpha = 0;
	return (image);
}

void	print_bit(char c)
{
	int		i;
	char	d;

	i = 7;
	while (i >= 0)
	{
		d = (c >> i--) & 1;
		ft_putchar(d + 48);
	}
	write(1, "\n", 1);
}

void	get_info_header(t_image *image, unsigned char *str)
{
	image->bits_alpha = str[17] << 4 >> 4;
	image->bits_color = str[16];
	image->w = str[13];
	image->w = (image->w << 8) + str[12];
	image->h = str[15];
	image->h = (image->h << 8) + str[14];
	if (!(image->tex = (Uint32 *)malloc(sizeof(Uint32)
	* (image->w * image->bits_color * image->h))))
		exit(-1);
	ft_bzero(image->tex, sizeof(image->tex));
}

t_image	*load_tga(char *path, int i, int idx, int ret)
{
	unsigned char	str[PARSE_BUFF_SIZE];
	t_image			*image;
	int				fd;

	ft_bzero(str, PARSE_BUFF_SIZE);
	image = initialize_image();
	fd = open(path, O_RDONLY);
	if (fd == -1 || (ret = read(fd, str, 18)) < 18)
	{
		ft_memdel((void **)&image);
		return (0);
	}
	get_info_header(image, str);
	while ((ret = read(fd, str, PARSE_BUFF_SIZE)) != 0)
	{
		i = 0;
		while (i < ret)
		{
			image->tex[idx] = ((str[i]) << 8) + (str[i + 1] << 16)
			+ (str[i + 2] << 24);
			i += 4;
			idx += 1;
		}
	}
	return (image);
}

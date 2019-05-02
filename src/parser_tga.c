/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tga.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:40:18 by malluin           #+#    #+#             */
/*   Updated: 2019/05/02 14:13:08 by ydonse           ###   ########.fr       */
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

void	print_header(t_image *image, char *str)
{
	printf("ID_LENGTH:%d\nCOLOR_MAP_TYPE:%d\nIMAGE_TYPE:%d\n",
		str[0], str[1], str[2]);
	printf("IMAGE_SPECS:\nX-origin:%d\nY-origin:%d\n", str[8] + str[9],
		str[10] + str[11]);
	printf("width:%d\nheight:%d\n", image->w, image->h);
	printf("pixel depth:%d\n", image->bits_color);
	printf("alpha depth:%d\n\n", image->bits_alpha);
}

void	print_bit(char c)
{
	int i;
	char	d;

	i = 7;
	while (i >= 0)
	{
		d = (c >> i--) & 1;
		ft_putchar(d + 48);
	}
	write(1, "\n", 1);
}

void	get_info_header(t_image *image, char *str)
{
	image->bits_alpha = str[17] << 4 >> 4;
	image->bits_color = str[16];
	image->w = str[13];
	image->w = (image->w << 8) + (unsigned char)str[12];
	image->h = str[15];
	image->h = (image->h << 8) + (unsigned char)str[14];
	if (!(image->tex = (Uint32 *)malloc(sizeof(Uint32) *
	 (image->w * image->bits_color * image->h))))
		exit(-1);
}

t_image	*load_tga(char *path)
{
	char	str[PARSE_BUFF_SIZE];
	t_image	*image;
	int		fd;
	int		ret;
	int		i;
	int		idx;

	ft_bzero(str, PARSE_BUFF_SIZE);
	image = initialize_image();
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	if ((ret = read(fd, str, 18)) == 0)
		return (0);
	get_info_header(image, str);
	print_header(image, str);
	idx = 0;
	while ((ret = read(fd, str, PARSE_BUFF_SIZE)) != 0)
	{
		i = 0;
		while (i < ret)
		{
			// if (i % 32 == 0)
				// printf("I = %d\n", i);
			image->tex[idx] = (str[i] << 24) + (str[i + 1] << 16) + (str[i + 2] << 8) + str[i + 3];
			// printf("B%hhu G%hhu R%hhu A:%hhu  ", image->tex[i + 3],
			// image->tex[i + 2], image->tex[i + 1], image->tex[i]);
			i += (image->bits_color / 32) * 4;
			idx += (image->bits_color / 32);

			// printf("B%3d G%3d R%3d A:%d \n", image->tex[0 + 3],
			// image->tex[0 + 2], image->tex[0 + 1], image->tex[0]);
			// if (i % (image->w * 4) == 0)
			// 	printf(" |%d|\n", i);
		}
	}
	return (image);
}

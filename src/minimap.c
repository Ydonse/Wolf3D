/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:20:14 by ydonse            #+#    #+#             */
/*   Updated: 2019/05/14 17:50:42 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_square(t_main *s, t_dpos orig, t_dpos dest, t_image *wall)
{
	t_position	coord;
	int			perx;
	int			pery;
	int			pix_tex;

	coord.x = orig.x;
	while (coord.x < dest.x)
	{
		coord.y = orig.y;
		perx = (int)(percent(coord.x - orig.x, dest.x - orig.x) * 100);
		while (coord.y < dest.y)
		{
			coord.y++;
			pery = (int)(percent(coord.y - orig.y, dest.y - orig.y) * 100);
			pix_tex = (int)(pery * wall->h / 100.0) * wall->w
			+ (int)(perx * wall->w / 100.0);
			if (pix_tex >= 0 && pix_tex < (wall->h * wall->w))
				set_pixel(s->sdl->map, wall->tex[pix_tex], coord);
		}
		coord.x++;
	}
}

void	get_case_color(t_main *s, t_dpos orig, t_dpos dest, t_case pos)
{
	if (pos.type == 'm')
		draw_square(s, orig, dest, s->areas[0].wall_n);
	else if (pos.type == '.')
	{
		s->sdl->map->color_tmp = 0xB0B0B0FF;
		draw_rect(s->sdl->map, orig, dest);
	}
	else if (pos.type == 'j')
	{
		s->sdl->map->color_tmp = 0xA0A0A0FF;
		draw_rect(s->sdl->map, orig, dest);
	}
	else if (pos.type == 'p' && pos.block == 1)
	{
		draw_square(s, orig, dest, s->door);
	}
	else if (pos.type == 'p' && pos.block == 0)
	{
		s->sdl->map->color_tmp = 0xB0B0B0FF;
		draw_rect(s->sdl->map, orig, dest);
	}
}

void	draw_black(t_main *s)
{
	t_position xy;

	xy.x = -1;
	while (xy.x++ < WIDTH)
	{
		xy.y = -1;
		while (xy.y++ < HEIGHT)
			set_pixel(s->sdl->map, 0x000000FF, xy);
	}
}


void	draw_minimap(t_main *s)
{
	t_dpos orig;
	t_dpos dest;
	int			i;
	int			j;
	double			half_s_x;
	double			half_s_y;
	int			bloc_x;
	int			bloc_y;
	int			bloc_y_cp;
	double		per_pos_x;
	double		per_pos_y;

	draw_black(s);
	half_s_x = (WIDTH / SPACE) / 2;
	half_s_y = (HEIGHT / SPACE) / 2;

	bloc_y = s->player_pos.y < half_s_y ? 0 : (int)(s->player_pos.y - half_s_y);
	bloc_y = bloc_y >= s->height - (HEIGHT / SPACE) && s->player_pos.y > s->height - half_s_y - 1? s->height - (HEIGHT / SPACE): bloc_y;
	bloc_y_cp = bloc_y;

	bloc_x = s->player_pos.x < half_s_x ? 0 : (int)(s->player_pos.x - half_s_x);
	bloc_x = bloc_x >= s->width - (WIDTH / SPACE) && s->player_pos.x > s->width - half_s_x - 1? s->width - (WIDTH / SPACE): bloc_x;
	per_pos_x =  s->player_pos.x - (int)s->player_pos.x;
	per_pos_y =  s->player_pos.y - (int)s->player_pos.y;
	i = 0;
	j = 0;
	while (bloc_y_cp < s->height)
	{
		while (bloc_x < s->width)
		{
			if (s->player_pos.x < half_s_x) //Si le joueur est placé dans la 1ere moitié du debut de la map
			{
				orig.x = SPACE * j;
				dest.x = orig.x + SPACE;
			}
			else if (s->player_pos.x >= half_s_x && s->player_pos.x < s->width - half_s_x - 1)
			{
				if (j == 0) // Je dessine partiellement la premiere case
				{
					orig.x = j - SPACE + ((1 - per_pos_x) * SPACE);
					dest.x = (orig.x + SPACE);
				}
				else if (j != 0) //Je dessine normalement le reste des cases par rapport a la premiere
				{
					orig.x = SPACE * j - (per_pos_x * SPACE);
					dest.x = orig.x + SPACE;
				}
			}
			else if (s->player_pos.x >= half_s_x && s->player_pos.x >= s->width - half_s_x - 1)
			{
				orig.x = SPACE * j;
				dest.x = orig.x + SPACE;
			}
			if (s->player_pos.y < half_s_y)
			{
				// printf("true\n");
				orig.y = SPACE * i;
				dest.y = orig.y + SPACE;
			}
			else if (s->player_pos.y >= half_s_y && s->player_pos.y < s->height - half_s_y - 1)
			{
				if (i == 0)
				{
					orig.y = i - SPACE + ((1 - per_pos_y) * SPACE);
					dest.y = (orig.y + SPACE);
				}
				else if (i != 0)
				{
					orig.y = SPACE * i - (per_pos_y * SPACE);
					dest.y = orig.y + SPACE;
				}
			}
			else if (s->player_pos.y >= half_s_y && s->player_pos.y >= s->height - half_s_y - 1)
			{
				// printf("LOL\n");
				orig.y = SPACE * i;
				dest.y = orig.y + SPACE;
			}
			// printf("%d\n", bloc_y);
			get_case_color(s, orig, dest, s->map[bloc_y][bloc_x++]);
			j++;
		}
			j = 0;
		bloc_x = s->player_pos.x < half_s_x ? 0 : (int)(s->player_pos.x - half_s_x);
		bloc_x = bloc_x >= s->width - (WIDTH / SPACE) && s->player_pos.x > s->width - half_s_x - 1? s->width - (WIDTH / SPACE): bloc_x;
		bloc_y++;
		bloc_y_cp++;
		i++;
	}
	double test1 = s->player_pos.x - half_s_x <= 0 ? s->player_pos.x : s->player_pos.x - (s->player_pos.x - half_s_x);
	double test2 = s->player_pos.y - half_s_y <= 0 ? s->player_pos.y : s->player_pos.y - (s->player_pos.y - half_s_y);
	if (s->player_pos.x > s->width - half_s_x - 1)
		test1 = WIDTH / SPACE - (s->width - s->player_pos.x);
	if (s->player_pos.y > s->height - half_s_y)
	{
		test2 = HEIGHT / SPACE - (s->height - s->player_pos.y) +1 ;
	}

	draw_player(s, s->sdl, test1, test2);
	raycast_visualization(s);
	update_image(s, s->sdl->map);

}

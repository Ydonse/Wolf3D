/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malluin <malluin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 11:55:41 by malluin           #+#    #+#             */
/*   Updated: 2019/04/30 17:43:46 by malluin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		check_entity_h(t_main *s, t_dpos point, double r_angle, char *type)
{

	if (r_angle > 180 && r_angle < 360)
	{
		if (point.x < 0 || point.x >= (double)s->width || point.y < 0
			|| point.y >= (double)s->height)
			return (-1);
		if (ft_strchr(type, s->map[(int)point.y][(int)point.x].type) != NULL)
		{
			draw_debug_rect(s->sdl, s->sdl->map, 0xFF0000FF, point);
			return (1);
		}
	}
	else if (r_angle > 0 && r_angle < 180)
	{
		if (point.x < 0 || point.x >= (double)s->width || point.y - 1 < 0
			|| point.y - 1 >= (double)s->height)
			return (-1);
		if (ft_strchr(type, s->map[(int)point.y - 1][(int)point.x].type) != NULL)
		{
			// printf("collision angle %f %f %f\n", r_angle, point.x, point.y);
			draw_debug_rect(s->sdl, s->sdl->map, 0xFF0000FF, point);
			return (1);
		}
	}
	return (0);
}

int		check_entity_v(t_main *s, t_dpos point, double r_angle, char *type)
{

	if ((r_angle >= 0 && r_angle < 90) || (r_angle > 270 && r_angle < 360))
	{
		if (point.x < 0 || point.x >= s->width || point.y < 0
			|| point.y >= s->height)
			return (-1);
		if (ft_strchr(type, s->map[(int)point.y][(int)point.x].type) != NULL)
		{
			draw_debug_rect(s->sdl, s->sdl->map, 0x00FF00FF, point);
			return (1);
		}
	}
	else if (r_angle > 90 && r_angle < 270)
	{
		if (point.x - 1 < 0 || point.x - 1 >= s->width || point.y < 0
			|| point.y>= s->height)
			return (-1);
		if (ft_strchr(type, s->map[(int)point.y][(int)point.x - 1].type) != NULL)
		{
			draw_debug_rect(s->sdl, s->sdl->map, 0x00FF00FF, point);
			return (1);
		}
	}
	return (0);
}

double		raycast_hor(t_main *s, t_dpos fp, double r_angle)
{
	char	sens;
	t_dpos 	b;
	double	xa;
	int		res;

	if (r_angle == 0 || r_angle == 180 || r_angle == 360)
		return (0);
	sens = (r_angle > 0 && r_angle < 180) ? -1 : 1;
	fp.y = (double)((int) s->player_pos.y + (sens == 1));
	fp.x = (s->player_pos.y - fp.y) / tan(to_rad(r_angle)) + s->player_pos.x;
	res = check_entity_h(s, fp, r_angle, "mp");
	if (res == 1)
		return (norme(s->player_pos, fp));
	else if (res == -1)
		return (-1);
	while (1)
	{
		xa = 1.0 / tan(to_rad(r_angle));
		b.y = fp.y + sens;
		b.x = fp.x + xa * -sens;
		if (b.y < 0 || b.y > (double)s->height || b.x < 0 || b.x > (double)s->width)
			break;
		res = check_entity_h(s, b, r_angle, "mp");
		if (res == 1)
			return (norme(s->player_pos, b));
		else if (res == -1)
			break;
		sens = sens < 0 ? sens - 1 : sens + 1;
	}
	return (0);
}

double		raycast_ver(t_main *s, t_dpos fp, double r_angle)
{
	char	sens;
	t_dpos	b;
	double	ya;
	int		res;

	if (r_angle == 90 || r_angle == 270)
		return (0);
	sens = (r_angle >= 0 && r_angle < 90) || (r_angle > 270 && r_angle < 360) ? 1 : -1;
	fp.x = (int) s->player_pos.x + (sens == 1);
	fp.y = s->player_pos.y +  (s->player_pos.x - fp.x ) * tan(to_rad(r_angle));
	res = check_entity_v(s, fp, r_angle, "mp");
	if (res == 1)
		return (norme(s->player_pos, fp));
	else if (res == -1)
		return (-1);
	while (1)
	{
		ya = tan(to_rad(r_angle));
		b.x = fp.x + sens;
		b.y = fp.y + ya * -sens;
		if (b.y < 0 || b.y > (double)s->height || b.x < 0 || b.x > (double)s->width)
			break;
		// printf("%f %f\n", b.x, b.y);
		res = check_entity_v(s, b, r_angle, "mp");
		if (res == 1)
			return (norme(s->player_pos, b));
		else if (res == -1)
			break;
		sens = sens <= 0 ? sens - 1 : sens + 1;
	}
	return (0);
}

double	raycast(t_main *s, double r_angle)
{
	t_dpos	collision;
	double	disth;
	double	distv;

	collision.x = 0;
	collision.y = 0;

	r_angle = fmod(r_angle + 360.0, 360.0);
	disth = raycast_hor(s, collision, r_angle);
	distv = raycast_ver(s, collision, r_angle);
	// printf ("angle: %f H: %f V: %f\n", r_angle, disth, distv);

	if ((!(disth <= 0) && disth < distv) || distv <= 0)
		return (disth);
	else
		return (distv);
	// printf("%f\n", dist);
	// printf("%d %d\n", s->width, s->height);
}

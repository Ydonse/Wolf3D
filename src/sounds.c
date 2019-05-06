/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 11:33:44 by ydonse            #+#    #+#             */
/*   Updated: 2019/05/06 14:47:20 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	create_sounds(t_sdl *sdl)
{
	Mix_AllocateChannels(10); //Allouer 32 canaux
	Mix_Volume(1, MIX_MAX_VOLUME/2); //Mettre à mi-volume le post 1
	sdl->sounds.shot = Mix_LoadWAV("sounds/Pistol.wav");
}

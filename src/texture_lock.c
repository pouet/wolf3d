/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_lock.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 12:26:29 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/26 12:28:51 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_lock.h"
#include "wolf3d.h"
#include "errors.h"

void	lock_textures(t_cont *cont)
{
	if (SDL_LockTexture(cont->img.tex, NULL, (void **)&cont->img.pixels,
				&cont->img.pitch) < 0)
		exit_sdlerror();
}

void	unlock_textures(t_cont *cont)
{
	SDL_UnlockTexture(cont->img.tex);
}

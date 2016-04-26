/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 14:22:51 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/26 14:23:34 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "SDL.h"

typedef struct	s_texture
{
	SDL_Texture		*tex;
	Uint32			*pixels;
	int				pitch;
	int				w;
	int				h;
}				t_texture;

#endif

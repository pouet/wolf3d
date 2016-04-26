/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 12:35:18 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/26 12:37:15 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_H
# define LOAD_H

# include "SDL.h"
# include "wolf3d.h"

void		load_textures(t_cont *cont);
void		load_animantions(t_cont *cont);
SDL_Texture	*load_bmp(t_cont *cont, char *name);
void		copy_surface_to_texture(SDL_Texture *tex, SDL_Surface *bmp);

#endif

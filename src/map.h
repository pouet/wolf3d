/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 08:54:33 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/27 12:36:42 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "wolf3d.h"

typedef struct	s_load_maps
{
	int			*map;
	int			h;
	int			w;
}				t_load_maps;

# define NMAPS 1

void			load_map(t_cont *cont, int n);

#endif

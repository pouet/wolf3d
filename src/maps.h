/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 08:56:09 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/27 08:56:13 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPS_H
# define MAPS_H

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

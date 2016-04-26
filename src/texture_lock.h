/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_lock.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 12:26:58 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/26 12:28:23 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_LOCK_H
# define TEXTURE_LOCK_H

# include "wolf3d.h"

void	lock_textures(t_cont *cont);
void	unlock_textures(t_cont *cont);

#endif

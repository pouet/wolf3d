/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 12:42:10 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/26 14:23:49 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIM_H
# define ANIM_H

# include "texture.h"

/*
** r.w, r.h => width, height of the texture
** w_one_frame => width one frame
** n_frame => number of frame in animation
** replay =>	-1: infinite
**				0: print 1rst frame
**				>0: replay n time
** time => time between each frame (multiple of FPS_DFLT)
** ticks => actual time since start
** frame => current frame
** started => ... need help ?
*/

typedef struct	s_anim
{
	t_texture	tex;
	int			w;
	int			h;
	int			w_one_frame;
	int			n_frame;
	int			replay;
	int			time;
	int			ticks;
	int			frame;
	int			started;
}				t_anim;

void			start_anim(t_anim *anim);
void			update_anim(t_anim *anim);

#endif

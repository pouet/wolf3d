/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 12:42:28 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/26 12:42:44 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "anim.h"

void	start_anim(t_anim *anim)
{
	if (anim->started == 1)
		return ;
	if (anim->replay == 0)
		anim->frame = 1;
	else
		anim->frame = 0;
	anim->ticks = 0;
	anim->started = 1;
}

void	update_anim(t_anim *anim)
{
	if (anim->started)
	{
		anim->ticks++;
		if (anim->ticks >= anim->time)
		{
			anim->frame++;
			if (anim->frame >= anim->n_frame)
			{
				anim->frame = 0;
				if (anim->replay == 0)
					anim->started = 0;
			}
			anim->ticks = 0;
		}
	}
}

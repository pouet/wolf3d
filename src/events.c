/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 12:22:18 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/27 14:09:19 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "events.h"

void	do_mousemotion(t_cont *cont)
{
	int				delta;
	const int		acceleration = 10;

	delta = cont->mouse.x;
	if (delta < -20)
	{
		while (delta < -10)
		{
			turn(cont, K_LEFT, 0.01);
			delta += acceleration;
		}
	}
	else if (delta > 20)
	{
		while (delta > 10)
		{
			turn(cont, K_RIGHT, 0.01);
			delta -= acceleration;
		}
	}
}

int		update_events(t_cont *cont)
{
	SDL_Event ev;

	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT)
			return (1);
		else if (ev.type == SDL_MOUSEWHEEL)
		{
			if (ev.wheel.y < 0)
			{
				cont->actual_gun = cont->actual_gun - 1;
				if (cont->actual_gun < 0)
					cont->actual_gun = N_ANIM - 1;
			}
			else if (ev.wheel.y > 0)
				cont->actual_gun = (cont->actual_gun + 1) % N_ANIM;
		}
	}
	cont->mouseb = SDL_GetRelativeMouseState(&cont->mouse.x, &cont->mouse.y);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 14:41:08 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/27 10:03:33 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include "SDL.h"
#include "libft.h"
#include "wolf3d.h"
#include "events.h"
#include "errors.h"
#include "texture_lock.h"
#include "load.h"
#include "init_quit.h"
#include "draw.h"
#include "calc.h"

void	framewait(t_cont *cont)
{
	unsigned	now;

	while (1)
	{
		now = SDL_GetTicks() - cont->g.ticks;
		if (now >= FPS_DFLT)
			break ;
		SDL_Delay(3);
	}
	cont->g.ticks = SDL_GetTicks();
	cont->ticks++;
}

void	do_all(t_cont *cont)
{
	do_mousemotion(cont);
	if (cont->state[SDL_SCANCODE_UP] || cont->state[SDL_SCANCODE_W])
		key_arrow(K_UP, cont);
	if (cont->state[SDL_SCANCODE_DOWN] || cont->state[SDL_SCANCODE_S])
		key_arrow(K_DOWN, cont);
	if (cont->state[SDL_SCANCODE_LEFT] || cont->state[SDL_SCANCODE_A])
		key_arrow(K_LEFT, cont);
	if (cont->state[SDL_SCANCODE_RIGHT] || cont->state[SDL_SCANCODE_D])
		key_arrow(K_RIGHT, cont);
	if (cont->state[SDL_SCANCODE_Q])
		key_arrow(K_SIDE_L, cont);
	if (cont->state[SDL_SCANCODE_E])
		key_arrow(K_SIDE_R, cont);
	if (cont->state[SDL_SCANCODE_U])
	{
		if (cont->full)
			SDL_SetWindowFullscreen(cont->win, 0);
		else
			SDL_SetWindowFullscreen(cont->win, SDL_WINDOW_FULLSCREEN);
		cont->full = !cont->full;
	}
	if ((cont->state[SDL_SCANCODE_SPACE] || (cont->mouseb & SDL_BUTTON(1))) &&
			cont->gun[cont->actual_gun].started == 0)
		start_anim(&cont->gun[cont->actual_gun]);
}

int		main_loop(t_cont *cont)
{
	int		i;

	while (1)
	{
		if (update_events(cont) || cont->state[SDL_SCANCODE_ESCAPE])
			break ;
		update_anim(&cont->gun[cont->actual_gun]);
		i = 0;
		while (i < N_ANIM)
		{
			update_anim(&cont->anim[i]);
			i++;
		}
		do_all(cont);
		lock_textures(cont);
		calc(cont);
		unlock_textures(cont);
		SDL_UpdateTexture(cont->img.tex, NULL, cont->pixels,
				cont->img.pitch);
		SDL_RenderCopy(cont->ren, cont->img.tex, NULL, NULL);
		SDL_RenderPresent(cont->ren);
		framewait(cont);
	}
	return (0);
}

int		main(void)
{
	t_cont	cont;

	ft_bzero(&cont, sizeof(cont));
	if (init_video(&cont) < 0)
		return (EXIT_FAILURE);
	init_var(&cont);
	main_loop(&cont);
	quit_video(&cont);
	return (0);
}

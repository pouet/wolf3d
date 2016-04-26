/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_quit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 14:30:17 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/26 14:41:42 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "init_quit.h"
#include "wolf3d.h"
#include "load.h"
#include "errors.h"
#include "xmalloc.h"

int		init_video(t_cont *cont)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		exit_sdlerror();
	cont->win = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0);
	if (cont->win == NULL)
		exit_sdlerror();
	cont->ren = SDL_CreateRenderer(cont->win, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE |
			SDL_RENDERER_PRESENTVSYNC);
	if (cont->ren == NULL)
		exit_sdlerror();
	SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1",
			SDL_HINT_OVERRIDE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	cont->pixels = xmalloc(WIN_H * WIN_W * sizeof(Uint32));
	return (0);
}

void	quit_video(t_cont *cont)
{
	free(cont->pixels);
	SDL_DestroyRenderer(cont->ren);
	SDL_DestroyWindow(cont->win);
	SDL_Quit();
}

void	init_var(t_cont *cont)
{
	cont->g.pos.x = 22;
	cont->g.pos.y = 12;
	cont->g.dir.x = -1;
	cont->g.dir.y = 0;
	cont->g.plane.x = 0;
	cont->g.plane.y = 0.66;
	cont->g.eye = 0;
	cont->g.ticks = SDL_GetTicks();
	cont->state = SDL_GetKeyboardState(NULL);
	cont->img.tex = SDL_CreateTexture(cont->ren, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	SDL_QueryTexture(cont->img.tex, NULL, NULL, &cont->img.w, &cont->img.h);
	load_textures(cont);
	load_animantions(cont);
}

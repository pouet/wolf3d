/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 12:35:39 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/27 10:10:01 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "load.h"
#include "wolf3d.h"
#include "errors.h"

void			copy_surface_to_texture(SDL_Texture *tex, SDL_Surface *bmp)
{
	SDL_Rect	r;
	void		*pixels;
	int			pitch;

	SDL_LockTexture(tex, NULL, &pixels, &pitch);
	r.y = 0;
	while (r.y < bmp->h)
	{
		r.x = 0;
		while (r.x < bmp->w)
		{
			*(Uint32 *)((char *)pixels + (r.y * pitch + r.x * 4)) =
				*(Uint32 *)((char *)bmp->pixels +
						(r.y * bmp->pitch + r.x * bmp->format->BytesPerPixel));
			r.x++;
		}
		r.y++;
	}
	SDL_UnlockTexture(tex);
}

SDL_Texture		*load_bmp(t_cont *cont, char *name)
{
	SDL_Surface	*bmp;
	SDL_Texture	*tex;

	bmp = SDL_LoadBMP(name);
	if (bmp == NULL)
		exit_sdlerror();
	tex = SDL_CreateTexture(cont->ren, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, bmp->w, bmp->h);
	if (tex == NULL)
		exit_sdlerror();
	copy_surface_to_texture(tex, bmp);
	SDL_FreeSurface(bmp);
	return (tex);
}

void			load_gun(t_cont *cont)
{
}

void			load_animantions(t_cont *cont)
{
	static char		*name[N_ANIM][2] = {
		{ "img/fusil_a_pompe.bmp", "" },
		{ "img/lance_roquette.bmp", "sfx/rocket1i.wav" },
		{ "img/coup_de_pied.bmp", "" },
		{ "img/ventilo.bmp", "" }
	};
	static t_anim	anims[N_ANIM] = {
		{ .n_frame = 6, .replay = 0, .time = 1, .started = 0 },
		{ .n_frame = 7, .replay = 0, .time = 3, .started = 0 },
		{ .n_frame = 3, .replay = 0, .time = 4, .started = 0 },
		{ .n_frame = 4, .replay = 0, .time = 5, .started = 0 }
	};
	int				i;

	i = 0;
	while (i < N_ANIM)
	{
		cont->anim[i].tex.tex = load_bmp(cont, name[i][0]);
		SDL_QueryTexture(cont->anim[i].tex.tex, NULL, NULL,
				&cont->anim[i].w, &cont->anim[i].h);
		cont->anim[i].tex.w = cont->anim[i].w;
		cont->anim[i].tex.h = cont->anim[i].h;
		cont->anim[i].n_frame = anims[i].n_frame;
		cont->anim[i].replay = -1;
		cont->anim[i].time = anims[i].time;
		cont->anim[i].w_one_frame = cont->anim[i].w / cont->anim[i].n_frame;
		cont->anim[i].started = 1;
		if (SDL_LockTexture(cont->anim[i].tex.tex, NULL,
					(void **)&cont->anim[i].tex.pixels, &cont->anim[i].tex.pitch) < 0)
			exit_sdlerror();
		start_anim(&cont->anim[i]);

		cont->gun[i].tex.tex = load_bmp(cont, name[i][0]);
		SDL_QueryTexture(cont->gun[i].tex.tex, NULL, NULL,
				&cont->gun[i].w, &cont->gun[i].h);
		cont->gun[i].tex.w = cont->gun[i].w;
		cont->gun[i].tex.h = cont->gun[i].h;
		cont->gun[i].n_frame = anims[i].n_frame;
		cont->gun[i].replay = anims[i].replay;
		cont->gun[i].time = anims[i].time;
		cont->gun[i].w_one_frame = cont->gun[i].w / cont->gun[i].n_frame;
		cont->gun[i].started = anims[i].started;
		if (SDL_LockTexture(cont->gun[i].tex.tex, NULL,
					(void **)&cont->gun[i].tex.pixels, &cont->gun[i].tex.pitch) < 0)
			exit_sdlerror();
		i++;
	}
	cont->gun[3].time = 1;
}

void			load_textures(t_cont *cont)
{
	static char	*name[N_TEXTURES] = {
		"img/eagle.bmp", "img/eagle.bmp", "img/pinkiepie.bmp",
		"img/rbdashgun.bmp", "img/greystone.bmp", "img/bluestone.bmp",
		"img/mossy.bmp", "img/wood.bmp", "img/colorstone.bmp", "img/barrel.bmp",
		"img/pillar.bmp", "img/greenlight.bmp", "img/rainbowdash512.bmp",
		"img/skybox.bmp"
	};
	int			i;

	i = 0;
	while (i < N_TEXTURES)
	{
		cont->tex[i].tex = load_bmp(cont, name[i]);
		SDL_QueryTexture(cont->tex[i].tex, NULL, NULL,
				&cont->tex[i].w, &cont->tex[i].h);
		if (SDL_LockTexture(cont->tex[i].tex, NULL,
					(void **)&cont->tex[i].pixels, &cont->tex[i].pitch) < 0)
			exit_sdlerror();
		i++;
	}
}

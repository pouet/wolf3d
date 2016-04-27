/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 12:35:39 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/27 14:06:41 by nchrupal         ###   ########.fr       */
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

t_anim			load_one_anim(t_cont *cont, char *file, t_anim specs)
{
	t_anim	anim;

	anim.tex.tex = load_bmp(cont, file);
	SDL_QueryTexture(anim.tex.tex, NULL, NULL,
			&anim.w, &anim.h);
	anim.tex.w = anim.w;
	anim.tex.h = anim.h;
	anim.n_frame = specs.n_frame;
	anim.replay = specs.replay;
	anim.time = specs.time;
	anim.w_one_frame = anim.w / anim.n_frame;
	anim.started = specs.started;
	anim.frame = 0;
	if (SDL_LockTexture(anim.tex.tex, NULL,
				(void **)&anim.tex.pixels, &anim.tex.pitch) < 0)
		exit_sdlerror();
	return (anim);
}

/*
**		{ "img/ventilo.bmp", "" }
**		{ .n_frame = 4, .replay = 0, .time = 5, .started = 0 };
*/


void			load_animantions(t_cont *cont)
{
	static char		*name[N_ANIM][2] = {
		{ "img/fusil_a_pompe.bmp", "" },
		{ "img/lance_roquette.bmp", "sfx/rocket1i.wav" },
		{ "img/coup_de_pied.bmp", "" }
	};
	static t_anim	anims[N_ANIM] = {
		{ .n_frame = 6, .replay = 0, .time = 1, .started = 0 },
		{ .n_frame = 7, .replay = 0, .time = 3, .started = 0 },
		{ .n_frame = 3, .replay = 0, .time = 4, .started = 0 }
	};
	int				i;

	i = 0;
	while (i < N_ANIM)
	{
		cont->anim[i] = load_one_anim(cont, name[i][0], anims[i]);
		cont->anim[i].started = 1;
		cont->anim[i].replay = -1;
		start_anim(&cont->anim[i]);
		cont->gun[i] = load_one_anim(cont, name[i][0], anims[i]);
		i++;
	}
}

void			load_textures(t_cont *cont)
{
	static char	*name[N_TEXTURES] = {
		"img/eagle.bmp", "img/eagle.bmp", "img/redbrick.bmp",
		"img/purplestone.bmp", "img/greystone.bmp", "img/bluestone.bmp",
		"img/mossy.bmp", "img/wood.bmp", "img/colorstone.bmp", "img/barrel.bmp",
		"img/pillar.bmp", "img/greenlight.bmp", "img/eagle.bmp",
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

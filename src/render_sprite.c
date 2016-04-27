/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 12:31:04 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/27 12:33:17 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "wolf3d.h"
#include "libft.h"

extern t_sprite g_sprite[NSPRITE];

void	render_sprite_fix(t_cont *cont, t_calc *c, int i, int stripe)
{
	SDL_Rect	tex;
	unsigned	col;
	int			y;
	int			w;

	w = cont->tex[g_sprite[c->order[i].order].text].w;
	tex.x = ((256 * (stripe - (-c->spw / 2 + c->spscrx)) * w /
				c->spw)) / 256;
	y = c->start.y;
	while (y < c->end.y)
	{
		tex.y = ((((y - c->vmovescr) * 256 - WIN_H * 128 + c->sph * 128) *
					w) / c->sph) / 256;
		col = cont->tex[g_sprite[c->order[i].order].text].pixels[tex.y *
			w + tex.x];
		col &= 0x00FFFFFF;
		if (col != 0)
			put_pixel(cont, stripe, y, col);
		y++;
	}
}

void	render_sprite_anim(t_cont *cont, t_calc *c, int i, int stripe)
{
	SDL_Rect	tex;
	unsigned	col;
	SDL_Rect	pt;
	unsigned	alpha;
	t_anim		*anim;

	anim = &cont->anim[g_sprite[c->order[i].order].text];
	alpha = anim->tex.pixels[0] & 0x00FFFFFF;
	pt.w = anim->w_one_frame;
	tex.x = (((256 * (stripe - (-c->spw / 2 + c->spscrx)) * pt.w /
				c->spw)) / 256) + anim->w_one_frame * anim->frame;
	if (tex.x >= anim->w_one_frame * (anim->frame + 1))
		return ;
	pt.y = c->start.y - 1;
	while (++pt.y < c->end.y)
	{
		tex.y = ((((pt.y - c->vmovescr) * 256 - WIN_H * 128 + c->sph * 128) *
					pt.w) / c->sph) / 256;
		if (tex.y > 0 && tex.y < anim->tex.h)
		{
			col = (anim->tex.pixels[tex.y * anim->tex.w + tex.x]) & 0x00FFFFFF;
			if (col != alpha)
				put_pixel(cont, stripe, pt.y, col);
		}
	}
}

void	render_sprite(t_cont *cont, t_calc *c, int i, int stripe)
{
	if (g_sprite[c->order[i].order].type == SP_ANIM)
		render_sprite_anim(cont, c, i, stripe);
	else
		render_sprite_fix(cont, c, i, stripe);
}

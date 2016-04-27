/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 15:36:21 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/27 11:27:14 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "wolf3d.h"
#include "libft.h"

t_sprite g_sprite[NSPRITE] =
{
	{ 20.5, 11.5, 11, SP_FIX },
	{ 18.5, 4.5, 11, SP_FIX },
	{ 10.0, 4.5, 11, SP_FIX },
	{ 10.0, 12.5, 11, SP_FIX },
	{ 3.5, 6.5, 11, SP_FIX },
	{ 3.5, 20.5, 11, SP_FIX },
	{ 3.5, 14.5, 11, SP_FIX },
	{ 14.5, 20.5, 11, SP_FIX },
	{ 18.5, 10.5, 10, SP_FIX },
	{ 18.5, 11.5, 10, SP_FIX },
	{ 18.5, 12.5, 10, SP_FIX },
	{ 21.5, 1.5, 9, SP_FIX },
	{ 15.5, 1.5, 9, SP_FIX },
	{ 16.0, 1.8, 9, SP_FIX },
	{ 16.2, 1.2, 9, SP_FIX },
	{ 3.5, 2.5, 9, SP_FIX },
	{ 9.5, 15.5, 9, SP_FIX },
	{ 10.0, 15.1, 9, SP_FIX },
	{ 10.5, 15.8, 9, SP_FIX },
	{ 20.5, 11.5, 2, SP_ANIM },
	{ 18.5, 4.5, 3, SP_ANIM },
	{ 10.0, 4.5, 0, SP_ANIM },
	{ 10.0, 12.5, 0, SP_ANIM },
	{ 3.5, 6.5, 1, SP_ANIM },
	{ 3.5, 20.5, 1, SP_ANIM },
	{ 3.5, 14.5, 1, SP_ANIM },
	{ 14.5, 20.5, 1, SP_ANIM }
};

void	draw_sprite(t_cont *cont, t_calc *c)
{
	int			i;
	int			stripe;

	init_var_sprite(cont, c);
	ft_qsort(c->order, NSPRITE, sizeof(c->order[0]), sort_sprite);
	i = 0;
	while (i < NSPRITE)
	{
		calc_var_sprite(cont, c, i);
		calc_points_sprite(c);
		stripe = c->start.x;
		while (stripe < c->end.x)
		{
			if (c->tr.y >= 0 && stripe >= 0 && stripe < WIN_W &&
					c->tr.y < c->zbuffer[stripe])
				render_sprite(cont, c, i, stripe);
			stripe++;
		}
		i++;
	}
}

void	init_var_sprite(t_cont *cont, t_calc *c)
{
	t_point		pos;
	int			i;

	c->invdet = 1. / (cont->g.plane.x * cont->g.dir.y -
			cont->g.dir.x * cont->g.plane.y);
	pos = cont->g.pos;
	i = 0;
	while (i < NSPRITE)
	{
		c->order[i].order = i;
		c->order[i].dist =
			((pos.x - g_sprite[i].x) * (pos.x - g_sprite[i].x) +
			(pos.y - g_sprite[i].y) * (pos.y - g_sprite[i].y));
		i++;
	}
}

void	calc_var_sprite(t_cont *cont, t_calc *c, int i)
{
	c->sp.x = g_sprite[c->order[i].order].x - cont->g.pos.x;
	c->sp.y = g_sprite[c->order[i].order].y - cont->g.pos.y;
	c->tr.x = c->invdet * (cont->g.dir.y * c->sp.x - cont->g.dir.x * c->sp.y);
	c->tr.y = c->invdet * (-cont->g.plane.y * c->sp.x + cont->g.plane.x *
			c->sp.y);
	c->spscrx = (WIN_W / 2.) * (1. + c->tr.x / c->tr.y);
}

void	calc_points_sprite(t_calc *c)
{
	c->vmovescr = 0.0;
	c->sph = abs((int)(WIN_H / c->tr.y));
	c->spw = abs((int)(WIN_H / c->tr.y));
	c->start.y = -c->sph / 2 + WIN_H / 2 + c->vmovescr;
	if (c->start.y < 0)
		c->start.y = 0;
	c->end.y = c->sph / 2 + WIN_H / 2 + c->vmovescr;
	if (c->end.y >= WIN_H)
		c->end.y = WIN_H;
	c->start.x = -c->spw / 2 + c->spscrx + c->vmovescr;
	if (c->start.x < 0)
		c->start.x = 0;
	c->end.x = c->spw / 2 + c->spscrx + c->vmovescr;
	if (c->end.x >= WIN_W)
		c->end.x = WIN_W;
}

int		sort_sprite(const void *p1, const void *p2)
{
	const t_sortsp	*sp1 = p1;
	const t_sortsp	*sp2 = p2;

	if (sp1->dist < sp2->dist)
		return (1);
	else if (sp1->dist > sp2->dist)
		return (-1);
	else
		return (0);
}

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

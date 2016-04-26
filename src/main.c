/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 14:41:08 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/26 14:40:46 by nchrupal         ###   ########.fr       */
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

enum {
	SP_FIX,
	SP_ANIM
};

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			text;
	int			type;
}				t_sprite;

t_sprite sprite[NSPRITE] =
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

#define MAPW 24
#define MAPH 24

int map[MAPW][MAPH] =
{
	{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 6, 4, 4, 6, 4, 6, 4, 4, 4, 6, 4 },
	{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 8, 0, 3, 3, 0, 0, 0, 0, 0, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6 },
	{ 8, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6 },
	{ 8, 0, 3, 3, 0, 0, 0, 0, 0, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
	{ 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 4, 0, 0, 0, 0, 0, 6, 6, 6, 0, 6, 4, 6 },
	{ 8, 8, 8, 8, 0, 8, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 4, 6, 0, 0, 0, 0, 0, 6 },
	{ 7, 7, 7, 7, 0, 7, 7, 7, 7, 0, 8, 0, 8, 0, 8, 0, 8, 4, 0, 4, 0, 6, 0, 6 },
	{ 7, 7, 0, 0, 0, 0, 0, 0, 7, 8, 0, 8, 0, 8, 0, 8, 8, 6, 0, 0, 0, 0, 0, 6 },
	{ 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 6, 0, 0, 0, 0, 0, 4 },
	{ 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 6, 0, 6, 0, 6, 0, 6 },
	{ 7, 7, 0, 0, 0, 0, 0, 0, 7, 8, 0, 8, 0, 8, 0, 8, 8, 6, 4, 6, 0, 6, 6, 6 },
	{ 7, 7, 7, 7, 0, 7, 7, 7, 7, 8, 8, 4, 0, 6, 8, 4, 8, 3, 3, 3, 0, 3, 3, 3 },
	{ 2, 2, 2, 2, 0, 2, 2, 2, 2, 4, 6, 4, 0, 0, 6, 0, 6, 3, 0, 0, 0, 0, 0, 3 },
	{ 2, 2, 0, 0, 0, 0, 0, 2, 2, 4, 0, 0, 0, 0, 0, 0, 4, 3, 0, 0, 0, 0, 0, 3 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 4, 3, 0, 0, 0, 0, 0, 3 },
	{ 12, 0, 0, 0, 0, 0, 0, 0, 12, 4, 4 ,4, 4, 4, 6, 0, 6, 3, 3, 0, 0, 0, 3, 3 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 12, 2, 2, 2, 6, 6, 0, 0, 5, 0, 5, 0, 5 },
	{ 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 5, 0, 5, 0, 0, 0, 5, 5 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 5, 0, 5, 0, 5, 0, 5, 0, 5 },
	{ 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 5, 0, 5, 0, 5, 0, 5, 0, 5 },
	{ 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 2, 0, 5, 0, 5, 0, 0, 0, 5, 5 },
	{ 2, 2, 2, 2, 12, 2 ,2 ,2 ,2, 2, 2, 12, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5 }
};

void	calc_val(t_cont *cont, int w, t_calc *c)
{
	cont->g.cam.x = 2. * w / WIN_W - 1.;
	cont->g.raypos.x = cont->g.pos.x;
	cont->g.raypos.y = cont->g.pos.y;
	cont->g.raydir.x = cont->g.dir.x + cont->g.plane.x * cont->g.cam.x;
	cont->g.raydir.y = cont->g.dir.y + cont->g.plane.y * cont->g.cam.x;
	c->delta.x = sqrt(1. + (cont->g.raydir.y * cont->g.raydir.y) /
			(cont->g.raydir.x * cont->g.raydir.x));
	c->delta.y = sqrt(1. + (cont->g.raydir.x * cont->g.raydir.x) /
			(cont->g.raydir.y * cont->g.raydir.y));
	c->mapx = cont->g.raypos.x;
	c->mapy = cont->g.raypos.y;
}

void	calc_step(t_cont *cont, t_calc *c)
{
	if (cont->g.raydir.x < 0)
	{
		c->step.x = -1;
		c->side.x = (cont->g.raypos.x - c->mapx) * c->delta.x;
	}
	else
	{
		c->step.x = 1;
		c->side.x = (c->mapx + 1. - cont->g.raypos.x) * c->delta.x;
	}
	if (cont->g.raydir.y < 0)
	{
		c->step.y = -1;
		c->side.y = (cont->g.raypos.y - c->mapy) * c->delta.y;
	}
	else
	{
		c->step.y = 1;
		c->side.y = (c->mapy + 1. - cont->g.raypos.y) * c->delta.y;
	}
}

void	calc_szray(t_calc *c, int *side)
{
	while (1)
	{
		if (c->side.x < c->side.y)
		{
			c->side.x += c->delta.x;
			c->mapx += c->step.x;
			*side = 0;
		}
		else
		{
			c->side.y += c->delta.y;
			c->mapy += c->step.y;
			*side = 1;
		}
		if (map[c->mapx][c->mapy] > 0)
			break ;
	}
}

void	calc_side(int *dir, t_calc *c)
{
	if (*dir == 0)
	{
		if (c->step.x < 0)
			*dir = S_NORTH;
		else
			*dir = S_SOUTH;
	}
	else
	{
		if (c->step.y < 0)
			*dir = S_WEST;
		else
			*dir = S_EAST;
	}
}

unsigned	side_brightness(unsigned col, int side)
{
	SDL_Color	c;
	unsigned	prct;

	c.r = (col & 0xFF0000) >> 16;
	c.g = (col & 0x00FF00) >> 8;
	c.b = (col & 0x0000FF);
	if (side == S_EAST)
		prct = 85;
	else if (side == S_WEST)
		prct = 70;
	else if (side == S_NORTH)
		prct = 55;
	else
		prct = 100;
	c.r = (c.r * prct) / 100;
	c.g = (c.g * prct) / 100;
	c.b = (c.b * prct) / 100;
	return ((c.r << 16) | (c.g << 8) | c.b);
}

void	draw_wall(t_cont *cont, t_calc *c, int w, int side)
{
	SDL_Rect	tex;
	unsigned	col;
	int			y;

	tex.x = c->wallx * c->sztex;
	if ((side == S_NORTH || side == S_SOUTH) && cont->g.raydir.x > 0)
		tex.x = c->sztex - tex.x - 1;
	if ((side == S_EAST || side == S_WEST) && cont->g.raydir.y < 0)
		tex.x = c->sztex - tex.x - 1;
	y = c->p1.y;
	while (y < c->p2.y)
	{
		tex.y = (((y * 256 - WIN_H * 128 + c->lineh * 128) * c->sztex) /
				c->lineh) / 256;
		if (tex.x >= 0 && tex.x < c->sztex && tex.y >= 0 && tex.y < c->sztex)
		{
			col = cont->tex[c->ntex].pixels[tex.y * c->sztex + tex.x];
			col = side_brightness(col, side);
			put_pixel(cont, w, y, col);
		}
		y++;
	}
}

void	calc_floorwall(t_calc *c, int side)
{
	if (side == S_SOUTH)
	{
		c->flrw.x = c->mapx;
		c->flrw.y = c->mapy + c->wallx;
	}
	else if (side == S_NORTH)
	{
		c->flrw.x = c->mapx + 1;
		c->flrw.y = c->mapy + c->wallx;
	}
	else if (side == S_EAST)
	{
		c->flrw.x = c->mapx + c->wallx;
		c->flrw.y = c->mapy;
	}
	else
	{
		c->flrw.x = c->mapx + c->wallx;
		c->flrw.y = c->mapy + 1;
	}
}

void	draw_floor(t_cont *cont, t_calc *c, int w, int y)
{
	SDL_Rect	tex;
	unsigned	col;
	int			sztex;

	sztex = cont->tex[4].w;
	tex.x = (int)(c->curflr.x * sztex) % sztex;
	tex.y = (int)(c->curflr.y * sztex) % sztex;
	if (tex.x >= 0 && tex.x < sztex && tex.y >= 0 && tex.y < sztex)
	{
		col = cont->tex[4].pixels[tex.y * sztex + tex.x];
		put_pixel(cont, w, y, col);
	}
}

void	draw_ceil(t_cont *cont, t_calc *c, int w, int y)
{
	SDL_Rect	tex;
	unsigned	col;
	int			sztex;

	sztex = cont->tex[7].w;
	tex.x = (int)(c->curflr.x * sztex) % sztex;
	tex.y = (int)(c->curflr.y * sztex) % sztex;
	if (tex.x >= 0 && tex.x < sztex && tex.y >= 0 && tex.y < sztex)
	{
		col = cont->tex[7].pixels[tex.y * sztex + tex.x];
		put_pixel(cont, w, WIN_H - y - 1, col);
	}
}

void	draw_floorceil(t_cont *cont, t_calc *c, int w, int side)
{
	int			y;

	calc_floorwall(c, side);
	y = c->p2.y;
	while (y < c->p3.y)
	{
		c->weight = (WIN_H / (2. * y - WIN_H)) / c->perp;
		if (c->weight > 1.)
			c->weight = 1.;
		c->curflr.x = c->weight * c->flrw.x + (1. - c->weight) * cont->g.pos.x;
		c->curflr.y = c->weight * c->flrw.y + (1. - c->weight) * cont->g.pos.y;
		draw_floor(cont, c, w, y);
		draw_ceil(cont, c, w, y);
		y++;
	}
}

void	calc_points(t_calc *c, int w, int lineh)
{
	c->p0.x = w;
	c->p0.y = 0;
	c->p1.x = w;
	c->p1.y = -lineh / 2 + WIN_H / 2;
	if (c->p1.y < 0)
		c->p1.y = 0;
	c->p2.x = w;
	c->p2.y = lineh / 2 + WIN_H / 2;
	if (c->p2.y >= WIN_H)
		c->p2.y = WIN_H;
	c->p3.x = w;
	c->p3.y = WIN_H;
}

void	draw_verticalline(t_cont *cont, t_calc *c, int w, int side)
{
	if (side == S_NORTH || side == S_SOUTH)
		c->perp = (c->mapx - cont->g.raypos.x + (1 - c->step.x) / 2.) /
			cont->g.raydir.x;
	else
		c->perp = (c->mapy - cont->g.raypos.y + (1 - c->step.y) / 2.) /
			cont->g.raydir.y;
	if (c->perp < 0.01)
		c->perp = 0.01;
	c->lineh = WIN_H / c->perp;
	if (side == S_NORTH || side == S_SOUTH)
		c->wallx = cont->g.raypos.y + c->perp * cont->g.raydir.y;
	else
		c->wallx = cont->g.raypos.x + c->perp * cont->g.raydir.x;
	c->wallx -= floor(c->wallx);
	calc_points(c, w, c->lineh);
	draw_wall(cont, c, w, side);
	draw_floorceil(cont, c, w, side);
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
			((pos.x - sprite[i].x) * (pos.x - sprite[i].x) +
			(pos.y - sprite[i].y) * (pos.y - sprite[i].y));
		i++;
	}
}

void	calc_var_sprite(t_cont *cont, t_calc *c, int i)
{
	c->sp.x = sprite[c->order[i].order].x - cont->g.pos.x;
	c->sp.y = sprite[c->order[i].order].y - cont->g.pos.y;
	c->tr.x = c->invdet * (cont->g.dir.y * c->sp.x - cont->g.dir.x * c->sp.y);
	c->tr.y = c->invdet * (-cont->g.plane.y * c->sp.x + cont->g.plane.x *
			c->sp.y);
	c->spscrx = (WIN_W / 2.) * (1. + c->tr.x / c->tr.y);
}

// pour agrandir et bouger les sprites
#define uDiv 1
#define vDiv 1
#define vmove 0.00
void	calc_points_sprite(t_calc *c)
{
	c->vmovescr = vmove / c->tr.y;
	c->sph = abs((int)(WIN_H / c->tr.y)) / vDiv;
	c->spw = abs((int)(WIN_H / c->tr.y)) / uDiv;
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

	w = cont->tex[sprite[c->order[i].order].text].w;
	tex.x = ((256 * (stripe - (-c->spw / 2 + c->spscrx)) * w /
				c->spw)) / 256;
	y = c->start.y;
	while (y < c->end.y)
	{
		tex.y = ((((y - c->vmovescr) * 256 - WIN_H * 128 + c->sph * 128) *
					w) / c->sph) / 256;
		col = cont->tex[sprite[c->order[i].order].text].pixels[tex.y *
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
	int			y;
	int			w;
	unsigned	alpha;
	t_anim		*anim;

	anim = &cont->anim[sprite[c->order[i].order].text];
	alpha = anim->tex.pixels[0] & 0x00FFFFFF;
	w = anim->w_one_frame;
	tex.x = ((256 * (stripe - (-c->spw / 2 + c->spscrx)) * w /
				c->spw)) / 256;
	tex.x = tex.x + anim->w_one_frame * anim->frame;
	if (tex.x >= anim->w_one_frame * (anim->frame + 1))
		return ;
	y = c->start.y;
	while (y < c->end.y)
	{
		tex.y = ((((y - c->vmovescr) * 256 - WIN_H * 128 + c->sph * 128) *
					w) / c->sph) / 256;
		if (tex.y > 0 && tex.y < anim->tex.h)
		{
			col = anim->tex.pixels[tex.y * anim->tex.w + tex.x];
			col &= 0x00FFFFFF;
			if (col != alpha)
				put_pixel(cont, stripe, y, col);
		}
		y++;
	}
}

void	render_sprite(t_cont *cont, t_calc *c, int i, int stripe)
{
	if (sprite[c->order[i].order].type == SP_ANIM)
		render_sprite_anim(cont, c, i, stripe);
	else
		render_sprite_fix(cont, c, i, stripe);
}

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

void	draw_gun(t_cont *cont)
{
	SDL_Rect	win;
	unsigned	col;
	unsigned	alpha;
	int			x;
	int			y;
	t_anim		*gun;

	gun = &cont->gun[cont->actual_gun];
	alpha = gun->tex.pixels[0] & 0x00FFFFFF;
	win.x = WIN_W / 2 - gun->w_one_frame / 2;// + 350;// + 50;
	win.y = WIN_H - gun->h;
	y = 0;
	while (y < gun->h)
	{
		x = gun->frame * (gun->w / gun->n_frame);
		while (x < (gun->frame + 1) * gun->w_one_frame)
		{
			col = gun->tex.pixels[y * gun->w + x];
			col &= 0x00FFFFFF;
			if (col != alpha)
				put_pixel(cont,
						win.x + x - gun->frame * (gun->w / gun->n_frame),
						win.y + y, col);
			x++;
		}
		y++;
	}
}

void	calc(t_cont *cont)
{
	t_calc	c;
	int		w;
	int		side;

	w = 0;
	while (w < WIN_W)
	{
		calc_val(cont, w, &c);
		calc_step(cont, &c);
		calc_szray(&c, &side);
		calc_side(&side, &c);
		c.ntex = map[c.mapx][c.mapy];
		c.sztex = cont->tex[c.ntex].w;
		draw_verticalline(cont, &c, w, side);
		c.zbuffer[w] = c.perp;
		w++;
	}
	draw_sprite(cont, &c);
	draw_gun(cont);
}

void		framewait(t_cont *cont)
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
	{
		start_anim(&cont->gun[cont->actual_gun]);
	}
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

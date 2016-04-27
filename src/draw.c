/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 15:17:11 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/27 10:02:43 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "wolf3d.h"

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

void	draw_gun(t_cont *cont)
{
	SDL_Rect	win;
	unsigned	col;
	unsigned	alpha;
	SDL_Rect	pt;
	t_anim		*gun;

	gun = &cont->gun[cont->actual_gun];
	alpha = gun->tex.pixels[0] & 0x00FFFFFF;
	win.x = WIN_W / 2 - gun->w_one_frame / 2;
	win.y = WIN_H - gun->h;
	pt.y = 0;
	while (pt.y < gun->h)
	{
		pt.x = gun->frame * (gun->w / gun->n_frame);
		while (pt.x < (gun->frame + 1) * gun->w_one_frame)
		{
			col = (gun->tex.pixels[pt.y * gun->w + pt.x]) & 0x00FFFFFF;
			if (col != alpha)
				put_pixel(cont,
						win.x + pt.x - gun->frame * (gun->w / gun->n_frame),
						win.y + pt.y, col);
			pt.x++;
		}
		pt.y++;
	}
}

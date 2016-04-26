/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floorceil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 15:28:47 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/26 15:38:53 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "draw.h"

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

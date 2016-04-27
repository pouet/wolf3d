/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 15:40:21 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/27 09:07:43 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"
#include "wolf3d.h"
#include "draw.h"

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

void	calc_szray(t_cont *cont, t_calc *c, int *side)
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
		if (c->mapx < 0 || c->mapy < 0 || c->mapy >= cont->board.mapw ||
		c->mapx >= cont->board.maph || cont->board.map[c->mapx][c->mapy] > 0)
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
		calc_szray(cont, &c, &side);
		calc_side(&side, &c);
		c.ntex = cont->board.map[c.mapx][c.mapy];
		c.sztex = cont->tex[c.ntex].w;
		draw_verticalline(cont, &c, w, side);
		c.zbuffer[w] = c.perp;
		w++;
	}
	draw_sprite(cont, &c);
	draw_gun(cont);
}

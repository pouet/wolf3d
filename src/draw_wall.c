/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 15:34:55 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/27 10:03:18 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "wolf3d.h"

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

void		draw_wall(t_cont *cont, t_calc *c, int w, int side)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 14:41:08 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/24 14:48:46 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include "libft.h"
#include "mlx.h"
#include "wolf3d.h"

#include "cos_sin.h"

#define PI_3 1.047197551196598
// A recalculer pour une taille de fenetre differente
#define DIST_CAM_PROJ 277
#define WALL_SZ 64

#define MAPW 24
#define MAPH 24

int map[MAPW][MAPH]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

/*
double	find_distx(t_cont *cont, double angle)
{
	t_point	delta;
	t_point	p;

	p.y = (cont->g.pos.y / WALL_SZ) * WALL_SZ;
	if (angle < M_PI)
		p.y -= 1.;
	else
		p.y += WALL_SZ;
	p.x = cont->g.pos.x + (cont->g.pos.y - p.y) / tan(angle);
	delta.y = 64.;
	if (angle < M_PI)
		delta.y = -delta.y;
	delta.x = WALL_SZ / tan(angle);
	while (1)
	{
		if (map[(int)p.y / WALL_SZ][(int)p.x / WALL_SZ] > 0)
			break ;
		p.x += delta.x;
		p.y += delta.y;
	}
	return (fabs(cont->g.pos.x - p.x) / cos(angle));
}

double	find_disty(t_cont *cont, double angle)
{
	t_point	delta;
	t_point	p;

	p.x = (cont->g.pos.x / WALL_SZ) * WALL_SZ;
	if (angle > M_PI_2 && angle < M_PI + M_PI_2)
		p.x -= 1.;
	else
		p.x += WALL_SZ;
	p.y = cont->g.pos.y + (cont->g.pos.x - p.x) / tan(angle);
	delta.x = 64.;
	if (angle > M_PI_2 && angle < M_PI + M_PI_2)
		delta.y = -delta.y;
	delta.y = WALL_SZ * tan(angle);
	while (1)
	{
		if (map[(int)p.y / WALL_SZ][(int)p.x / WALL_SZ] > 0)
			break ;
		p.x += delta.x;
		p.y += delta.y;
	}
	return (fabs(cont->g.pos.x - p.x) / cos(angle));
}*/

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

int		calc_szline(t_cont *cont, t_calc *c, int *side)
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
	if (*side == 0)
		return (WIN_H / ((c->mapx - cont->g.raypos.x + (1 - c->step.x) / 2) /
					cont->g.raydir.x));
	else
		return (WIN_H / ((c->mapy - cont->g.raypos.y + (1 - c->step.y) / 2) /
					cont->g.raydir.y));
}

void	draw(t_cont *cont)
{
	t_point		p1;
	t_point		p2;
	unsigned	col;
	int			w;

	w = 0;
	while (w < WIN_W)
	{
		p1.x = w;
		p1.y = -cont->g.wallh[w] / 2 + WIN_H / 2;
		p2.x = w;
		p2.y = 0;
		put_line(cont, p2, p1, 0x00888888);
		p2.y = cont->g.wallh[w] / 2 + WIN_H / 2;
		if (cont->g.side[w] == S_NORTH)
			col = 0x0000ff00;
		else if (cont->g.side[w] == S_SOUTH)
			col = 0x000000ff;
		else if (cont->g.side[w] == S_WEST)
			col = 0x00ff0000;
		else
			col = 0x000aa00aa;
		put_line(cont, p1, p2, col);
		p1.y = WIN_H - 1;
		put_line(cont, p2, p1, 0x00555555);
		w++;
	}
}

void	calc_side(int *dir, t_calc *c, int side)
{
	if (side == 0)
	{
		if (c->step.x < 0)
			*dir = S_WEST;
		else
			*dir = S_EAST;
	}
	else
	{
		if (c->step.y < 0)
			*dir = S_NORTH;
		else
			*dir = S_SOUTH;
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
		cont->g.wallh[w] = calc_szline(cont, &c, &side);
		cont->g.valh[w] = map[c.mapx][c.mapy];
		calc_side(&cont->g.side[w], &c, side);
		w++;
	}
	draw(cont);
}

int		main(int ac, char **av)
{
	t_cont	cont;

	(void)ac;
	(void)av;
	ft_bzero(&cont, sizeof(cont));
	cont.g.pos.x = 22;
	cont.g.pos.y = 12;
	cont.g.dir.x = -1;
	cont.g.dir.y = 0;
	cont.g.plane.x = 0;
	cont.g.plane.y = 0.66;

	init(&cont);
	return (0);
}

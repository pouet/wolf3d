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

void	calc(t_cont *cont)
{
	int		i;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	t_point	side;
	t_point	delta;
	int		cote;
	int		szline;

	i = 0;
	while (i < WIN_W)
	{
		cont->g.cam.x = 2. * i / WIN_W - 1.;
		cont->g.raypos.x = cont->g.pos.x;
		cont->g.raypos.y = cont->g.pos.y;
		cont->g.raydir.x = cont->g.dir.x + cont->g.plane.x * cont->g.cam.x;
		cont->g.raydir.y = cont->g.dir.y + cont->g.plane.y * cont->g.cam.x;
		mapx = cont->g.raypos.x;
		mapy = cont->g.raypos.y;
		delta.x = sqrt(1. + (cont->g.raydir.y * cont->g.raydir.y) /
				(cont->g.raydir.x * cont->g.raydir.x));
		delta.x = sqrt(1. + (cont->g.raydir.x * cont->g.raydir.x) /
				(cont->g.raydir.y * cont->g.raydir.y));

		if (cont->g.raydir.x < 0)
		{
			stepx = -1;
			side.x = (cont->g.raypos.x - mapx) * delta.x;
		}
		else
		{
			stepx = 1;
			side.x = (mapx + 1. - cont->g.raypos.x) * delta.x;
		}
		if (cont->g.raydir.y < 0)
		{
			stepy = -1;
			side.y = (cont->g.raypos.y - mapy) * delta.y;
		}
		else
		{
			stepy = 1;
			side.y = (mapy + 1. - cont->g.raypos.y) * delta.y;
		}
int hit = 0;
		while (hit == 0)
		{
			if (side.x < side.y)
			{
				side.x += delta.x;
				mapx += stepx;
				cote = 0;
			}
			else
			{
				side.y += delta.y;
				mapy += stepy;
				cote = 1;
			}
			if (map[mapx][mapy] > 0)
				hit = 1;
		}
		if (cote == 0)
			szline = WIN_H / ((mapx - cont->g.raypos.x + (1 - stepx) / 2) / cont->g.raydir.x);
		else
			szline = WIN_H / ((mapy - cont->g.raypos.y + (1 - stepy) / 2) / cont->g.raydir.y);

		{
			t_point p1, p2;

			p1.x = i;
			p1.y = -szline / 2 + WIN_H / 2;
			p2.x = i;
			p2.y = szline / 2 + WIN_H / 2;
			put_line(cont, p1, p2, 0x00FF0000);
		}


		i++;
	}
}

int		main(int ac, char **av)
{
	t_cont	cont;

	(void)ac;
	(void)av;
	cont.g.pos.x = 22;
	cont.g.pos.y = 12;
	cont.g.dir.x = -1;
	cont.g.dir.y = 0;
	cont.g.plane.x = 0;
	cont.g.plane.y = 0.66;

	init(&cont);
	return (0);
}

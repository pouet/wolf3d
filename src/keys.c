/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 09:32:37 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/01 12:20:22 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include "libft.h"
#include "SDL.h"
#include "wolf3d.h"

void	turn(t_cont *cont, int key)
{
	double	olddirx;
	double	oldplanex;
	double	move;
	double	cosmove;
	double	sinmove;

	move = 0.05;
	if (key == K_RIGHT)
		move = -move;
	cosmove = cos(move);
	sinmove = sin(move);
	olddirx = cont->g.dir.x;
	oldplanex = cont->g.plane.x;
	cont->g.dir.x = cont->g.dir.x * cosmove - cont->g.dir.y * sinmove;
	cont->g.dir.y = olddirx * sinmove + cont->g.dir.y * cosmove;
	cont->g.plane.x = cont->g.plane.x * cosmove - cont->g.plane.y * sinmove;
	cont->g.plane.y = oldplanex * sinmove + cont->g.plane.y * cosmove;
}

extern int map[24][24];

void	move(t_cont *cont, int key)
{
	SDL_Rect	r;
	double		move;

	move = 0.25;
	if (key == K_UP)
	{
		r.x = cont->g.pos.x + cont->g.dir.x * move;
		r.y = cont->g.pos.y;
		if (map[r.x][r.y] == 0)
			cont->g.pos.x += cont->g.dir.x * move;
		r.x = cont->g.pos.x;
		r.y = cont->g.pos.y + cont->g.dir.y * move;
		if (map[r.x][r.y] == 0)
			cont->g.pos.y += cont->g.dir.y * move;
	}
	else if (key == K_DOWN)
	{
		r.x = cont->g.pos.x - cont->g.dir.x * move;
		r.y = cont->g.pos.y;
		if (map[r.x][r.y] == 0)
			cont->g.pos.x -= cont->g.dir.x * move;
		r.x = cont->g.pos.x;
		r.y = cont->g.pos.y - cont->g.dir.y * move;
		if (map[r.x][r.y] == 0)
			cont->g.pos.y -= cont->g.dir.y * move;
	}
}

void	move_side(t_cont *cont, int key)
{
	SDL_Rect	r;
	double		move;

	move = 0.10;
	if (key == K_SIDE_L)
	{
		r.x = cont->g.pos.x;
		r.y = cont->g.pos.y + cont->g.dir.x * move;
		if (map[r.x][r.y] == 0)
			cont->g.pos.y += cont->g.dir.x * move;
		r.x = cont->g.pos.x - cont->g.dir.y * move;
		r.y = cont->g.pos.y;
		if (map[r.x][r.y] == 0)
			cont->g.pos.x -= cont->g.dir.y * move;
	}
	else if (key == K_SIDE_R)
	{
		r.x = cont->g.pos.x;
		r.y = cont->g.pos.y - cont->g.dir.x * move;
		if (map[r.x][r.y] == 0)
			cont->g.pos.y -= cont->g.dir.x * move;
		r.x = cont->g.pos.x + cont->g.dir.y * move;
		r.y = cont->g.pos.y;
		if (map[r.x][r.y] == 0)
			cont->g.pos.x += cont->g.dir.y * move;
	}
}

void			key_arrow(int key, t_cont *cont)
{
	if (key == K_LEFT || key == K_RIGHT)
		turn(cont, key);
	else if (key == K_UP || key == K_DOWN)
		move(cont, key);
	else if (key == K_SIDE_L || key == K_SIDE_R)
		move_side(cont, key);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 09:32:37 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/24 14:05:17 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include "libft.h"
#include "mlx.h"
#include "wolf3d.h"

void	turn(t_cont *cont, int key)
{
	double	olddirx;
	double	oldplanex;
	double	move;

	move = 0.05;
	if (key == K_RIGHT)
		move = -move;
	olddirx = cont->g.dir.x;
	oldplanex = cont->g.plane.x;
	cont->g.dir.x = cont->g.dir.x * cos(move) - cont->g.dir.y * sin(move);
	cont->g.dir.y = olddirx * sin(move) + cont->g.dir.y * cos(move);
	cont->g.plane.x = cont->g.plane.x * cos(move) - cont->g.plane.y * sin(move);
	cont->g.plane.y = oldplanex * sin(move) + cont->g.plane.y * cos(move);
}

extern int map[24][24];

void	move(t_cont *cont, int key)
{
	double	move;

	move = 0.25;
	if (key == K_UP)
	{
		if (map[(int)(cont->g.pos.x + cont->g.dir.x * move)][(int)cont->g.pos.y] == 0)
			cont->g.pos.x += cont->g.dir.x * move;
		if (map[(int)cont->g.pos.x][(int)(cont->g.pos.y + cont->g.dir.y * move)] == 0)
			cont->g.pos.y += cont->g.dir.y * move;
	}
	else if (key == K_DOWN)
	{
		if (map[(int)(cont->g.pos.x - cont->g.dir.x * move)][(int)cont->g.pos.y] == 0)
			cont->g.pos.x -= cont->g.dir.x * move;
		if (map[(int)cont->g.pos.x][(int)(cont->g.pos.y - cont->g.dir.y * move)] == 0)
			cont->g.pos.y -= cont->g.dir.y * move;
	}
}

int				key_arrow(int key, t_cont *cont)
{
	if (key == K_LEFT)
		turn(cont, key);
	else if (key == K_RIGHT)
		turn(cont, key);
	else if (key == K_UP)
		move(cont, key);
	else if (key == K_DOWN)
		move(cont, key);
	if (key == K_LEFT || key == K_RIGHT || key == K_UP || key == K_DOWN)
		return (1);
	else
		return (0);
}

int				key_zoom(int key, t_cont *cont)
{
	(void)cont;
	if (key == K_ONE)
	{
		return (1);
	}
	else if (key == K_TWO)
	{
		return (1);
	}
	else if (key == K_PLUS)
	{
		return (1);
	}
	else if (key == K_MINUS)
	{
		return (1);
	}
	return (0);
}

int				key_func(int key, void *par)
{
	t_cont	*cont;
	int		draw;

	cont = par;
	draw = 0;
	if (key == K_ESCAPE)
		mlx_quit(par);
	else if (key == K_ENTER)
		;
	else if (key == K_LEFT || key == K_RIGHT || key == K_UP || key == K_DOWN)
		draw = key_arrow(key, cont);
	else if (key == K_ONE || key == K_TWO || key == K_PLUS || key == K_MINUS)
		draw = key_zoom(key, cont);
	else if (key == K_SPACE)
	{
		draw = 1;
	}
	if (draw)
	{
//		mlx_clear_window(cont->mlx, cont->win);
	}
	return (0);
}

int				mouse_func(int button, int x, int y, void *par)
{
	t_cont	*cont;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return (0);
	cont = par;
	if (button == M_SCROLL_UP)
		;
	else if (button == M_SCROLL_DO)
		;
	else if (button == M_BLEFT)
		;
	return (0);
}

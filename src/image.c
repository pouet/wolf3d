/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 09:39:11 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/24 14:01:50 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include "libft.h"
#include "mlx.h"
#include "wolf3d.h"

void			new_image(t_cont *cont)
{
	cont->img = mlx_new_image(cont->mlx, WIN_W, WIN_H);
	cont->pixels = mlx_get_data_addr(cont->img, &cont->bpp, &cont->szline,
		&cont->endian);
	cont->bpp /= 8;
}

inline int		put_pixel(t_cont *cont, int x, int y, unsigned color)
{
	char	*p;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return (0);
	p = cont->pixels + y * cont->szline + x * cont->bpp;
	if (cont->bpp == 4)
		*(unsigned*)p = color;
	else
	{
		ft_putendl("bpp not supported...");
		exit(1);
	}
	return (0);
}

int		iabs(int a)
{
	if (a < 0)
		return (-a);
	else
		return (a);
}

void	put_line(t_cont *cont, t_point p1, t_point p2, unsigned color)
{
	const int		dx = iabs(p2.x - p1.x);
	const int		dy = -iabs(p2.y - p1.y);
	int				sx;
	int				sy;
	int				err;

	sx = p1.x < p2.x ? 1 : -1;
	sy = p1.y < p2.y ? 1 : -1;
	err = dx + dy;
	while (put_pixel(cont, p1.x, p1.y, color) == 0)
	{
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		p1.z = 2 * err;
		if (p1.z >= dy)
		{
			err += dy;
			p1.x += sx;
		}
		if (p1.z <= dx)
		{
			err += dx;
			p1.y += sy;
		}
	}
}

int				mlx_quit(t_cont *cont)
{
	mlx_destroy_image(cont->mlx, cont->img);
	mlx_destroy_window(cont->mlx, cont->win);
	exit(0);
	return (0);
}

void			init(t_cont *cont)
{
	cont->mlx = mlx_init();
	cont->win = mlx_new_window(cont->mlx, WIN_W, WIN_H, TITLE);
	new_image(cont);
	calc(cont);
	mlx_put_image_to_window(cont->mlx, cont->win, cont->img, 0, 0);
	mlx_mouse_hook(cont->win, mouse_func, cont);
	mlx_key_hook(cont->win, key_func, cont);
	mlx_hook(cont->win, 17, 0, mlx_quit, cont);
//	mlx_hook(cont->win, 6, 0, cont->fct_mouse, cont);
	mlx_loop(cont->mlx);
}

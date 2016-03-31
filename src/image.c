/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 09:39:11 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/31 16:25:33 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include "SDL.h"
#include "libft.h"
#include "wolf3d.h"

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

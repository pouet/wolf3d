/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 09:39:11 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/26 12:25:40 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include "SDL.h"
#include "libft.h"
#include "wolf3d.h"

int		put_pixel(t_cont *cont, int x, int y, unsigned col)
{
	Uint32 *pix32;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return (0);
	pix32 = cont->pixels;
	pix32[y * WIN_W + x] = col;
	return (1);
}

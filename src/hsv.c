/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsv.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:53:15 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/16 15:16:36 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "hsv.h"

unsigned	hsvtorgb(double h, double s, double v)
{
	t_hsv		hsv;
	unsigned	hi;
	double		f;

	hi = h / 60;
	hi %= 6;
	f = h / 60. - hi;
	hsv.l = (v * (1. - s)) * 0xFF;
	hsv.m = (v * (1. - f * s)) * 0xFF;
	hsv.n = (v * (1. - (1. - f) * s)) * 0xFF;
	hsv.vv = v * 0xFF;
	if (hi == 0)
		return ((hsv.vv << 16) | (hsv.n << 8) | hsv.l);
	else if (hi == 1)
		return ((hsv.m << 16) | (hsv.vv << 8) | hsv.l);
	else if (hi == 2)
		return ((hsv.l << 16) | (hsv.vv << 8) | hsv.n);
	else if (hi == 3)
		return ((hsv.l << 16) | (hsv.m << 8) | hsv.vv);
	else if (hi == 4)
		return ((hsv.n << 16) | (hsv.l << 8) | hsv.vv);
	else
		return ((hsv.vv << 16) | (hsv.l << 8) | hsv.m);
}

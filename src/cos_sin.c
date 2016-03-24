/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cos_sin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 14:21:32 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/24 14:32:49 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cos_sin.h"

double 			get_cos(int n)
{
	static double	tabcos[360];
	static int		initcos;
	int				i;

	if (initcos)
		return (tabcos[n]);
	i = 0;
	while (i < 360)
	{
		tabcos[i] = cos(((2 * M_PI) / 360.) * i);
		i++;
	}
	initcos = 1;
	return (tabcos[n]);
}

double 			get_sin(int n)
{
	static double	tabsin[360];
	static int		initsin;
	int				i;

	if (initsin)
		return (tabsin[n]);
	i = 0;
	while (i < 360)
	{
		tabsin[i] = sin(((2 * M_PI) / 360.) * i);
		i++;
	}
	initsin = 1;
	return (tabsin[n]);
}

double inline	dcos(int n)
{
	if (n < 0 || n >= 360)
		n = 0;
	return (get_cos(n));
}

double inline	dsin(int n)
{
	if (n < 0 || n >= 360)
		n = 0;
	return (get_sin(n));
}

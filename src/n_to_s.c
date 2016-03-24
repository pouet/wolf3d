/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_to_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 15:17:46 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/16 15:24:16 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_to_s.h"

int		utos(char *s, unsigned n)
{
	int	len;

	len = 0;
	if (n >= 10)
		len = utos(s, n / 10);
	s[len] = "0123456789"[n % 10];
	s[len + 1] = '\0';
	return (len + 1);
}

void	dtos(char *s, double n)
{
	unsigned	e;
	unsigned	d;
	int			lene;
	int			lend;
	int			sign;

	sign = 0;
	if (n < 0.)
	{
		n = -n;
		sign = 1;
		s[0] = '-';
	}
	e = n;
	d = (n - e) * 100000;
	lene = utos(s + sign, e) + sign;
	s[lene] = '.';
	lend = utos(s + lene + 1, d);
	s[lene + 1 + lend] = '\0';
}

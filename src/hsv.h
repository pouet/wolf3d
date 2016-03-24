/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:55:39 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/16 14:57:54 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HSV_H
# define HSV_H

typedef struct	s_hsv
{
	unsigned	l;
	unsigned	vv;
	unsigned	m;
	unsigned	n;
}				t_hsv;

unsigned		hsvtorgb(double h, double s, double v);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 15:40:59 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/26 15:49:08 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
# define CALC_H

# include "wolf3d.h"

void	calc(t_cont *cont);
void	calc_side(int *dir, t_calc *c);
void	calc_szray(t_calc *c, int *side);
void	calc_step(t_cont *cont, t_calc *c);
void	calc_val(t_cont *cont, int w, t_calc *c);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 15:31:34 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/27 11:11:41 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "wolf3d.h"

enum {
	SP_FIX,
	SP_ANIM
};

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			text;
	int			type;
}				t_sprite;

void			calc_points(t_calc *c, int w, int lineh);
void			draw_verticalline(t_cont *cont, t_calc *c, int w, int side);
void			draw_sprite(t_cont *cont, t_calc *c);
void			draw_gun(t_cont *cont);
void			draw_wall(t_cont *cont, t_calc *c, int w, int side);
void			draw_floorceil(t_cont *cont, t_calc *c, int w, int side);
void			draw_ceil(t_cont *cont, t_calc *c, int w, int y);
void			draw_floor(t_cont *cont, t_calc *c, int w, int y);

void			draw_sprite(t_cont *cont, t_calc *c);
void			render_sprite(t_cont *cont, t_calc *c, int i, int stripe);
void			init_var_sprite(t_cont *cont, t_calc *c);
void			calc_var_sprite(t_cont *cont, t_calc *c, int i);
void			calc_points_sprite(t_calc *c);
int				sort_sprite(const void *p1, const void *p2);
void			render_sprite_fix(t_cont *cont, t_calc *c, int i, int stripe);
void			render_sprite_anim(t_cont *cont, t_calc *c, int i, int stripe);

#endif

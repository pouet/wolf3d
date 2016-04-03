/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 13:55:24 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/01 15:24:54 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "SDL.h"



# define TITLE "wolf3d"

enum
{
	FPS = 60,
	FPS_DFLT = 1000 / FPS,
	N_TEXTURES = 14,
	N_ANIM = 2
};

enum	e_keys
{
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_SIDE_L,
	K_SIDE_R
};

enum
{
	WIN_W = 1024,
	WIN_H = 768,
	WALL_SZ = 512
};

enum
{
	S_SOUTH,
	S_NORTH,
	S_EAST,
	S_WEST
};

typedef struct	s_point
{
	double		x;
	double		y;
	double		z;
}				t_point;

typedef struct	s_game
{
	unsigned	ticks;
	t_point		cam;
	t_point		pos;
	t_point		dir;
	t_point		plane;
	t_point		raypos;
	t_point		raydir;
	int			eye;
}				t_game;

#define NSPRITE 19
typedef struct	s_calcsprite
{
	int			order;
	double		dist;
}				t_sortsp;

typedef struct	s_calc
{
	int			ntex;
	int			sztex;
	SDL_Rect	p0;
	SDL_Rect	p1;
	SDL_Rect	p2;
	SDL_Rect	p3;
	int			mapx;
	int			mapy;
	SDL_Rect	step;
	t_point		side;
	t_point		delta;
	double		perp;
	int			lineh;
	double		wallx;
	t_point		flrw;
	t_point		curflr;
	double		weight;
	t_sortsp	order[NSPRITE];
	double		zbuffer[WIN_W];
	t_point		sp;
	t_point		tr;
	int			sph;
	int			spw;
	int			vmovescr;
	double		invdet;
	int			spscrx;
	SDL_Rect	start;
	SDL_Rect	end;
}				t_calc;

typedef struct	s_texture
{
	SDL_Texture		*tex;
	Uint32			*pixels;
	int				pitch;
	int				w;
	int				h;
}				t_texture;

/*
** r.w, r.h => width, height of the texture
** w_one_frame => width one frame
** n_frame => number of frame in animation
** replay =>	-1: infinite
**				0: print 1rst frame
**				>0: replay n time
** time => time between each frame (multiple of FPS_DFLT)
** ticks => actual time since start
** frame => current frame
** started => ... need help ?
*/

typedef struct	s_anim
{
	t_texture	tex;
	int			w;
	int			h;
	int			w_one_frame;
	int			n_frame;
	int			replay;
	int			time;
	int			ticks;
	int			frame;
	int			started;
}				t_anim;

typedef struct	s_cont
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	t_texture		tex[N_TEXTURES];
	t_anim			gun[N_ANIM];
	int				actual_gun;
	t_texture		img;
	Uint32			*pixels;
	const Uint8		*state;
	SDL_Rect		mouse;
	Uint32			mouseb;
	int				full;
	int				frame;
	int				ticks;
	t_game		g;
}				t_cont;

void			key_arrow(int key, t_cont *cont);


int				put_pixel(t_cont *cont, int x, int y, unsigned col);
void			put_line(t_cont *cont, t_point p1, t_point p2, unsigned color);

void	calc(t_cont *cont);
void	turn(t_cont *cont, int key, double move);


#endif

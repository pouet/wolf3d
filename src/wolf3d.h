/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 13:55:24 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/30 15:37:38 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"

# define TITLE "wolf3d"

# define FPS 20

enum	e_keys
{
	K_ESCAPE = 53,
	K_ENTER = 36,
	K_SPACE = 49,
	K_UP = 126,
	K_DOWN = 125,
	K_LEFT = 123,
	K_RIGHT = 124,
	K_MINUS = 27,
	K_PLUS = 24,
	K_ONE = 18,
	K_TWO = 19
};

enum	e_mouse
{
	M_BLEFT = 1,
	M_BRIGHT = 2,
	M_SCROLL_UP = 4,
	M_SCROLL_DO = 5
};

enum
{
	WIN_W = 1024,
	WIN_H = 768
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
//#pragma pack(1)
typedef struct	s_game
{
	unsigned	ticks;
	t_point		cam;
	t_point		pos;
	t_point		dir;
	t_point		plane;
	t_point		raypos;
	t_point		raydir;
	double		eye;
}				t_game;

typedef struct	s_calc
{
	int		mapx;
	int		mapy;
	t_point	step;
	t_point	side;
	t_point	delta;
	double	perp;
	int		lineh;
	double	wallx;
}				t_calc;

typedef struct	s_cont
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*pixels;
	int			w;
	int			h;
	int			bpp;
	int			szline;
	int			endian;
	int			key[0xFF];
	t_game		g;
}				t_cont;

void			new_image(t_cont *cont);
int				put_pixel(t_cont *cont, int x, int y, unsigned color);
int				mlx_quit(t_cont *cont);
int				key_arrow(int key, t_cont *cont);
int				key_zoom(int key, t_cont *cont);
int				key_func(int key, void *par);
int				mouse_func(int button, int x, int y, void *par);
void			init(t_cont *cont);


void			put_line(t_cont *cont, t_point p1, t_point p2, unsigned color);
void	calc(t_cont *cont);

#endif
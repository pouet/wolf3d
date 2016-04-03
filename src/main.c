/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 14:41:08 by nchrupal          #+#    #+#             */
/*   Updated: 2016/04/01 16:07:10 by nchrupal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include "SDL.h"
#include "libft.h"
#include "wolf3d.h"
#include "SDL.h"


typedef struct	s_sprite
{
	double		x;
	double		y;
	int			text;
}				t_sprite;


t_sprite sprite[NSPRITE] =
{
	{20.5, 11.5, 11}, //green light in front of playerstart
	//green lights in every room
	{18.5,4.5, 11},
	{10.0,4.5, 11},
	{10.0,12.5,11},
	{3.5, 6.5, 11},
	{3.5, 20.5,11},
	{3.5, 14.5,11},
	{14.5,20.5,11},

	//row of pillars in front of wall: fisheye test
	{18.5, 10.5, 10},
	{18.5, 11.5, 10},
	{18.5, 12.5, 10},

	//some barrels around the map
	{21.5, 1.5, 9},
	{15.5, 1.5, 9},
	{16.0, 1.8, 9},
	{16.2, 1.2, 9},
	{3.5,  2.5, 9},
	{9.5, 15.5, 9},
	{10.0, 15.1,9},
	{10.5, 15.8,9},
};

#define MAPW 24
#define MAPH 24

int map[MAPW][MAPH]=
{
	{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 6, 4, 4, 6, 4, 6, 4, 4, 4, 6, 4},
	{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	{8, 0, 3, 3, 0, 0, 0, 0, 0, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
	{8, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
	{8, 0, 3, 3, 0, 0, 0, 0, 0, 8, 8, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
	{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 4, 0, 0, 0, 0, 0, 6, 6, 6, 0, 6, 4, 6},
	{8, 8, 8, 8, 0, 8, 8, 8, 8, 8, 8, 4, 4, 4, 4, 4, 4, 6, 0, 0, 0, 0, 0, 6},
	{7, 7, 7, 7, 0, 7, 7, 7, 7, 0, 8, 0, 8, 0, 8, 0, 8, 4, 0, 4, 0, 6, 0, 6},
	{7, 7, 0, 0, 0, 0, 0, 0, 7, 8, 0, 8, 0, 8, 0, 8, 8, 6, 0, 0, 0, 0, 0, 6},
	{7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 6, 0, 0, 0, 0, 0, 4},
	{7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 6, 0, 6, 0, 6, 0, 6},
	{7, 7, 0, 0, 0, 0, 0, 0, 7, 8, 0, 8, 0, 8, 0, 8, 8, 6, 4, 6, 0, 6, 6, 6},
	{7, 7, 7, 7, 0, 7, 7, 7, 7, 8, 8, 4, 0, 6, 8, 4, 8, 3, 3, 3, 0, 3, 3, 3},
	{2, 2, 2, 2, 0, 2, 2, 2, 2, 4, 6, 4, 0, 0, 6, 0, 6, 3, 0, 0, 0, 0, 0, 3},
	{2, 2, 0, 0, 0, 0, 0, 2, 2, 4, 0, 0, 0, 0, 0, 0, 4, 3, 0, 0, 0, 0, 0, 3},
	{2, 0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 4, 3, 0, 0, 0, 0, 0, 3},
	{12,0, 0, 0, 0, 0, 0, 0, 12,4, 4 ,4, 4, 4, 6, 0, 6, 3, 3, 0, 0, 0, 3, 3},
	{2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2 ,12,2, 2, 2, 6, 6, 0, 0, 5, 0, 5, 0, 5},
	{2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0 ,0, 0, 2, 2, 0, 5, 0, 5, 0, 0, 0, 5, 5},
	{2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0 ,0, 0, 0, 2, 5, 0, 5, 0, 5, 0, 5, 0, 5},
	{12,0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
	{2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0 ,0, 0, 0, 2, 5, 0, 5, 0, 5, 0, 5, 0, 5},
	{2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 0 ,0, 0, 2, 2, 0, 5, 0, 5, 0, 0, 0, 5, 5},
	{2, 2, 2, 2, 12,2 ,2 ,2 ,2, 2, 2 ,12,2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5}
};

void	calc_val(t_cont *cont, int w, t_calc *c)
{
	cont->g.cam.x = 2. * w / WIN_W - 1.;
	cont->g.raypos.x = cont->g.pos.x;
	cont->g.raypos.y = cont->g.pos.y;
	cont->g.raydir.x = cont->g.dir.x + cont->g.plane.x * cont->g.cam.x;
	cont->g.raydir.y = cont->g.dir.y + cont->g.plane.y * cont->g.cam.x;
	c->delta.x = sqrt(1. + (cont->g.raydir.y * cont->g.raydir.y) /
			(cont->g.raydir.x * cont->g.raydir.x));
	c->delta.y = sqrt(1. + (cont->g.raydir.x * cont->g.raydir.x) /
			(cont->g.raydir.y * cont->g.raydir.y));
	c->mapx = cont->g.raypos.x;
	c->mapy = cont->g.raypos.y;
}

void	calc_step(t_cont *cont, t_calc *c)
{
	if (cont->g.raydir.x < 0)
	{
		c->step.x = -1;
		c->side.x = (cont->g.raypos.x - c->mapx) * c->delta.x;
	}
	else
	{
		c->step.x = 1;
		c->side.x = (c->mapx + 1. - cont->g.raypos.x) * c->delta.x;
	}
	if (cont->g.raydir.y < 0)
	{
		c->step.y = -1;
		c->side.y = (cont->g.raypos.y - c->mapy) * c->delta.y;
	}
	else
	{
		c->step.y = 1;
		c->side.y = (c->mapy + 1. - cont->g.raypos.y) * c->delta.y;
	}
}

void	calc_szray(t_calc *c, int *side)
{
	while (1)
	{
		if (c->side.x < c->side.y)
		{
			c->side.x += c->delta.x;
			c->mapx += c->step.x;
			*side = 0;
		}
		else
		{
			c->side.y += c->delta.y;
			c->mapy += c->step.y;
			*side = 1;
		}
		if (map[c->mapx][c->mapy] > 0)
			break ;
	}
}

void	calc_side(int *dir, t_calc *c)
{
	if (*dir == 0)
	{
		if (c->step.x < 0)
			*dir = S_NORTH;
		else
			*dir = S_SOUTH;
	}
	else
	{
		if (c->step.y < 0)
			*dir = S_WEST;
		else
			*dir = S_EAST;
	}
}

void	draw_wall(t_cont *cont, t_calc *c, int w, int side)
{
	SDL_Rect	tex;
	unsigned	col;
	int			y;

	tex.x = c->wallx * c->sztex;
	if ((side == S_NORTH || side == S_SOUTH) && cont->g.raydir.x > 0)
		tex.x = c->sztex - tex.x - 1;
	if ((side == S_EAST || side == S_WEST) && cont->g.raydir.y < 0)
		tex.x = c->sztex - tex.x - 1;
	y = c->p1.y;
	while (y < c->p2.y)
	{
		tex.y = (((y * 256 - WIN_H * 128 + c->lineh * 128) * c->sztex) /
				c->lineh) / 256;
		if (tex.x >= 0 && tex.x < c->sztex && tex.y >= 0 && tex.y < c->sztex)
		{
			col = cont->tex[c->ntex].pixels[tex.y * c->sztex + tex.x];
			put_pixel(cont, w, y, col);
		}
		y++;
	}
}

void	calc_floorwall(t_calc *c, int side)
{
	if (side == S_SOUTH)
	{
		c->flrw.x = c->mapx;
		c->flrw.y = c->mapy + c->wallx;
	}
	else if (side == S_NORTH)
	{
		c->flrw.x = c->mapx + 1;
		c->flrw.y = c->mapy + c->wallx;
	}
	else if (side == S_EAST)
	{
		c->flrw.x = c->mapx + c->wallx;
		c->flrw.y = c->mapy;
	}
	else
	{
		c->flrw.x = c->mapx + c->wallx;
		c->flrw.y = c->mapy + 1;
	}
}

void	draw_floor(t_cont *cont, t_calc *c, int w, int y)
{
	SDL_Rect	tex;
	unsigned	col;
	int			sztex;

	sztex = cont->tex[4].w;
	tex.x = (int)(c->curflr.x * sztex) % sztex;
	tex.y = (int)(c->curflr.y * sztex) % sztex;
	if (tex.x >= 0 && tex.x < sztex && tex.y >= 0 && tex.y < sztex)
	{
		col = cont->tex[4].pixels[tex.y * sztex + tex.x];
		put_pixel(cont, w, y, col);
	}
}

void	draw_ceil(t_cont *cont, t_calc *c, int w, int y)
{
	SDL_Rect	tex;
	unsigned	col;
	int			sztex;

	sztex = cont->tex[7].w;
	tex.x = (int)(c->curflr.x * sztex) % sztex;
	tex.y = (int)(c->curflr.y * sztex) % sztex;
	if (tex.x >= 0 && tex.x < sztex && tex.y >= 0 && tex.y < sztex)
	{
		col = cont->tex[7].pixels[tex.y * sztex + tex.x];
		put_pixel(cont, w, WIN_H - y - 1, col);
	}
}

void	draw_floorceil(t_cont *cont, t_calc *c, int w, int side)
{
	int			y;

	calc_floorwall(c, side);
	y = c->p2.y;
	while (y < c->p3.y)
	{
		c->weight = (WIN_H / (2. * y - WIN_H)) / c->perp;
		if (c->weight > 1.)
			c->weight = 1.;
		c->curflr.x = c->weight * c->flrw.x + (1. - c->weight) * cont->g.pos.x;
		c->curflr.y = c->weight * c->flrw.y + (1. - c->weight) * cont->g.pos.y;
		draw_floor(cont, c, w, y);
		draw_ceil(cont, c, w, y);
		y++;
	}
}

void	calc_points(t_calc *c, int w, int lineh)
{
	c->p0.x = w;
	c->p0.y = 0;
	c->p1.x = w;
	c->p1.y = -lineh / 2 + WIN_H / 2;
	if (c->p1.y < 0)
		c->p1.y = 0;
	c->p2.x = w;
	c->p2.y = lineh / 2 + WIN_H / 2;
	if (c->p2.y >= WIN_H)
		c->p2.y = WIN_H;
	c->p3.x = w;
	c->p3.y = WIN_H;
}

void	draw_verticalline(t_cont *cont, t_calc *c, int w, int side)
{
	if (side == S_NORTH || side == S_SOUTH)
		c->perp = (c->mapx - cont->g.raypos.x + (1 - c->step.x) / 2.) /
			cont->g.raydir.x;
	else
		c->perp = (c->mapy - cont->g.raypos.y + (1 - c->step.y) / 2.) /
			cont->g.raydir.y;
	if (c->perp < 0.01)
		c->perp = 0.01;
	c->lineh = WIN_H / c->perp;
	if (side == S_NORTH || side == S_SOUTH)
		c->wallx = cont->g.raypos.y + c->perp * cont->g.raydir.y;
	else
		c->wallx = cont->g.raypos.x + c->perp * cont->g.raydir.x;
	c->wallx -= floor(c->wallx);
	calc_points(c, w, c->lineh);
	draw_wall(cont, c, w, side);
	draw_floorceil(cont, c, w, side);
}

void	init_var_sprite(t_cont *cont, t_calc *c)
{
	t_point		pos;
	int			i;

	c->invdet = 1. / (cont->g.plane.x * cont->g.dir.y -
			cont->g.dir.x * cont->g.plane.y);
	pos = cont->g.pos;
	i = 0;
	while (i < NSPRITE)
	{
		c->order[i].order = i;
		c->order[i].dist =
			((pos.x - sprite[i].x) * (pos.x - sprite[i].x) +
			 (pos.y - sprite[i].y) * (pos.y - sprite[i].y));
		i++;
	}
}

void	calc_var_sprite(t_cont *cont, t_calc *c, int i)
{
	c->sp.x = sprite[c->order[i].order].x - cont->g.pos.x;
	c->sp.y = sprite[c->order[i].order].y - cont->g.pos.y;
	c->tr.x = c->invdet * (cont->g.dir.y * c->sp.x - cont->g.dir.x * c->sp.y);
	c->tr.y = c->invdet * (-cont->g.plane.y * c->sp.x + cont->g.plane.x *
			c->sp.y);
	c->spscrx = (WIN_W / 2.) * (1. + c->tr.x / c->tr.y);
}

// pour agrandir et bouger les sprites
#define uDiv 1
#define vDiv 1
#define vmove 0.00
void	calc_points_sprite(t_calc *c)
{
	c->vmovescr = vmove / c->tr.y;
	c->sph = abs((int)(WIN_H / c->tr.y)) / vDiv;
	c->spw = abs((int)(WIN_H / c->tr.y)) / uDiv;
	c->start.y = -c->sph / 2 + WIN_H / 2 + c->vmovescr;
	if (c->start.y < 0)
		c->start.y = 0;
	c->end.y = c->sph / 2 + WIN_H / 2 + c->vmovescr;
	if (c->end.y >= WIN_H)
		c->end.y = WIN_H;

	c->start.x = -c->spw / 2 + c->spscrx + c->vmovescr;
	if (c->start.x < 0)
		c->start.x = 0;
	c->end.x = c->spw / 2 + c->spscrx + c->vmovescr;
	if (c->end.x >= WIN_W)
		c->end.x = WIN_W;
}

int		sort_sprite(const void *p1, const void *p2)
{
	const t_sortsp	*sp1 = p1;
	const t_sortsp	*sp2 = p2;

	if (sp1->dist < sp2->dist)
		return (1);
	else if (sp1->dist > sp2->dist)
		return (-1);
	else
		return (0);
}

void	render_sprite(t_cont *cont, t_calc *c, int i, int stripe)
{
	SDL_Rect	tex;
	unsigned	col;
	int			y;
	int			w;

	w = cont->tex[sprite[c->order[i].order].text].w;
	tex.x = ((256 * (stripe - (-c->spw / 2 + c->spscrx)) * w /
				c->spw)) / 256;
	y = c->start.y;
	while (y < c->end.y)
	{
		tex.y = ((((y - c->vmovescr) * 256 - WIN_H * 128 + c->sph * 128) *
					w) / c->sph) / 256;
		col = cont->tex[sprite[c->order[i].order].text].pixels[tex.y *
			w + tex.x];
		col &= 0x00FFFFFF;
		if (col != 0)
			put_pixel(cont, stripe, y, col);
		y++;
	}
}

void	draw_sprite(t_cont *cont, t_calc *c)
{
	int			i;
	int			stripe;

	init_var_sprite(cont, c);
	ft_qsort(c->order, NSPRITE, sizeof(c->order[0]), sort_sprite);
	i = 0;
	while (i < NSPRITE)
	{
		calc_var_sprite(cont, c, i);
		calc_points_sprite(c);
		stripe = c->start.x;
		while (stripe < c->end.x)
		{
			if (c->tr.y >= 0 && stripe >= 0 && stripe < WIN_W &&
					c->tr.y < c->zbuffer[stripe])
				render_sprite(cont, c, i, stripe);
			stripe++;
		}
		i++;
	}
}

void	draw_gun(t_cont *cont)
{
	SDL_Rect	win;
	unsigned	col;
	unsigned	col_transparent;
	int			x;
	int			y;

	col_transparent = cont->tex[0].pixels[0] & 0x00FFFFFF;
	win.x = WIN_W / 2 - cont->tex[0].w / 2 + 350;// + 50;
	win.y = WIN_H - cont->tex[0].h;
	y = 0;
	while (y < cont->tex[0].h)
	{
//		cont->frame = 3;
		x = cont->frame * 156;
		while (x < (cont->frame + 1) * 156)//cont->tex[0].w / 4)
		{
			col = cont->tex[0].pixels[y * cont->tex[0].w + x];
			col &= 0x00FFFFFF;
			if (col != col_transparent)
				put_pixel(cont, win.x + x - cont->frame * 156, win.y + y, col);
			x++;
		}
		y++;
	}
}

void	calc(t_cont *cont)
{
	t_calc	c;
	int		w;
	int		side;

	w = 0;
	while (w < WIN_W)
	{
		calc_val(cont, w, &c);
		calc_step(cont, &c);
		calc_szray(&c, &side);
		calc_side(&side, &c);
		c.ntex = map[c.mapx][c.mapy];
		c.sztex = cont->tex[c.ntex].w;
		draw_verticalline(cont, &c, w, side);
		c.zbuffer[w] = c.perp;
		w++;
	}
	draw_sprite(cont, &c);
	draw_gun(cont);
}

void	exit_sdlerror(void)
{
	ft_putendl_fd(SDL_GetError(), 2);
	exit(EXIT_FAILURE);
}

int		init_video(t_cont *cont)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		exit_sdlerror();
	cont->win = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0);
	if (cont->win == NULL)
		exit_sdlerror();
	cont->ren = SDL_CreateRenderer(cont->win, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
	if (cont->ren == NULL)
		exit_sdlerror();
	return (0);
}

void		copy_surface_to_texture(SDL_Texture *tex, SDL_Surface *bmp)
{
	SDL_Rect	r;
	void		*pixels;
	int			pitch;

	SDL_LockTexture(tex, NULL, &pixels, &pitch);
	r.y = 0;
	while (r.y < bmp->h)
	{
		r.x = 0;
		while (r.x < bmp->w)
		{
			*(Uint32 *)((char *)pixels + (r.y * pitch + r.x * 4)) =
				*(Uint32 *)((char *)bmp->pixels +
						(r.y * bmp->pitch + r.x * bmp->format->BytesPerPixel));
			r.x++;
		}
		r.y++;
	}
	SDL_UnlockTexture(tex);
}

SDL_Texture	*load_bmp(t_cont *cont, char *name)
{
//	SDL_Surface	*bmp;
	SDL_Texture	*tex;

	bmp = SDL_LoadBMP(name);
	if (bmp == NULL)
		exit_sdlerror();
	return (bmp);
	/*
	tex = SDL_CreateTexture(cont->ren, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, bmp->w, bmp->h);
	if (tex == NULL)
		exit_sdlerror();
	copy_surface_to_texture(tex, bmp);
	SDL_FreeSurface(bmp);
	return (tex);*/
}

void	quit_video(t_cont *cont)
{
	SDL_DestroyRenderer(cont->ren);
	SDL_DestroyWindow(cont->win);
	SDL_Quit();
}

void	render_texture(t_cont *cont, SDL_Texture *tex, int x, int y)
{
	SDL_Rect dst;

	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
//	SDL_RenderCopy(cont->ren, tex, NULL, &dst);
	SDL_RenderCopy(cont->ren, tex, NULL, NULL);
}

void	load_textures(t_cont *cont)
{
	static char	*name[N_TEXTURES] = {
		"img/gun_gif.bmp",
		"img/eagle.bmp",
//		"img/pinkiepie.bmp",
		"img/redbrick.bmp",
//		"img/rbdashgun.bmp",
		"img/purplestone.bmp",
//		"img/herb.bmp",
		"img/greystone.bmp",
		"img/bluestone.bmp",
		"img/mossy.bmp",
//		"img/sky.bmp",
		"img/wood.bmp",
		"img/colorstone.bmp",
		"img/barrel.bmp",
		"img/pillar.bmp",
		"img/greenlight.bmp",
		"img/eagle.bmp",
//		"img/rainbowdash512.bmp",
		"img/skybox.bmp"
	};
	int		i;

	i = 0;
	while (i < N_TEXTURES)
	{
//		cont->tex[i] = load_bmp(cont, name[i]);
//		if (i % 2)
//		cont->tex[i] = load_bmp(cont, "img/rainbowdash512.bmp");
//		else
//		cont->tex[i] = load_bmp(cont, "img/pinkiepie.bmp");


		cont->tex[i].tex = load_bmp(cont, name[i]);
//		cont->tex[i].tex = load_bmp(cont, "img/pinkiepie.bmp");
		SDL_QueryTexture(cont->tex[i].tex, NULL, NULL,
				&cont->tex[i].w, &cont->tex[i].h);
//		if (cont->tex[i].w != cont->tex[i].h)
//		{
//			ft_putendl_fd("image must have same heigth and width !", 2);
//			exit(EXIT_FAILURE);
//		}
		

// TODO: checker la taille de l'image : SDL_Query et comparer avec WALL_SZ
		i++;
	}
}

void	init_var(t_cont *cont)
{
	cont->g.pos.x = 22;
	cont->g.pos.y = 12;
	cont->g.dir.x = -1;
	cont->g.dir.y = 0;
	cont->g.plane.x = 0;
	cont->g.plane.y = 0.66;
	cont->g.eye = 0;
	cont->g.ticks = SDL_GetTicks();
	cont->state = SDL_GetKeyboardState(NULL);
	cont->img.tex = SDL_CreateTexture(cont->ren, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	SDL_QueryTexture(cont->img.tex, NULL, NULL, &cont->img.w, &cont->img.h);
	load_textures(cont);
}

void		framewait(t_cont *cont)
{
	unsigned	now;

	while (1)
	{
		now = SDL_GetTicks() - cont->g.ticks;
		if (now >= FPS_DFLT)
			break ;
		SDL_Delay(3);
	}
	cont->g.ticks = SDL_GetTicks();
}

int		update_events(void)
{
	SDL_Event ev;

	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT)
			return (1);
	}
	return (0);
}

void	lock_textures(t_cont *cont)
{
	int		i;

	if (SDL_LockTexture(cont->img.tex, NULL, (void **)&cont->img.pixels,
				&cont->img.pitch) < 0)
		exit_sdlerror();
	i = 0;
	while (i < N_TEXTURES)
	{
		if (SDL_LockTexture(cont->tex[i].tex, NULL,
					(void **)&cont->tex[i].pixels, &cont->tex[i].pitch) < 0)
			exit_sdlerror();
		i++;
	}
}

void	unlock_textures(t_cont *cont)
{
	int		i;

	i = 0;
	while (i < N_TEXTURES)
	{
		SDL_UnlockTexture(cont->tex[i].tex);
		i++;
	}
	SDL_UnlockTexture(cont->img.tex);
}

void	do_all(t_cont *cont)
{
	if (cont->state[SDL_SCANCODE_UP] || cont->state[SDL_SCANCODE_W])
		key_arrow(K_UP, cont);
	if (cont->state[SDL_SCANCODE_DOWN] || cont->state[SDL_SCANCODE_S])
		key_arrow(K_DOWN, cont);
	if (cont->state[SDL_SCANCODE_LEFT] || cont->state[SDL_SCANCODE_A])
		key_arrow(K_LEFT, cont);
	if (cont->state[SDL_SCANCODE_RIGHT] || cont->state[SDL_SCANCODE_D])
		key_arrow(K_RIGHT, cont);
	if (cont->state[SDL_SCANCODE_Q])
		key_arrow(K_SIDE_L, cont);
	if (cont->state[SDL_SCANCODE_E])
		key_arrow(K_SIDE_R, cont);
	if (cont->state[SDL_SCANCODE_SPACE] && cont->frame == 1)
	{
		cont->frame = 2;
		cont->ticks = 0;
	}
}

int		main_loop(t_cont *cont)
{
cont->pixels = malloc(WIN_H * WIN_W * sizeof(Uint32));
cont->frame = 1;
	while (1)
	{
		SDL_RenderClear(cont->ren);
		if (update_events() || cont->state[SDL_SCANCODE_ESCAPE])
			break ;
		if (cont->frame > 3)
			cont->frame = 1;
		else if (cont->frame > 1 && cont->ticks >= 1)
		{
			cont->frame++;
			cont->ticks = 0;
		}
		do_all(cont);
		lock_textures(cont);
/*{
	for (int h = 0; h < WIN_H; h++)
	{
		for (int w = 0; w < WIN_W; w++)
		{
			cont->img.pixels[h * WIN_W + w] = 0;
		}
	}
}*/
		calc(cont);
		unlock_textures(cont);
SDL_UpdateTexture(cont->img.tex, NULL, cont->pixels, cont->img.pitch);
SDL_RenderCopy(cont->ren, cont->img.tex, NULL, NULL);
		// Plaque la texture sur la fenetre
//		render_texture(cont, cont->img.tex, 0, 0);
//		SDL_RenderCopy(cont->ren, cont->img.tex, NULL, NULL);
		// Equivalent de SDL_Flip
		SDL_RenderPresent(cont->ren);
		cont->ticks++;
		framewait(cont);
	}
	return (0);
}

int		main(void)
{
	t_cont	cont;

	ft_bzero(&cont, sizeof(cont));
	if (init_video(&cont) < 0)
		return (EXIT_FAILURE);
	init_var(&cont);
	main_loop(&cont);
	quit_video(&cont);
	return (0);
}

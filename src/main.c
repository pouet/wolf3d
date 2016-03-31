/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchrupal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 14:41:08 by nchrupal          #+#    #+#             */
/*   Updated: 2016/03/31 16:41:21 by nchrupal         ###   ########.fr       */
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
	{20.5, 11.5, 10}, //green light in front of playerstart
	//green lights in every room
	{18.5,4.5, 10},
	{10.0,4.5, 10},
	{10.0,12.5,10},
	{3.5, 6.5, 10},
	{3.5, 20.5,10},
	{3.5, 14.5,10},
	{14.5,20.5,10},

	//row of pillars in front of wall: fisheye test
	{18.5, 10.5, 9},
	{18.5, 11.5, 9},
	{18.5, 12.5, 9},

	//some barrels around the map
	{21.5, 1.5, 8},
	{15.5, 1.5, 8},
	{16.0, 1.8, 8},
	{16.2, 1.2, 8},
	{3.5,  2.5, 8},
	{9.5, 15.5, 8},
	{10.0, 15.1,8},
	{10.5, 15.8,8},
};

//unsigned buffer[WIN_H][WIN_W];
//double zbuffer[WIN_W];
//int sprite_order[NSPRITE];
//double sprite_dist[NSPRITE];

#define MAPW 24
#define MAPH 24


int map[MAPW][MAPH]=
{
	{8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
	{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
	{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
	{8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
	{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
	{8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
	{7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
	{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
	{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
	{7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
	{2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
	{2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
	{2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
	{12,0,0,0,0,0,0,0,12,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
	{2,0,0,0,0,0,0,0,2,2,2,12,2,2,2,6,6,0,0,5,0,5,0,5},
	{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
	{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
	{12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
	{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
	{2,2,2,2,12,2,2,2,2,2,2,12,2,2,2,5,5,5,5,5,5,5,5,5}
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

	tex.x = c->wallx * WALL_SZ;
	if ((side == S_NORTH || side == S_SOUTH) && cont->g.raydir.x > 0)
		tex.x = WALL_SZ - tex.x - 1;
	if ((side == S_EAST || side == S_WEST) && cont->g.raydir.y < 0)
		tex.x = WALL_SZ - tex.x - 1;
	y = c->p1.y;
	while (y < c->p2.y)
	{
		tex.y = (((y * 256 - WIN_H * 128 + c->lineh * 128) * WALL_SZ) /
				c->lineh) / 256;
		if (tex.x >= 0 && tex.x < WALL_SZ && tex.y >= 0 && tex.y < WALL_SZ)
		{
			col = cont->pix_tex[map[c->mapx][c->mapy] - 1][tex.y * WALL_SZ + tex.x];
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

void	draw_floorceil(t_cont *cont, t_calc *c, int w, int side)
{
	SDL_Rect	tex;
	unsigned	col;
	t_point		curfloor;
	int			y;

	calc_floorwall(c, side);
	y = c->p2.y;
	while (y < c->p3.y)
	{
		c->weight = (WIN_H / (2. * y - WIN_H)) / c->perp;
		if (c->weight > 1.)
			c->weight = 1.;
		curfloor.x = c->weight * c->flrw.x + (1. - c->weight) * cont->g.pos.x;
		curfloor.y = c->weight * c->flrw.y + (1. - c->weight) * cont->g.pos.y;
		tex.x = (int)(curfloor.x * WALL_SZ) % WALL_SZ;
		tex.y = (int)(curfloor.y * WALL_SZ) % WALL_SZ;
		if (tex.x >= 0 && tex.x < WALL_SZ && tex.y >= 0 && tex.y < WALL_SZ)
		{
			col = cont->pix_tex[3][tex.y * WALL_SZ + tex.x];
			put_pixel(cont, w, y, col);
			col = cont->pix_tex[6][tex.y * WALL_SZ + tex.x];
			put_pixel(cont, w, WIN_H - y, col);
		}
		y++;
	}
}

void	calc_points(t_calc *c, int w, int lineh)
{
	c->p0.x = w;
	c->p1.x = w;
	c->p2.y = 0;
	c->p3.x = w;
	c->p0.y = 0;
	c->p1.y = -lineh / 2 + WIN_H / 2;
	if (c->p1.y < 0)
		c->p1.y = 0;
	c->p2.y = lineh / 2 + WIN_H / 2;
	if (c->p2.y >= WIN_H)
		c->p2.y = WIN_H - 1;
	c->p3.y = WIN_H - 1;
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

void	init_var_sprite(t_cont *cont, t_calcsprite *c)
{
	t_point		pos;
	int			i;

	pos = cont->g.pos;
	i = 0;
	while (i < NSPRITE)
	{
		c->sprite_order[i] = i;
		c->sprite_dist[i] =
			((pos.x - sprite[i].x) * (pos.x - sprite[i].x) +
			 (pos.y - sprite[i].y) * (pos.y - sprite[i].y));
		i++;
	}
}

void	draw_sprite(t_cont *cont, t_calc *c)
{
	unsigned	col;
//	t_point		transform;
	t_point		sp;
	t_point		tr;
	int			i;
	int			y;
	double		invdet;
	t_point start, end;

	int			spscrx;
//	SDL_Rect	sp;
	int			sph;
	int			spw;

	int			stripe;
	SDL_Rect	tex;

	invdet = 1. / (cont->g.plane.x * cont->g.dir.y -
			cont->g.dir.x * cont->g.plane.y);

	init_var_sprite(cont, &c->sprite);
// tri des sprites
	i = 0;
	while (i < NSPRITE)
	{
		sp.x = sprite[c->sprite.sprite_order[i]].x - cont->g.pos.x;
		sp.y = sprite[c->sprite.sprite_order[i]].y - cont->g.pos.y;
		tr.x = invdet * (cont->g.dir.y * sp.x - cont->g.dir.x * sp.y);
		tr.y = invdet * (-cont->g.plane.y * sp.x - cont->g.plane.x * sp.y);
		spscrx = (WIN_W / 2.) * (1. + tr.x / tr.y);
		sph = abs((int)(WIN_H / tr.y));
		spw = sph;

		start.y = -sph / 2 + WIN_H / 2;
		if (start.y < 0)
			start.y = 0;
		end.y = sph / 2 + WIN_H / 2;
		if (end.y >= WIN_H)
			end.y = WIN_H - 1;

		start.x = -spw / 2 + spscrx;
		if (start.x < 0)
			start.x = 0;
		end.x = spw / 2 + spscrx;
		if (end.x >= WIN_W)
			end.x = WIN_W - 1;

		stripe = start.x;
		while (stripe < end.x)
		{
			if (tr.y > 0 && stripe > 0 && stripe < WIN_W && tr.y < c->sprite.zbuffer[stripe])
			{
				tex.x = ((256 * (stripe - (-spw / 2 + spscrx)) * WALL_SZ /
							spw)) / 256;
				y = start.y;
				while (y < end.y)
				{
					tex.y = (((y * 256 - WIN_H * 128 + sph * 128) *
								WALL_SZ) / sph) / 256;
					col = cont->pix_tex[sprite[c->sprite.sprite_order[i]].text][tex.y * WALL_SZ + tex.x];
					col &= 0x00FFFFFF;
					if (col != 0)
						put_pixel(cont, stripe, y, col);
					y++;
				}
			}
			stripe++;
		}
		i++;
	}

// draw sprite
	if (0)
	{
/*		for (int i = 0; i < NSPRITE; i++)
		{
			sprite_order[i] = i;
			sprite_dist[i] = ((cont->g.pos.x - sprite[i].x) * (cont->g.pos.x - sprite[i].x) + (cont->g.pos.y - sprite[i].y) * (cont->g.pos.y - sprite[i].y));
		}*/

// fonction de tri des sprites !
/*
		for (int i = 0; i < NSPRITE; i++)
		{
			sp.x = sprite[c->sprite.sprite_order[i]].x - cont->g.pos.x;
			sp.y = sprite[c->sprite.sprite_order[i]].y - cont->g.pos.y;

			double spritex = sprite[c->sprite.sprite_order[i]].x - cont->g.pos.x;
			double spritey = sprite[c->sprite.sprite_order[i]].y - cont->g.pos.y;
//			invdet = 1. / (cont->g.plane.x * cont->g.dir.y -
//					cont->g.dir.x * cont->g.plane.y);
			transform.x = invdet * (cont->g.dir.y * spritex - cont->g.dir.x * spritey);
			transform.y = invdet * (-cont->g.plane.y * spritex - cont->g.plane.x * spritey);

			int spritescreenx = (WIN_W / 2.) * (1. + transform.x / transform.y);
			int spriteheight = abs((int)(WIN_H / transform.y));

			start.y = -spriteheight / 2 + WIN_H / 2;
			if (start.y < 0)
				start.y = 0;
			end.y = spriteheight / 2 + WIN_H / 2;
			if (end.y >= WIN_H)
				end.y = WIN_H - 1;

			int spritewidth = spriteheight; //fabs(WIN_H / transform.y);
			start.x = -spritewidth / 2 + spritescreenx;
			if (start.x < 0)
				start.x = 0;
			end.x = spritewidth / 2 + spritescreenx;
			if (end.x >= WIN_W)
				end.x = WIN_W - 1;
			for (int stripe = start.x; stripe < end.x; stripe++)
			{
				if (transform.y > 0 && stripe > 0 && stripe < WIN_W && transform.y < zbuffer[stripe])
				{
					int texx = ((256 * (stripe - (-spritewidth / 2 + spritescreenx)) * WALL_SZ / spritewidth)) / 256;
					for (int y = start.y; y < end.y; y++)
					{
						int d = y * 256 - WIN_H * 128 + spriteheight * 128;
						int texy = ((d * WALL_SZ) / spriteheight) / 256;
						//						col = *(unsigned *)(pilliertex + (((texy) * WALL_SZ + (texx)) * 3));
						col = cont->pix_tex[sprite[c->sprite.sprite_order[i]].text][texy * WALL_SZ + texx];
						col &= 0x00FFFFFF;
						if (col != 0)
							put_pixel(cont, stripe, y, col);
					}
				}
			}
		}*/
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
		draw_verticalline(cont, &c, w, side);
		c.sprite.zbuffer[w] = c.perp;
		w++;
	}
//	draw_sprite(cont, &c);
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
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
	SDL_Surface	*bmp;
	SDL_Texture	*tex;

	bmp = SDL_LoadBMP(name);
	if (bmp == NULL)
		exit_sdlerror();
	tex = SDL_CreateTexture(cont->ren, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, bmp->w, bmp->h);
	if (tex == NULL)
		exit_sdlerror();
	copy_surface_to_texture(tex, bmp);
	SDL_FreeSurface(bmp);
	return (tex);
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
	SDL_RenderCopy(cont->ren, tex, NULL, &dst);
}

void	load_textures(t_cont *cont)
{
	static char	*name[N_TEXTURES] = {
		"img/eagle.bmp",
		"img/redbrick.bmp",
		"img/purplestone.bmp",
		"img/greystone.bmp",
		"img/bluestone.bmp",
		"img/mossy.bmp",
		"img/wood.bmp",
		"img/colorstone.bmp",
		"img/barrel.bmp",
		"img/pillar.bmp",
		"img/greenlight.bmp",
		"img/rainbowdash.bmp"
	};
	int		i;

	i = 0;
	while (i < N_TEXTURES)
	{
//		cont->tex[i] = load_bmp(cont, name[i]);
		if (i % 2)
		cont->tex[i] = load_bmp(cont, "img/rainbowdash512.bmp");
		else
		cont->tex[i] = load_bmp(cont, "img/pinkiepie.bmp");
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
	cont->img = SDL_CreateTexture(cont->ren, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	SDL_QueryTexture(cont->img, NULL, NULL, &cont->w, &cont->h);
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
	int		pitch;
	int		i;

	if (SDL_LockTexture(cont->img, NULL, (void **)&cont->pixels,
				&cont->pitch) < 0)
		exit_sdlerror();
	i = 0;
	while (i < N_TEXTURES)
	{
		if (SDL_LockTexture(cont->tex[i], NULL, (void **)&cont->pix_tex[i],
					&pitch) < 0)
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
		SDL_UnlockTexture(cont->tex[i]);
		i++;
	}
	SDL_UnlockTexture(cont->img);
}

int		main_loop(t_cont *cont)
{

	while (1)
	{
		if (update_events() || cont->state[SDL_SCANCODE_ESCAPE])
			break ;
		if (cont->state[SDL_SCANCODE_UP])
			key_arrow(K_UP, cont);
		if (cont->state[SDL_SCANCODE_DOWN])
			key_arrow(K_DOWN, cont);
		if (cont->state[SDL_SCANCODE_LEFT])
			key_arrow(K_LEFT, cont);
		if (cont->state[SDL_SCANCODE_RIGHT])
			key_arrow(K_RIGHT, cont);
		lock_textures(cont);
		calc(cont);
		unlock_textures(cont);
		// Plaque la texture sur la fenetre
		render_texture(cont, cont->img, 0, 0);
		// Equivalent de SDL_Flip
		SDL_RenderPresent(cont->ren);
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

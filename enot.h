#ifndef __ENOT_H
# define __ENOT_H

//# include <SDL.h>
# include "SDL2/SDL2.framework/Headers/SDL.h"
//# include "SDL2/SDL2_image.framework/Headers/SDL_image.h"
//# include "SDL2/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include <math.h>
# include <time.h>

# define WINDOW_W 1300
# define WINDOW_H 700

typedef struct s_sector
{
	int startWall;
	int numWalls;
}				t_sector;

typedef struct s_wall_flags
{
	//char	floor;
	//char	ceil;
	char	type; // 0 - wall, 1 - object
}				t_wall_flags;

typedef struct s_wall
{
	int				x;
	int				y;
	int				zd;
	int				zu;
	int				nextsector;
	char			hv; // horizontal: -1 vertical: 1 other: 0
	float			k;
	float			b;
	/*t_wall_flags	f;*/
	char	type; // 1 - wall, -1 - object
}				t_wall;

typedef struct s_player
{
	int x;
	int y;
	int z;
	int rot;
	int angle;
}				t_player;

typedef struct s_wall_line
{
	int		x;
	int		yu;
	int		yd;
}				t_wall_line;

typedef struct	s_brez
{
	int			x;
	int			y;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			k;
	char		dest;
	int			prev_x;
	int			indx;
	t_wall_line *lines;
}				t_brez;

typedef struct	s_draw_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
}				t_draw_line;

typedef struct s_save_wall_list
{
	int						i;
	int						wall;
	struct s_save_wall_list *next;
}				t_save_wall_list;

//typedef struct	s_draw2
//{
//	int		start;
//	int		end;
//	int		len;
//}				t_draw2;


typedef struct	s_draw_portal
{
	int		xleft;
	int		xright;
	int		pyu1; // p means - portal
	int		pyu2;
	int		pyd1;
	int		pyd2;
	int		yu1;
	int		yu2;
	int		yd1;
	int		yd2;
	int		pyu;
	int		pyd;
	int		yu;
	int		yd;
}				t_draw_portal;

typedef struct	s_draw
{
	float	ang;
	char	xdir;
	char	ydir;
	int		curr_sector;
	int		curr_wall;
	int		i;
	float	k;
	float	b;
	int		topY[WINDOW_W];
	int		bottomY[WINDOW_W];
	int		rx;
	int		ry;
	int		len;
	//int		wallsz;
	int		zd;
	int		zu;
	int		xright;
	t_draw_portal *p;
	int		len_plus;
}				t_draw;

typedef struct s_variables
{
	int		numSectors;
	int 	last_sector;
}				t_variables;

typedef struct s_sdl
{
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Texture *tex;
	SDL_Surface *sur;
	char		quit;
	//SDL_Surface *tex1;

	t_sector	*sectors;
	t_wall		*walls;
	t_player	p;
	t_variables	v;
	t_save_wall_list *l;
}				t_sdl;

#endif

#ifndef _PARSING_H

# define _PARSING_H

#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include "gnl/get_next_line.h"

# define MXPM  mlx_xpm_file_to_image
# define ADR   mlx_get_data_addr

typedef struct  s_img {
    void        *img;
    char        *addr;
    int         bp;
    int         ll;
    int         end;
}               t_img;

typedef struct  s_tex {
    void        *i;
    char        *addr;
    int         bp;
    int         ll;
    int         end;
    int         w;
    int         h; 
}               t_tex;

typedef struct  s_sprt {

  double x;
  double y;
  //int dist;
}               t_sprt;

typedef struct  s_sprite {

    int count;
    double **buff;
    double y;
    int texture;
    double X;
    double Y; 
    double inv;
    double tranX;
    double tranY;
    int ScreenX;
    int move_s;
    t_sprt *buf;
    int w;
    int d;

}               t_sprite;

typedef struct		s_rend
{
    int x;
    int y;

}					t_rend;

typedef struct		s_NO
{
    char *p;
    
}					t_NO;

typedef struct		s_WE
{
    char *p;
    
}					t_WE;

typedef struct		s_SO
{
    char *p;
    
}					t_SO;

typedef struct		s_EA
{
    char *p;
    
}					t_EA;

typedef struct		s_F
{
    int r;
    int g;
    int b;
}					t_F;

typedef struct		s_C
{
    int r;
    int g;
    int b;
    
}					t_C;

typedef struct		s_S
{
    char *s;
    
}					t_S;

typedef struct	s_win //структура для окна
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			line_l;
	int			bpp;
	int			en;
}				  t_win;

typedef struct	s_point // структура для точки
{
	int			x;
	int			y;
}				  t_point;

typedef struct	s_ray // структура для точки
{
    unsigned int color;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    int sX;
    int sY;
    int hit;
    int side;
    double deltaDistX;
    double deltaDistY;
    double wd;
}				  t_ray;

typedef struct s_draw
{
    int lhi;
    int drawStart;
    int drawEnd;
    int drawStartX;
    int drawEndX;
    int drawStartY;
    int drawEndY;
    double wallX;
    int texX;
    int texY;
    double step;

}              t_draw;

typedef struct	s_plr //структура для игрока и луча
{
	double		x;
	double		y;
	double		dirX;
	double		dirY;
	double		end;
    double		planeX;
	double		planeY;
    double      cameraX;
    double      rpsX;
    double      rpsY;
}				  t_plr;

typedef struct	s_a // структура для всего вместе
{
	t_win		win;
	t_plr		p;
	char		**map;
    char        **only_m;
    t_rend      rend;
    t_F         F;
    t_point     point;
    t_NO         NO;
    t_WE         WE;
    t_EA         EA;
    t_SO         SO;
    t_C          C;
    t_S          S;
    int         save;
    int         flag;
    t_img      img;
    t_tex       t[5];
    t_sprt      sprt[5];
    t_sprite    s;
    t_ray       ray;
    t_draw      draw;
}				  t_a;

#endif

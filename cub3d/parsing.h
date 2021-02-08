#ifndef _PARSING_H

# define _PARSING_H

#include <stdio.h>
#include <math.h> 
#define SCALE 20 // условный размер каждого квадратика в карте


typedef struct  s_img {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_img;

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

/*typedef struct		s_only_m
{
    char **m;
    
}					t_only_m;
*/
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

typedef struct	s_plr //структура для игрока и луча
{
	float		x;
	float		y;
	float		dir;
	float		start;
	float		end;
}				  t_plr;

typedef struct	s_all // структура для всего вместе
{
	t_win		win;
	t_plr		plr;
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
    t_img      img;

}				  t_all;

#endif

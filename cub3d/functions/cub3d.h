/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:28:20 by jshondra          #+#    #+#             */
/*   Updated: 2021/03/07 18:44:20 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H

# define _CUB3D_H

# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"

# define MXPM  mlx_xpm_file_to_image
# define ADR   mlx_get_data_addr
# define BMP "screenshot.bmp"

typedef struct		s_img
{
	void			*img;
	char			*addr;
	int				bp;
	int				ll;
	int				end;
}					t_img;

typedef struct		s_tex
{
	void			*i;
	char			*addr;
	int				bp;
	int				ll;
	int				end;
	int				w;
	int				h;
}					t_tex;

typedef struct		s_sprt
{
	double			x;
	double			y;
}					t_sprt;

typedef struct		s_sprite
{
	int				count;
	double			**buff;
	double			y;
	int				texture;
	double			x;
	double			inv;
	double			tranx;
	double			trany;
	int				screenx;
	int				move_s;
	t_sprt			*buf;
	int				w;
	int				d;

}					t_sprite;

typedef struct		s_rend
{
	int				x;
	int				y;

}					t_rend;

typedef struct		s_no
{
	char			*n;
	char			*w;
	char			*s;
	char			*e;
	char			*sprite;
}					t_no;

typedef struct		s_f
{
	int				r;
	int				g;
	int				b;
}					t_f;

typedef struct		s_c
{
	int				r;
	int				g;
	int				b;
}					t_c;

typedef struct		s_win
{
	void			*mlx;
	void			*win;

}					t_win;

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_ray
{
	unsigned int	color;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	int				sx;
	int				sy;
	int				hit;
	int				side;
	double			deltadistx;
	double			deltadisty;
	double			wd;
}					t_ray;

typedef struct		s_draw
{
	int				lhi;
	int				drawstart;
	int				drawend;
	int				drawstartx;
	int				drawendx;
	int				drawstarty;
	int				drawendy;
	double			wallx;
	int				texx;
	int				texy;
	double			step;

}					t_draw;

typedef struct		s_plr
{
	double			x;
	double			y;
	double			dirx;
	double			diry;
	double			end;
	double			planex;
	double			planey;
	double			camerax;
	double			rpsx;
	double			rpsy;
}					t_plr;

typedef struct		s_a
{
	t_win			win;
	t_plr			p;
	char			**map;
	char			**only_m;
	t_rend			rend;
	t_f				f;
	t_point			point;
	t_no			no;
	t_c				c;
	int				save;
	int				flag;
	int				j;
	t_img			img;
	t_tex			t[5];
	int				flags[9];
	t_sprt			sprt;
	t_sprite		s;
	t_ray			ray;
	t_draw			draw;
}					t_a;

int					error(int i);
int					error_2(int i);
void				parse_sprite(t_a *a, int i, int j);
int					skip_space(char *str, int i, int j);
int					rgb_to_int_f(t_a *a);
int					rgb_to_int_c(t_a *a);
void				we_pos(t_a *a);
void				ea_pos(t_a *a);
void				so_pos(t_a *a);
void				no_pos(t_a *a);
int					check_view(t_a *a, int i, int j);
int					parse_player(t_a *a, int i, int j);
void				valid_map(t_a *a, int i, int j);
void				go_map(char **map, t_a *a, int k);
int					parse_r(char *map, t_a *a, int flag, int j);
int					parse_c(char *map, t_a *a, int j);
int					parse_f(char *map, t_a *a, int j);
int					helper(char **map, t_a *a, int flag, int i);
int					helper1(char **map, t_a *a, int flag, int i);
int					pars_map(char **map, t_a *a, int i, int flag);
int					next(int i, char *s1);
int					open_file(char *name, int *fd, int i);
void				parser(int *fd, int save);
void				get_data_tex(t_a *a);
void				bubble_sort(double *num, double *s, int size);
int					ft_close(t_a *a, int win);
void				my_mlx_pixel_put(t_a *a, int x, int y, int color);
unsigned int		get_color(t_a *a, int x, int y, int i);
void				ft_clean_window(t_a *a, int f, int c);
void				selecter(t_a *a);
void				newselector(t_a *a);
int					init(t_a *a, int x);
int					choose_side(t_a *a, int g);
int					choose_side1(t_a *a, int g);
void				draw_walls(t_a *a, int x, int g);
void				spr_init(t_a *a, double spriteorder[a->s.count], int i);
void				draw_spr(t_a *a, double z[a->rend.x], int y, int c);
void				ft_sprites(t_a *a, double zbuff[a->rend.x]);
int					newcub(t_a *a);
void				move_forward(t_a *a);
void				move_back(t_a *a);
void				rotate_l(t_a *a);
void				rotate_r(t_a *a);
int					key_press(int key, t_a *a);
void				print_map(t_a *a);
int					mode_atoi(const char *str);
int					create_bmp(t_a *a);
void				init_some(int save, t_a *a);
void				for_flag(t_a *a, int flag);
void 				check_help(t_a *a, int i, int j, char **map);
void 				node_check(char *map, int j);
void				init_some(int save, t_a *a);

#endif

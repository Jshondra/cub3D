#include <mlx.h>
#include "cub3D.h"
#include "libft/libft.h"
#include <unistd.h>

int		rgb_to_int_f(t_a *a);
int		rgb_to_int_c(t_a *a);
int		error(int i);

static void		add_to_bit(char *t, int i, int k)
{
	t[i] = k % 256;
	t[i + 1] = k / 256 % 256;
	t[i + 2] = k / 256 / 256 % 256;
	t[i + 3] = k / 256 / 256 / 256;
}

static void		filehead(int fd, t_a *a)
{
	int		i;
	char	t[14];

	i = -1;
	while (++i < 14)
		t[i] = 0;
	t[0] = 66;
	t[1] = 77;
	t[10] = 54;
	add_to_bit(t, 2, a->rend.y * a->rend.x);
	write(fd, t, 14);
}

static void		infohead(int fd, t_a *a)
{
	int		i;
	char	t[40];

	i = -1;
	while (++i < 40)
		t[i] = 0;
	t[0] = 40;
	t[12] = 1;
	t[14] = 32;
	add_to_bit(t, 4, a->rend.x);
	add_to_bit(t, 8, a->rend.y);
	write(fd, t, 40);
}

static void		color_table(int fd, t_a *a)
{
	int y;
	int x;

	y = a->rend.y;
	while (y-- && (x = -1))
		while (++x < a->rend.x)
			write(fd, (a->img.addr + (y * a->img.ll + x * (a->img.bp / 8))), 4);
}

int				create_bmp(t_a *a)
{
	int fd;

	if ((fd = open(BMP, O_CREAT | O_TRUNC | O_RDWR, 0644)) <= 0)
		return (error(1));
	filehead(fd, a);
	infohead(fd, a);
	color_table(fd, a);
	close(fd);
	return (0);
}

void			get_data_tex(t_a *a)
{
	if (!(a->t[0].i = MXPM(a->win.mlx, a->NO.n, &a->t[0].w, &a->t[0].h)) ||
	!(a->t[0].addr = ADR(a->t[0].i, &a->t[0].bp, &a->t[0].ll, &a->t[0].end)))
		error(11);
	if (!(a->t[1].i = MXPM(a->win.mlx, a->NO.s, &a->t[1].w, &a->t[1].h)) ||
	!(a->t[1].addr = ADR(a->t[1].i, &a->t[1].bp, &a->t[1].ll, &a->t[1].end)))
		error(11);
	if (!(a->t[2].i = MXPM(a->win.mlx, a->NO.w, &a->t[2].w, &a->t[2].h)) ||
	!(a->t[2].addr = ADR(a->t[2].i, &a->t[2].bp, &a->t[2].ll, &a->t[2].end)))
		error(11);
	if (!(a->t[3].i = MXPM(a->win.mlx, a->NO.e, &a->t[3].w, &a->t[3].h)) ||
	!(a->t[3].addr = ADR(a->t[3].i, &a->t[3].bp, &a->t[3].ll, &a->t[3].end)))
		error(11);
	if (!(a->t[4].i = MXPM(a->win.mlx, a->NO.sprite, &a->t[4].w, &a->t[4].h)) ||
	!(a->t[4].addr = ADR(a->t[4].i, &a->t[4].bp, &a->t[4].ll, &a->t[4].end)))
		error(11);
}

void			bubble_sort(double *num, double *s, int size)
{
	int i;
	int j;
	int temp;
	int t;

	i = -1;
	j = (size - 1);
	while (++i < size - 1)
	{
		while (j > i)
		{
			if (num[j] > num[j - 1])
			{
				temp = num[j - 1];
				num[j - 1] = num[j];
				num[j] = temp;
				t = s[j - 1];
				s[j - 1] = s[j];
				s[j] = t;
			}
			j--;
		}
		j = (size - 1);
	}
}

int				ft_close(t_a *a, int win)
{
	if (win == 1)
		mlx_destroy_window(a->win.mlx, a->win.win);
	exit(0);
	return (1);
}

void			my_mlx_pixel_put(t_a *a, int x, int y, int color)
{
	char	*dst;

	dst = a->img.addr + (y * a->img.ll + x * (a->img.bp / 8));
	*(unsigned int*)dst = color;
}

unsigned int	get_color(t_a *a, int x, int y, int i)
{
	char				*dst;
	unsigned int		color;

	dst = a->t[i].addr + (y * a->t[i].ll + x * (a->t[i].bp / 8));
	color = *(unsigned int*)dst;
	return (color);
}

void			ft_clean_window(t_a *a, int f, int c)
{
	int	i;
	int	j;

	f = rgb_to_int_f(a);
	c = rgb_to_int_c(a);
	i = -1;
	while (++i < a->rend.y / 2)
	{
		j = -1;
		while (++j < a->rend.x)
			my_mlx_pixel_put(a, j, i, c);
	}
	while (++i < a->rend.y)
	{
		j = -1;
		while (++j < a->rend.x)
			my_mlx_pixel_put(a, j, i, f);
	}
}

void			selecter(t_a *a)
{
	a->ray.deltadistx = fabs(1 / a->p.rpsx);
	a->ray.deltadisty = fabs(1 / a->p.rpsy);
	a->ray.hit = 0;
	if (a->p.rpsx < 0)
	{
		a->ray.sx = -1;
		a->ray.sidedistx = (a->p.x - a->ray.mapx) * a->ray.deltadistx;
	}
	else
	{
		a->ray.sx = 1;
		a->ray.sidedistx = (a->ray.mapx + 1.0 - a->p.x) * a->ray.deltadistx;
	}
	if (a->p.rpsy < 0)
	{
		a->ray.sy = -1;
		a->ray.sidedisty = (a->p.y - a->ray.mapy) * a->ray.deltadisty;
	}
	else
	{
		a->ray.sy = 1;
		a->ray.sidedisty = (a->ray.mapy + 1.0 - a->p.y) * a->ray.deltadisty;
	}
}

void			newselector(t_a *a)
{
	while (a->ray.hit == 0)
	{
		if (a->ray.sidedistx < a->ray.sidedisty)
		{
			a->ray.sidedistx += a->ray.deltadistx;
			a->ray.mapx += a->ray.sx;
			a->ray.side = 0;
		}
		else
		{
			a->ray.sidedisty += a->ray.deltadisty;
			a->ray.mapy += a->ray.sy;
			a->ray.side = 1;
		}
		if (a->only_m[a->ray.mapy][a->ray.mapx] == '1')
			a->ray.hit = 1;
	}
	if (a->ray.side == 0)
		a->ray.wd = (a->ray.mapx - a->p.x + (1 - a->ray.sx) / 2) / a->p.rpsx;
	else
		a->ray.wd = (a->ray.mapy - a->p.y + (1 - a->ray.sy) / 2) / a->p.rpsy;
}

int				init(t_a *a, int x)
{
	a->p.camerax = 2 * x / (double)a->rend.x - 1;
	a->p.rpsx = a->p.dirx + a->p.planex * a->p.camerax;
	a->p.rpsy = a->p.diry + a->p.planey * a->p.camerax;
	a->ray.mapx = (int)a->p.x;
	a->ray.mapy = (int)a->p.y;
	selecter(a);
	newselector(a);
	a->draw.lhi = (int)(a->rend.y / a->ray.wd);
	a->draw.drawstart = -a->draw.lhi / 2 + a->rend.y / 2;
	if (a->draw.drawstart < 0)
		a->draw.drawstart = 0;
	a->draw.drawend = a->draw.lhi / 2 + a->rend.y / 2;
	if (a->draw.drawend >= a->rend.y)
		a->draw.drawend = a->rend.y - 1;
	if (a->ray.side == 0)
		a->draw.wallx = a->p.y + a->ray.wd * a->p.rpsy;
	else
		a->draw.wallx = a->p.x + a->ray.wd * a->p.rpsx;
	a->draw.wallx -= floor((a->draw.wallx));
	return (x);
}

int				choose_side(t_a *a, int g)
{
	if (a->ray.sx > 0)
	{
		a->draw.texx = a->t[3].w - (int)(a->draw.wallx * (double)a->t[3].w) - 1;
		a->draw.step = 1.0 * a->t[3].w / a->draw.lhi;
		g = 3;
	}
	else
	{
		a->draw.texx = a->t[2].w - (int)(a->draw.wallx * (double)a->t[2].w) - 1;
		a->draw.step = 1.0 * a->t[2].w / a->draw.lhi;
		g = 2;
	}
	return (g);
}

int				choose_side1(t_a *a, int g)
{
	if (a->ray.sy > 0)
	{
		a->draw.texx = a->t[1].w - (int)(a->draw.wallx * (double)a->t[1].w) - 1;
		a->draw.step = 1.0 * a->t[1].w / a->draw.lhi;
		g = 1;
	}
	else
	{
		a->draw.texx = a->t[0].w - (int)(a->draw.wallx * (double)a->t[0].w) - 1;
		a->draw.step = 1.0 * a->t[0].w / a->draw.lhi;
		g = 0;
	}
	return (g);
}

void			draw_walls(t_a *a, int x, int g)
{
	unsigned int	color;
	double			texpos;
	int				y;

	y = a->draw.drawstart;
	texpos = (a->draw.drawstart - a->rend.y / 2 + a->draw.lhi / 2);
	texpos *= a->draw.step;
	while (y < a->draw.drawend)
	{
		a->draw.texy = (int)texpos % (a->t[g].h - 1);
		texpos += a->draw.step;
		color = get_color(a, a->draw.texx, a->draw.texy, g);
		my_mlx_pixel_put(a, x, y, color);
		y++;
	}
}

void			spr_init(t_a *a, double spriteorder[a->s.count], int i)
{
	a->s.X = a->s.buf[(int)spriteorder[i]].x - a->p.x;
	a->s.y = a->s.buf[(int)spriteorder[i]].y - a->p.y;
	a->s.inv = 1.0 / (a->p.planex * a->p.diry - a->p.dirx * a->p.planey);
	a->s.tranx = a->s.inv * (a->p.diry * a->s.X - a->p.dirx * a->s.y);
	a->s.trany = a->s.inv * (-a->p.planey * a->s.X + a->p.planex * a->s.y);
	a->s.screenx = (int)((a->rend.x / 2) * (1 + a->s.tranx / a->s.trany));
	a->s.move_s = (int)(0.0 / a->s.trany);
	a->t[4].h = abs((int)(a->rend.y / (a->s.trany))) / 1;
	a->draw.drawstarty = -a->t[4].h / 2 + a->rend.y / 2 + a->s.move_s;
	if (a->draw.drawstarty < 0)
		a->draw.drawstarty = 0;
	a->draw.drawendy = a->t[4].h / 2 + a->rend.y / 2 + a->s.move_s;
	if (a->draw.drawendy >= a->rend.y)
		a->draw.drawendy = a->rend.y - 1;
	a->s.w = abs( (int) (a->rend.y / (a->s.trany))) / 1;
	a->draw.drawstartx = -a->s.w / 2 + a->s.screenx;
	if (a->draw.drawstartx < 0)
		a->draw.drawstartx = 0;
	a->draw.drawendX = a->s.w / 2 + a->s.screenx;
	if (a->draw.drawendX >= a->rend.x)
		a->draw.drawendX = a->rend.x - 1;
}

void			draw_spr(t_a *a, double zbuff[a->rend.x], int y, int stripe)
{
	unsigned int color;

	stripe = a->draw.drawstartx;
	y = a->draw.drawstarty;
	while (stripe < a->draw.drawendX)
	{
		a->draw.texx = (int)(256 * (stripe - (-a->s.w / 2 + a->s.screenx)));
		a->draw.texx = (int)(a->draw.texx * a->t[4].w / a->s.w / 256);
		if (a->s.trany > 0 && stripe > 0 && stripe < a->rend.x &&
		a->s.trany < zbuff[stripe])
		while (y < a->draw.drawendy)
			{
				a->s.d = (y - a->s.move_s) * 256 - a->rend.y * 128;
				a->s.d += a->t[4].h * 128;
				a->draw.texy = ((a->s.d * a->t[4].w) / a->t[4].h) / 256;
				color = get_color(a, a->draw.texx, a->draw.texy, 4);
				if ((color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(a, stripe, y, color);
				y++;
			}
		y = a->draw.drawstarty;
		stripe++;
	}
}

void			ft_sprites(t_a *a, double zbuff[a->rend.x])
{
	double	spriteorder[a->s.count];
	double	spritedistance[a->s.count];
	int		i;

	i = -1;
	while (++i < a->s.count)
	{
		spriteorder[i] = i;
		spritedistance[i] = pow(a->p.x - a->s.buf[i].x, 2);
		spritedistance[i] += pow(a->p.y - a->s.buf[i].y, 2);
	}
	bubble_sort(spritedistance, spriteorder, a->s.count);
	i = -1;
	while (++i < a->s.count)
	{
		spr_init(a, spriteorder, i);
		draw_spr(a, zbuff, 0, 0);
	}
}

int				newcub(t_a *a)
{
	double	zbuff[a->rend.x];
	int		g;
	int		x;

	g = 0;
	x = 0;
	a->img.img = mlx_new_image(a->win.mlx, a->rend.x, a->rend.y);
	a->img.addr = ADR(a->img.img, &a->img.bp, &a->img.ll, &a->img.end);
	ft_clean_window(a, 0, 0);
	while (x < a->rend.x)
	{
		x = init(a, x);
		if (a->ray.side == 0)
			g = choose_side(a, g);
		else
			g = choose_side1(a, g);
		draw_walls(a, x, g);
		zbuff[x] = a->ray.wd;
		x++;
	}
	ft_sprites(a, zbuff);
	a->save && !create_bmp(a) ? key_press(53, a->win.mlx) : 0;
	mlx_put_image_to_window(a->win.mlx, a->win.win, a->img.img, 0, 0);
	return (1);
}

void			move_forward(t_a *a)
{
	if (a->only_m[(int)(a->p.y + a->p.diry)][(int)(a->p.x + a->p.dirx)] == '0')
	{
		a->p.x += a->p.dirx * 0.5;
		a->p.y += a->p.diry * 0.5;
	}
}

void			move_back(t_a *a)
{
	if (a->only_m[(int)(a->p.y - a->p.diry)][(int)(a->p.x - a->p.dirx)] == '0')
	{
		a->p.x -= a->p.dirx * 0.5;
		a->p.y -= a->p.diry * 0.5;
	}
}

void			rotate_l(t_a *a)
{
	double olddirx;
	double oldplanex;
	double rotspeed;

	rotspeed = 0.05; 
	olddirx = a->p.dirx;
	a->p.dirx = a->p.dirx * cos(-rotspeed) - a->p.diry * sin(-rotspeed);
	a->p.diry = olddirx * sin(-rotspeed) + a->p.diry * cos(-rotspeed);
	oldplanex = a->p.planex;
	a->p.planex = a->p.planex * cos(-rotspeed) - a->p.planey * sin(-rotspeed);
	a->p.planey = oldplanex * sin(-rotspeed) + a->p.planey * cos(-rotspeed);
}

void			rotate_r(t_a *a)
{
	double olddirx;
	double oldplanex;
	double rotspeed;

	rotspeed = 0.05; 
	olddirx = a->p.dirx;
	a->p.dirx = a->p.dirx * cos(rotspeed) - a->p.diry * sin(rotspeed);
	a->p.diry = olddirx * sin(rotspeed) + a->p.diry * cos(rotspeed);
	oldplanex = a->p.planex;
	a->p.planex = a->p.planex * cos(rotspeed) - a->p.planey * sin(rotspeed);
	a->p.planey = oldplanex * sin(rotspeed) + a->p.planey * cos(rotspeed);
}

int				key_press(int key, t_a *a)
{
	if (key == 13)
		move_forward(a);
	if (key == 1)
		move_back(a);
	if (key == 0)
		rotate_l(a);
	if (key == 2)
		rotate_r(a);
	if (key == 53)
		exit(0);
	return (0);
}

void			print_map(t_a *a)
{
	a->win.mlx = mlx_init();
	a->win.win = mlx_new_window(a->win.mlx, a->rend.x, a->rend.y, "Cub3D");
	a->img.img = mlx_new_image(a->win.mlx, a->rend.x, a->rend.y);
	a->img.addr = ADR(a->img.img, &a->img.bp, &a->img.ll, &a->img.end);
	get_data_tex(a);
	newcub(a);
	mlx_hook(a->win.win, 2, 0, key_press, a);
	mlx_hook(a->win.win, 17, 0, ft_close, a);
	mlx_loop_hook(a->win.mlx, (newcub), a);
	mlx_loop(a->win.mlx);
}
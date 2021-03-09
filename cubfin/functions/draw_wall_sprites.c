/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:26:12 by jshondra          #+#    #+#             */
/*   Updated: 2021/03/07 18:26:14 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	a->s.x = a->s.buf[(int)spriteorder[i]].x - a->p.x;
	a->s.y = a->s.buf[(int)spriteorder[i]].y - a->p.y;
	a->s.inv = 1.0 / (a->p.planex * a->p.diry - a->p.dirx * a->p.planey);
	a->s.tranx = a->s.inv * (a->p.diry * a->s.x - a->p.dirx * a->s.y);
	a->s.trany = a->s.inv * (-a->p.planey * a->s.x + a->p.planex * a->s.y);
	a->s.screenx = (int)((a->rend.x / 2) * (1 + a->s.tranx / a->s.trany));
	a->s.move_s = (int)(0.0 / a->s.trany);
	a->t[4].h = abs((int)(a->rend.y / (a->s.trany))) / 1;
	a->draw.drawstarty = -a->t[4].h / 2 + a->rend.y / 2 + a->s.move_s;
	if (a->draw.drawstarty < 0)
		a->draw.drawstarty = 0;
	a->draw.drawendy = a->t[4].h / 2 + a->rend.y / 2 + a->s.move_s;
	if (a->draw.drawendy >= a->rend.y)
		a->draw.drawendy = a->rend.y - 1;
	a->s.w = abs((int)(a->rend.y / (a->s.trany))) / 1;
	a->draw.drawstartx = -a->s.w / 2 + a->s.screenx;
	if (a->draw.drawstartx < 0)
		a->draw.drawstartx = 0;
	a->draw.drawendx = a->s.w / 2 + a->s.screenx;
	if (a->draw.drawendx >= a->rend.x)
		a->draw.drawendx = a->rend.x - 1;
}

void			draw_spr(t_a *a, double z[a->rend.x], int y, int c)
{
	unsigned int color;

	c = a->draw.drawstartx;
	y = a->draw.drawstarty;
	while (c < a->draw.drawendx)
	{
		a->draw.texx = (int)(256 * (c - (-a->s.w / 2 + a->s.screenx)));
		a->draw.texx = (int)(a->draw.texx * a->t[4].w / a->s.w / 256);
		if (a->s.trany > 0 && c > 0 && c < a->rend.x &&
		a->s.trany < z[c])
			while (y < a->draw.drawendy)
			{
				a->s.d = (y - a->s.move_s) * 256 - a->rend.y * 128;
				a->s.d += a->t[4].h * 128;
				a->draw.texy = ((a->s.d * a->t[4].w) / a->t[4].h) / 256;
				color = get_color(a, a->draw.texx, a->draw.texy, 4);
				if ((color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(a, c, y, color);
				y++;
			}
		y = a->draw.drawstarty;
		c++;
	}
}

void			ft_sprites(t_a *a, double z[a->rend.x])
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
		draw_spr(a, z, 0, 0);
	}
}

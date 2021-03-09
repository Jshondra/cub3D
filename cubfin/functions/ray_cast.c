/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:27:03 by jshondra          #+#    #+#             */
/*   Updated: 2021/03/07 18:27:04 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

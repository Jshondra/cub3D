/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:26:01 by jshondra          #+#    #+#             */
/*   Updated: 2021/03/07 18:26:03 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

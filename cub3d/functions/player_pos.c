/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:30:10 by jshondra          #+#    #+#             */
/*   Updated: 2021/03/07 18:30:13 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	we_pos(t_a *a)
{
	a->p.dirx = -1.0;
	a->p.diry = 0.0;
	a->p.planex = 0.0;
	a->p.planey = -0.70;
	a->only_m[(int)a->p.y][(int)a->p.x] = '0';
}

void	ea_pos(t_a *a)
{
	a->p.dirx = 1.0;
	a->p.diry = 0.0;
	a->p.planex = 0.0;
	a->p.planey = 0.70;
	a->only_m[(int)a->p.y][(int)a->p.x] = '0';
}

void	so_pos(t_a *a)
{
	a->p.dirx = 0.0;
	a->p.diry = 1.0;
	a->p.planex = -0.70;
	a->p.planey = 0.0;
	a->only_m[(int)a->p.y][(int)a->p.x] = '0';
}

void	no_pos(t_a *a)
{
	a->p.dirx = 0.0;
	a->p.diry = -1.0;
	a->p.planex = 0.70;
	a->p.planey = 0.0;
	a->only_m[(int)a->p.y][(int)a->p.x] = '0';
}

int		check_view(t_a *a, int i, int j)
{
	a->p.x = j + 0.5;
	a->p.y = i + 0.5;
	if (a->only_m[i][j] == 'E')
		ea_pos(a);
	else if (a->only_m[i][j] == 'W')
		we_pos(a);
	else if (a->only_m[i][j] == 'S')
		so_pos(a);
	else if (a->only_m[i][j] == 'N')
		no_pos(a);
	a->flag += 1;
	if (a->flag != 1)
		error(1);
	return (1);
}

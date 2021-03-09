/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:26:38 by jshondra          #+#    #+#             */
/*   Updated: 2021/03/07 18:26:40 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			parse_player(t_a *a, int i, int j)
{
	if (!(a->only_m[i][j + 1]) || !(a->only_m[i + 1][j])
		|| !(a->only_m[i - 1][j]) || !(a->only_m[i][j - 1]))
		error(2);
	if ((a->only_m[i][j + 1]) == ' ' || (a->only_m[i + 1][j]) == ' '
		|| (a->only_m[i - 1][j]) == ' ' || (a->only_m[i][j - 1]) == ' ')
		error(2);
	if ((int)ft_strlen(a->only_m[i - 1]) < j)
		error(2);
	if (ft_strchr("NSEW", a->only_m[i][j]))
		check_view(a, i, j);
	return (1);
}

void		valid_map(t_a *a, int i, int j)
{
	while (a->only_m[++i])
	{
		j = 0;
		// if (!a->only_m[i][0] && i++)
		// 	continue ;
		while (a->only_m[i][j])
		{
			if (ft_strchr("NSEW", a->only_m[i][j]) || a->only_m[i][j] == '0')
			{
				parse_player(a, i, j);
				j++;
			}
			else if (a->only_m[i][j] == '1' || a->only_m[i][j] == ' ' ||
			a->only_m[i][j] == '\n')
				j++;
			else if (a->only_m[i][j] == '2')
			{
				a->s.count++;
				j++;
			}
			else
				error(3);
		}
	}
}

void		go_map(char **map, t_a *a)
{
	int i;
	int j;
	int flag;

	i = 0;
	j = 0;
	flag = 0;
	while (map[i][0] != '1' && map[i][0] != '0')
	{
		if (!map[i][0])
		{
			i++;
			continue ;
		}
		i++;
	}
	a->only_m = &map[i];
	a->s.count = 0;
	a->flag = 0;
	valid_map(a, -1, 0);
}

void		parse_sprite(t_a *a, int i, int j)
{
	int l;

	l = 0;
	if (!(a->s.buf = (t_sprt*)malloc(sizeof(t_sprt) * a->s.count)))
		error(10);
	while (a->only_m[++i])
	{
		j = -1;
		while (a->only_m[i][++j])
			if (a->only_m[i][j] == '2')
			{
				a->s.buf[l].y = (double)(i + 0.5);
				a->s.buf[l].x = (double)(j + 0.5);
				l++;
			}
	}
}

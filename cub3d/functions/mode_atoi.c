/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:02:35 by jshondra          #+#    #+#             */
/*   Updated: 2020/11/04 18:43:49 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		mode_atoi(const char *str)
{
	int			i;
	int			n;

	n = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	while (str[i] <= '9' && str[i] >= '0')
	{
		n = n * 10 + str[i] - 48;
		i++;
		if (n > 2560)
			return (2560);
	}
	return (n);
}

void	init_some(int save, t_a *a)
{
	int i;

	a->save = 0;
	a->j = 0;
	if (save == 1)
		a->save = 1;
	i = -1;
	while (++i < 8)
		a->flags[i] = 0;
}

void	node_check(char *map, int j)
{
	int k;

	k = 0;
	while (map[++j])
	{
		if ((map[j] > '9' || map[j] < '0')
		&& (map[j] != ',' && map[j] != ' '))
			error(5);
		if (map[j] == ',')
			k++;
	}
	if (j < 5 || k != 2)
		error(5);
}

void	check_help(t_a *a, int i, int j, char **map)
{
	if (map[i][a->j] == 'E')
	{
		a->no.e = &(map[i][j]);
		a->flags[3] += 1;
	}
	if (map[i][a->j] == 'S' && map[i][1 + a->j] == ' ')
	{
		a->no.sprite = &(map[i][j]);
		a->flags[4] += 1;
	}
	if (!(ft_strncmp(map[i] + a->j, "SO ", 3)))
	{
		a->no.s = &(map[i][j]);
		a->flags[2] += 1;
	}
}

void	for_flag(t_a *a, int flag)
{
	int i;

	i = -1;
	if (flag != 8)
		error(7);
	while (++i < 8)
		if (a->flags[i] != 1)
			error(7);
}

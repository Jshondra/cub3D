/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:26:27 by jshondra          #+#    #+#             */
/*   Updated: 2021/03/07 18:26:29 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_r(char *map, t_a *a, int flag)
{
	int j;

	j = 0;
	while (map[++j])
		if ((map[j] > '9' || map[j] < '0') && map[j] != ' ')
			error(5);
	if (j < 4)
		error(4);
	j = 1;
	a->rend.x = mode_atoi(&map[j]);
	j = skip_space(map, j);
	while (ft_isdigit(map[j]))
		j++;
	if (map[j] != ' ')
		error(4);
	j = skip_space(map, j);
	a->rend.y = mode_atoi(&(map[j]));
	if ((a->rend.x) < 0 || (a->rend.y) < 0)
		error(4);
	flag++;
	if (a->rend.y > 1440)
		a->rend.y = 1440;
	return (flag);
}

int		parse_c(char *map, t_a *a, int j)
{
	while (map[++j])
		if ((map[j] > '9' || map[j] < '0')
		&& (map[j] != ',' && map[j] != ' '))
			error(6);
	if (j < 5)
		error(6);
	j = skip_space(map, 1);
	a->c.r = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	if (map[j] != ',')
		error(6);
	j = skip_space(map, (j + 1));
	a->c.g = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	if ((map[j]) != ',')
		error(6);
	j = skip_space(map, j + 1);
	a->c.b = ft_atoi(&map[j]);
	return (1);
}

int		parse_f(char *map, t_a *a, int j)
{
	while (map[++j])
		if ((map[j] > '9' || map[j] < '0')
		&& (map[j] != ',' && map[j] != ' '))
			error(6);
	if (j < 5)
		error(6);
	j = skip_space(map, 1);
	a->f.r = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	if (map[j] != ',')
		error(6);
	j = skip_space(map, (j + 1));
	a->f.g = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	if ((map[j]) != ',')
		error(6);
	j = skip_space(map, j + 1);
	a->f.b = ft_atoi(&map[j]);
	return (1);
}

int		helper(char **map, t_a *a, int flag, int i)
{
	if (map[i][0] == 'N')
		a->no.n = &(map[i][3]);
	else if (map[i][0] == 'W')
		a->no.w = &(map[i][3]);
	else if (map[i][0] == 'E')
		a->no.e = &(map[i][3]);
	else if (map[i][0] == 'S' && map[i][1] == ' ')
		a->no.sprite = &(map[i][2]);
	else
		a->no.s = &(map[i][3]);
	flag++;
	return (flag);
}

void	pars_map(char **map, t_a *a, int i, int flag)
{
	while (map[i][0] != '1' && map[i][0] != ' ' && map[i][0] != '0')
	{
		if (!map[i][0])
		{
			i++;
			continue ;
		}
		if (!(ft_strncmp(map[i], "R ", 2)))
			flag = parse_r(map[i], a, flag);
		else if (!ft_strncmp((map[i]), "NO ", 3) ||
		!ft_strncmp(map[i], "WE ", 3) || !ft_strncmp(map[i], "EA ", 3) ||
		!(ft_strncmp(map[i], "SO ", 3)) || !(ft_strncmp(map[i], "S ", 2)))
			flag = helper(map, a, flag, i);
		else if (!(ft_strncmp((map[i]), "F ", 2)) ||
		!(ft_strncmp(map[i], "C ", 2)))
			flag = helper1(map, a, flag, i);
		else
			error(7);
		i++;
		printf("\nflag =%d", flag);
	}
	if (flag != 8)
		error(7);
	printf("\n%d, %d\n", a->rend.x, a->rend.y);
}

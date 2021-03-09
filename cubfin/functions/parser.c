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
	int j;

	j = skip_space(map[i], 2 + a->j);
	if (map[i][a->j] == 'N')
		a->no.n = &(map[i][j]);
	else if (map[i][a->j] == 'W')
		a->no.w = &(map[i][j]);
	else if (map[i][a->j] == 'E')
		a->no.e = &(map[i][j]);
	else if (map[i][a->j] == 'S' && map[i][1 + a->j] == ' ')
		a->no.sprite = &(map[i][j]);
	else if (!(ft_strncmp(map[i] + a->j, "SO ", 3)))
		a->no.s = &(map[i][j]);
	flag++;
	return (flag);
}

void	pars_map(char **map, t_a *a, int i, int flag)
{
	while (map[i][0] != '1' && map[i][0] != '0')
	{
		if (!map[i][0])
		{
			i++;
			continue ;	
		}
        if (flag != 8)
            a->j = skip_space(map[i], 0);
		if (!(ft_strncmp(map[i] + a->j, "R ", 2)))
			flag = parse_r(map[i] + a->j, a, flag);
		else if (!ft_strncmp((map[i] + a->j), "NO ", 3) ||
		!ft_strncmp(map[i] + a->j, "WE ", 3) || !ft_strncmp(map[i] + a->j, "EA ", 3) ||
		!(ft_strncmp(map[i] + a->j, "SO ", 3)) || !(ft_strncmp(map[i] + a->j, "S ", 2)))
			flag = helper(map, a, flag, i);
		else if (!(ft_strncmp((map[i] + a->j), "F ", 2)) ||
		!(ft_strncmp(map[i] + a->j, "C ", 2)))
			flag = helper1(map, a, flag, i);
        else if (map[i][0] == ' ' || map[i][0] == '2')
            break ;
		else
			error(7) ;
		i++;
	}
	if (flag != 8)
		error(7);
}

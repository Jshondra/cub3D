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

int		parse_r(char *map, t_a *a, int flag, int j)
{
	a->flags[5] += 1;
	while (map[++j])
		if ((map[j] > '9' || map[j] < '0') && map[j] != ' ')
			error(4);
	if (j < 4)
		error(4);
	j = 1;
	a->rend.x = mode_atoi(&map[j]);
	j = skip_space(map, j, 1);
	while (ft_isdigit(map[j]))
		j++;
	if (map[j] != ' ')
		error(4);
	j = skip_space(map, j, 1);
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
	a->flags[6] += 1;
	node_check(map, j);
	j = skip_space(map, 1, 0);
	a->c.r = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	j = skip_space(map, j, 1);
	if (map[j] != ',')
		error(5);
	j = skip_space(map, (j + 1), 1);
	a->c.g = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	j = skip_space(map, j, 1);
	if ((map[j]) != ',')
		error(5);
	j = skip_space(map, j + 1, 1);
	a->c.b = ft_atoi(&map[j]);
	return (1);
}

int		parse_f(char *map, t_a *a, int j)
{
	a->flags[7] += 1;
	node_check(map, j);
	j = skip_space(map, 1, 0);
	a->f.r = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	j = skip_space(map, j, 1);
	if (map[j] != ',')
		error(5);
	j = skip_space(map, (j + 1), 1);
	a->f.g = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	j = skip_space(map, j, 1);
	if ((map[j]) != ',')
		error(5);
	j = skip_space(map, j + 1, 1);
	a->f.b = ft_atoi(&map[j]);
	return (1);
}

int		helper(char **map, t_a *a, int flag, int i)
{
	int j;

	j = skip_space(map[i], 2 + a->j, 1);
	if (map[i][a->j] == 'N')
	{
		a->no.n = &(map[i][j]);
		a->flags[0] += 1;
	}
	else if (map[i][a->j] == 'W')
	{
		a->no.w = &(map[i][j]);
		a->flags[1] += 1;
	}
	check_help(a, i, j, map);
	flag++;
	return (flag);
}

int		pars_map(char **map, t_a *a, int i, int flag)
{
	while (map[i] && map[i][0] != '1' && map[i][0] != '0')
	{
		//write(1,"here\n", 5);
		if (!map[i][0] && i++)
			continue ;
		if (flag < 9)
			a->j = skip_space(map[i], 0, 1);
		if (!(ft_strncmp(map[i] + a->j, "R ", 2)))
			flag = parse_r(map[i] + a->j, a, flag, 0);
		else if (!ft_strncmp((map[i] + a->j), "NO ", 3) ||
		!ft_strncmp(map[i] + a->j, "WE ", 3) ||
		!ft_strncmp(map[i] + a->j, "EA ", 3) ||
		!(ft_strncmp(map[i] + a->j, "SO ", 3)) ||
		!(ft_strncmp(map[i] + a->j, "S ", 2)))
			flag = helper(map, a, flag, i);
		else if (!(ft_strncmp((map[i] + a->j), "F ", 2)) ||
		!(ft_strncmp(map[i] + a->j, "C ", 2)))
			flag = helper1(map, a, flag, i);
		else if (map[i][0] == ' ')
			break ;
		else
			error(7);
		i++;
	}
	for_flag(a, flag);
	return (i);
}

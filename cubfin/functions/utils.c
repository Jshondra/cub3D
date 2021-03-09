/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:25:39 by jshondra          #+#    #+#             */
/*   Updated: 2021/03/07 18:27:27 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		skip_space(char *str, int i)
{
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	return (i);
}

int		rgb_to_int_f(t_a *a)
{
	a->f.r > 255 ? a->f.r = 255 : 0;
	a->f.g > 255 ? a->f.g = 255 : 0;
	a->f.b > 255 ? a->f.b = 255 : 0;
	return ((int)a->f.r * 65536 + (int)a->f.g * 256 + (int)a->f.b);
}

int		rgb_to_int_c(t_a *a)
{
	a->c.r > 255 ? a->c.r = 255 : 0;
	a->c.g > 255 ? a->c.g = 255 : 0;
	a->c.b > 255 ? a->c.b = 255 : 0;
	return ((int)a->c.r * 65536 + (int)a->c.g * 256 + (int)a->c.b);
}

int		next(int i, char *s1)
{
	if (!s1[i])
		return (0);
	return (1);
}

int		helper1(char **map, t_a *a, int flag, int i)
{
	if (map[i][a->j] == 'C')
		parse_c(map[i] + a->j, a, 0);
	else
		parse_f(map[i] + a->j, a, 0);
	flag++;
	return (flag);
}

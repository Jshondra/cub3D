/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:25:48 by jshondra          #+#    #+#             */
/*   Updated: 2021/03/07 18:25:52 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			bubble_sort(double *num, double *s, int size)
{
	int i;
	int j;
	int temp;
	int t;

	i = -1;
	j = (size - 1);
	while (++i < size - 1)
	{
		while (j > i)
		{
			if (num[j] > num[j - 1])
			{
				temp = num[j - 1];
				num[j - 1] = num[j];
				num[j] = temp;
				t = s[j - 1];
				s[j - 1] = s[j];
				s[j] = t;
			}
			j--;
		}
		j = (size - 1);
	}
}

int				ft_close(t_a *a, int win)
{
	if (win == 1)
		mlx_destroy_window(a->win.mlx, a->win.win);
	exit(0);
	return (1);
}

void			my_mlx_pixel_put(t_a *a, int x, int y, int color)
{
	char	*dst;

	dst = a->img.addr + (y * a->img.ll + x * (a->img.bp / 8));
	*(unsigned int*)dst = color;
}

unsigned int	get_color(t_a *a, int x, int y, int i)
{
	char				*dst;
	unsigned int		color;

	dst = a->t[i].addr + (y * a->t[i].ll + x * (a->t[i].bp / 8));
	color = *(unsigned int*)dst;
	return (color);
}

void			ft_clean_window(t_a *a, int f, int c)
{
	int	i;
	int	j;

	f = rgb_to_int_f(a);
	c = rgb_to_int_c(a);
	i = -1;
	while (++i < a->rend.y / 2)
	{
		j = -1;
		while (++j < a->rend.x)
			my_mlx_pixel_put(a, j, i, c);
	}
	while (++i < a->rend.y)
	{
		j = -1;
		while (++j < a->rend.x)
			my_mlx_pixel_put(a, j, i, f);
	}
}

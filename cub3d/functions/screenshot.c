/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:27:10 by jshondra          #+#    #+#             */
/*   Updated: 2021/03/07 18:27:12 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		add_to_bit(char *t, int i, int k)
{
	t[i] = k % 256;
	t[i + 1] = k / 256 % 256;
	t[i + 2] = k / 256 / 256 % 256;
	t[i + 3] = k / 256 / 256 / 256;
}

static void		filehead(int fd, t_a *a)
{
	int		i;
	char	t[14];

	i = -1;
	while (++i < 14)
		t[i] = 0;
	t[0] = 66;
	t[1] = 77;
	t[10] = 54;
	add_to_bit(t, 2, a->rend.y * a->rend.x);
	write(fd, t, 14);
}

static void		infohead(int fd, t_a *a)
{
	int		i;
	char	t[40];

	i = -1;
	while (++i < 40)
		t[i] = 0;
	t[0] = 40;
	t[12] = 1;
	t[14] = 32;
	add_to_bit(t, 4, a->rend.x);
	add_to_bit(t, 8, a->rend.y);
	write(fd, t, 40);
}

static void		color_table(int fd, t_a *a)
{
	int y;
	int x;

	y = a->rend.y;
	while (y-- && (x = -1))
		while (++x < a->rend.x)
			write(fd, (a->img.addr + (y * a->img.ll + x * (a->img.bp / 8))), 4);
}

int				create_bmp(t_a *a)
{
	int fd;

	if ((fd = open(BMP, O_CREAT | O_TRUNC | O_RDWR, 0644)) <= 0)
		return (error(1));
	filehead(fd, a);
	infohead(fd, a);
	color_table(fd, a);
	close(fd);
	return (0);
}

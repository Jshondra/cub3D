/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:26:49 by jshondra          #+#    #+#             */
/*   Updated: 2021/03/07 18:26:52 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			get_data_tex(t_a *a)
{
	if (!(a->t[0].i = MXPM(a->win.mlx, a->no.n, &a->t[0].w, &a->t[0].h)) ||
	!(a->t[0].addr = ADR(a->t[0].i, &a->t[0].bp, &a->t[0].ll, &a->t[0].end)))
		error(11);
	if (!(a->t[1].i = MXPM(a->win.mlx, a->no.s, &a->t[1].w, &a->t[1].h)) ||
	!(a->t[1].addr = ADR(a->t[1].i, &a->t[1].bp, &a->t[1].ll, &a->t[1].end)))
		error(11);
	if (!(a->t[2].i = MXPM(a->win.mlx, a->no.w, &a->t[2].w, &a->t[2].h)) ||
	!(a->t[2].addr = ADR(a->t[2].i, &a->t[2].bp, &a->t[2].ll, &a->t[2].end)))
		error(11);
	if (!(a->t[3].i = MXPM(a->win.mlx, a->no.e, &a->t[3].w, &a->t[3].h)) ||
	!(a->t[3].addr = ADR(a->t[3].i, &a->t[3].bp, &a->t[3].ll, &a->t[3].end)))
		error(11);
	if (!(a->t[4].i = MXPM(a->win.mlx, a->no.sprite, &a->t[4].w, &a->t[4].h)) ||
	!(a->t[4].addr = ADR(a->t[4].i, &a->t[4].bp, &a->t[4].ll, &a->t[4].end)))
		error(11);
}

int				newcub(t_a *a)
{
	double	z[a->rend.x];
	int		g;
	int		x;

	g = 0;
	x = 0;
	a->img.img = mlx_new_image(a->win.mlx, a->rend.x, a->rend.y);
	a->img.addr = ADR(a->img.img, &a->img.bp, &a->img.ll, &a->img.end);
	ft_clean_window(a, 0, 0);
	while (x < a->rend.x)
	{
		x = init(a, x);
		if (a->ray.side == 0)
			g = choose_side(a, g);
		else
			g = choose_side1(a, g);
		draw_walls(a, x, g);
		z[x] = a->ray.wd;
		x++;
	}
	ft_sprites(a, z);
	a->save && !(create_bmp(a)) ? key_press(53, a->win.mlx) : 0;
	mlx_put_image_to_window(a->win.mlx, a->win.win, a->img.img, 0, 0);
	return (1);
}

void			print_map(t_a *a)
{
	a->win.mlx = mlx_init();
	a->win.win = mlx_new_window(a->win.mlx, a->rend.x, a->rend.y, "Cub3D");
	a->img.img = mlx_new_image(a->win.mlx, a->rend.x, a->rend.y);
	a->img.addr = ADR(a->img.img, &a->img.bp, &a->img.ll, &a->img.end);
	get_data_tex(a);
	newcub(a);
	mlx_hook(a->win.win, 2, 0, key_press, a);
	mlx_hook(a->win.win, 17, 0, ft_close, a);
	mlx_loop_hook(a->win.mlx, (newcub), a);
	mlx_loop(a->win.mlx);
}

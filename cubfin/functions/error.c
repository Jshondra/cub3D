/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:24:31 by jshondra          #+#    #+#             */
/*   Updated: 2021/03/07 18:25:31 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		error(int i)
{
	if (i == 1)
		write(1, "Error\nShould be only one player!\n", 6 + 28);
	else if (i == 2)
		write(1, "Error\nNot valid map!\n", 6 + 16);
	else if (i == 3)
		write(1, "Error\nWrong symbol on the map!\n", 6 + 26);
	else if (i == 4)
		write(1, "Error\nWrong info format about resolution!\n", 6 + 37);
	else if (i == 5)
		write(1, "Error\nWrong info format about ceil!\n", 6 + 31);
	else if (i == 6)
		write(1, "Error\nWrong info format about floor!\n", 6 + 32);
	else if (i == 7)
		write(1, "Error\nNot valid format info!\n", 6 + 24);
	else if (i == 8)
		write(1, "Error\nCan't open the file!\n", 6 + 22);
	else if (i == 9)
		write(1, "Error\nWrong file name!\n", 6 + 18);
	else if (i == 10)
		write(1, "Error\nCan't allocate the memory!\n", 6 + 28);
	else if (i == 11)
		write(1, "Error\nNot valid texture!\n", 6 + 20);
	exit(0);
	return (0);
}

int		error_2(int i)
{
	if (i == 1)
		write(1, "Error\nWrong arguments!\n", 24);
	// else if (i == 2)
	// 	write(1, "Error\nNot valid map!\n", 6 + 16);
	else if (i == 3)
		write(1, "Error\nWrong symbol on the map!\n", 6 + 26);
	else if (i == 4)
		write(1, "Error\nWrong info format about resolution!\n", 6 + 37);
	else if (i == 5)
		write(1, "Error\nWrong info format about ceil!\n", 6 + 31);
	else if (i == 6)
		write(1, "Error\nWrong info format about floor!\n", 6 + 32);
	else if (i == 7)
		write(1, "Error\nNot valid format info!\n", 6 + 24);
	else if (i == 8)
		write(1, "Error\nCan't open the file!\n", 6 + 22);
	else if (i == 9)
		write(1, "Error\nWrong file name!\n", 6 + 18);
	else if (i == 10)
		write(1, "Error\nCan't allocate the memory!\n", 6 + 28);
	else if (i == 11)
		write(1, "Error\nNot valid texture!\n", 6 + 20);
	exit(0);
	return (0);
}

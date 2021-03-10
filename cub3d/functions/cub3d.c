/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:28:06 by jshondra          #+#    #+#             */
/*   Updated: 2021/03/07 18:28:08 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	make_map(t_list **head, int size, int save)
{
	char	**map;
	int		i;
	t_list	*tmp;
	t_a		*a;

	i = -1;
	tmp = *head;
	a = NULL;
	if ((map = ft_calloc(size + 1, sizeof(char *))) == NULL)
		error(10);
	if ((a = malloc(sizeof(t_a))) == NULL)
		error(10);
	while (tmp)
	{
		map[++i] = tmp->content;
		tmp = tmp->next;
	}
	init_some(save, a);
	i = pars_map(map, a, 0, 0);
	write(1,"here\n", 5);
	go_map(map, a, i);
	parse_sprite(a, -1, 0);
	print_map(a);
}

int		open_file(char *name, int *fd, int i)
{
	if ((*fd = open(name, O_RDONLY)) <= 0)
		error(8);
	while (name[i] && name[i] != '.')
		i++;
	if (!name[i] || !i || ft_strncmp(&name[i], ".cub", 4)
	|| !next(i + 4, &name[i]))
	{
		close(*fd);
		error(9);
	}
	return (0);
}

void	parser(int *fd, int save)
{
	char	*line;
	t_list	*head;
	int		j;
	int		i;

	j = 0;
	i = 0;
	head = NULL;
	line = NULL;
	while ((j = get_next_line(*fd, &line)) > 0)
	{	
		ft_lstadd_back(&head, ft_lstnew(line));
		i++;
	}
	if (i == 0 && j == 0)
		{
			close(*fd);
			error_2(5);
		}
	ft_lstadd_back(&head, ft_lstnew(line));
	make_map(&head, ft_lstsize(head), save);
	free(line);
	close(*fd);
}

int		main(int argc, char **argv)
{
	int	fd;
	int	save;

	save = 0;
	if (argc > 3)
		error_2(1);
	open_file(argv[1], &fd, 0);
	if (argc == 3)
		if (argv[2] &&
		!ft_strncmp(argv[2], "--save", ft_strlen(argv[2])))
			save = 1;
	if (argc == 3 && save != 1)
		error_2(1);
	parser(&fd, save);
	return (0);
}


#include "libft/libft.h"

#include <stdio.h>
#include "cub3D.h"
#include <unistd.h>
#include <mlx.h>

int		error(int i)
{
	if (i == 1)
		write(1, "Should be only one player!\n", 28);
	else if (i == 2)
		write(1, "Not valid map!\n", 16);
	else if (i == 3)
		write(1, "Wrong symbol on the map!\n", 26);
	else if (i == 4)
		write(1, "Wrong info format about resolution!\n", 37);
	else if (i == 5)
		write(1, "Wrong info format about ceil!\n", 31);
	else if (i == 6)
		write(1, "Wrong info format about floor!\n", 32);
	else if (i == 7)
		write(1, "Not valid format info!\n", 24);
	else if (i == 8)
		write(1, "Can't open the file!\n", 22);
	else if (i == 9)
		write(1, "Wrong file name!\n", 18);
	else if (i == 10)
		write(1, "Can't allocate the memory!\n", 28);
	else if (i == 11)
		write(1, "Not valid texture!\n", 20);
	exit(0);
	return (0);
}

int		error_2(int i)
{
	if (i == 1)
		write(1, "Too many arguments!\n", 28);
	else if (i == 2)
		write(1, "Not valid map!\n", 16);
	else if (i == 3)
		write(1, "Wrong symbol on the map!\n", 26);
	else if (i == 4)
		write(1, "Wrong info format about resolution!\n", 37);
	else if (i == 5)
		write(1, "Wrong info format about ceil!\n", 31);
	else if (i == 6)
		write(1, "Wrong info format about floor!\n", 32);
	else if (i == 7)
		write(1, "Not valid format info!\n", 24);
	else if (i == 8)
		write(1, "Can't open the file!\n", 22);
	else if (i == 9)
		write(1, "Wrong file name!\n", 18);
	else if (i == 10)
		write(1, "Can't allocate the memory!\n", 28);
	else if (i == 11)
		write(1, "Not valid texture!\n", 20);
	exit(0);
	return (0);
}

void		parse_sprite(t_a *a, int i, int j)
{
	int l;

	l = 0;
	if (!(a->s.buf = (t_sprt*)malloc(sizeof(t_sprt) * a->s.count)))
		error(10);
	while (a->only_m[++i])
	{
		j = -1;
		while (a->only_m[i][++j])
			if (a->only_m[i][j] == '2')
			{
				a->s.buf[l].y = (double)(i + 0.5);
				a->s.buf[l].x = (double)(j + 0.5);
				l++;
			}
	}
}

int		skip_space(char *str, int i)
{
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	return (i);
}

int		rgb_to_int_f(t_a *a)
{
	a->F.r > 255 ? a->F.r = 255 : 0;
	a->F.g > 255 ? a->F.g = 255 : 0;
	a->F.b > 255 ? a->F.b = 255 : 0;
	return ((int)a->F.r * 65536 + (int)a->F.g * 256 + (int)a->F.b);
}

int		rgb_to_int_c(t_a *a)
{
	a->C.r > 255 ? a->C.r = 255 : 0;
	a->C.g > 255 ? a->C.g = 255 : 0;
	a->C.b > 255 ? a->C.b = 255 : 0;
	return ((int)a->C.r * 65536 + (int)a->C.g * 256 + (int)a->C.b);
}

void	we_pos(t_a *a)
{
	a->p.dirX = -1.0;
	a->p.dirY = 0.0;
	a->p.planeX = 0.0;
	a->p.planeY = -0.70;
	a->only_m[(int)a->p.y][(int)a->p.x] = '0';
}

void	ea_pos(t_a *a)
{
	a->p.dirX = 1.0;
	a->p.dirY = 0.0;
	a->p.planeX = 0.0;
	a->p.planeY = 0.70;
	a->only_m[(int)a->p.y][(int)a->p.x] = '0';
}

void	so_pos(t_a *a)
{
	a->p.dirX = 0.0;
	a->p.dirY = 1.0;
	a->p.planeX = -0.70;
	a->p.planeY = 0.0;
	a->only_m[(int)a->p.y][(int)a->p.x] = '0';
}

void	no_pos(t_a *a)
{
	a->p.dirX = 0.0;
	a->p.dirY = -1.0;
	a->p.planeX = 0.70;
	a->p.planeY = 0.0;
	a->only_m[(int)a->p.y][(int)a->p.x] = '0';
}

int		check_view(t_a *a, int i, int j)
{
	a->p.x = j + 0.5;
	a->p.y = i + 0.5;
	if (a->only_m[i][j] == 'E')
		ea_pos(a);
	else if (a->only_m[i][j] == 'W')
		we_pos(a);
	else if (a->only_m[i][j] == 'S')
		so_pos(a);
	else if (a->only_m[i][j] == 'N')
		no_pos(a);
	a->flag++;
	if (a->flag > 1 || a->flag == 0)
		error(1);
	return (1);
}

int		parse_player(t_a *a, int i, int j)
{
	if (i == 0 || j == 0)
		error(2);
	if (!(a->only_m[i][j + 1]) || !(a->only_m[i + 1][j])
		|| !(a->only_m[i - 1][j]) || !(a->only_m[i][j - 1]))
		error(2);
	if ((a->only_m[i][j + 1]) == ' ' || (a->only_m[i + 1][j]) == ' '
		|| (a->only_m[i - 1][j]) == ' ' || (a->only_m[i][j - 1]) == ' ')
		error(2);
	if ((int)ft_strlen(a->only_m[i - 1]) < j)
		error(2);
	if (ft_strchr("NSEW", a->only_m[i][j]))
		check_view(a, i, j);
	return (1);
}

void		valid_map(t_a *a, int i, int j)
{
	while (a->only_m[++i])
	{
		j = 0;
		while (a->only_m[i][j])
		{
			if (ft_strchr("NSEW", a->only_m[i][j]) || a->only_m[i][j] == '0')
			{
				parse_player(a, i, j);
				j++;
			}
			else if (a->only_m[i][j] == '1' || a->only_m[i][j] == ' ' ||
			a->only_m[i][j] == '\n')
				j++;
			else if (a->only_m[i][j] == '2')
			{
				a->s.count++;
				j++;
			}
			else
				error(3);
		}
	}
}

void		go_map(char **map, t_a *a)
{
	int i;
	int j;
	int flag;

	i = 0;
	j = 0;
	flag = 0;
	while (map[i][0] != '1' && map[i][0] != ' ' && map[i][0] != '0')
	{
		if (!map[i][0])
		{
			i++;
			continue ;
		}
		i++;
	}
	a->only_m = &map[i];
	a->s.count = 0;
	a->flag = 0;
	valid_map(a, -1, 0);
}

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
	a->C.r = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	if (map[j] != ',')
		error(6);
	j = skip_space(map, (j + 1));
	a->C.g = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	if ((map[j]) != ',')
		error(6);
	j = skip_space(map, j + 1);
	a->C.b = ft_atoi(&map[j]);
	printf("\n%d", a->F.b);
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
	a->F.r = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	if (map[j] != ',')
		error(6);
	j = skip_space(map, (j + 1));
	a->F.g = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	if ((map[j]) != ',')
		error(6);
	j = skip_space(map, j + 1);
	a->F.b = ft_atoi(&map[j]);
	printf("\n%d", a->F.b);
	return (1);
}

int		helper(char **map, t_a *a, int flag, int i)
{
	if (map[i][0] == 'N')
		a->NO.n = &(map[i][3]);
	else if (map[i][0] == 'W')
		a->NO.w = &(map[i][3]);
	else if (map[i][0] == 'E')
		a->NO.e = &(map[i][3]);
	else if (map[i][0] == 'S' && map[i][1] == ' ')
		a->NO.sprite = &(map[i][2]);
	else
		a->NO.s = &(map[i][3]);
	flag++;
	return (flag);
}

int		helper1(char **map, t_a *a, int flag, int i)
{
	if (map[i][0] == 'C')
		parse_c(map[i], a, 0);
	else
		parse_f(map[i], a, 0);
	flag++;
	return (flag);
}

void		pars_map(char **map, t_a *a, int i, int flag)
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

void	make_map(t_list **head, int size, int save)
{
	char	**map;
	int		i;
	t_list	*tmp;
	t_a		*a;

	i = -1;
	tmp = *head;
	a = NULL;
	if (save == 1)
		a->save = 1;
	if ((map = ft_calloc(size + 1, sizeof(char *))) == NULL)
		error(10);
	if ((a = malloc(sizeof(t_a))) == NULL)
		error(10);
	while (tmp)
	{
		map[++i] = tmp->content;
		tmp = tmp->next;
	}
	a->save = 0;
	pars_map(map, a, 0, 0);
	go_map(map, a);
	parse_sprite(a, -1, 0);
	print_map(a);
}

int		next(int i, char *s1)
{
	if (!s1[i])
		return (0);
	return (1);
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

	head = NULL;
	line = NULL;
	while (get_next_line(*fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
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
	if (argv[2] && !ft_strncmp(argv[2], "--save", ft_strlen(argv[2])))
		save = 1;
	printf("%d save = ", save);
	parser(&fd, save);
	return (0);
}

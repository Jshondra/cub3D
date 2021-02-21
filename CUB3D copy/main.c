
#include "libft/libft.h"

#include <stdio.h>
#include "parsing.h"
#include <unistd.h>
#include <mlx.h>

int         print_map(t_all *all);
void        my_mlx_pixel_put(t_all *all, int x, int y, int color);


int parse_sprite(t_all *all, int i, int j)
{
	int l;

	l = 0;
	 if (!(all->sprite.buf = (t_sprt*)malloc(sizeof(t_sprt) *
		all->sprite.count)))
    return (666);
	while(all->only_m[++i])
	{
		j = -1;
		while(all->only_m[i][++j])
			if (all->only_m[i][j] == '2')
			{
				all->sprite.buf[l].y = (double)(i + 0.5);
				all->sprite.buf[l].x  = (double)(j + 0.5);
				l++;
			}
	}
	printf ("\n%d\n", all->sprite.count);
	for (i = 0; i < all->sprite.count; i++){
		             printf ("\n%f\n, %f", all->sprite.buf[i].x, all->sprite.buf[i].y);
     }
    return 0;
}

int skip_space(char *str, int i)
{
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	return(i);
}
int		rgb_to_int_f(t_all *all)
{
	all->F.r > 255 ? all->F.r = 255 : 0;
	all->F.g > 255 ? all->F.g = 255 : 0;
	all->F.b > 255 ? all->F.b = 255 : 0;
	return ((int)all->F.r * 65536 + (int)all->F.g * 256 + (int)all->F.b);
}


int		rgb_to_int_c(t_all *all)
{
	all->C.r > 255 ? all->C.r = 255 : 0;
	all->C.g > 255 ? all->C.g = 255 : 0;
	all->C.b > 255 ? all->C.b = 255 : 0;
	return ((int)all->C.r * 65536 + (int)all->C.g * 256 + (int)all->C.b);
}

void we_pos(t_all *all, int i, int j)
{
	all->plr.dirX = -1.0;
	all->plr.dirY = 0.0;
	all->plr.planeX = 0.0;
	all->plr.planeY = -0.70;
	all->only_m[(int)all->plr.y][(int)all->plr.x] = '0';
}

void ea_pos(t_all *all, int i, int j)
{
	all->plr.dirX = 1.0;
	all->plr.dirY = 0.0;
	all->plr.planeX = 0.0;
	all->plr.planeY = 0.70;
	all->only_m[(int)all->plr.y][(int)all->plr.x] = '0';
}

void so_pos(t_all *all, int i, int j)
{
	all->plr.dirX = 0.0;
	all->plr.dirY = 1.0;
	all->plr.planeX = -0.70;
	all->plr.planeY = 0.0;
	
	all->only_m[(int)all->plr.y][(int)all->plr.x] = '0';
}

void no_pos(t_all *all, int i, int j)
{
	all->plr.dirX = 0.0;
	all->plr.dirY = -1.0;
	all->plr.planeX = 0.70;
	all->plr.planeY = 0.0;
	all->only_m[(int)all->plr.y][(int)all->plr.x] = '0';
}

int check_view(t_all *all, int i, int j, int flag)
{
	all->plr.x = j + 0.5;
	all->plr.y = i + 0.5;
	if (all->only_m[i][j] == 'E')//ea
		ea_pos(all, i, j);
	else if (all->only_m[i][j] == 'W')//w
		we_pos(all, i, j);
	else if (all->only_m[i][j] == 'S')//s
		so_pos(all, i, j);
	else if (all->only_m[i][j] == 'N')//s
		no_pos(all, i, j);
	if (flag > 1 || flag == 0)
		return (988);
	return (1);
}

int		parse_player(t_all *all, int i, int j)
{
	int flag;

	flag = 0;
	if (i == 0 || j == 0)
		return (888);
	if (!(all->only_m[i][j + 1]) || !(all->only_m[i + 1][j])
		|| !(all->only_m[i - 1][j]) || !(all->only_m[i][j - 1]))
		return (755);
	if ((all->only_m[i][j + 1]) == ' ' || (all->only_m[i + 1][j]) == ' '
		|| (all->only_m[i - 1][j]) == ' ' || (all->only_m[i][j - 1]) == ' ')
		return (755);
	if (ft_strlen(all->only_m[i - 1]) < j)
		return (666);
	if (ft_strchr("NSEW",all->only_m[i][j]))
		check_view(all,i, j, ++flag);
	return (1);
}

int valid_map(t_all *all, int i, int j)
{
	while(all->only_m[++i])
	{
		j = 0;
		while(all->only_m[i][j])
		{
			if (ft_strchr("NSEW", all->only_m[i][j]) || all->only_m[i][j] == '0') 
				{
					if ((parse_player(all, i, j)) != 1 && j++)
						return (888);
					j++;
				}
			else if (all->only_m[i][j] == '1' || all->only_m[i][j] == ' '
				|| all->only_m[i][j] == '\n')
				j++;
			else if (all->only_m[i][j] == '2')
			{
				all->sprite.count++;
				j++;
			}
			else
			return (999);
		}
	}
	i = 0;
	return (555);
}

int		go_map(char **map, t_all *all)
{
	int i = 0;
	int j = 0;
	int flag = 0;

	while (map[i][0] != '1' && map[i][0] != ' ' && map[i][0] != '0')
	{
		if (!map[i][0])
		{
			i++;
			continue ;
		}
		i++;
	}
	all->only_m = &map[i];
	all->sprite.count = 0;
	return(valid_map(all, -1, 0));
}


int		parse_r(char *map, t_all *all)
{
	int j = 1;

	if (ft_strlen(&map[j]) < 6)
		return (666);
	all->rend.x = ft_atoi(&map[j]);
	j += 2;
	while (ft_isdigit(map[j]))
		j++;
	if (map[j] != ' ')
		return (666);
	j++;
	all->rend.y = ft_atoi(&(map[j]));
	if ((all->rend.x) < 0 || (all->rend.y) < 0)
		return (666);
	return (1);
}


int parse_c(char *map, t_all *all, int j)
{
	while (map[++j])
		if ((map[j] > '9' || map[j] < '0')
			&& (map[j] != ',' && map[j] != ' '))
			return (999);
	if (j < 5)
		return (669);
	j = skip_space(map, 1);
	all->C.r = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	if (map[j] != ',')
		return (6699);
	j = skip_space(&map[j], (j + 1));
	all->C.g = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	if ((map[j]) != ',')
		return (664);
	j = skip_space(&map[j], j + 1);
	all->C.b = ft_atoi(&map[j]);
	return (1);
}


int parse_f(char *map, t_all *all, int j)
{
	while (map[++j])
		if ((map[j] > '9' || map[j] < '0')
			&& (map[j] != ',' && map[j] != ' '))
			return (999);
	if (j < 5)
		return (669);
	j = skip_space(map, 1);
	all->F.r = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	if (map[j] != ',')
		return (6699);
	j = skip_space(&map[j], (j + 1));
	all->F.g = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	if ((map[j]) != ',')
		return (664);
	j = skip_space(&map[j], j + 1);
	all->F.b = ft_atoi(&map[j]);
	return (1);
}

int help_pars(char **map, t_all *all, int i)
{
	int flag = 0;

	 	if ((ft_strncmp(map[i], "NO ", 3)) == 0)
			all->NO.p = &(map[i][3]);
		else if ((ft_strncmp((map[i]), "WE ", 3) == 0))
			all->WE.p = &(map[i][3]);
		else if ((ft_strncmp((map[i]), "EA ", 3) == 0))
			all->EA.p = &(map[i][3]);
		else if ((ft_strncmp((map[i]), "SO ", 3) == 0)) 
			(all->SO.p) = &(map[i][3]);
		else if ((ft_strncmp((map[i]), "F ", 2) == 0))
		{
			if ((flag = parse_f(map[i],all, 1)) != 1)
				return(flag);
		}
		else if ((ft_strncmp(map[i], "S ", 2) == 0))
			all->S.s = &(map[i][2]);
		return (1);
}


int		pars_map(char **map, t_all *all)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (map[i][0] != '1' && map[i][0] != ' ' && map[i][0] != '0')
	{
		if (!map[i][0])
		{	
				i++;
			continue ;
		}
		if (!(ft_strncmp(map[i], "R ", 2)))
		{
			if ((flag = parse_r(map[i], all)) != 1)
				return (flag);
		}
		// else if ((help_pars(map, all, i)) != 1)
		// 	return (999);
		else if (!(ft_strncmp((map[i]), "NO ", 3)))
			all->NO.p = &(map[i][3]);
		else if ((ft_strncmp((map[i]), "WE ", 3) == 0))
			all->WE.p = &(map[i][3]);
		else if ((ft_strncmp((map[i]), "EA ", 3) == 0))
			all->EA.p = &(map[i][3]);
		else if ((ft_strncmp((map[i]), "SO ", 3) == 0)) 
			(all->SO.p) = &(map[i][3]);
		else if ((ft_strncmp((map[i]), "F ", 2) == 0))
		{
			if ((flag = parse_f(map[i],all, 1)) != 1)
				return(flag);
		}
		else if ((ft_strncmp(map[i], "S ", 2) == 0))
			all->S.s = &(map[i][2]);
		else if ((ft_strncmp(map[i], "C", 1) == 0))
		{
			if ((flag = parse_c(map[i], all, 1)) != 1)
				return(flag);
		}
		else
			return (601);
		i++;
	}
		printf("%s, %d, %d, %d, %d, %d, %s, %s, %s, %s, %d, %d, %d",all->S.s, all->rend.x,all->rend.y,all->F.r,all->F.g,all->F.b,all->EA.p,all->NO.p,all->SO.p,all->WE.p, all->C.r,all->C.g,all->C.b);
		return (1);
}

char	**make_map(t_list **head, int size, int save)
{
	char	  **map; 
	int		  i = -1;
	t_list	*tmp; 
	int j = 777;
	t_all *all;

	tmp = *head;
	if ((map = ft_calloc(size + 1, sizeof(char *))) == NULL)
		return (map);
	if ((all = malloc(sizeof(t_all))) == NULL)
		return (map);
	while (tmp)
	{
		map[++i] = tmp->content;
		tmp = tmp->next;
	}
	j = pars_map(map, all);
	printf("\n%d\n", j);
	j = go_map(map, all);
	parse_sprite(all, -1, 0);
	printf("\n%d\n", j);
	print_map(all);
	return (map);
}

int next(int i, char *s1)
{
	if (!s1[i])
		return (0);
	return (1);
}

static int		open_file(char *name, int *fd, int i)
{
	if ((*fd = open(name, O_RDONLY)) <= 0)
		return (-1);
	while (name[i] != '.' && name[i])
		i++;
	if (!name[i] || (!i || ft_strncmp(&name[i], ".cub", 4))
		|| (next(i + 4, &name[i])))
	{
		close(*fd);
		return ((-2));
	}
	return (1);
}

void  parser(int *fd, int save)
{
	char	  *line = NULL;
	t_list	*head = NULL;

	while (get_next_line(*fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	make_map(&head, ft_lstsize(head), save);
	free(line);
	close(*fd);
}

int		main(int argc, char **argv)
{
	int      fd;
	// char	  *line = NULL;
	// t_list	*head = NULL;
	int save;

	save = 0;
	if (argc > 3)
		return (9);
	if (open_file(argv[1], &fd, 0) != 1)
		return (0);
	if (argv[2] && !ft_strncmp(argv[2], "--save", ft_strlen(argv[2])))
	 	save = 1;
	printf("%d save = ", save);
	parser(&fd, save);
	return (0);
}

#include "libft/libft.h"

#include <stdio.h>
#include "parsing.h"
#include <unistd.h>
#include <mlx.h>

int         print_map(t_all *all);
void        my_mlx_pixel_put(t_all *all, int x, int y, int color);

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
	all->plr.dirX = 1.0;
	all->plr.dirY = 0.0;
	all->plr.planeX = 0.0;
	all->plr.planeY = -0.70;
	all->only_m[(int)all->plr.y][(int)all->plr.x] = '0';
}

void ea_pos(t_all *all, int i, int j)
{
	all->plr.dirX = -1.0;
	all->plr.dirY = 0.0;
	all->plr.planeX = 0.0;
	all->plr.planeY = 0.70;
	all->only_m[(int)all->plr.y][(int)all->plr.x] = '0';
}

void so_pos(t_all *all, int i, int j)
{
	all->plr.dirX = 0.0;
	all->plr.dirY = 1.0;
	all->plr.planeX = 0.70;
	all->plr.planeY = 0.0;
	
	all->only_m[(int)all->plr.y][(int)all->plr.x] = '0';
}

void no_pos(t_all *all, int i, int j)
{
	all->plr.dirX = 0.0;
	all->plr.dirY = -1.0;
	all->plr.planeX = -0.70;
	all->plr.planeY = 0.0;
	all->only_m[(int)all->plr.y][(int)all->plr.x] = '0';
}

void check_view(t_all *all, int i, int j)
{
	if (all->only_m[i][j] == 'E')//ea
		ea_pos(all, i, j);
	else if (all->only_m[i][j] == 'W')//w
		we_pos(all, i, j);
	else if (all->only_m[i][j] == 'S')//s
		so_pos(all, i, j);
	else if (all->only_m[i][j] == 'N')//s
		no_pos(all, i, j);
}

int		parse_player(t_all *all, int i, int j)
{

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
	{
		all->plr.x = j;
		all->plr.y = i;
		check_view(all,i, j);
	}
	return (1);
}

int		valid_map(char **map, t_all *all)
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
	i = 0;
	while (all->only_m[i])
	{
		ft_putendl(all->only_m[i]);
		i++;
	}
	i = 0;
	while(all->only_m[i])
	{
		j = 0;
		while(all->only_m[i][j])
		{
	
			if (ft_strchr("NSEW", all->only_m[i][j])) 
				{
					printf("\n%d\n",j);
					if ((parse_player(all, i, j)) != 1)
						return (888);
					all->plr.x = i + 0.5;
					all->plr.y = j + 0.5;
					j++;
					flag++;
				}
			else if (all->only_m[i][j] == '1')
				j++;
			else if (all->only_m[i][j] == '0')
			{
				if ((parse_player(all, i, j)) != 1)
						return (879);
				j++;
			}
			
			else if (all->only_m[i][j] == '2')
				j++;
			else if (all->only_m[i][j] == ' ')
				j++;
			else if (all->only_m[i][j] == '\n')
				j++;
			else
				return (999);
		}
		i++;
	}
	if (flag > 1 || flag == 0)
			return (989);
	i = 0;
/*	while (all->only_m[i])
	{
		ft_putendl(all->only_m[i]);
		i++;
	}
	printf("\n%f\n%f",all->plr.x,all->plr.y);*/
	return (555);
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


int parse_c(char *map, t_all *all)
{
	int j = 1;

	if (ft_strlen(map) < 7)
		return (669);
	all->C.r = ft_atoi(&map[j]);
	j += 2;
	while (ft_isdigit(map[j]))
		j++;
	if (all->C.r > 255 || all->F.r < 0)
		return (668);
	if (map[j] != ',')
		return (6699);
	j++;
	all->C.g = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	if (all->C.g > 255 || all->F.g < 0)
		return (665);
	if ((map[j]) != ',')
		return (664);
	j++;
	all->C.b = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	if (all->C.b > 255 || all->F.b < 0)
		return (663);
	return (1);
}


int parse_f(char *map, t_all *all)
{
	int j;

	j = 1;
	if (ft_strlen(map) < 7 || ft_strlen(map) > 13)
		return (669);
	all->F.r = ft_atoi(&map[1]);
	j += 2;
	while (ft_isdigit(map[j]))
		j++;
	if (all->F.r > 255 || all->F.r < 0)
		return (668);
	if (map[j] != ',')
		return (6699);
	j++;
	all->F.g = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	if (all->F.g > 255 || all->F.g < 0)
		return (665);
	if ((map[j]) != ',')
		return (664);
	j++;
	all->F.b = ft_atoi(&map[j]);
	while (ft_isdigit(map[j]))
		j++;
	if (all->F.b > 255 || all->F.b < 0)
		return (663);
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
			if ((flag = parse_f(map[i],all)) != 1)
				return(flag);
		}
		else if ((ft_strncmp(map[i], "S ", 2) == 0))
			all->S.s = &(map[i][2]);
		else if ((ft_strncmp(map[i], "C", 1) == 0))
		{
			if ((flag = parse_c(map[i], all)) != 1)
				return(flag);
		}
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
		//else if ((help_pars(map, all, i)) != 1)
			//return (999);
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
			if ((flag = parse_f(map[i],all)) != 1)
				return(flag);
		}
		else if ((ft_strncmp(map[i], "S ", 2) == 0))
			all->S.s = &(map[i][2]);
		else if ((ft_strncmp(map[i], "C", 1) == 0))
		{
			if ((flag = parse_c(map[i], all)) != 1)
				return(flag);
		}
		else
			return (601);
		i++;
	}
		printf("%d, %d, %d, %d, %d, %s, %s, %s, %s, %d, %d, %d",all->rend.x,all->rend.y,all->F.r,all->F.g,all->F.b,all->EA.p,all->NO.p,all->SO.p,all->WE.p, all->C.r,all->C.g,all->C.b);
		return (1);
}

char	**make_map(t_list **head, int size)
{
	char	  **map = ft_calloc(size + 1, sizeof(char *));
	int		  i = -1;
	t_list	*tmp = *head;
	int j = 777;
	t_all  *all;

	all = malloc(sizeof(t_all));
	while (tmp)
	{
		map[++i] = tmp->content;
		tmp = tmp->next;
	}
	j = pars_map(map, all);
	printf("\n%d\n", j);
	j = valid_map(map, all);
	printf("\n%d\n", j);
	print_map(all);
	
	return (map);
}

int		main(int argc, char **argv)
{
	int      fd;
	char	  *line = NULL;
	t_list	*head = NULL;

	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	while (get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	make_map(&head, ft_lstsize(head));
	free(line);
	close(fd);
}
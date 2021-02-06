/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:35:13 by jshondra          #+#    #+#             */
/*   Updated: 2020/11/16 20:48:08 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		frv(int byte, char *re)
{
	if (byte < 0)
		return (-1);
	else if (byte == 0 && !(*re))
		return (0);
	if (byte || ft_strlen(re))
		return (1);
	return (0);
}

void	proverka(char **point, char **buf, char **line, char *re)
{
	char	*tmp;

	if ((*point = ft_strchr(*buf, '\n')))
	{
		**point = '\0';
		*point += 1;
		ft_strcpy(re, *point);
	}
	tmp = *line;
	*line = ft_strjoin(*line, *buf);
	free(tmp);
}

size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

char	*check_re(char *re, char **line)
{
	char *point;

	point = NULL;
	*line = ft_strdup("");
	if (re)
	{
		if ((point = ft_strchr(re, '\n')))
		{
			*point = '\0';
			free(*line);
			*line = ft_strdup(re);
			ft_strcpy(re, ++point);
		}
		else
		{
			free(*line);
			*line = ft_strdup(re);
			*re++ = '\0';
		}
	}
	return (point);
}

int		get_next_line(int fd, char **line)
{
	char			*buf;
	int				byte;
	char			*point;
	static char		re[1 + 1];

	buf = NULL;
	if (fd < 0 || 1 < 1
			|| fd > 1024 || read(fd, buf, 0) < 0 || !line)
		return (-1);
	if (!(point = check_re(re, line)))
	{
		if (!(buf = malloc(1 + 1)))
			return (-1);
		while (!point && (byte = read(fd, buf, 1)))
		{
			buf[byte] = '\0';
			proverka(&point, &buf, line, &re[0]);
		}
		free(buf);
		return (frv(byte, re));
	}
	free(buf);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 16:26:50 by jshondra          #+#    #+#             */
/*   Updated: 2020/11/16 20:46:23 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *c)
{
	int		i;
	char	*src;

	i = 0;
	while (c[i])
		i++;
	if ((src = malloc(i + 1)) != NULL)
	{
		i = 0;
		while (c[i])
		{
			src[i] = c[i];
			i++;
		}
		src[i] = '\0';
	}
	return (src);
}

char	*ft_strchr(const char *s, int ch)
{
	char			*str;

	str = (char*)s;
	while (*str)
	{
		if (*str == ch)
			return (str);
		str++;
	}
	if (ch == '\0')
		return (str);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;
	int		n;

	if ((!s1) || (!s2))
		return (NULL);
	i = ft_strlen(s1);
	n = ft_strlen(s2);
	j = 0;
	if ((str = malloc(n + i + 1)) != NULL)
	{
		while (i > 0)
		{
			str[j] = s1[j];
			j++;
			i--;
		}
		i = -1;
		while (++i < n)
			str[j++] = s2[i];
		str[j] = '\0';
	}
	return (str);
}

char	*ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

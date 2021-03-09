/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 18:15:25 by jshondra          #+#    #+#             */
/*   Updated: 2020/11/16 20:48:16 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_strdup(const char *c);
char	*ft_strchr(const char *s, int ch);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strcpy(char *dest, char *src);
int		get_next_line(int fd, char **line);
char	*check_re(char *re, char **line);
size_t	ft_strlen(char const *str);
int		frv(int byte, char *re);

#endif

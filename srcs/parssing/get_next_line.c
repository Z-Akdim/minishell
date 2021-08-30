/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:56:03 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:56:05 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void			ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (s)
		while (s[i] != '\0')
			write(fd, &s[i++], 1);
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		length;
	char		*tab;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	length = ft_strlen(&s[start]);
	if (length >= len)
		length = len;
	tab = (char *)malloc(sizeof(char) * (length + 1));
	if (!tab)
		return (0);
	while (i < length && s[start] != '\0')
		tab[i++] = s[start++];
	tab[i] = '\0';
	return (tab);
}

static	int		ft_store(char **new, int ret, char **line, int fd)
{
	char		*temp;
	int			i;

	i = 0;
	while (new[fd][i] && new[fd][i] != '\n')
		i++;
	*line = ft_substr(new[fd], 0, i);
	if (!new[fd][i])
	{
		temp = new[fd];
		new[fd] = NULL;
		free(temp);
		return (0);
	}
	else
	{
		temp = new[fd];
		new[fd] = ft_strdup((new[fd]) + i + 1);
		free(temp);
	}
	if (!new[fd] || !*line)
		return (-1);
	if (ret || (ret == 0 && new[fd] != NULL))
		return (1);
	return (-1);
}

int				get_next_line(int fd, char **line)
{
	char		*buff;
	static char	*rest[4864];
	char		*temp;
	int			ret;

	buff = NULL;
	if (!line || fd < 0 || fd >= 4864 || BUFFER_SIZE <= 0 ||
	!(buff = malloc(BUFFER_SIZE + 1)) || read(fd, buff, 0) < 0)
		return (-1);
	if (!rest[fd])
		if (!(rest[fd] = ft_strdup("")))
			return (-1);
	while (!(ft_strchr(rest[fd], '\n')) && (ret = read(fd, buff, BUFFER_SIZE)))
	{
		if (ret < 0)
			return (-1);
		temp = rest[fd];
		buff[ret] = '\0';
		if (!(rest[fd] = ft_strjoin(rest[fd], buff)))
			return (-1);
		free(temp);
	}
	free(buff);
	return (ft_store(rest, ret, line, fd));
}

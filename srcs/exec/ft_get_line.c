/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:57:58 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:58:00 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void		*ft_calloc(size_t count, size_t size)
{
	void	*hep;

	hep = (void*)malloc(count * size);
	if (hep == NULL)
		return (NULL);
	ft_bzero(hep, count * size);
	return (hep);
}

char		*get_line(char **line, int *i, int b, char **tmp)
{
	int		l;
	char	*buff;
	char	*tmp1;

	l = 1;
	buff = (char *)malloc((sizeof(char)) * BUFFER_SIZE + 1);
	*line = ft_calloc(1, 1);
	while (!ft_chr(*line, '\n') && (*i = read(1, buff, BUFFER_SIZE)) > 0)
	{
		buff[*i] = '\0';
		tmp1 = *line;
		*line = ft_strjoin(*line, buff);
		free(tmp1);
	}
	free(buff);
	if (*i < 0)
		ft_putstr_fd("error", 2);
	if (b == 2)
	{
		*tmp = clean_join(*tmp, *line);
		free(*line);
		*line = *tmp;
	}
	return (*line);
}

void		ft_ctrl_c_line(t_mini *m)
{
	if (g_v.is_ctrl_c == 100)
	{
		free(m->line);
		m->line = malloc(sizeof(char) * 1);
		m->line[0] = '\0';
		g_v.is_ctrl_c = 0;
	}
}

void		get_input(t_mini *m, int i, int b, int len)
{
	char	*tmp;

	while (b)
	{
		m->line = get_line(&m->line, &i, b, &tmp);
		ft_ctrl_c_line(m);
		if ((len = ft_strlen(m->line)) && m->line[len - 1] != '\n')
		{
			ft_putstr_fd("  \b\b", 1);
			tmp = ft_strdup(m->line);
			m->line = ft_free2(m->line);
			b = 2;
		}
		else
		{
			b = 0;
			if (len != 0)
				m->line[len - 1] = '\0';
			if (i == 0 && !len)
			{
				ft_putstr_fd("exit\n", STDERR);
				exit(0);
			}
		}
	}
}

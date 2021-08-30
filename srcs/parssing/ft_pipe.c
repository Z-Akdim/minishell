/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:22:36 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:22:39 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void				ft_check_pipe_command(t_mini *m, int i)
{
	int				j;

	j = 0;
	while (m->m_cmd[i][j])
	{
		if (m->m_cmd[i][j] == '|')
		{
			m->check_pipe = 1;
			ft_pipe(m, i);
			return ;
		}
		j++;
	}
	m->check_pipe = 0;
	m->pipe.args = malloc(sizeof(char *) * 1);
	m->pipe.args[0] = ft_strdup(m->m_cmd[i]);
	m->pipe.args[1] = NULL;
}

void				ft_free(char **tab, char *str)
{
	int				i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	free(str);
}

void				ft_error(char *error_msg, char *command, char *line)
{
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(line, 2);
}

char				*ft_itoa(int n)
{
	char			*str;
	int				numlen;
	unsigned int	nb;

	numlen = num_len(n);
	nb = n;
	if (n < 0)
	{
		nb = -n;
		numlen++;
	}
	if (!(str = malloc(numlen + 1)))
		return (0);
	str[numlen] = '\0';
	str[--numlen] = nb % 10 + '0';
	while (nb /= 10)
		str[--numlen] = nb % 10 + '0';
	if (n < 0)
		*(str) = '-';
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:22:03 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:22:09 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void		ft_dollar_init(t_mini *m)
{
	m->d.index = 0;
	m->d.i = 0;
	m->d.j = 0;
	m->d.s_quotes = 0;
	m->d.new_line = NULL;
	m->d.new_line = malloc(sizeof(char) * (ft_strlen(m->m_cmd[m->d.ret] + 1)));
}

void		ft_get_dollar_value(t_mini *m, char *str)
{
	int		k;
	int		j;
	int		index;
	char	*arg;

	k = -1;
	j = 0;
	index = 0;
	arg = ft_strjoin(str, "=");
	while (m->envp_g[++k])
		if (ft_strncmp(m->envp_g[k], arg, ft_strlen(arg)) == 0)
		{
			index = 1;
			while (m->envp_g[k][j] != '=')
				j++;
			j++;
			m->d.value = ft_strdup(&m->envp_g[k][j]);
		}
	if (index == 0)
		m->d.value = ft_strdup("NON");
	free(arg);
}

void		ft_get_dollar_value_1(t_mini *m)
{
	int		count;
	int		j;

	count = 0;
	m->d.i++;
	m->d.index = m->d.i;
	while (ft_is_alphanum(m->m_cmd[m->d.ret][m->d.i]))
	{
		m->d.i++;
		count++;
	}
	m->d.i = m->d.index;
	m->d.tmp = malloc(sizeof(char) * (count + 1));
	j = 0;
	while (m->m_cmd[m->d.ret][m->d.i] &&
	ft_is_alphanum(m->m_cmd[m->d.ret][m->d.i]))
	{
		m->d.tmp[j] = m->m_cmd[m->d.ret][m->d.i];
		j++;
		m->d.i++;
	}
	m->d.tmp[j] = '\0';
	ft_get_dollar_value(m, m->d.tmp);
	free(m->d.tmp);
}

void		ft_get_line_value(t_mini *m)
{
	int		i;
	char	*tmp;

	i = 0;
	if (m->d.value && ft_strcmp(m->d.value, "NON") != 0)
	{
		tmp = ft_strdup(m->d.new_line);
		free(m->d.new_line);
		m->d.new_line = NULL;
		m->d.new_line = ft_strjoin(tmp, m->d.value);
		free(tmp);
		i = 0;
		while (m->d.value[i])
		{
			m->d.new_line[m->d.j] = m->d.value[i];
			m->d.j++;
			i++;
		}
	}
	free(m->d.value);
}

void		ft_print_num(void)
{
	char	*num;

	num = ft_itoa(g_v.exit_status);
	ft_putstr_fd(num, 1);
	free(num);
}

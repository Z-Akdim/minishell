/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_lvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:58:40 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:58:42 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char		*ft_env_shellvl(t_mini *m)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (m->envp_g[i])
	{
		if (ft_strncmp(m->envp_g[i], "SHLVL=", 6) == 0)
		{
			while (m->envp_g[i][j] != '=')
				j++;
			j++;
			return (&m->envp_g[i][j]);
		}
		i++;
	}
	return ("0");
}

void		ft_first_lvl(t_mini *m)
{
	m->first_lvl = ft_atoi(ft_env_shellvl(m));
	m->shell_lvl = m->first_lvl;
	m->first_lvl++;
}

void		ft_add_shell_lvl(t_mini *m)
{
	char *num;
	char *arg;

	m->shell_lvl = 0;
	m->shell_lvl++;
	num = ft_itoa(m->shell_lvl);
	arg = ft_strjoin("SHLVL=", num);
	ft_strjoin2(m, arg);
	free(num);
	free(arg);
}

void		ft_shell_lvl(t_mini *m, int j, int index)
{
	char	*arg;
	char	*num;

	ft_first_lvl(m);
	while (m->envp_g[++j])
		if (ft_strncmp(m->envp_g[j], "SHLVL=", ft_strlen("SHLVL=")) == 0)
		{
			index = 1;
			m->shell_lvl++;
			num = ft_itoa(m->shell_lvl);
			arg = ft_strjoin("SHLVL=", num);
			free(m->envp_g[j]);
			m->envp_g[j] = NULL;
			m->envp_g[j] = ft_strdup(arg);
			free(num);
			free(arg);
			break ;
		}
	if (index == 0)
		ft_add_shell_lvl(m);
}

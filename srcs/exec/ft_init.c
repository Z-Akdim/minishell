/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:58:05 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:58:06 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void		ft_exit_1(t_mini *m)
{
	char	*arg;
	char	*num;
	int		j;

	j = 0;
	arg = ft_strdup("SHLVL=");
	while (m->envp_g[++j])
		if (ft_strncmp(m->envp_g[j], arg, ft_strlen(arg)) == 0)
		{
			free(m->envp_g[j]);
			m->envp_g[j] = NULL;
			free(arg);
			break ;
		}
	num = ft_itoa(m->shell_lvl);
	arg = ft_strjoin("SHLVL=", num);
	ft_strjoin2(m, arg);
	free(arg);
	free(num);
}

void		ft_exit_2(char *arg1)
{
	waitpid(-1, 0, 0);
	if ((arg1[0] < '0' || arg1[0] > '9') && arg1[0] != '-')
	{
		g_v.exit_status = 255;
		exit(255);
	}
	exit(ft_atoi(arg1));
	free(arg1);
}

void		ft_exit_3(t_mini *m)
{
	while (m->args[1][m->v.i])
	{
		if (m->args[1][m->v.i] < '0'
		|| m->args[1][m->v.i] > '9')
		{
			ft_error("exit: ", m->args[1],
			": numeric argument required\n");
			break ;
		}
		m->v.i++;
	}
}

void		ft_exit(t_mini *m)
{
	char *arg1;

	m->v.i = 0;
	m->v.j = -1;
	m->shell_lvl--;
	ft_putstr_fd("exit\n", 1);
	if (m->args[2] && m->args_num > 1)
	{
		g_v.exit_status = 1;
		arg1 = ft_strdup("0");
		ft_error("exit", ": too many argument", "\n");
	}
	else if (m->args[1])
	{
		ft_exit_3(m);
		if (m->v.i == (int)ft_strlen(m->args[1]))
			arg1 = ft_strdup(m->args[1]);
	}
	else
		arg1 = ft_strdup("0");
	if (m->shell_lvl >= m->first_lvl)
		ft_exit_1(m);
	else if (m->shell_lvl < m->first_lvl)
		ft_exit_2(arg1);
}

void		ft_init(t_mini *m)
{
	m->run_path = NULL;
	m->oldpwd = NULL;
	m->v.index = 0;
	m->v.i = 0;
	m->v.k = 0;
	m->v.j = 0;
	m->v.c = 0;
	m->v.n = 0;
	m->v.tmp = NULL;
	m->v.type = NULL;
	m->v.arg = NULL;
	m->v.correct_args = NULL;
	m->v.new_line = NULL;
}

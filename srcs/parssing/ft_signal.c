/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:23:05 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:23:07 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		skip_quots(char *str, char c, int i)
{
	int j;

	j = i + 1;
	while (str[j])
	{
		if (str[j] == c)
			return (j);
		j++;
	}
	return (j);
}

int		ft_signal(void)
{
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, ft_ctrl_anti);
	return (0);
}

void	ft_ctrl_d(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

void	ft_ctrl_c(int sig)
{
	int status;
	int wpid;

	g_v.exit_status = 1;
	g_v.is_ctrl_c = 100;
	while ((wpid = wait(&status)) > 0)
		;
	if (WTERMSIG(status) == SIGINT)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		return ;
	}
	if (sig == SIGINT)
	{
		ft_putstr_fd("\b\b  ", 1);
		ft_putstr_fd("\n\e[1;32m➜  \e[1;31mminishell\e[0;37m$ ", 1);
	}
	return ;
}

void	ft_ctrl_anti(int signum)
{
	int		status;
	char	*nbr;

	nbr = ft_itoa(signum);
	waitpid(g_v.pid, &status, 0);
	if (g_v.pid != 0)
	{
		g_v.pid = 0;
		ft_putstr_fd("\b\b", 1);
		ft_putstr_fd("QUIT : ", 1);
		ft_putstr_fd(nbr, 1);
		ft_putstr_fd("\n", 1);
		return ;
	}
	else if (g_v.pid == 0)
		ft_putstr_fd("\b\b  \b\b", 1);
	signal(signum, ft_ctrl_anti);
	free(nbr);
}

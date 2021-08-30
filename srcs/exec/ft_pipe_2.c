/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:58:17 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:58:19 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		ft_command_pipe_run_2(t_mini *m, int i)
{
	ft_init(m);
	ft_get_pipe_args(m, i);
	ft_quotes(m);
	ft_sorte_args(m);
	ft_sort_args2(m);
	ft_check_args(m);
	ft_get_path(m);
	m->redirection_error = 0;
	if (ft_check_redirection(m) == -1)
		return (-1);
	if (m->args[0][0] == '/')
		m->command = ft_strdup(m->args[0]);
	else if (m->run_path)
		m->command = ft_strdup(m->run_path);
	return (0);
}

void	ft_creat_pipe(t_mini *m)
{
	int i;

	i = 0;
	m->v.pipefds = (int *)malloc(sizeof(int) * (2 * m->pipe.num));
	while (i < m->pipe.num)
	{
		if (pipe(m->v.pipefds + i * 2) < 0)
		{
			perror("couldn't pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	ft_close_pipe(t_mini *m)
{
	int i;
	int status;

	i = 0;
	while (i < 2 * m->pipe.num)
	{
		close(m->v.pipefds[i]);
		i++;
	}
	i = 0;
	while (i < m->pipe.num + 1)
	{
		wait(&status);
		if (WIFEXITED(status))
			g_v.exit_status = WEXITSTATUS(status);
		i++;
	}
	ft_free_pipe_args(m);
	ft_free_args(m);
	free(m->v.pipefds);
}

void	ft_close_fd(t_mini *m)
{
	int i;

	i = 0;
	while (i < 2 * m->pipe.num)
	{
		close(m->v.pipefds[i]);
		i++;
	}
}

void	ft_pipe_run2(t_mini *m, int k, int j)
{
	ft_creat_pipe(m);
	while (m->pipe.args[k] != NULL)
	{
		g_v.pid = fork();
		if (g_v.pid == 0)
		{
			if (m->pipe.args[k + 1] && m->redirection == 0)
				if (dup2(m->v.pipefds[j + 1], 1) < 0)
					exit(0);
			if (j != 0)
				if (dup2(m->v.pipefds[j - 2], 0) < 0)
					exit(0);
			ft_close_fd(m);
			if (ft_command_pipe_run_2(m, k) == -1)
				break ;
			ft_command_2(m, m->command, 1);
		}
		else if (g_v.pid < 0)
			exit(0);
		k++;
		j += 2;
	}
	ft_close_pipe(m);
}

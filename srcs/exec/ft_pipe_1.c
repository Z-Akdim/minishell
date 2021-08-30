/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:58:11 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:58:13 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		ft_pipe_1(t_mini *m)
{
	int i;

	i = 0;
	ft_get_pipe_args(m, 0);
	if ((ft_strncmp(m->pipe.args[i], "cat", 3) == 0 && !m->args[1]) ||
	ft_strncmp(m->pipe.args[i], "grep", 4) == 0 ||
	ft_strncmp(m->pipe.args[i], "tail", 4) == 0 ||
	ft_strncmp(m->pipe.args[i], "head", 4) == 0 ||
	ft_strncmp(m->pipe.args[i], "sleep", 4) == 0)
	{
		m->pipe.num = ft_count_pipes(m);
		ft_pipe_run2(m, 0, 0);
		waitpid(-1, 0, 0);
		return (1);
	}
	ft_free_args(m);
	return (0);
}

int		ft_command_pipe_run(t_mini *m, int i)
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

void	ft_wait(t_mini *m)
{
	int status;

	waitpid(g_v.pid, &status, 0);
	if (WIFEXITED(status))
		g_v.exit_status = WEXITSTATUS(status);
	close(m->pipe.fd[1]);
	m->pipe.fd2 = m->pipe.fd[0];
}

void	ft_pipe_continue(t_mini *m, int i)
{
	if (m->pipe.args[i + 1] && m->redirection == 0)
		dup2(m->pipe.fd[1], 1);
	ft_command_2(m, m->command, 0);
	close(m->pipe.fd[0]);
	exit(1);
}

void	ft_pipe_run(t_mini *m, int i)
{
	if (ft_pipe_1(m) == 1)
		i++;
	else
	{
		while (m->pipe.args[i] != NULL)
		{
			pipe(m->pipe.fd);
			g_v.pid = fork();
			if (g_v.pid == 0)
			{
				dup2(m->pipe.fd2, 0);
				if (ft_command_pipe_run(m, i) == -1)
				{
					close(m->pipe.fd[0]);
					exit(1);
				}
				ft_pipe_continue(m, i);
			}
			else
				ft_wait(m);
			i++;
		}
		ft_free_pipe_args(m);
	}
}

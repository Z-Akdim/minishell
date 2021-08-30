/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_run.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:57:04 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:57:05 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void		ft_exec(t_mini *m, char *command)
{
	int		status;

	status = 0;
	g_v.pid = fork();
	if (g_v.pid == 0)
		execve(command, m->args, m->envp_g);
	else
	{
		waitpid(g_v.pid, &status, 0);
		if (WIFEXITED(status))
			g_v.exit_status = WEXITSTATUS(status);
	}
}

void		ft_command_2(t_mini *m, char *command, int index)
{
	if (ft_strcmp(m->args[0], TYPE_CD) == 0)
		ft_cd(m);
	else if (ft_strcmp(m->args[0], TYPE_PWD) == 0)
		ft_pwd(m);
	else if (ft_strcmp(m->args[0], TYPE_ECHO) == 0)
		ft_echo(m);
	else if (ft_strcmp(m->args[0], TYPE_ENV) == 0)
		ft_env(m);
	else if (ft_strcmp(m->args[0], TYPE_EXPORT) == 0)
		ft_export(m, 0, 0);
	else if (ft_strcmp(m->args[0], TYPE_UNSET) == 0)
		ft_unset(m);
	else if (ft_strcmp(m->args[0], TYPE_EXITE) == 0)
		ft_exit(m);
	else if (m->run_path == NULL && m->args[0][0] != '/'
	&& m->args[0][0] != '$' && ft_strcmp(m->args[0], "./minishell") != 0
	&& ft_strcmp(m->args[0], "minishell") != 0)
	{
		g_v.exit_status = 127;
		ft_error(m->args[0], ": command not found", "\n");
	}
	else if (index == 0)
		ft_exec(m, command);
	else if (index == 1)
		execve(command, m->args, m->envp_g);
}

void		ft_run_command(t_mini *m)
{
	char	*command;
	int		status;

	command = NULL;
	status = 0;
	if (m->check_pipe == 0)
		command = m->args[0][0] == '/' ? m->args[0] : m->run_path;
	if (command == NULL && m->check_pipe == 0)
		command = m->args[0];
	if (m->check_pipe == 1)
		ft_pipe_run(m, 0);
	else
		ft_command_2(m, command, 0);
	command = NULL;
}

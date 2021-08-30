/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:59:11 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:59:13 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void		ft_style(void)
{
	ft_putstr_fd(GRN, 1);
	ft_putstr_fd("➜  ", 1);
	ft_putstr_fd(RED, 1);
	ft_putstr_fd("minishell", 1);
	ft_putstr_fd(WHT, 1);
	ft_putstr_fd("$ ", 1);
}

void		ft_start(t_mini *m)
{
	ft_init(m);
	ft_redirection_space(m);
	ft_check_multi_command(m);
	ft_start_minishell(m, 0, 0);
}

void		ft_start_first(t_mini *m, char **envp)
{
	ft_signal();
	ft_copy_env(m, envp);
	ft_get_home(m);
	ft_shell_lvl(m, -1, 0);
	ft_copy_export(m);
	ft_init(m);
}

void		ft_remove_line_space(t_mini *m)
{
	char	*new_line;
	int		i;

	i = 0;
	while (m->line[i] == ' ' || m->line[i] == '\t')
		i++;
	new_line = ft_strdup(&m->line[i]);
	free(m->line);
	m->line = ft_strdup(new_line);
	free(new_line);
}

int			main(int argc, char **argv, char **envp)
{
	t_mini	m;
	int		i;

	i = 0;
	argc = 0;
	argv = NULL;
	ft_start_first(&m, envp);
	while (1)
	{
		getcwd(m.cwd, sizeof(m.cwd));
		ft_style();
		get_input(&m, 0, 1, 0);
		ft_remove_line_space(&m);
		if (m.line[0] != '\0' && m.line[0] != ' ')
			if ((syn_error(&m, 0) == 0))
				ft_start(&m);
		i = 0;
		free(m.line);
	}
	return (0);
}

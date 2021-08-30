/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:58:23 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:58:25 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		ft_count_pipes(t_mini *m)
{
	int j;
	int pipe;

	j = 0;
	pipe = 0;
	while (m->line[j])
	{
		if (m->line[j] == '|')
			pipe++;
		j++;
	}
	return (pipe);
}

void	ft_pwd(t_mini *m)
{
	g_v.exit_status = 0;
	getcwd(m->cwd, ft_strlen(m->cwd));
	ft_putstr_fd(m->cwd, 1);
	ft_putstr_fd("\n", 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:58:35 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:58:37 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void		ft_free_new_args(t_mini *m)
{
	int i;

	i = 0;
	while (m->v.new_args[i])
	{
		free(m->v.new_args[i]);
		m->v.new_args[i] = NULL;
		i++;
	}
	free(m->v.new_args);
}

void		ft_copy_args_to_new(t_mini *m, int i)
{
	int j;

	j = 0;
	while (m->args[j])
	{
		m->v.new_args[i] = ft_strdup(m->args[j]);
		i++;
		j++;
	}
	m->v.new_args[i] = NULL;
	free(m->args[0]);
	free(m->args[1]);
}

void		ft_redirection_nocommand(t_mini *m)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	m->redirection_nocommand = 0;
	if ((ft_strcmp(m->args[0], ">") == 0
	|| ft_strcmp(m->args[0], ">>") == 0) && !m->args[2])
	{
		m->redirection_nocommand = 1;
		m->v.new_args = malloc(sizeof(char *) * (5));
		m->v.new_args[i] = ft_strdup("echo");
		i++;
		m->v.new_args[i] = ft_strdup("-n");
		i++;
		ft_copy_args_to_new(m, i);
		i = 0;
		while (m->v.new_args[i])
		{
			m->args[i] = ft_strdup(m->v.new_args[i]);
			i++;
		}
		m->args[i] = NULL;
		ft_free_new_args(m);
	}
}

void		ft_free_args_redirection(t_mini *m, int index)
{
	while (m->args[index])
	{
		free(m->args[index]);
		m->args[index] = NULL;
		m->args_num--;
		index++;
	}
}

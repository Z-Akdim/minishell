/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:57:20 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:57:21 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void	ft_env(t_mini *m)
{
	int i;

	i = 0;
	if (m->args[1])
	{
		ft_error("env: ", m->args[1], ": No such file or directory\n");
		g_v.exit_status = 127;
	}
	else
		g_v.exit_status = 0;
	if (m->args_num <= 1)
	{
		while (m->envp_g[i])
		{
			if (ft_strcmp(m->envp_g[i], "UNSETTHISVSRISBLE") != 0
			&& ft_equal_check(m->envp_g[i]) == 1)
			{
				ft_putstr_fd(m->envp_g[i], 1);
				ft_putstr_fd("\n", 1);
			}
			i++;
		}
	}
}

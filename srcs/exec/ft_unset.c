/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:59:05 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:59:08 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_unset_1(t_mini *m, int j)
{
	char	*arg;
	int		i;

	g_v.exit_status = 0;
	arg = ft_strjoin(m->args[j], "=");
	i = 0;
	while (m->envp_g[i])
	{
		if (m->envp_g[i] && ft_strncmp(m->envp_g[i],
		arg, ft_strlen(arg)) == 0)
		{
			free(m->envp_g[i]);
			m->envp_g[i] = NULL;
			m->envp_g[i] = ft_strdup("UNSETTHISVSRISBLE");
			break ;
		}
		i++;
	}
	free(arg);
}

void	ft_unset(t_mini *m)
{
	int		index;
	int		j;

	index = 0;
	j = 1;
	if (m->args_num > 1)
		while (m->args[j])
		{
			if ((ft_equal_check(m->args[j])) == 1 || (m->args[j][0] >= '0'
			&& m->args[j][0] <= '9') || !(ft_ischar(m->args[j][0])))
			{
				index = -1;
				break ;
			}
			else
				ft_unset_1(m, j);
			j++;
		}
	if (index == -1)
	{
		g_v.exit_status = 1;
		ft_error("`", m->args[j], "': not a valid identifier\n");
	}
}

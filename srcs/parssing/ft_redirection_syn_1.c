/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_syn_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:22:53 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:22:54 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int			ft_space_nb(t_mini *m, int i, int space_nb)
{
	while (m->line[++i])
	{
		if (m->line[i] == '>' && m->line[i + 1] != '>')
		{
			if (m->line[i - 1] != ' ')
				space_nb++;
			if (m->line[i + 1] != ' ')
				space_nb++;
		}
		else if (m->line[i] == '<')
		{
			if (m->line[i - 1] != ' ')
				space_nb++;
			if (m->line[i + 1] != ' ')
				space_nb++;
		}
		else if (m->line[i] == '>' && m->line[i + 1] == '>')
		{
			if (m->line[i - 1] != ' ')
				space_nb++;
			if (m->line[i + 2] != ' ')
				space_nb++;
		}
	}
	return (space_nb);
}

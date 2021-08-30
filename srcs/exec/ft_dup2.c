/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:57:09 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:57:11 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void		ft_free_args_to_sort(t_mini *m)
{
	int i;

	i = 0;
	while (m->args_to_sort[i])
	{
		free(m->args_to_sort[i]);
		m->args_to_sort[i] = NULL;
		i++;
	}
	if (m->args_to_sort)
		free(m->args_to_sort);
}

void		ft_dup2(t_mini *m)
{
	int fdd;

	if (m->std == 1)
		fdd = dup(0);
	else
		fdd = dup(1);
	dup2(fdd, m->std);
	close(fdd);
}

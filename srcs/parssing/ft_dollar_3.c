/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:21:54 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:21:56 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void		ft_do_if_3(t_mini *m)
{
	char	*num;
	char	*tmp;
	int		j;

	j = 0;
	m->d.i += 2;
	tmp = ft_strdup(m->d.new_line);
	free(m->d.new_line);
	m->d.new_line = NULL;
	num = ft_itoa(g_v.exit_status);
	m->d.new_line = ft_strjoin(tmp, num);
	while (num[j])
	{
		m->d.new_line[m->d.j] = num[j];
		j++;
		m->d.j++;
	}
	free(num);
	free(tmp);
}

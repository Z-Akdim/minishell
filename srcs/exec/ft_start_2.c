/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:58:45 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:58:49 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_start_minishell_2(t_mini *m)
{
	ft_check_home(m);
	ft_run_command(m);
	ft_dup2(m);
	if (m->check_pipe == 0)
		ft_free_no_pipe(m);
	if (m->home_error)
	{
		free(m->home_error);
		m->home_error = NULL;
	}
}

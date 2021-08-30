/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:56:51 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:56:53 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void		ft_cd_1(t_mini *m, int i, int j)
{
	if (i == 0)
	{
		free(m->oldpwd);
		m->oldpwd = NULL;
	}
	if (i == 1)
	{
		ft_get_home_2(m);
		ft_free_args(m);
		m->args = malloc(sizeof(char *) * 3);
		m->args[0] = ft_strdup("cd");
		m->args[1] = ft_strdup(m->home_two);
		m->args[2] = NULL;
	}
	if (i == 2)
	{
		free(m->args[1]);
		while (m->envp_g[j] &&
		ft_strncmp(m->envp_g[j], "OLDPWD=", 7) != 0)
			j++;
		m->args[1] = ft_strdup(&m->envp_g[j][7]);
		ft_error(&m->envp_g[j][7], "\n", "");
	}
}

void		ft_oldpwd_refresh(t_mini *m)
{
	int		i;
	int		j;
	char	*arg;

	i = 0;
	j = -1;
	m->v.index = 0;
	while (m->envp_g[++j])
		if (ft_strncmp(m->envp_g[j], "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
		{
			m->v.index = 1;
			free(m->envp_g[j]);
			arg = ft_strjoin("OLDPWD=", m->cwd);
			m->envp_g[j] = ft_strdup(arg);
		}
	if (m->v.index == 0)
	{
		arg = ft_strjoin("OLDPWD=", m->cwd);
		ft_strjoin2(m, arg);
	}
	free(arg);
}

void		ft_pwd_refresh(t_mini *m)
{
	int		i;
	int		j;
	char	*arg;

	i = 0;
	j = -1;
	m->v.index = 0;
	getcwd(m->cwd, sizeof(m->cwd));
	while (m->envp_g[++j])
		if (ft_strncmp(m->envp_g[j], "PWD=", ft_strlen("PWD=")) == 0)
		{
			m->v.index = 1;
			free(m->envp_g[j]);
			m->envp_g[j] = NULL;
			arg = ft_strjoin("PWD=", m->cwd);
			m->envp_g[j] = ft_strdup(arg);
		}
	if (m->v.index == 0)
	{
		arg = ft_strjoin("PWD=", m->cwd);
		ft_strjoin2(m, arg);
	}
	free(arg);
}

void		ft_cd(t_mini *m)
{
	int		i;

	i = 0;
	g_v.exit_status = 0;
	ft_oldpwd_refresh(m);
	if (!m->args[1])
	{
		if (ft_strcmp(m->home_error, "ERROR") == 0)
		{
			ft_error("cd: HOME not set", "", "\n");
			return ;
		}
		ft_cd_1(m, 1, 0);
	}
	else if ((ft_strcmp(m->args[1], "-") == 0))
		ft_cd_1(m, 2, 0);
	if (chdir(m->args[1]) == -1)
	{
		g_v.exit_status = 1;
		ft_error("cd: ", m->args[1], ": No such file or directory\n");
	}
	ft_pwd_refresh(m);
}

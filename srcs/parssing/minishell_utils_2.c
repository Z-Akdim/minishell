/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:56:10 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:56:12 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void			ft_putchar(char c)
{
	write(1, &c, 1);
}

void			ft_putstr(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

int				char_test(char *command, char *str)
{
	int			i;

	i = 0;
	if (command[i] == '\0' || command[i] == '\n')
		return (0);
	while (command[i])
	{
		if ((command[i] - str[i]) == 0)
			i++;
		else
			return (0);
	}
	return (1);
}

int				ft_ischar(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
		return (1);
	return (0);
}

int				ft_strcmp(const char *s1, const char *s2)
{
	size_t		i;
	char		*s11;
	char		*s22;

	i = 0;
	if (s1 == NULL)
		return (1);
	s11 = (char *)s1;
	s22 = (char *)s2;
	while ((s11[i] || s22[i]))
	{
		if (s11[i] != '\0' && s22[i] == '\0')
			return (s11[i]);
		if (s11[i] == '\0' && s22[i] != '\0')
			return (-s22[i]);
		if (s11[i] > s22[i])
			return (s11[i] - s22[i]);
		if (s11[i] < s22[i])
			return (s11[i] - s22[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:56:23 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:56:24 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

char				*ft_strcpy(char *dst, char *src)
{
	int				i;

	i = 0;
	dst = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char				*ft_strlcpy(char *dst, char *src, int l)
{
	int				i;

	i = 0;
	dst = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	while (src[i] != '\0' && i < l)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int					ft_equal_check(char *arg)
{
	int				i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int					ft_atoi(const char *str)
{
	int				s;
	int				r;

	s = 1;
	r = 0;
	while (*str == ' ' || *str == '\t' || *str == '\r' ||
	*str == '\n' || *str == '\v' || *str == '\f')
		str++;
	if (*str == '-')
		s = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		r = (r * 10) + (*str - '0');
		str++;
	}
	r = r * s;
	return (r);
}

int					num_len(int n)
{
	int				i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

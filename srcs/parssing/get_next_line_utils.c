/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:55:58 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:55:59 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t		ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char		*ft_strjoin3(char const *s1, char const s2)
{
	char	*ret;
	int		i;

	i = (ft_strlen(s1) + 2);
	if (!(ret = malloc(i)))
		return (0);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = s2;
	ret[++i] = '\0';
	return (ret);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		i;
	int		count;

	count = 0;
	i = (ft_strlen(s1) + ft_strlen(s2) + 1);
	ret = (char *)malloc(sizeof(char) * (i));
	i = 0;
	while (s1[i])
	{
		ret[count] = s1[i];
		count++;
		i++;
	}
	i = 0;
	while (s2[i])
	{
		ret[count] = s2[i];
		count++;
		i++;
	}
	ret[count] = '\0';
	return (ret);
}

char		*ft_strdup(const char *s1)
{
	char	*str;
	int		i;
	int		j;

	j = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	i = 0;
	while (i < j)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char		*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		++s;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}

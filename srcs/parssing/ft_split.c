/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:23:28 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:23:31 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int				count_str(char *s1, char c)
{
	int		i;
	int		lengt;
	int		count;

	lengt = ft_strlen(s1);
	count = 0;
	i = 0;
	while (s1[i] == c)
	{
		count++;
		i++;
	}
	i = lengt - 1;
	while (s1[i] == c)
	{
		count++;
		i--;
	}
	return (count);
}

char			*ft_strtrim(char *s1, char set)
{
	char		*str;
	int			len;
	int			i;
	int			j;

	j = 0;
	i = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(s1) - count_str(s1, set) + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i] == set)
		i++;
	len = ft_strlen(s1) - 1;
	while (s1[len] == set)
		len--;
	while (i <= len)
	{
		str[j] = s1[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

static	int		c_word(char *str, char c)
{
	int			i;
	int			count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = skip_quots(str, str[i], i);
		if (str[i] == c && str[i + 1] != c)
			count++;
		if (str[i] != c && str[i + 1] == '\0')
			count++;
	}
	return (count);
}

static	char	*remplir(char *s, int *k, char c)
{
	int			i;
	int			start;
	int			end;
	char		*str;
	int			startt;

	i = *k;
	while (s[i] == c)
		i++;
	start = i;
	startt = i;
	while (s[i] != c && s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			i = skip_quots(s, s[i], i);
		i++;
	}
	end = i;
	*k = i;
	while (startt < end)
		startt++;
	str = ft_substr(s, start, (end - start));
	if (str == NULL)
		return (NULL);
	return (str);
}

char			**ft_split(char *s, char c)
{
	char		*str;
	char		**tab;
	int			i;
	int			j;
	int			k;

	i = -1;
	str = ft_strtrim((char*)s, c);
	if (str == NULL)
		return (NULL);
	j = c_word(str, c);
	tab = (char **)malloc((j + 1) * sizeof(char*));
	if (tab == NULL)
		return (NULL);
	k = 0;
	while (++i < j)
		if ((tab[i] = remplir(str, &k, c)) == NULL)
		{
			ft_free(tab, str);
			return (0);
		}
	tab[i] = 0;
	free(str);
	return (tab);
}

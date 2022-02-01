/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:27:57 by fbonini           #+#    #+#             */
/*   Updated: 2022/02/01 17:05:01 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_first(char c)
{
	char	*add;

	add = (char *)malloc(sizeof(char) * 2);
	if (!add)
		return (NULL);
	add[0] = c;
	add[1] = '\0';
	return (add);
}

char	*ft_strjoin_char(char *s1, char const c)
{
	char	*add;
	int		i;

	if (!c)
		return (NULL);
	if (!s1)
		return (ft_strjoin_first(c));
	add = (char *)malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (!add)
	{
		free(add);
		return (NULL);
	}
	i = -1;
	while (s1[++i])
		add[i] = s1[i];
	add[i++] = c;
	add[i] = '\0';
	return (add);
}

void	ft_add_char(char **tmp, char **ret, char c)
{
	*tmp = ft_strjoin_char(*ret, c);
	free(*ret);
	*ret = ft_strdup(*tmp);
	free(*tmp);
}

void	ft_join_string(char **tmp, char **ret, char *str)
{
	if (*ret)
	{
		*tmp = ft_strjoin(*ret, str);
		free(*ret);
		*ret = ft_strdup(*tmp);
		free(*tmp);
	}
	else
		*ret = ft_strdup(str);
}

void	ft_strjoin_env(char **ret, char *content)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (content[i] != '\0')
	{
		ft_add_char(&tmp, ret, content[i]);
		i++;
	}
}

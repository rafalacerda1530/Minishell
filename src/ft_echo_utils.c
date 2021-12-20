/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:28:51 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/20 12:30:43 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_char(char **tmp, char **ret, char c)
{
	*tmp = ft_strjoin_char(*ret, c);
	free(*ret);
	*ret = ft_strdup(*tmp);
	free(*tmp);
}

int	ft_get_key_size(char *str, int *i)
{
	int	size;

	size = 0;
	while (str[*i] != ' ' && str[*i] != '\'' && str[*i] != '"')
	{
		if (str[*i] == '\0')
			break ;
		(*i)++;
		size++;
	}
	return (size);
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

int	ft_true_dollar(char *str, int i, int quote)
{
	if (quote != 1)
	{
		if (str[i + 1] == '\'')
			return (0);
		if (str[i + 1] == '"')
			return (0);
		if (str[i + 1] == ' ')
			return (0);
		return (1);
	}
	return (0);
}

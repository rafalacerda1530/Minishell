/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:28:51 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/29 15:32:34 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_space_remove(char *str, int i, int quote)
{
	if (quote == 0)
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
			return (1);
		if (str[i] == ' ' && str[i + 1] == '\0')
			return (1);
	}
	return (0);
}

int	ft_get_key_size(char *str, int i)
{
	int	size;

	size = 0;
	while (str[i] != ' ' && str[i] != '\'' && str[i] != '"')
	{
		if (str[i] == '\0')
			break ;
		if (str[i] == '=')
		{
			size--;
			break ;
		}
		i++;
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

int	ft_true_dollar(char *str, t_parse *parser)
{
	if (parser->quote != 1)
	{
		if (str[parser->index + 1] == '\'')
			return (0);
		if (str[parser->index + 1] == '"')
			return (0);
		if (str[parser->index + 1] == ' ')
			return (0);
		return (1);
	}
	return (0);
}

int	ft_true_home(char *str, t_parse *parser)
{
	if (parser->quote == 0)
	{
		if (str[parser->index + 1] == '/')
			return (1);
		if (str[parser->index + 1] == ' ')
			return (1);
		if (str[parser->index + 1] == '\0')
			return (1);
		return (0);
	}
	return (0);
}

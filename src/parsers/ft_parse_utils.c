/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:28:51 by fbonini           #+#    #+#             */
/*   Updated: 2022/02/01 17:06:20 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (str[parser->index + 1] == '\0')
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

int	ft_quote_check(char *str, int *i, int quote)
{
	if (str[*i] == '"' && (quote == 0 || quote == 2))
	{
		(*i)++;
		if (quote == 0)
			return (2);
		else
			return (0);
	}
	else if (str[*i] == '\'' && (quote == 0 || quote == 1))
	{
		(*i)++;
		if (quote == 0)
			return (1);
		else
			return (0);
	}
	return (quote);
}

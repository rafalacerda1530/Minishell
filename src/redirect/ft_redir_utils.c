/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:06:03 by fbonini           #+#    #+#             */
/*   Updated: 2022/02/01 17:19:34 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_nb_redirect(t_tolken *tolken, t_parse parser, char *ret)
{
	while (ret[parser.index] != '\0')
	{
		if (ret[parser.index] == '>' || ret[parser.index] == '<')
		{
			while (ret[parser.index] != ' ' && ret[parser.index] != '\0')
				parser.index++;
			tolken->numb_redir++;
		}
		parser.index++;
	}
}

void	ft_redirect_check(char *ret, t_tolken *tolken)
{
	int		i;
	t_parse	parser;

	ft_bzero(&parser, sizeof(t_parse));
	ft_get_nb_redirect(tolken, parser, ret);
	tolken->redir = (int *) malloc (sizeof(int) * tolken->numb_redir);
	i = 0;
	while (ret[parser.index] != '\0')
	{
		ft_quote_check(ret, &parser.index, parser.quote);
		if (ret[parser.index] == '>' || ret[parser.index] == '<')
		{
			if (parser.quote == 0)
				tolken->redir[i] = 1;
			else
				tolken->redir[i] = 0;
			while (ret[parser.index] != ' ')
				parser.index++;
			i++;
		}
		parser.index++;
	}
}

int	ft_valid_redir(char *key)
{
	if (ft_strlen(key) > 2)
		return (0);
	if (key[0] == '>' && key[1] == '<')
		return (0);
	return (1);
}

char	*ft_str_remove(char *key, char *aux, char *file)
{
	char	*remove;
	char	*tmp;
	int		i;

	remove = ft_strdup(key);
	if (ft_strcmp(aux, key) == 0)
		ft_add_char(&tmp, &remove, ' ');
	i = 0;
	while (file[i] != '\0')
	{
		ft_add_char(&tmp, &remove, file[i]);
		i++;
	}
	return (remove);
}

char	*ft_remove_extra_spaces(char *str)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = 0;
	ret = NULL;
	while (str[i] == ' ')
		i++;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' && str[i + 1] == ' ')
		{
			i++;
			if (str[i] == '\0')
				break ;
		}
		if (str[i] == ' ' && str[i + 1] == '\0')
			break ;
		ft_add_char(&tmp, &ret, str[i]);
		i++;
	}
	return (ret);
}

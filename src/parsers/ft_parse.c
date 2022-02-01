/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:44:59 by fbonini           #+#    #+#             */
/*   Updated: 2022/02/01 17:05:14 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_return(char **ret, char *str, int *i)
{
	int		j;
	int		quote;
	char	*numb;
	char	*tmp;

	j = 0;
	quote = 0;
	if (str[*i] != '?')
		return ;
	numb = ft_itoa(g_last_return);
	ft_join_string(&tmp, ret, numb);
	while (str[*i + j] != '\0')
	{
		quote = ft_quote_check(&str[*i], &j, quote);
		if ((str[*i + j] == ' ' || str[*i + j] != '\0') && quote == 0)
			break ;
		ft_add_char(&tmp, ret, str[*i + j]);
		j++;
	}
	*i = *i + j;
	free(numb);
}

void	ft_check_env(char **ret, char *str, t_env_list *env_list, int *i)
{
	int			key_size;
	char		*key;
	char		*content;

	key_size = ft_get_key_size(str, *i);
	key = (char *) malloc ((key_size + 1) * sizeof(char));
	if (!key)
	{
		free(key);
		return ;
	}
	ft_memcpy(key, &str[*i], key_size);
	key[key_size] = '\0';
	*i = *i + key_size;
	content = ft_get_env(key, env_list);
	if (content != NULL)
		ft_strjoin_env(ret, content);
	free(key);
	free(content);
}

void	ft_get_home(char **tmp, char **ret, t_env_list *env_list)
{
	char	*new_ret;

	*tmp = ft_get_env("HOME", env_list);
	new_ret = NULL;
	if (*ret)
	{
		new_ret = ft_strjoin(*ret, *tmp);
		free(*ret);
		*ret = ft_strdup(new_ret);
		free(new_ret);
	}
	else
		*ret = ft_strdup(*tmp);
	free(*tmp);
}

void	ft_env_checks(t_mem *mem, char *str, t_parse *parser, t_env_list *list)
{
	(void)mem;
	if (str[parser->index] == '~' && ft_true_home(str, parser))
	{
		ft_get_home(&parser->aux, &parser->ret, list);
		if (str[parser->index + 1] == '/')
		{
			parser->index++;
			ft_add_char(&parser->aux, &parser->ret, str[parser->index]);
		}
		parser->index++;
	}
	if (str[parser->index] == '$' && ft_true_dollar(str, parser))
	{
		parser->index++;
		ft_check_return(&parser->ret, str, &parser->index);
		ft_check_env(&parser->ret, str, list, &parser->index);
	}
}

char	*ft_parse_string(t_mem *mem, char *str, t_env_list *env_list)
{
	t_parse	parser;

	ft_bzero(&parser, sizeof(t_parse));
	while (*str == ' ')
		str++;
	while (str[parser.index] != '\0')
	{
		parser.quote = ft_quote_check(str, &parser.index, parser.quote);
		if (ft_space_remove(str, parser.index, parser.quote))
		{
			while (str[parser.index] == ' ')
				parser.index++;
			if (str[parser.index] != '\0')
				ft_add_char(&parser.aux, &parser.ret, str[parser.index - 1]);
		}
		ft_env_checks(mem, str, &parser, env_list);
		parser.quote = ft_quote_check(str, &parser.index, parser.quote);
		if (str[parser.index] != '\0')
		{
			ft_add_char(&parser.aux, &parser.ret, str[parser.index]);
			parser.index++;
		}
	}
	return (parser.ret);
}

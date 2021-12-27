/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:44:59 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/27 18:09:44 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_check_env(char **ret, char *str, t_env_list *env_list, int i)
{
	int			key_size;
	int			total;
	t_env_list	list;
	char		*key;

	key_size = ft_get_key_size(str, i);
	key = (char *) malloc ((key_size + 1) * sizeof(char));
	// if (!key)
	// {
		// Free Error msg
	// }
	ft_bzero(&list, sizeof(list));
	ft_memcpy(key, &str[i], key_size);
	i = i + key_size;
	list.last = env_list->last;
	total = env_list->total;
	while (total > 0)
	{
		if (!ft_strncmp(key, list.last->key, key_size))
			break ;
		list.last = list.last->prev;
		total--;
	}
	if (total > 0)
		ft_strjoin_env(ret, list.last->content);
	free(key);
	return (i);
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

char	*ft_get_string(char *str, t_env_list *env_list)
{
	int		i;
	int		quote;
	char	*ret;
	char	*tmp;

	i = 0;
	ret = NULL;
	quote = 0;
	while (str[i] != '\0')
	{
		quote = ft_quote_check(str, &i, quote);
		if (str[i] == '$' && ft_true_dollar(str, i, quote))
		{
			i++;
			i = i + ft_check_env(&ret, str, env_list, i);
		}
		else if (str[i] != '\0')
		{
			ft_add_char(&tmp, &ret, str[i]);
			i++;
		}
	}
	return (ret);
}

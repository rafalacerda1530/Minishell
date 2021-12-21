/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 14:41:43 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/21 16:13:35 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_quote_check(char *str, int *i, int *quote)
{
	if (str[*i] == '"' && (*quote == 0 || *quote == 2))
	{
		(*i)++;
		if (*quote == 0)
			*quote = 2;
		else
			*quote = 0;
	}
	else if (str[*i] == '\'' && (*quote == 0 || *quote == 1))
	{
		(*i)++;
		if (*quote == 0)
			*quote = 1;
		else
			*quote = 0;
	}
}

void	ft_check_env(char **ret, char *str, t_env_list *env_list, int *i)
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
	ft_memcpy(key, &str[*i - key_size], key_size);
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
		ft_quote_check(str, &i, &quote);
		if (str[i] == '$' && ft_true_dollar(str, i, quote))
		{
			i++;
			ft_check_env(&ret, str, env_list, &i);
		}
		else if (str[i] != '\0')
		{
			ft_add_char(&tmp, &ret, str[i]);
			i++;
		}
	}
	return (ret);
}

int	ft_flag_n(char **str)
{
	int	n_flag;

	n_flag = 0;
	if (str[0][0] == '-' && str[0][1] == 'n')
	{
		(*str)++;
		(*str)++;
		while (**str == ' ')
			(*str)++;
		n_flag = 1;
	}
	return (n_flag);
}

int	ft_echo(t_mem *mem, char *str, t_env_list *env_list)
{
	int		i;
	int		flag_n;

	i = 0;
	while (*str == ' ')
		str++;
	flag_n = ft_flag_n(&str);
	mem->print = ft_get_string(str, env_list);
	if (flag_n == 1)
		printf("%s", mem->print);
	else
		printf("%s\n", mem->print);
	free(mem->print);
	return (0);
}

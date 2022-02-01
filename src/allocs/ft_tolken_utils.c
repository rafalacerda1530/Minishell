/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolken_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:02:17 by fbonini           #+#    #+#             */
/*   Updated: 2022/02/01 17:18:26 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_tolken_sizes(int *i, int *j, char *input)
{
	t_parse	n;

	ft_bzero(&n, sizeof(t_parse));
	while (input[n.index] != ' ' && input[n.index] != '\0')
	{
		if (input[0] == '>' || input[0] == '<')
		{
			while (input[n.index] == '>' || input[n.index] == '<')
				n.index++;
			break ;
		}
		n.index++;
	}
	*i = n.index;
	while (input[n.index + 1] != '\0')
	{
		n.quote = ft_quote_check(input, &n.index, n.quote);
		if (input[n.index] == '|' && n.quote == 0)
		{
			n.index--;
			break ;
		}
		n.index++;
	}
	*j = n.index - *i;
}

void	ft_tolken_key(t_mem *mem, t_tolken *tlk, int len, char *str)
{
	char	*tmp;

	tmp = (char *) malloc ((len + 1) * sizeof(char));
	if (!tmp)
	{
		ft_memory_error();
		ft_exit(mem, 2);
	}
	ft_strlcpy(tmp, str, len + 1);
	tlk->key = ft_parse_string(mem, tmp, mem->env_list);
	free(tmp);
}

char	*ft_check_swap_str(t_tolken *tolken, char *key, char *content)
{
	char	**split;
	char	*ret;
	char	*tmp;
	int		i;

	split = ft_split(content, ' ');
	i = 0;
	if (!split[1])
	{
		ft_free_split(split);
		return (content);
	}
	ret = ft_strdup(key);
	ft_free_two_to_four(tolken->key, &*content, NULL, NULL);
	tolken->key = ft_strdup(split[1]);
	while (split[i])
	{
		ft_add_char(&tmp, &ret, ' ');
		ft_join_string(&tmp, &ret, split[i]);
		if (i == 0)
			i++;
		i++;
	}
	ft_free_split(split);
	return (ret);
}

void	ft_tolken_content(t_mem *m, t_tolken *tlk, int len, char *str)
{
	int		i;
	char	*tmp;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i] != '\0' && i < len)
	{
		if (str[i] != '\0')
			ft_add_char(&tmp, &ret, str[i]);
		i++;
	}
	i = ft_check_key(tlk->key, m->keys);
	if (i > 6 && i < 12)
		ret = ft_check_swap_str(tlk, tlk->key, ret);
	ft_redirect_check(ret, tlk);
	tlk->content = ft_parse_string(m, ret, m->env_list);
	free(ret);
}

void	ft_tolken_string(char **str, char *key, char *content)
{
	char	*tmp;

	tmp = ft_strjoin_char(key, ' ');
	if (content == NULL)
		*str = ft_strdup(tmp);
	else
		*str = ft_strjoin(tmp, content);
	free(tmp);
}

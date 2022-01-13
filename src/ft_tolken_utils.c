/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolken_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:02:17 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/13 12:06:35 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_get_tolken_sizes(int *i, int *j, char *input)
{
	int	quote;
	int	k;

	k = 0;
	while (input[k] != ' ' && input[k] != '\0')
		k++;
	*i = k;
	quote = 0;
	while (input[k + 1] != '\0')
	{
		quote = ft_quote_check(input, &k, quote);
		if (input[k] == '|' && quote == 0)
		{
			k--;
			break ;
		}
		k++;
	}
	*j = k - *i;
}

void	ft_tolken_key(t_mem *mem, t_tolken *tolken, int size, char *input)
{
	char	*tmp;

	tmp = (char *) malloc ((size + 1) * sizeof(char));
	if (!tmp)
	{
		ft_memory_error();
		ft_exit(mem, 2);
	}
	ft_strlcpy(tmp, input, size + 1);
	tolken->key = ft_parse_string(tmp, mem->env_list);
	free(tmp);
}

void	ft_tolken_content(t_mem *mem, t_tolken *tolken, int size, char *input)
{
	int		i;
	char	*tmp;
	char	*ret;

	i = 0;
	quote = 0;
	ret = NULL;
	while (input[i] != '\0' && i < size)
	{
		if (input[i] != '\0')
			ft_add_char(&tmp, &ret, input[i]);
		i++;
	}
	ft_redirect_check(ret, tolken);
	tolken->content = ft_parse_string(ret, mem->env_list);
	free(ret);
}

void	ft_tolken_string(char **str, char *key, char *content)
{
	char	*tmp;

	tmp = ft_strjoin_char(key, ' ');
	*str = ft_strjoin(tmp, content);
	free(tmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolken_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:02:17 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/27 18:07:44 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_quotes(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '"')
	{
		i++;
		while (input[i] != '"' && input[i] != '\0')
			i++;
	}
	else if (input[i] == '\'')
	{
		i++;
		while (input[i] != '\'' && input[i] != '\0')
			(i)++;
	}
	return (i);
}

void	ft_get_tolken_sizes(int *i, int *key, int *content, char *input)
{
	while (input[*i] == ' ')
		(*i)++;
	while (input[*i + *key] != ' ' && input[*i + *key] != '\0')
		(*key)++;
	while (input[*i + *key + *content] != '\0')
	{
		if (input[*i + *key + *content] == '|')
			break ;
		(*content)++;
	}
}

void	ft_tolken_key(t_mem *mem, t_tolken *tolken, int size, char *input)
{
	char	*tmp;

	tmp = (char *) malloc ((size + 1) * sizeof(char));
	// if (!tmp)
	// {
		// Free Error msg
	// }
	ft_strlcpy(tmp, input, size + 1);
	tolken->key = ft_get_string(tmp, mem->env_list);
	free(tmp);
}

void	ft_tolken_content(t_mem *mem, t_tolken *tolken, int size, char *input)
{
	char	*tmp;

	tmp = (char *) malloc ((size + 1) * sizeof(char));
	// if (!tmp)
	// {
		// Free Error msg
	// }
	ft_strlcpy(tmp, input, size + 1);
	tolken->content = ft_get_string(tmp, mem->env_list);
	free(tmp);
}

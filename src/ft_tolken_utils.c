/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolken_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:02:17 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/21 16:59:10 by fbonini          ###   ########.fr       */
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
	else if(input[i] == '\'')
	{
		i++;
		while (input[i] != '\'' && input[i] != '\0')
			(i)++;
	}
	return (i);
}

void	ft_get_tolken_sizes(int *i, int *key, int *content, char *input)
{
	while(input[*i] == ' ')
		(*i)++;
	while (input[*i + *key] != ' ')
	{
		if (input[*i + *key] == '"' || input[*i + *key] == '\'')
			*key += ft_check_quotes(&input[*i + *key]);
		(*key)++;
	}
	while (input[*i + *key + *content] != '\0')
	{
		if (input[*i + *key + *content] == '"' || input[*i + *key + *content] == '\'')
			*content += ft_check_quotes(&input[*i + *key + *content]);
		else if (input[*i + *key + *content] == '|')
		 	break;
		(*content)++;
	}
}

void	ft_create_tolken_strings(t_tolken *tolken, int key, int content, char *input)
{
	tolken->key = (char *) malloc ((key + 1) * sizeof(char));
	// if (!tolken->key)
	// {
		// Free Error msg
	// }
	ft_strlcpy(tolken->key, input, key + 1);
	tolken->content = (char *) malloc ((content + 1) * sizeof(char));
	// if (!tolken->content)
	// {
		// Free Error msg
	// }
	ft_strlcpy(tolken->content, &input[key], content + 1);
}

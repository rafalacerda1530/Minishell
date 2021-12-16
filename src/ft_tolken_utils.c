/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolken_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:02:17 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/16 12:15:43 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_get_tolken_sizes(int *i, int *key, int *content, char *input)
{
	while(input[*i] == ' ')
		(*i)++;
	while (input[*i + *key] != ' ')
		(*key)++;
	while (input[*i + *key + *content] != '\0')
	{
		if (input[*i + *key + *content] == '"')
		{
			(*content)++;
			while (input[*i + *key + *content] != '"')
				(*content)++;
		}
		else if(input[*i + *key + *content] == '\'')
		{
			(*content)++;
			while (input[*i + *key + *content] != '\'')
				(*content)++;
		}
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
	tolken->content = (char *) malloc ((content) * sizeof(char));
	// if (!tolken->content)
	// {
		// Free Error msg
	// }
	ft_strlcpy(tolken->content, &input[key], content + 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:06:03 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/13 18:52:36 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_get_numb_redirect(t_tolken *tolken, t_parse parser, char *ret)
{
	while (ret[parser.index] != '\0')
	{
		if (ret[parser.index] == '>' || ret[parser.index] == '<')
		{
			while (ret[parser.index] != ' ')
				parser.index++;
			tolken->redir_numb++;
		}
		parser.index++;
	}
}

void	ft_redirect_check(char *ret, t_tolken *tolken)
{
	int		i;
	t_parse	parser;

	ft_bzero(&parser, sizeof(t_parse));
	ft_get_numb_redirect(parser, ret);
	tolken->redir = (int *) malloc (sizeof(int) * redir_numb);
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

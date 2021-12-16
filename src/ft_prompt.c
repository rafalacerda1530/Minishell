/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:42:41 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/16 11:44:35 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_read_input(char **input)
{
	char	*prompt;
	char	intro[3];
	char	*msg;

	intro[0] = '$';
	intro[1] = ' ';
	intro[2] = '\0';
	prompt = NULL;
	prompt = getcwd(prompt, 0);
	msg = ft_strjoin(prompt, intro);
	*input = readline(msg);
	free(msg);
	free(prompt);
}

void	ft_create_history(char *input)
{
	if (input && *input)
		add_history(input);
}

void	ft_create_shell(t_mem *mem)
{
	char	*input;

	while (1)
	{
		input = NULL;
		ft_read_input(&input);
		ft_create_history(input);
		ft_fill_tolken_list(mem->tolken_list, input);
		if (input)
		{
			ft_free_tolken_list(mem->tolken_list);
			free(input);
		}
	}
	rl_clear_history();
}

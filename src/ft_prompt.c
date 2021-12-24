/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:42:41 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/24 15:37:40 by fbonini          ###   ########.fr       */
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

void	ft_actions(t_mem *mem)
{
	int	key;

	key = ft_check_key(mem->tolken_list->first->key, mem->keys);
	ft_use_built_in(mem->built_in->function[key], mem->tolken_list->first->content, mem);
}

void	ft_create_shell(t_mem *mem)
{
	char	*input;

	(void)mem;
	while (1)
	{
		input = NULL;
		ft_read_input(&input);
		ft_create_history(input);
		printf("\n------------START ENV----------------\n");
		if (input)
		{
			ft_fill_tolken_list(mem->tolken_list, input);
			// ft_echo(mem, mem->tolken_list->last->content, mem->env_list);
			/* 			WORKING BUILT INS 
			ft_pwd(); 
			ft_cd(mem, mem->tolken_list->first->content, mem->env_list);
						WORKING BUILT INS */
			// ft_env(mem, mem->env_list);
			/* \/ Precisar criar função pra loop quando usar pipes \/ */
			// if (mem->tolken_list->first)
			// 	ft_actions(mem);
			/* /\ Precisar criar função pra loop quando usar pipes /\ */
			ft_free_tolken_list(mem->tolken_list);
			free(input);
		}
	}
	rl_clear_history();
}

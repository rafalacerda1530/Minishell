/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:42:41 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/27 17:43:30 by fbonini          ###   ########.fr       */
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
	ft_use_built_in(mem->built_in->function[key], mem, mem->tolken_list->first->content);
}

void	ft_create_shell(t_mem *mem)
{
	char	*input;
	int		i;

	i = 0;
	while (1)
	{
		input = NULL;
		ft_read_input(&input);
		ft_create_history(input);
		if (input)
		{
			ft_fill_tolken_list(mem, mem->tolken_list, input);
			ft_export(mem, mem->env_list, mem->tolken_list->first->content);
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
			if (i == 5)
				ft_exit(mem, mem->all_return);
			i++;
		}
	}
}

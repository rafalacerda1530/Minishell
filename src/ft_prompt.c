/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:42:41 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/11 16:40:24 by fbonini          ###   ########.fr       */
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
	int	i;

	i = 0;
	if (input && *input)
	{
		while (input[i] == ' ')
			i++;
		add_history(&input[i]);
	}
}

// void	ft_make_commands(t_mem *mem, t_tolken_list *tolken_list)
// {
// 	int	key;
// 	int	total;
// 	/*
// 		pegar lista de token
// 		Pegar Keys ate o ultimo tolken
// 		if (total > 1)
// 			Tem Pipe

// 	*/
// 	total = tolken_list->total;
// 	while (total > 0)
// 	{
// 		key = ft_check_key(tolken_list->first->key, mem->keys);
// 		ft_use_built_in(mem->built_in->function[key], mem, mem->tolken_list->first->content);
// 		total--;
// 	}
// }

void	ft_create_shell(t_mem *mem)
{
	char	*input;
	int		i=0;

	while (1)
	{
		input = NULL;
		ft_read_input(&input);
		ft_create_history(input);
		if (input)
		{
			ft_fill_tolken_list(mem, mem->tolken_list, input);
			// ft_env(mem, mem->env_list);
			// << < "<" > >>
			// ft_echo(mem, mem->tolken_list->last->content, mem->env_list);
			ft_execv(mem, mem->env_list, mem->tolken_list->first->key);
			// if (mem->tolken_list->first->str)
			// 	printf(">%s<\n", mem->tolken_list->first->str);
			/* 			WORKING BUILT INS
			ft_echo(mem, mem->tolken_list->last->content, mem->env_list);
			ft_pwd(); 
			ft_cd(mem, mem->tolken_list->first->content, mem->env_list);
			ft_export(mem, mem->env_list, mem->tolken_list->first->content);
			ft_unset(mem, mem->env_list, mem->tolken_list->first->content);
						WORKING BUILT INS */
			/* \/ Precisar criar função pra loop quando usar pipes \/ */
			// if (mem->tolken_list->first)
			// 	ft_make_commands(mem);
			/* /\ Precisar criar função pra loop quando usar pipes /\ */
			ft_free_tolken_list(mem->tolken_list);
			free(input);
			if (i == 5)
				ft_exit(mem, mem->all_return);
			i++;
		}
	}
}

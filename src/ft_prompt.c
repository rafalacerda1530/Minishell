/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:42:41 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/23 17:56:29 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* \/ Print para checkar \/ */
void	print_tolken(t_tolken_list *tolken_list)
{
	t_tolken	*tolken;
	int			total;

	tolken = NULL;
	total = tolken_list->total;
	tolken = tolken_list->last;
	printf("\n----------------------Tolkens Criados------------------------\n");
	while (total != 0)
	{
		printf("The Key is >> %s\nThe Command is >> %s\n", tolken->key, tolken->content);
		tolken = tolken->prev;
		total--;
	}
	printf("\n----------------------Fim------------------------\n");
}
/* /\ Print para checkar /\ */

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
	ft_use_built_in(mem->built_in->function[key]);
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
		// // print_tolken(mem->tolken_list);
		if (input)
		{
			ft_fill_tolken_list(mem->tolken_list, input);
			/* 			WORKING BUILT INS 
			ft_pwd(); 
			ft_echo(mem, mem->tolken_list->last->content, mem->env_list);
			ft_cd(mem, mem->tolken_list->first->content, mem->env_list);
						WORKING BUILT INS */

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

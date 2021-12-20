/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:42:41 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/19 20:35:50 by fbonini          ###   ########.fr       */
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

void	ft_create_shell(t_mem *mem)
{
	char	*input;

	while (1)
	{
		input = NULL;
		ft_read_input(&input);
		ft_create_history(input);
		ft_fill_tolken_list(mem->tolken_list, input);
		// // print_tolken(mem->tolken_list);
		ft_echo(mem, mem->tolken_list->last->content, mem->env_list);
		if (input)
		{
			ft_free_tolken_list(mem->tolken_list);
			free(input);
		}
	}
	rl_clear_history();
}

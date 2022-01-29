/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:42:41 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/29 10:47:48 by fbonini          ###   ########.fr       */
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
	if (!*input)
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
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

void	ft_make_commands(t_mem *mem, t_tolken *tolken)
{
	int		i;

	i = ft_check_key(tolken->key, mem->keys);
	if (i < 12)
	{
		if (tolken->content)
			ft_built_in(mem->built_in->function[i], mem, tolken->content, i);
		else
			ft_built_in(mem->built_in->function[i], mem, NULL, i);
	}
	else
		ft_execv(mem, mem->env_list, tolken->key, tolken);
}

void	ft_exec_cmd(t_mem *mem, t_tolken *tolken)
{
	if (!tolken)
		return ;
	if (mem->tolken_list->total > 1)
		ft_pipe_cmd(mem);
	else
	{
		if (ft_redirects(mem, tolken, tolken->content) != -1)
			ft_make_commands(mem, mem->tolken_list->first);
	}
}

void	ft_create_shell(t_mem *mem)
{
	char				*input;
	struct sigaction	act;

	ft_bzero(&act, sizeof(struct sigaction));
	ft_copy_stds(mem);
	while (1)
	{
		input = NULL;
		ft_signals(&act, sigint_handler, SIGINT, mem);
		ft_read_input(&input);
		ft_create_history(input);
		if (input)
		{
			ft_fill_tolken_list(mem, mem->tolken_list, input);
			ft_exec_cmd(mem, mem->tolken_list->first);
			ft_free_tolken_list(mem->tolken_list);
			free(input);
		}
		ft_reset_stds(mem);
	}
	ft_close_copy_stds(mem);
}

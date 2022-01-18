/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarodrig < rarodrig@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:42:41 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/18 19:30:35 by rarodrig         ###   ########.fr       */
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

void	ft_make_commands(t_mem *mem, t_tolken_list *tolken_list)
{
	int	key;

	key = ft_check_key(tolken_list->first->key, mem->keys);
	if (key < 11)
		ft_use_built_in(mem->built_in->function[key], mem, mem->tolken_list->first->content);
	else
		ft_use_built_in(mem->built_in->function[key], mem, mem->tolken_list->first->key);
}

void	ft_send_tolken(t_mem *mem)
{
	int check;
	int fd_pipe[2];
	t_tolken *token;

	token = mem->tolken_list->last;
	check = mem->tolken_list->total;

	while(check != 1)
	{
		pipe(fd_pipe);
		dup2(fd_pipe[0], STDIN_FILENO);
		dup2(fd_pipe[1], STDOUT_FILENO);
		ft_make_commands(mem, mem->tolken_list);
		token = token->prev;
		check--;
		close(fd_pipe[1]);
		ft_make_commands(mem, mem->tolken_list);	
		close(fd_pipe[0]);
	}
	dup2(mem->std_pipe[0], STDIN_FILENO);
	dup2(mem->std_pipe[1], STDOUT_FILENO);
	ft_make_commands(mem, mem->tolken_list);
}

void	ft_create_shell(t_mem *mem)
{
	char	*input;

	mem->std_pipe[0] = dup(STDIN_FILENO);
	mem->std_pipe[1] = dup(STDOUT_FILENO);
	while (1)
	{
		input = NULL;
		ft_read_input(&input);
		ft_create_history(input);
		if (input)
		{
			ft_fill_tolken_list(mem, mem->tolken_list, input);
			ft_send_tolken(mem);
			ft_free_tolken_list(mem->tolken_list);
			free(input);
		}
		dup2(mem->std_pipe[0], STDIN_FILENO);
		dup2(mem->std_pipe[1], STDOUT_FILENO);
	}
	close(mem->std_pipe[1]);
	close(mem->std_pipe[0]);
}

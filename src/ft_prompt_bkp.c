/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt_bkp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:42:41 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/20 14:38:04 by fbonini          ###   ########.fr       */
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


/*

while (i < mem->tolken_list->total)
{
	if (i > 0)
		dup2(fd_pipe[i - 1][0], STDIN_FILENO);
	if (i != mem->tolken_list->total)
		dup2(fd_pipe[i][1], STDOUT_FILENO);
	else
		dup2(mem->std_pipe[1], STDOUT_FILENO);
	ft_make_commands(mem, mem->tolken_list);
	if (i > 0)
		close(fd_pipe[i - 1][0]);
	if (i != mem->tolken_list->total)
		close(fd_pipe[i][1]);
	token = token->prev;
	i++;
}

	FD 0 			
	FD 1  		
	FD 2 ----> 		STDOUT
	FD 3 Pipe[0][0] ----> STDIN
	FD 4 Pipe[0][1]

	printf("Pipe %zu : in %d , out %d\n", i , fd_pipe[i][0], fd_pipe[i][1]);

	CMD 01
	i = 0
	in - STDIN
	out - DUP2(fd[i][1], STDOUT)
	close(fd[i][1])
	Exec

	CMD 02
	i = 1
	in - DUP2(fd[i - 1][0], STDIN)
	out - DUP2(fd[i][1], STDOUT)
	close(fd[i - 1][0])
	close(fd[i][1])
	Exec

	CMD 03
	i = 2
	in - DUP2(fd[i - 1][0], STDIN)
	out - DUP2(fd[i][1], STDOUT)
	close(fd[i - 1][0])
	close(fd[i][1])
	Exec


	CMD 04
	i = 3
	in - DUP2(fd[i - 1][0], STDIN)
	out - DUP2(mem->std_pipe[1], STDOUT)
	Exec
	close(fd[i - 1][0])





	int check;
	int *fd_pipe;
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







*/











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

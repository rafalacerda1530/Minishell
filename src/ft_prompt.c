/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarodrig < rarodrig@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:42:41 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/20 17:25:28 by rarodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		printf("The Key is >%s<\nThe Command is >%s<\n", tolken->key, tolken->content);
		tolken = tolken->prev;
		total--;
	}
	printf("\n----------------------Fim------------------------\n");
}

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

void	ft_make_commands(t_mem *mem, t_tolken_list *tolken_list, t_tolken *tolken)
{
	int	key;
	(void)tolken_list;
	key = ft_check_key(tolken->key, mem->keys);
	if (key < 11)
	{
		if (tolken->content)
			ft_use_built_in(mem->built_in->function[key], mem, tolken->content);
		else
			ft_use_built_in(mem->built_in->function[key], mem, NULL);
	}
	else
		ft_execv(mem, mem->env_list, tolken->key, tolken);
}

/*
	int *fd_pipe

	/-----------------------------/
			Pipe Creation
	/-----------------------------/
	int	i;

	fd_pipe = (int *) malloc (check * sizeof(int));
	i = 0;
	while (fd_pipe[i])
	{
		fd_pipe[i] = (int) malloc (2 * sizeof(int));
		if (pipe(fd_pipe[i]) < 0)
			Error
		i++;
	}

	/-----------------------------/
			Execution (3 Pipes)
	/-----------------------------/
	STDIN_FILENO
	STDOUT_FILENO

	CMD 01									i = 0
	In > Original
	Out > fd_pipe[0][1]

	dup2(fd_pipe[0][1], STDOUT_FILENO);
	Executar CMD 1

	CMD 02									i = 1
	In > fd_pipe[0][0]
	Out > fd_pipe[1][1]
	
	dup2(fd_pipe[0][0], STDIN_FILENO);
	dup2(fd_pipe[1][1], STDOUT_FILENO);
	Executar CMD 2

	CMD 03									i = 2
	In > fd_pipe[1][0]
	Out > fd_pipe[2][1]

	dup2(fd_pipe[1][0], STDIN_FILENO);
	dup2(fd_pipe[2][1], STDOUT_FILENO);
	Executar CMD 3

	(Last)
	CMD 04									i = 3
	In > fd_pipe[2][0]
	Out > Original

	dup2(fd_pipe[2][0], STDIN_FILENO);
	dup2(mem->std_pipe[1], STDOUT_FILENO);
	Executar CMD 4

	dup2(mem->std_pipe[0], STDIN_FILENO);

	/-----------------------------/
			Pipe Free
	/-----------------------------/
	i = 0;
	while (fd_pipe[i])
	{
		free(fd_pipe[i]);
		i++;
	}
	free(fd_pipe);


*/
void	ft_send_tolken(t_mem *mem)
{
	size_t i;
	int **fd_pipe;
	t_tolken *tolken;
	// char	bufs[100];

	tolken = mem->tolken_list->last;
	fd_pipe = (int **) malloc ((mem->tolken_list->total - 1) * sizeof(int *));
	i = 0;
	while (i < mem->tolken_list->total - 1)
	{
		fd_pipe[i] = (int *) malloc (2 * sizeof(int));
		if (pipe(fd_pipe[i]) < 0)
			return ;
		i++;
	}
	i = 0;
	while (i < mem->tolken_list->total)
	{
		if (i > 0)
		{
			dup2(fd_pipe[i - 1][0], STDIN_FILENO);
			// read(fd_pipe[i - 1][0], bufs, 100);
			// dup2(mem->std_pipe[1], STDOUT_FILENO);
			// ft_putstr_fd("The buffer is ", 1);
			// ft_putstr_fd(bufs, 1);
			// ft_putstr_fd("\n", 1);
			close(fd_pipe[i - 1][0]);
		}
		/*
		i = 0  in = STDIN
		i = 1  in = 0  Abriu e fecho
		i = 2  in = 1  Fecha
		fd[2][0]
		*/
		if (i != mem->tolken_list->total - 1)
		{
			dup2(fd_pipe[i][1], STDOUT_FILENO);
			close(fd_pipe[i][1]);
		} 
		/*
		i = 0  out = 0 Abriu fecho
		i = 1  out = 1 Abriu fecho
		i = 2  out = 2 Fecha
		*/
		else
		{
			dup2(mem->std_pipe[1], STDOUT_FILENO);
			// read(fd_pipe[i - 1][0], bufs, 100);
			// ft_putstr_fd("The buffer is ", 1);
			// ft_putstr_fd(bufs, 1);
			// ft_putstr_fd("\n", 1);
			// exit(0);
		/*
				i = 0				i = 1				i = 2				i = 3
				echo a		|		echo b		|		echo c		|		echo d
		In	0	STDIN				P[0][0]				P[1][0]				P[2][0]
		Out	1	P[0][1]				P[1][1]				P[2][1]				STDOUT
		*/
		}
		ft_make_commands(mem, mem->tolken_list, tolken);
		tolken = tolken->prev;
		i++;
	}
	i = 0;
	while (i < mem->tolken_list->total - 1)
	{
		free(fd_pipe[i]);
		i++;
	}
	if (fd_pipe)
		free(fd_pipe);
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
			// print_tolken(mem->tolken_list);
			if (mem->tolken_list->total > 1)
				ft_send_tolken(mem);
			else
				ft_make_commands(mem, mem->tolken_list, mem->tolken_list->first);
			ft_free_tolken_list(mem->tolken_list);
			free(input);
		}
		dup2(mem->std_pipe[0], STDIN_FILENO);
		dup2(mem->std_pipe[1], STDOUT_FILENO);
	}
	close(mem->std_pipe[1]);
	close(mem->std_pipe[0]);
}

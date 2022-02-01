/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_arrow_left.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:25 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/31 14:14:49 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_here_input(char **input, char *eof)
{
	*input = readline("> ");
	if (!*input)
	{
		ft_putstr_fd("-MiniShell: warning: ", 2);
		ft_putstr_fd("here-document delimited by ", 2);
		ft_putstr_fd("end-of-file (wanted `", 2);
		ft_putstr_fd(eof, 2);
		ft_putstr_fd("')\n", 2);
		exit(0);
	}
}

void	start_prompt(int fd, char *eof)
{
	char	*input;

	while (1)
	{
		ft_read_here_input(&input, eof);
		if (input)
		{
			if (ft_strcmp(input, eof) == 0)
			{
				close(fd);
				free(input);
				break ;
			}
			ft_putendl_fd(input, fd);
			free(input);
		}
	}
	exit(0);
}

int	create_temporary(void)
{
	int	fd;

	fd = open("/tmp/file.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (-1);
	return (fd);
}

void	ft_make_tmp_file_input(void)
{
	int		tmp_fd;

	tmp_fd = open("/tmp/file.tmp", O_RDONLY);
	unlink("/tmp/file.tmp");
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
}

int	ft_d_arrow_left(t_mem *mem, char *eof)
{
	int		tmp_fd;
	int		save_fd;
	int		pid;
	int		status;

	tmp_fd = create_temporary();
	if (tmp_fd == -1)
		return (-1);
	save_fd = dup(STDOUT_FILENO);
	dup2(mem->std_pipe[1], STDOUT_FILENO);
	(void)mem;
	pid = fork();
	if (pid == 0)
		start_prompt(tmp_fd, eof);
	waitpid(pid, &status, 0);
	ft_make_tmp_file_input();
	dup2(save_fd, STDOUT_FILENO);
	close(save_fd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_arrow_left.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini- <fbonini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:25 by fbonini           #+#    #+#             */
/*   Updated: 2022/02/02 20:30:41 by fbonini-         ###   ########.fr       */
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

void	ft_start_prompt(int fd, char *eof)
{
	char				*input;
	struct sigaction	act;

	while (1)
	{
		ft_signals(&act, ft_sigint_heredoc, SIGINT);
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

int	ft_create_temporary(void)
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
	int					tmp_fd;
	int					save_fd;
	int					pid;
	int					status;
	struct sigaction	act;

	tmp_fd = ft_create_temporary();
	if (tmp_fd == -1)
		return (-1);
	ft_signals(&act, SIG_IGN, SIGINT);
	ft_signals(&act, SIG_IGN, SIGQUIT);
	save_fd = dup(STDOUT_FILENO);
	dup2(mem->std_pipe[1], STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
		ft_start_prompt(tmp_fd, eof);
	waitpid(pid, &status, 0);
	ft_make_tmp_file_input();
	dup2(save_fd, STDOUT_FILENO);
	close(save_fd);
	if (!WIFEXITED(status))
		return (130);
	else
		return (0);
}

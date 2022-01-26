/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_arrow_left.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:25 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/26 17:48:05 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	start_prompt(int fd, char **eof)
{
	char	*input;
	int		i;

	i = 0;
	while (1)
	{
		input = readline("> ");
		if (input)
		{
			if (ft_strcmp(input, eof[i]) == 0)
			{
				i++;
				if (eof[i] == NULL)
				{
					close(fd);
					free(input);
					break ;
				}
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

int	ft_d_arrow_left(char **eof)
{
	int		tmp_fd;
	int		pid;
	int		status;

	tmp_fd = create_temporary();
	if (tmp_fd == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		start_prompt(tmp_fd, eof);
	waitpid(pid, &status, 0);
	close(tmp_fd);
	return (0);
}

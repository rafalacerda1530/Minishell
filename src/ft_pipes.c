/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:40:21 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/26 14:32:49 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**ft_create_pipes(t_mem *mem)
{
	size_t	i;
	int		**fd_pipe;

	fd_pipe = (int **) malloc ((mem->tolken_list->total - 1) * sizeof(int *));
	i = 0;
	while (i < mem->tolken_list->total - 1)
	{
		fd_pipe[i] = (int *) malloc (2 * sizeof(int));
		if (pipe(fd_pipe[i]) < 0)
			return (NULL);
		i++;
	}
	return (fd_pipe);
}

void	ft_free_pipes(t_mem *mem, int **fd_pipe)
{
	size_t	i;

	i = 0;
	while (i < mem->tolken_list->total - 1)
	{
		free(fd_pipe[i]);
		i++;
	}
	if (fd_pipe)
		free(fd_pipe);
}

void	ft_send_pipes(t_mem *mem, int **fd_pipe, size_t i)
{
	if (i > 0)
	{
		dup2(fd_pipe[i - 1][0], STDIN_FILENO);
		close(fd_pipe[i - 1][0]);
	}
	if (i != mem->tolken_list->total - 1)
	{
		dup2(fd_pipe[i][1], STDOUT_FILENO);
		close(fd_pipe[i][1]);
	}
	else
		dup2(mem->std_pipe[1], STDOUT_FILENO);
}

void	ft_pipe_cmd(t_mem *mem)
{
	size_t		i;
	int			**fd_pipe;
	t_tolken	*tolken;

	tolken = mem->tolken_list->last;
	fd_pipe = ft_create_pipes(mem);
	i = 0;
	while (i < mem->tolken_list->total)
	{
		ft_send_pipes(mem, fd_pipe, i);
		if (ft_redirects(mem, tolken, tolken->content) == -1)
			break ;
		ft_make_commands(mem, tolken);
		tolken = tolken->prev;
		i++;
	}
	ft_free_pipes(mem, fd_pipe);
}

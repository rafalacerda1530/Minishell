/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_arrow_right.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:29 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/24 12:31:39 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_d_arrow_right(char *file)
{
	int	fd_file;

	// printf("Aqui the |%s|\n", file);
	fd_file = open(file, O_WRONLY | O_CREAT |  O_APPEND, 0777);
	// printf("Aqui the |%d|\n", fd_file);
	// if (fd_file == -1)
	// 	error_message("redirect", strerror(errno), 1);
	// else
	// {
		dup2(fd_file, STDOUT_FILENO);
		close(fd_file);
	// printf("Aqui the |%d|\n", STDOUT_FILENO);
	// }
	return 0;
}

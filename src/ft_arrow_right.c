/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrow_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:15 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/24 13:15:42 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_arrow_right(char *file)
{
	int	fd_file;

	// printf("the |%s|\n", file);
	fd_file = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	// if (fd_file == -1)
	// 	error_message("redirect", strerror(errno), 1);
	// else
	// {
		dup2(fd_file, STDOUT_FILENO);
		close(fd_file);
	// }
	return 0;
}

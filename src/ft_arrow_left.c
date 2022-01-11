/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrow_left.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:02 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/11 15:12:19 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_arrow_left(char *file)
{
	int	fd_file;

	fd_file = open(file, O_RDONLY | O_CREAT, 0777);
	// if (fd_file == -1)
	// 	error_message("redirect", strerror(errno), 1);
	// else
	// {
		dup2(fd_file, 1);
		close(fd_file);
	// }
	return 0;
}

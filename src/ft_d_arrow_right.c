/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_arrow_right.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:29 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/26 15:10:43 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_d_arrow_right(char *file)
{
	int	fd_file;

	fd_file = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd_file == -1)
		return (-1);
	else
	{
		dup2(fd_file, STDOUT_FILENO);
		close(fd_file);
	}
	return (0);
}

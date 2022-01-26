/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrow_left.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:02 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/26 15:05:49 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_arrow_left(char *file)
{
	int	fd_file;

	fd_file = open(file, O_RDONLY);
	if (fd_file == -1)
		return (-1);
	else
	{
		dup2(fd_file, STDIN_FILENO);
		close(fd_file);
	}
	return (0);
}

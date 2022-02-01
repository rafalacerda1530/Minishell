/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_std.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:02:59 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/31 14:15:16 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_copy_stds(t_mem *mem)
{
	mem->std_pipe[0] = dup(STDIN_FILENO);
	mem->std_pipe[1] = dup(STDOUT_FILENO);
}

void	ft_reset_stds(t_mem *mem)
{
	dup2(mem->std_pipe[0], STDIN_FILENO);
	dup2(mem->std_pipe[1], STDOUT_FILENO);
}

void	ft_close_copy_stds(t_mem *mem)
{
	close(mem->std_pipe[1]);
	close(mem->std_pipe[0]);
}

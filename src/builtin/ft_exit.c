/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:40 by fbonini           #+#    #+#             */
/*   Updated: 2022/02/01 16:32:23 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_mem(t_mem *mem)
{
	if (mem->tolken_list)
		ft_free_tolken_list(mem->tolken_list);
	ft_free_env_list(mem->env_list);
	free(mem->built_in);
	free(mem->keys);
}

int	ft_exit(t_mem *mem, int ret)
{
	if (mem->tolken_list->total > 1)
		return (0);
	ft_free_mem(mem);
	rl_clear_history();
	exit(ret);
}

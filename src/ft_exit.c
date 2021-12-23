/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarodrig < rarodrig@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:40 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/23 19:31:04 by rarodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_mem(t_mem *mem)
{
	ft_free_env_list(mem->env_list);
	free(mem->built_in);
	free(mem->keys);
}

int	ft_exit(t_mem *mem, int ret)
{
	ft_free_mem(mem);
	rl_clear_history();
    exit(ret);	
}

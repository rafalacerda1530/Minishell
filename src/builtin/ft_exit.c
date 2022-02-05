/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:40 by fbonini           #+#    #+#             */
/*   Updated: 2022/02/05 17:08:17 by fbonini          ###   ########.fr       */
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

int	ft_exit(t_mem *mem, t_env_list *list, char *ret)
{
	int	the_exit;

	(void)list;
	the_exit = 0;
	if (ret)
		the_exit = ft_atoi(ret);
	if (mem->tolken_list->total > 1)
		return (the_exit);
	ft_free_mem(mem);
	rl_clear_history();
	exit(the_exit);
}

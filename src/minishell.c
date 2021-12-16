/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 01:04:41 by Rarodrig          #+#    #+#             */
/*   Updated: 2021/12/16 11:44:33 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_alloc_mem(t_mem *mem)
{
	mem->env_list = ft_alloc_env_list();
	mem->tolken_list = ft_alloc_tolken_list();
}

int	main(int argc, char **argv, char **envp)
{
	t_mem	mem;

	(void) argc;
	(void) argv;
	ft_alloc_mem(&mem);
	ft_fill_env_list(mem.env_list,envp);
	ft_create_shell(&mem);
	ft_free_env_list(mem.env_list);
	return (0);
}

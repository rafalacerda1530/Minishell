/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 01:04:41 by Rarodrig          #+#    #+#             */
/*   Updated: 2021/12/24 20:08:23 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
	Codar o ?para o echo
	Coletar o retorno de todos as funções
*/
void	ft_alloc_mem(t_mem *mem)
{
	mem->print = NULL;
	mem->env_list = ft_alloc_env_list();
	mem->tolken_list = ft_alloc_tolken_list();
	mem->built_in = ft_alloc_built_in();
	mem->keys = ft_set_keys();
	mem->all_return = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_mem	mem;
	int		i;

	(void) argc;
	(void) argv;
	(void) envp;
	ft_alloc_mem(&mem);
	i = 0;
	while (envp[i] != (void *)0)
	{
		ft_fill_env_list(mem.env_list, envp[i], 'A');
		i++;
	}
	// ft_fill_env_list(mem.env_list, envp, 'A');
	ft_create_shell(&mem);
	ft_free_mem(&mem);
	return (0);
}

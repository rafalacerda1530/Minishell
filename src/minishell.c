/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 01:04:41 by Rarodrig          #+#    #+#             */
/*   Updated: 2022/01/26 17:09:09 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
	Codar o ?para o echo
	Coletar o retorno de todos as funções
	Precisa fazer retorno dos erros possiveis
*/
void	ft_alloc_mem(t_mem *mem)
{
	mem->env_list = ft_alloc_env_list(mem);
	mem->tolken_list = ft_alloc_tolken_list(mem);
	mem->built_in = ft_alloc_built_in(mem);
	mem->keys = ft_set_keys(mem);
	mem->all_return = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_mem	mem;
	int		i;

	(void) argc;
	(void) argv;
	ft_alloc_mem(&mem);
	i = 0;
	while (envp[i] != (void *)0)
	{
		ft_fill_env_list(&mem, mem.env_list, envp[i]);
		i++;
	}
	ft_create_shell(&mem);
	ft_free_mem(&mem);
	return (0);
}

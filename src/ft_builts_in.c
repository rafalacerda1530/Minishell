/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builts_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarodrig < rarodrig@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:13:06 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/18 19:30:47 by rarodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_get_built_in(t_funct *function)
{
	int	i;

	i = 0;
	function[i] = &ft_echo;
	function[++i] = &ft_cd;
	function[++i] = &ft_pwd;
	function[++i] = &ft_export;
	function[++i] = &ft_unset;
	function[++i] = &ft_env;
	function[++i] = &ft_exit;
	function[++i] = &ft_arrow_left;
	function[++i] = &ft_arrow_right;
	function[++i] = &ft_d_arrow_left;
	function[++i] = &ft_d_arrow_right;
	function[++i] = &ft_execv;
}

t_built_in	*ft_alloc_built_in(t_mem *mem)
{
	t_built_in	*built;

	built = (t_built_in *) malloc (sizeof(t_built_in));
	if (!built)
	{
		ft_memory_error();
		ft_exit(mem, 2);
	}
	ft_get_built_in(&built->function[0]);
	return (built);
}

int	ft_use_built_in(int (*funct)(), t_mem *mem, char *key)
{
	funct(mem, mem->env_list, key);
	return (0);
}

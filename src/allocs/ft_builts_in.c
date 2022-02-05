/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builts_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:13:06 by fbonini           #+#    #+#             */
/*   Updated: 2022/02/05 17:09:05 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	function[++i] = &ft_d_arrow_right;
	function[++i] = &ft_d_arrow_left;
}

t_built_in	*ft_alloc_built_in(t_mem *mem)
{
	t_built_in	*built;

	built = (t_built_in *) malloc (sizeof(t_built_in));
	if (!built)
	{
		ft_memory_error();
		ft_exit(mem, mem->env_list, "2");
	}
	ft_get_built_in(&built->function[0]);
	return (built);
}

int	ft_built_in(int (*funct)(), t_mem *mem, char *str, int key)
{
	if (key == 10)
	{
		dup2(mem->std_pipe[0], STDIN_FILENO);
		g_last_return = funct(mem, str);
	}
	else if (key > 6)
		g_last_return = funct(str);
	else
		g_last_return = funct(mem, mem->env_list, str);
	return (0);
}

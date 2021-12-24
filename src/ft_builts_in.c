/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builts_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:13:06 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/24 17:00:26 by fbonini          ###   ########.fr       */
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

t_built_in	*ft_alloc_built_in(void)
{
	t_built_in *built;

	built = (t_built_in *) malloc (sizeof(t_built_in));
	// if(built)
	// {
	// 	Error msg
	// }
	ft_get_built_in(&built->function[0]);
	return (built);
}

int	ft_use_built_in(int (*funct)(), t_mem *mem, char *key)
{
	funct(mem, mem->env_list, key);
	return 0;
}

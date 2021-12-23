/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarodrig < rarodrig@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:52:31 by coder             #+#    #+#             */
/*   Updated: 2021/12/23 19:01:109 by rarodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/*
int	ft_exit(ft_mem *mem, int resul)
{
	func_free_stop();
	return(mem->result_da_ultima_func)
}
*/

void	ft_free_mem(t_mem *mem)
{
	ft_free_env_list(mem->env_list);
	free(mem->built_in);
	free(mem->keys);
}

int main(void)
{
	int aux;

	aux = mem->return_all;
	ft_free_mem(mem);
	rl_clear_history();
    exit(aux);
}

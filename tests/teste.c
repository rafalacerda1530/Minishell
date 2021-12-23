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
int ft_unset(t_mem *mem)
{
	t_mem *aux;
	t_env_list	aux;
	int			i;
															1 2 3
	i = env_list->total;
	ft_bzero(&aux, sizeof(aux));
	aux.first = env_list->first;
	(void)str;
	while (i > 0)
	{
		if(!ft_strcmp(aux.first->key, key))
		{
			ft_free_env(mem->env_list, &aux.first);
			mem->all_return = 0;
			return(0);
		}
		aux.first = aux.first->next;
		i--;
	}
}
}
*/ 
int main(void)
{
	int aux;

	aux = mem->return_all;
	ft_free_mem(mem);
	rl_clear_history();
    exit(aux);
}

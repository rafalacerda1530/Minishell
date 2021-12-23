/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarodrig < rarodrig@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:55 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/23 20:28:12 by rarodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_unset(t_mem *mem, t_env_list *env_list, char *key)
{
	t_env_list	aux;
	int			i;
	i = env_list->total;
	ft_bzero(&aux, sizeof(aux));
	aux.first = env_list->first;
	while (i > 0)
	{
		
		if(!ft_strcmp(aux.first->key, key))
		{
			ft_free_env(mem->env_list, aux.first);
			mem->all_return = 0;
			return(0);
		}
		aux.first = aux.first->next;
		i--;
	}
	mem->all_return = 1;
	return(1);
}

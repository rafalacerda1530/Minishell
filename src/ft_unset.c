/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:55 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/24 17:52:37 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_unset(t_mem *mem, t_env_list *env_list, char *key)
{
	t_env_list	aux;
	int			i;
	i = env_list->total;
	ft_bzero(&aux, sizeof(aux));
	aux.last = env_list->last;
	while (i > 0)
	{
		if(!ft_strcmp(aux.last->key, key))
		{
			ft_free_env(mem->env_list, aux.last);
			mem->all_return = 0;
			return(0);
		}
		aux.last = aux.last->prev;
		i--;
	}
	mem->all_return = 1;
	return(1);
}

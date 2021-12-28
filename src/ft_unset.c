/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:55 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/28 08:17:23 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_mem *mem, t_env_list *env_list, char *key)
{
	t_env_list	aux;
	char		**split;
	int			total;
	int			i;

	ft_bzero(&aux, sizeof(aux));
	aux.last = env_list->last;
	split = ft_split(key, ' ');
	i = 0;
	while (split[i])
	{
		total = env_list->total;
		while (total > 0)
		{
			if (!ft_strcmp(aux.last->key, split[i]))
				ft_free_env(mem->env_list, aux.last);
			aux.last = aux.last->prev;
			total--;
		}
		i++;
	}
	ft_free_split(split);
	mem->all_return = 0;
	return (0);
}

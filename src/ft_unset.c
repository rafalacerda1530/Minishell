/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:55 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/29 18:20:44 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clear_envs(t_env_list *list, t_env_list *aux, char **split, int i)
{
	int	total;

	total = list->total;
	while (total > 0)
	{
		if (!ft_strcmp(aux->last->key, split[i]))
			ft_free_env(list, aux->last);
		aux->last = aux->last->prev;
		total--;
	}
}

int	ft_unset(t_mem *mem, t_env_list *env_list, char *key)
{
	t_env_list	aux;
	char		**split;
	int			i;

	ft_bzero(&aux, sizeof(aux));
	aux.last = env_list->last;
	split = ft_split(key, ' ');
	if (!split)
	{
		ft_memory_error();
		ft_exit(mem, 2);
	}
	i = 0;
	while (split[i])
	{
		ft_clear_envs(env_list, &aux, split, i);
		i++;
	}
	ft_free_split(split);
	mem->all_return = 0;
	return (0);
}

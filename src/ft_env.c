/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:36 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/27 18:12:56 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_mem *mem, t_env_list *env_list)
{
	int			i;
	t_env_list	aux;

	i = env_list->total;
	ft_bzero(&aux, sizeof(aux));
	aux.last = env_list->last;
	while (i > 0)
	{
		if (aux.last->tag == 'A')
		{
			ft_putstr_fd(aux.last->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(aux.last->content, 1);
			ft_putchar_fd('\n', 1);
		}
		aux.last = aux.last->prev;
		i--;
	}
	mem->all_return = 0;
	return (0);
}

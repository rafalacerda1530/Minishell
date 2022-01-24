/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:11:52 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/24 16:36:34 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_set_keys(t_mem *mem)
{
	char	**keys;
	int		i;

	i = 0;
	keys = (char **) malloc (sizeof(char *) * MAX_KEYS);
	if (!keys)
	{
		ft_memory_error();
		ft_exit(mem, 2);
	}
	keys[i] = "echo";
	keys[++i] = "cd";
	keys[++i] = "pwd";
	keys[++i] = "export";
	keys[++i] = "unset";
	keys[++i] = "env";
	keys[++i] = "exit";
	keys[++i] = "<";
	keys[++i] = ">";
	keys[++i] = ">>";
	keys[++i] = "<<";
	keys[++i] = "<>";
	keys[++i] = "\0";
	return (keys);
}

int	ft_check_key(char *str, char **keys)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str);
	while (i < MAX_KEYS)
	{
		if (!ft_strcmp(str, keys[i]))
			break ;
		i++;
	}
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:30:47 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/26 15:31:08 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_cd_arguments(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	ft_swap_pwd(char *pwd, char *oldpwd, t_env_list *env_list)
{
	ft_search_and_change(pwd, "OLDPWD", env_list);
	ft_search_and_change(oldpwd, "PWD", env_list);
}

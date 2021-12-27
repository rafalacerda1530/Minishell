/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 14:41:43 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/27 17:52:24 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_flag_n(char **str)
{
	int	n_flag;

	n_flag = 0;
	if (str[0][0] == '-' && str[0][1] == 'n')
	{
		(*str)++;
		(*str)++;
		while (**str == ' ')
			(*str)++;
		n_flag = 1;
	}
	return (n_flag);
}

int	ft_echo(t_mem *mem, char *str, t_env_list *env_list)
{
	int		i;
	int		flag_n;
	char	*print;

	i = 0;
	while (*str == ' ')
		str++;
	flag_n = ft_flag_n(&str);
	print = ft_get_string(str, env_list);
	ft_putstr_fd(print, 1);
	if (flag_n == 0)
		ft_putchar_fd('\n', 1);
	free(print);
	mem->all_return = 0;
	return (0);
}

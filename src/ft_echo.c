/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarodrig < rarodrig@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 14:41:43 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/18 18:14:03 by rarodrig         ###   ########.fr       */
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

	(void) env_list;
	i = 0;
	while (*str == ' ')
		str++;
	flag_n = ft_flag_n(&str);
	ft_putstr_fd(str, 1);
	if (flag_n == 0)
		ft_putchar_fd('\n', 1);
	mem->all_return = 0;
	return (0);
}

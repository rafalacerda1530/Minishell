/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 18:04:28 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/27 18:04:35 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_key_error(char *str)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

void	ft_content_error(void)
{
	ft_putstr_fd("export: ! is a special character, ", 2);
	ft_putstr_fd("use \\! or single quotes \n", 2);
}

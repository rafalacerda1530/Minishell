/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 19:30:01 by rarodrig          #+#    #+#             */
/*   Updated: 2022/01/27 09:55:38 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		// g_sh_status = 130;
	}
	else if (sig == SIGINT)
		exit(0);
}

void	ft_signals(struct sigaction *act, void (*handler)(int), int sig, t_mem *mem)
{
	act->sa_handler = handler;
	act->sa_flags = 0;
	sigemptyset(&act->sa_mask);
	sigaction(sig, act, NULL);
	(void)mem;
}

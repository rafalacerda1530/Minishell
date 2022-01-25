/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarodrig < rarodrig@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 19:30:01 by rarodrig          #+#    #+#             */
/*   Updated: 2022/01/25 19:54:56 by rarodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		// g_sh_status = 130;
	}
}

void	ft_signals(struct sigaction *act, void (*handler)(int), int sig, t_mem *mem)
{
	act->sa_handler = handler;
	act->sa_flags = 0;
	sigemptyset(&act->sa_mask);
	sigaction(sig, act, NULL);
	(void)mem;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini- <fbonini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 19:30:01 by rarodrig          #+#    #+#             */
/*   Updated: 2022/02/05 19:51:27 by fbonini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint_exec(int sig)
{
	(void)sig;
	g_last_return = 130;
	ft_putchar_fd('\n', 2);
}

void	ft_sigquit_exec(int sig)
{
	(void)sig;
	g_last_return = 131;
	ft_putstr_fd("Quit (core dumped)\n", 2);
}

void	ft_sigint_heredoc(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	exit(130);
}

void	ft_sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_last_return = 130;
	}
}

void	ft_signals(struct sigaction *act, void (*hand)(int), int sig)
{
	act->sa_handler = hand;
	act->sa_flags = 0;
	sigemptyset(&act->sa_mask);
	sigaction(sig, act, NULL);
}

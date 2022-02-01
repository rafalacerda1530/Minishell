/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 19:30:01 by rarodrig          #+#    #+#             */
/*   Updated: 2022/02/01 17:34:37 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
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
	sigaddset(&act->sa_mask, SIGINT);
	sigaction(sig, act, NULL);
}

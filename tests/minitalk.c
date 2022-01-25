/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarodrig < rarodrig@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:18:55 by rarodrig          #+#    #+#             */
/*   Updated: 2022/01/25 19:29:38 by rarodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>

void handler(int sig, siginfo_t *sinal, void* whatever)
{
	(void)whatever;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		// g_sh_status = 130;
	}
}

int main(void)
{
	struct sigaction	teste;
	// int sig;

	teste.sa_sigaction = handler;
	sigaction(SIGINT, &teste, NULL);
	while(1)
	{
		pause();
	}
}

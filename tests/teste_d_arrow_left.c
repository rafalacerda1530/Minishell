/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 23:17:06 by coder             #+#    #+#             */
/*   Updated: 2022/01/13 23:17:35 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <sys/stat.h>

static void	clear_tmp_file_input(void)
{
	int		tmp_fd;

	tmp_fd = open(TMP_FILE, O_WRONLY | O_TRUNC, 0600);
	close(tmp_fd);
}
}


void	ft_putendl_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}


int	ft_strncmp(const char *s1, const char *s2)
{
	size_t			cont;
	unsigned char	*n_s1;
	unsigned char	*n_s2;

	n_s1 = (unsigned char *) s1;
	n_s2 = (unsigned char *) s2;
	cont = 0;
	while ((n_s1[cont] != '\0' || n_s2[cont] != '\0'))
	{
		if (n_s1[cont] != n_s2[cont])
		{
			return (n_s1[cont] - n_s2[cont]);
		}
		cont++;
	}
	return (0);
}

void	start_prompt(int fd, char **eof)
{
	char	*input;
	int		i = 0;

	while (1)
	{
		input = readline("> ");
		if (input)
		{
			if (ft_strncmp(input, eof[i]))
			{
				ft_putendl_fd(input, fd);
			}
			else
			{
				i++;
				if (eof[i] == NULL)
				{
					close(fd);
					free(input);
					break ;
				}
				ft_putendl_fd(input, fd);
			}
			free(input);
		}
	}
	exit(0);
}

int create_temporary(void)
{
	int fd;

	fd = open("./tmp_file", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return -1;
	return (fd);
}

void ft_teste_red(char **eof)
{
	int		tmp_fd;
	int		pid;
	int		status;

	tmp_fd = create_temporary();
	if (tmp_fd == -1)
		return ;
	pid = fork();
	if (pid == 0)
		start_prompt(tmp_fd, eof);
	waitpid(pid, &status, 0);
	close(tmp_fd);
}

int main(void)
{
	char *teste[1];

	teste[0] = "EOF";
	teste[1] = "ABC";
	teste[2] = NULL;
	ft_teste_red(teste);
	return 0;
}

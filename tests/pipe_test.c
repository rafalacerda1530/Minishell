#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char *argv[], char **envp)
{
	int		pipe_fd[2];
	int		status;
	char	buf[10];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	printf("Child\n--------\n");
	write(pipe_fd[1], "Hi", 3);
	printf("Main\n-------\n");
	close(pipe_fd[1]);
	read(pipe_fd[0], buf, 3);
	close(pipe_fd[0]);
	printf("The buff %s\n", buf);
	return 0;
	// STDOUT_FILENO pipe[1]
	// STDIN_FILENO pipe[0]
}
/*

- Salvar IN/OUT Padroes, Na struct
- Inicia Minishell
- Separar com pipe e sem pipe
- Se tem pipe
	Loop até ultimo pipe
		- 1: Pegar fd do pipe 
		- 2: Executa comando no fd[1] do pipe
		- 3: Fecha fd[1] pipe
		- 4: Proximo comando le fd[0]
			- 4a: Se tiver pipe volta Passo 1
			- 4b: Se nao tiver escrever no STDOUT padrao

	- restaurar Saidas Padroes
		dup2(STDIN Salvo, STDIN Padrao);
		dup2(STDOUT Salvo, STDOUT Padrao);

*/
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void	redirect_output(char *file, int flags)
{
	int	fd_file;

	fd_file = open(file, flags, 0777);
	// if (fd_file == -1)
	// 	error_message("redirect", strerror(errno), 1);
	// else
	// {
		dup2(fd_file, 1);
		close(fd_file);
	// }
}

static void	redirect_input(char *file, int flags)
{
	int	fd_file;

	fd_file = open(file, flags);
	// if (fd_file == -1)
	// 	// error_message("redirect", strerror(errno), 1);
	// else
	// {
		dup2(fd_file, 0);
		close(fd_file);
	// }
}	

// void	ft_make_redirect()
// {
// 	if (!ft_strcmp(redirect, ">"))
// 		redirect_output(file, O_WRONLY | O_CREAT | O_TRUNC);
// 	else if (!ft_strcmp(redirect, "<"))
// 		redirect_input(file, O_RDONLY | O_CREAT);
// 	else if (!ft_strcmp(redirect, ">>"))
// 		redirect_output(file, O_WRONLY | O_CREAT | O_APPEND);
// 	else if (!ft_strcmp(redirect, "<<"))
// 		here_doc_input(file, save_fd);
// }

void	ft_make_pipe(int *the_pipe)
{
	int	new_pipe[2];

	dup2(*the_pipe, STDIN_FILENO);
	if (*the_pipe != 0)
		close(*the_pipe);
	pipe(new_pipe);
	dup2(new_pipe[1], STDOUT_FILENO);
	close(new_pipe[1]);
	*the_pipe = dup(new_pipe[0]);
	close(new_pipe[0]);
}

int	main (void)
{
	// int	get_fd[2];
	// int	the_pipe;

	// the_pipe = 0;
	// get_fd[0] = dup(STDIN_FILENO);
	// get_fd[1] = dup(STDOUT_FILENO);
	int a = O_RDONLY;
	int	b = O_WRONLY;
	int	c = O_CREAT;
	int	d = O_TRUNC;
	int	e = O_APPEND;

	// redirect_output("aqui.txt", O_WRONLY | O_CREAT | O_TRUNC);     >
	// redirect_input("aqui2.txt", O_RDONLY | O_CREAT);               <
	// redirect_output("aqui.txt", O_WRONLY | O_CREAT | O_APPEND);    >>
	printf("%d\n", a);
	printf("%d\n", b);
	printf("%d\n", c);
	printf("%d\n", d);
	printf("%d\n", e);
	printf("------------\n");
	printf("%d\n", b + c + d);
	printf("%d\n", a + c);
	printf("%d\n", b + c + e);
	// printf("------------\n");
	return 0;
}
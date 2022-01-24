#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	ft_arrow_left(char *file)
{
	int	fd_file;

	fd_file = open(file, O_RDONLY);
	if (fd_file == -1)
	{
		printf("Aqui\n");
	}
	// 	error_message("redirect", strerror(errno), 1);
	// else
	return 0;
}

int main (void)
{
	ft_arrow_left("123");
	return 0;
}
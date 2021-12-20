/*
execute:
	Initiante: ../ ./ /

Search Key Function:
	echo < Done +-
	cd
	pwd
	export
	unset
	env
	exit
	<
	>
	<<
	>>

	# define MAX_KEYS 10

	Char *keys[MAX_KEYS]
		[0] echo
		[1] pwd
		[2] export
		[3] unset
		[4] env
		[5] exit
		[6] <
		[7] >
		[8] <<
		[9] >>
		[10] \0
*/
#include <stdio.h>
#include <stdlib.h>
# define MAX_KEYS 10

typedef int	(*t_funct)();

typedef struct s_built_in
{
	t_funct	function[MAX_KEYS];
}			t_built_in;

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			cont;
	unsigned char	*n_s1;
	unsigned char	*n_s2;

	n_s1 = (unsigned char *) s1;
	n_s2 = (unsigned char *) s2;
	cont = 0;
	while ((n_s1[cont] != '\0' || n_s2[cont] != '\0') && cont < n)
	{
		if (n_s1[cont] != n_s2[cont])
		{
			return (n_s1[cont] - n_s2[cont]);
		}
		cont++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	cont;

	cont = 0;
	while (*s != 0)
	{
		++s;
		cont++;
	}
	return (cont);
}

int	ft_echo(void)
{
	printf("Function echo\n");
	return 0;
}

int	ft_pwd(void)
{
	printf("Function pwd\n");
	return 0;
}

int	ft_export(void)
{
	printf("Function export\n");
	return 0;
}

int	ft_unset(void)
{
	printf("Function unset\n");
	return 0;
}

int	ft_env(void)
{
	printf("Function env\n");
	return 0;
}

int	ft_exit(void)
{
	printf("Function exit\n");
	return 0;
}

int	ft_arrow_right(void)
{
	printf("Function >\n");
	return 0;
}

int	ft_arrow_left(void)
{
	printf("Function <\n");
	return 0;
}

int	ft_d_arrow_right(void)
{
	printf("Function >>\n");
	return 0;
}

int	ft_d_arrow_left(void)
{
	printf("Function <<\n");
	return 0;
}

int	ft_built_in_error(void)
{
	printf("Function error\n");
	return 0;
}

void	ft_get_built_in(t_funct *function)
{
	int	i;

	i = 0;
	function[i] = &ft_echo;
	function[++i] = &ft_pwd;
	function[++i] = &ft_export;
	function[++i] = &ft_unset;
	function[++i] = &ft_env;
	function[++i] = &ft_exit;
	function[++i] = &ft_arrow_left;
	function[++i] = &ft_arrow_right;
	function[++i] = &ft_d_arrow_left;
	function[++i] = &ft_d_arrow_right;
	function[++i] = &ft_built_in_error;
}


int	ft_built_in(int (*funct)())
{
	funct();
}

int main (int argc, char **argv)
{
	int i = 0;
	char *key[MAX_KEYS];
	t_built_in	*built;

	key[0] = "echo";
	key[1] = "pwd";
	key[2] = "export";
	key[3] = "unset";
	key[4] = "env";
	key[5] = "exit";
	key[6] = "<";
	key[7] = ">";
	key[8] = "<<";
	key[9] = ">>";
	key[10] = "\0";
	
	printf("The arg: %s\n", argv[1]);
	built = (t_built_in *) malloc (sizeof(t_built_in));
	ft_get_built_in(&built->function[0]);
	while (i < MAX_KEYS)
	{
		if (!ft_strncmp(argv[1], key[i], ft_strlen(argv[1])))
			break ;
		i++;
	}
	ft_built_in(built->function[i]);
	return 0;
}
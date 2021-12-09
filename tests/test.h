#ifndef TEST_H
# define TEST_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>


typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*key;
	char			*content;
}			t_env;

typedef struct s_env_list
{
	t_env			*first;
	t_env			*last;
	unsigned int	total;
}			t_env_list;

typedef struct s_mem
{
	t_env_list		*env_list;
}			t_mem;

#endif
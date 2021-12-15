#ifndef TEST_H
# define TEST_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h> // need to delete, can't use


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


typedef struct s_tolken
{
	struct s_tolken	*next;
	struct s_tolken	*prev;
	char			*key;
	char			*content;
	int				size;
}			t_tolken;

typedef struct s_tolken_list
{
	t_tolken			*first;
	t_tolken			*last;
	unsigned int		total;
}			t_tolken_list;


// typedef struct s_parse
// {
// 	struct s_env	*next;
// 	struct s_env	*prev;
// 	char			*parsed;
// }			t_parse;

// typedef struct s_parse_list
// {
// 	t_env			*first;
// 	t_env			*last;
// 	unsigned int	total;
// }			t_parse_list;

typedef struct s_mem
{
	// t_env_list		*env_list;
	t_tolken_list	*tolken_list;
}			t_mem;

#endif
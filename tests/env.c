/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:28:54 by fbonini-          #+#    #+#             */
/*   Updated: 2021/12/15 18:12:57 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/* ---------------------------------------------     --------------------------------------------- */
/* --------------------------------------------- Env --------------------------------------------- */
/* ---------------------------------------------     --------------------------------------------- */
t_env_list	*ft_alloc_env_list(void)
{
	t_env_list	*env_list;
	
	env_list = (t_env_list *) malloc (sizeof(t_env_list));
	// if (!env_list)
	// {
		// Free Error msg
	// }
	env_list->first = NULL;
	env_list->last = NULL;
	env_list->total = 0;
	return (env_list);
}

t_env	*ft_alloc_env(char *envp)
{
	t_env	*env;
	int		key_size;
	int		content_size;

	key_size = 0;
	content_size = 0;
	while (envp[key_size] != '=')
		key_size++;
	while (envp[key_size + content_size + 1] != '\0')
		content_size++;
	env = (t_env *) malloc (sizeof(t_env));
	// if (!env)
	// {
		// Free Error msg
	// }
	env->key = (char *) malloc ((key_size + 1) * sizeof(char));
	// if (!env->key)
	// {
		// Free Error msg
	// }
	strncpy(env->key, envp, key_size); // Using STRING.H
	env->content = (char *) malloc ((content_size + 1) * sizeof(char));
	// if (!env->content)
	// {
		// Free Error msg
	strncpy(env->content, &envp[key_size + 1], content_size); // Using STRING.H
	env->next = env;
	env->prev = env;
	return (env);
}

void	ft_fill_env_list(t_env_list *env_list, char **envp)
{
	t_env	*env;

	while (*envp != 0)
	{
		env = ft_alloc_env(*envp);
		if (env_list->total == 0)
			env_list->last = env;
		else
		{
			env->next = env_list->first;
			env_list->first->prev = env;
			env->prev = env_list->last;
			env_list->last->next = env;
		}
		env_list->first = env;
		env_list->total++;
		envp++;
	}
}

void	ft_free_env(t_env_list *env_list, t_env *env)
{
	if (env_list->first == env)
	{
		if (env_list->last == env)
		{
			env_list->first = NULL;
			env_list->last = NULL;
		}
		else
		{
			env_list->first = env->next;
			env_list->last->next = env->next;
			env->next->prev = env_list->last;
		}
	}
	else
	{
		if (env_list->last == env)
			env_list->last = env->prev;
		env->prev->next = env->next;
		env->next->prev = env->prev;
	}
	env_list->total--;
	free(env);
}

void	ft_free_env_list(t_env_list *env_list)
{
	while(env_list->total != 0)
	{
		free(env_list->first->key);
		free(env_list->first->content);
		ft_free_env(env_list,env_list->first);
	}
	free(env_list);
}

void	print_env(t_env_list *env_list, char **envp)
{
	t_env	*env;
	int		total;

	env = NULL;
	env = env_list->last;
	printf("the envp is %s\n", envp[0]);
	printf("The key is: %s	the content is: %s\n", env->key, env->content);
	printf("\n\n------Get PWD--------\n");
	total = env_list->total;
	env = env_list->last;
	while (total != 0)
	{
		// if (strncmp(env->key,"PWD", 3) == 0)  // Using STRING.H
			printf("%s			%s\n", env->key, env->content);
		env = env->next;
		total--;
	}
}
/* ---------------------------------------------     --------------------------------------------- */
/* --------------------------------------------- Env --------------------------------------------- */
/* ---------------------------------------------     --------------------------------------------- */


/* ---------------------------------------------     --------------------------------------------- */
/* ---------------------------------------- Token List ------------------------------------------ */
/* ---------------------------------------------     --------------------------------------------- */

void	print_tolken(t_tolken_list *tolken_list)
{
	t_tolken	*tolken;
	int		total;

	tolken = NULL;
	tolken = tolken_list->last;
	total = tolken_list->total;
	tolken = tolken_list->last;
	while (total != 0)
	{
	// 	// if (strncmp(env->key,"PWD", 3) == 0)  // Using STRING.H
		printf("The I is %d The Size is %d\n", total, tolken_list->total);
		tolken = tolken->next;
		total--;
	}
}

t_tolken_list	*ft_alloc_tolken_list(void)
{
	t_tolken_list	*tolken_list;
	
	tolken_list = (t_tolken_list *) malloc (sizeof(t_tolken_list));
	// if (!env_list)
	// {
		// Free Error msg
	// }
	tolken_list->first = NULL;
	tolken_list->last = NULL;
	tolken_list->total = 0;
	return (tolken_list);
}

t_tolken	*ft_alloc_tolken(char *input)
{
	t_tolken	*tolken;
	int			i;
	int			key;
	int			content;

	i = 0;
	key = 0;
	content = 0;
	while(input[i] == ' ')
	{
		i++;
		// printf("Aqui\n");
	}
	while (input[i + key] != ' ')
	{
		key++;
	}
	while (input[i + key + content + 1] != '\0')
	{
		if (input[i + key + content + 1] == '"')
		{
			while (input[i + key + content + 1] != '"')
				content++;
		}
		if (input[i + key + content + 1] == '\'')
		{
			while (input[i + key + content + 1] != '\'')
				content++;
		}
		if (input[i + key + content + 1] == '|')
			break;
		content++;
	}
	tolken = (t_tolken *) malloc (sizeof(t_tolken));
	tolken->key = (char *) malloc ((key + 1) * sizeof(char));
	strncpy(tolken->key, &input[i], key);// Using STRING.
	tolken->content = (char *) malloc ((content + 1) * sizeof(char));
	strncpy(tolken->content, &input[i + key + 1], content); // Using STRING.H
	tolken->size = key + content;
	tolken->next = tolken;
	tolken->prev = tolken;
	return (tolken);
}

// input[0]
// &input[| + 1]
// &input[| + 1]

void	ft_fill_tolken_list(t_tolken_list *tolken_list, char *input)
{
	t_tolken	*tolken;
	int			i;

	i = 0;
	while (input[i] != '\0')
	{
		tolken = ft_alloc_tolken(&input[i]);
		if (tolken_list->total == 0)
			tolken_list->last = tolken;
		else
		{
			tolken->next = tolken_list->first;
			tolken_list->first->prev = tolken;
			tolken->prev = tolken_list->last;
			tolken_list->last->next = tolken;
		}
		tolken_list->first = tolken;
		tolken_list->total++;
		printf("The Key is %s The Content is %s\n", tolken_list->first->key, tolken_list->first->content);
		i = i + tolken_list->first->size + 2;
	}
}

void	ft_free_tolken(t_tolken_list *tolken_list, t_tolken *tolken)
{
	if (tolken_list->first == tolken)
	{
		if (tolken_list->last == tolken)
		{
			tolken_list->first = NULL;
			tolken_list->last = NULL;
		}
		else
		{
			tolken_list->first = tolken->next;
			tolken_list->last->next = tolken->next;
			tolken->next->prev = tolken_list->last;
		}
	}
	else
	{
		if (tolken_list->last == tolken)
			tolken_list->last = tolken->prev;
		tolken->prev->next = tolken->next;
		tolken->next->prev = tolken->prev;
	}
	tolken_list->total--;
	free(tolken);
}

void	ft_free_tolken_list(t_tolken_list *tolken_list)
{
	while(tolken_list->total != 0)
	{
		tolken_list->first->size = 0;
		free(tolken_list->first->key);
		free(tolken_list->first->content);
		ft_free_tolken(tolken_list,tolken_list->first);
	}
}


/* ---------------------------------------------     --------------------------------------------- */
/* ---------------------------------------- Token List ------------------------------------------ */
/* ---------------------------------------------     --------------------------------------------- */


/* ---------------------------------------------     --------------------------------------------- */
/* ---------------------------------------- Token Split ------------------------------------------ */
/* ---------------------------------------------     --------------------------------------------- */

// void	ft_create_tolken(t_mem *mem, char *input)
// {
// 	int	i;

// 	// Key
// 	while(input[i] != ' ')
// 	{
		
// 	}
// }
//a
/* ---------------------------------------------     --------------------------------------------- */
/* ---------------------------------------- Token Split ------------------------------------------ */
/* ---------------------------------------------     --------------------------------------------- */


/* ---------------------------------------------     --------------------------------------------- */
/* ------------------------------------------- History ------------------------------------------- */
/* ---------------------------------------------     --------------------------------------------- */

void	ft_create_history(char *input)
{
	if (input && *input)
		add_history(input);
}

/* ---------------------------------------------     --------------------------------------------- */
/* ------------------------------------------- History ------------------------------------------- */
/* ---------------------------------------------     --------------------------------------------- */

/* ---------------------------------------------     --------------------------------------------- */
/* ----------------------------------------- Basic Shell ----------------------------------------- */
/* ---------------------------------------------     --------------------------------------------- */

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*nstr;
	size_t	i;
	size_t	cont;

	i = ft_strlen(s1);
	nstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	cont = 0;
	if (nstr == NULL)
		return (NULL);
	if (!s1 || !s2)
		return (NULL);
	while (s1[cont])
	{
		nstr[cont] = s1[cont];
		cont++;
	}
	i = 0;
	while (s2[i])
	{
		nstr[cont] = s2[i];
		i++;
		cont++;
	}
	nstr[cont] = '\0';
	return (nstr);
}

void	ft_read_input(char **input)
{
	char	*prompt;
	char	intro[3];
	char	*msg;

	intro[0] = '$';
	intro[1] = ' ';
	intro[2] = '\0';
	prompt = NULL;
	prompt = getcwd(prompt, 0);
	msg = ft_strjoin(prompt, intro);
	*input = readline(msg);
	free(msg);
	free(prompt);
}

void	ft_create_shell(t_mem *mem)
{
	char	*input;
	// int		parse;

	while (1)
	{
		input = NULL;
		ft_read_input(&input);
		ft_create_history(input);
		ft_fill_tolken_list(mem->tolken_list, input);
		// print_tolken(mem->tolken_list);
		// ft_create_tolken(mem, input);
		// parse = ft_parse_input(input);
		printf("The input was:\n%s\n", input);
		if (input)
		{
			ft_free_tolken_list(mem->tolken_list);
			free(input);
		}
	}
	rl_clear_history();
}

/* ---------------------------------------------     --------------------------------------------- */
/* ----------------------------------------- Basic Shell ----------------------------------------- */
/* ---------------------------------------------     --------------------------------------------- */


/* ---------------------------------------------     --------------------------------------------- */
/* --------------------------------------- Memory Control ---------------------------------------- */
/* ---------------------------------------------     --------------------------------------------- */

void	ft_alloc_mem(t_mem *mem)
{
	// mem->env_list = ft_alloc_env_list();
	mem->tolken_list = ft_alloc_tolken_list();
}

/* ---------------------------------------------     --------------------------------------------- */
/* --------------------------------------- Memory Control ---------------------------------------- */
/* ---------------------------------------------     --------------------------------------------- */

int	main(int argc, char **argv, char **envp)
{
	t_mem	mem;

	(void) argc;
	(void) argv;
	(void) envp;
	ft_alloc_mem(&mem);
	// ft_fill_env_list(mem.env_list,envp);
	// print_env(mem.env_list, envp);
	// ft_free_env_list(mem.env_list);
	ft_create_shell(&mem);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini- <fbonini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:28:54 by fbonini-          #+#    #+#             */
/*   Updated: 2021/12/08 22:16:50 by fbonini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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

t_env	*ft_alloc_env(t_env_list *env_list, char *envp)
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
	// }
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
		env = ft_alloc_env(env_list, *envp);
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

void	ft_alloc_mem(t_mem *mem)
{
	mem->env_list = ft_alloc_env_list();
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

int	main(int argc, char **argv, char **envp)
{
	t_mem	mem;
	t_env	*env;
	int		total;

	printf("the envp is %s\n", envp[0]);
	ft_alloc_mem(&mem);
	ft_fill_env_list(mem.env_list,envp);
	env = NULL;
	env = mem.env_list->last;
	printf("The key is: %s	the content is: %s\n", env->key, env->content);
	printf("\n\n------Get PWD--------\n");
	total = mem.env_list->total;
	env = mem.env_list->first;
	while (total != 0)
	{
		if (strncmp(env->key,"PWD", 3) == 0)  // Using STRING.H
			printf("%s			%s\n", env->key, env->content);
		env = env->next;
		total--;
	}
	ft_free_env_list(mem.env_list);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:08:08 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/24 15:47:44 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_env	*ft_alloc_env(char *envp, char tag)
{
	t_env	*env;
	int		key_size;
	int		content_size;

	key_size = 0;
	content_size = 0;
	ft_get_env_sizes(&key_size, &content_size, envp);
	env = (t_env *) malloc (sizeof(t_env));
	// if (!env)
	// {
		// Free Error msg
	// }
	ft_create_env_strings(env, key_size, content_size, envp);
	env->next = env;
	env->prev = env;
	env->tag = tag;
	return (env);
}

void	ft_fill_env_list(t_env_list *env_list, char **envp, char tag)
{
	t_env	*env;

	while (*envp != 0)
	{
		env = ft_alloc_env(*envp, tag);
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

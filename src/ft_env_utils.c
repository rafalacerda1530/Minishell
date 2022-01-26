/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:10:07 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/26 17:22:12 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_get_env_sizes(int *key_size, int *size, char *envp)
{
	while (envp[*key_size] != '=')
	{
		(*key_size)++;
		if (envp[*key_size] == '\0')
			return ;
	}
	while (envp[*key_size + *size + 1] != '\0')
		(*size)++;
}

void	ft_create_env_str(t_env *env, int key_size, int size, char *envp)
{
	env->key = (char *) malloc ((key_size + 1) * sizeof(char));
	if (!env->key)
	{
		free (env->key);
		return ;
	}
	ft_strlcpy(env->key, envp, key_size + 1);
	env->content = (char *) malloc ((size + 1) * sizeof(char));
	if (!env->content)
	{
		free(env->key);
		free(env->content);
		return ;
	}
	ft_strlcpy(env->content, &envp[key_size + 1], size + 1);
}

char	*ft_get_env(char *key, t_env_list *env_list)
{
	int			i;
	char		*path;
	t_env_list	aux;

	i = env_list->total;
	ft_bzero(&aux, sizeof(t_env_list));
	aux.first = env_list->first;
	path = NULL;
	while (i > 0)
	{
		if (!ft_strcmp(key, aux.first->key))
		{
			path = ft_strdup(aux.first->content);
			return (path);
		}
		aux.first = aux.first->next;
		i--;
	}
	return (path);
}

void	ft_search_and_change(char *str, char *key, t_env_list *env_list)
{
	t_env_list	aux;
	int			i;

	i = env_list->total;
	ft_bzero(&aux, sizeof(aux));
	aux.first = env_list->first;
	(void)str;
	while (i > 0)
	{
		if (!ft_strcmp(aux.first->key, key))
		{
			free(aux.first->content);
			aux.first->content = ft_strdup(str);
			break ;
		}
		aux.first = aux.first->next;
		i--;
	}
}

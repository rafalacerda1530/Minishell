/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:10:07 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/16 12:14:52 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_get_env_sizes(int *key_size, int *content_size, char *envp)
{
	while (envp[*key_size] != '=')
		(*key_size)++;
	while (envp[*key_size + *content_size + 1] != '\0')
		(*content_size)++;
}

void	ft_create_env_strings(t_env *env, int key_size, int content_size, char *envp)
{
	env->key = (char *) malloc ((key_size + 1) * sizeof(char));
	// if (!env->key)
	// {
		// Free Error msg
	// }
	ft_strlcpy(env->key, envp, key_size);
	env->content = (char *) malloc ((content_size + 1) * sizeof(char));
	// if (!env->content)
	// {
		// Free Error msg
	ft_strlcpy(env->content, &envp[key_size + 1], content_size);
}

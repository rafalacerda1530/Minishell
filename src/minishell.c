/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 01:04:41 by Rarodrig          #+#    #+#             */
/*   Updated: 2021/12/21 15:52:22 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/* \/ Print para checkar \/ */
void	print_env(t_env_list *env_list, char **envp)
{
	t_env	*env;
	int		total;

	env = NULL;
	env = env_list->last;
	printf("\n----------------------Printando variaveis de ambiente------------------------\n");
	printf("the envp is %s\n", envp[0]);
	printf("The key is: %s\nthe Env is: %s\n------\n", env->key, env->content);
	// printf("\n\n------Get PWD--------\n");
	total = env_list->total;
	env = env_list->last;
	while (total != 0)
	{
		// if (strncmp(env->key,"PWD", 3) == 0)  // Using STRING.H
		printf("The Key Env is >> %s \nThe Env is >> %s\n\n", env->key, env->content);
		env = env->prev;
		total--;
	}
	printf("\n----------------------Fim------------------------\n");
}

/* /\ Print para checkar /\ */

void	ft_alloc_mem(t_mem *mem)
{
	mem->print = NULL;
	mem->env_list = ft_alloc_env_list();
	mem->tolken_list = ft_alloc_tolken_list();
	mem->built_in = ft_alloc_built_in();
	mem->keys = ft_set_keys();
}

void	ft_free_mem(t_mem *mem)
{
	ft_free_env_list(mem->env_list);
	free(mem->built_in);
	free(mem->keys);
}

int	main(int argc, char **argv, char **envp)
{
	t_mem	mem;

	(void) argc;
	(void) argv;
	ft_alloc_mem(&mem);
	ft_fill_env_list(mem.env_list, envp);
	print_env(mem.env_list, envp);
	ft_create_shell(&mem);
	ft_free_mem(&mem);
	return (0);
}

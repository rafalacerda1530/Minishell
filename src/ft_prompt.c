/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:42:41 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/21 23:22:52 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char *get_value(t_mem *mem, char *key)
// {
// 	int i;
// 	t_env aux;

// 	aux = mem->env_list->last;
// 	i = env_list->total;
// 	while(i > 0)
//     {
//         if (!ft_strcmp(aux->key, key))
//         {
//            return(aux->content);
//         }
//         aux = aux->next;
// 		i--;
//     }
// }

int get_old(t_mem *mem)
{
	t_env *aux = NULL;
	char str[4096];
	char *str_aux;
	int i;

	i =  mem->env_list->total;
	aux = mem->env_list->last;
    while(i > 0)
    {
        if (!ft_strcmp(aux->key, "OLDPWD"))
        {
			str_aux = aux->content;
			printf("mizera = %s\n", str_aux);
			printf("oldpwd = %s\n", aux->content);
			aux->content = getcwd(str, 4096);
			printf("oldpwd = %s\n", aux->content);
            break;
        }
        aux = aux->next;
		i--;
    }
	printf("mizera = %s\n", str_aux);
	i =  mem->env_list->total;
	aux = mem->env_list->last;
	while(i > 0)
    {
        if (!ft_strcmp(aux->key, "PWD"))
        {
			aux->content = str_aux;
            break;
        }
        aux = aux->next;
		i--;
    }
	printf("str_aux = %s\n", str_aux);
	chdir(str_aux);
	return (0);
}

/* \/ Print para checkar \/ */
void	print_tolken(t_tolken_list *tolken_list)
{
	t_tolken	*tolken;
	int			total;

	tolken = NULL;
	total = tolken_list->total;
	tolken = tolken_list->last;
	printf("\n----------------------Tolkens Criados------------------------\n");
	while (total != 0)
	{
		printf("The Key is >> %s\nThe Command is >> %s\n", tolken->key, tolken->content);
		tolken = tolken->prev;
		total--;
	}
	printf("\n----------------------Fim------------------------\n");
}
/* /\ Print para checkar /\ */

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

void	ft_create_history(char *input)
{
	if (input && *input)
		add_history(input);
}

void	ft_actions(t_mem *mem)
{
	int	key;

	key = ft_check_key(mem->tolken_list->first->key, mem->keys);
	ft_use_built_in(mem->built_in->function[key]);
}

void	ft_create_shell(t_mem *mem)
{
	char	*input;

	(void)mem;
	while (1)
	{
		input = NULL;
		ft_read_input(&input);
		ft_create_history(input);
		//ft_pwd();
		// // print_tolken(mem->tolken_list);
		//ft_echo(mem, mem->tolken_list->last->content, mem->env_list);
		if (input)
		{
			ft_fill_tolken_list(mem->tolken_list, input);
			get_old(mem);
			/* \/ Precisar criar função pra loop quando usar pipes \/ */
			if (mem->tolken_list->first)
				ft_actions(mem);
			/* /\ Precisar criar função pra loop quando usar pipes /\ */
			ft_free_tolken_list(mem->tolken_list);
			free(input);
		}
	}
	rl_clear_history();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:52:31 by coder             #+#    #+#             */
/*   Updated: 2021/12/21 22:11:05 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"


int get_home(t_mem *mem)
{
	t_env *aux = NULL;
	int i;

	i =  mem->env_list->total;
	aux = mem->env_list->last;
	printf("key = %s\n", aux->next->key);
    while(i > 0)
    {
		printf("key = %s\n", aux->key);
        if (!ft_strncmp(aux->key, "HOME", 5))
        {
			
            chdir(aux->content);
            break;
        }
        aux = aux->next;
		i--;
    }
	return (0);
}



/*
int get_home(t_mem *mem)
{
    int i;
	t_env *aux;
	
	aux = mem->env_list->first;
    i = mem->env_list->total;
    while(i > 0)
    {
        if (ft_strncmp(aux->key, "HOME", 4))
        {
            chdir(aux->content)
            break;
        }
        aux = aux->next;
        i--;
    }
}

int ft_cd(char *content, t_mem *mem)
{
    int resul;

    else if(content = " " || content == NULL '\0' || content == "~")
        get_home(mem);
    else if (content == "-")
        func para o ultimo caminho OLDPWD
    if (len de content > 1)
        printa erro 
    resul = chdir(content);
    if (resul != 0)
        printa erro

}
*/

int main(void)
{
    char *path[2021];
    char *resul;

    resul = getcwd(*path, 2021);

    while(1)
    {
        chdir("/home/coder/Desktop/Minishell/Minishell");
        // printf("teste = %d\n",chdir("/home/coder/Desktop/Minishell/Minishell"));
    }
    return (0);
}

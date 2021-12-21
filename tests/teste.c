/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:52:31 by coder             #+#    #+#             */
/*   Updated: 2021/12/21 20:50:18 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"


/*
    
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

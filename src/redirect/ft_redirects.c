/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:04:26 by fbonini           #+#    #+#             */
/*   Updated: 2022/02/01 17:36:04 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_call_redirect(t_mem *mem, t_tolken *tolken, char *str, t_redir *vars)
{
	char	*file;
	size_t	i;
	int		value;

	i = ft_strlen(vars->key);
	if (strcmp(vars->aux, vars->key) == 0)
		file = ft_get_file_name(str, vars->i + i + 1);
	else
		file = ft_get_file_name(str, vars->i + i);
	value = ft_check_key(vars->key, mem->keys);
	ft_new_str(tolken, vars->aux, vars->key, file);
	if (value != 11)
		ft_built_in(mem->built_in->function[value], mem, file, value);
	else
	{
		ft_arrow_left(file);
		ft_arrow_right(file);
	}
	free(file);
}

char	*ft_new_tmp(char *str, char *aux, char *key)
{
	int		i;
	char	*ret;
	char	*tmp;

	ret = NULL;
	tmp = NULL;
	if (ft_strcmp(aux, key) == 0)
		i = 3;
	else
		i = 1;
	while (str[i] != ' ' && str[i] != '\0')
	{
		ft_add_char(&tmp, &ret, str[i]);
		i++;
	}
	return (ret);
}

int	ft_check_string(t_mem *mem, t_tolken *tolken, char *str, int *j)
{
	t_redir	vars;

	ft_bzero(&vars, sizeof(t_redir));
	vars.i = *j;
	*j = ft_break_str(&vars, str, *j);
	if (ft_strcmp(vars.key, "<<") == 0)
	{
		vars.tmp = ft_new_tmp(&str[*j - 2], vars.aux, vars.key);
		ft_built_in(mem->built_in->function[10], mem, vars.tmp, 10);
		ft_new_str(tolken, vars.aux, vars.key, vars.tmp);
		free(vars.tmp);
	}
	else
		ft_call_redirect(mem, tolken, str, &vars);
	ft_free_two_to_four(vars.key, vars.aux, NULL, NULL);
	return (1);
}

int	ft_redirects(t_mem *mem, t_tolken *tolken, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < tolken->numb_redir && str[j] != '\0')
	{
		if (str[j] == '>' || str[j] == '<')
		{
			if (tolken->redir[i] == 0)
			{
				while (str[j] != ' ' && str[j + 1] != '\0')
					j++;
				i++;
			}
			else if (tolken->redir[i] == 1)
			{
				if (!ft_check_string(mem, tolken, str, &j))
					return (-1);
			}
		}
		j++;
	}
	return (1);
}
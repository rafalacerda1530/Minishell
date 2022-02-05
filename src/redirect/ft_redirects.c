/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:04:26 by fbonini           #+#    #+#             */
/*   Updated: 2022/02/05 15:18:24 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_call_redirect(t_mem *mem, t_tolken *tolken, char *str, t_redir *vars)
{
	char	*name;
	size_t	i;
	int		value;

	i = ft_strlen(vars->key);
	if (strcmp(vars->aux, vars->key) == 0)
		name = ft_get_file_name(str, vars->i + i + 1);
	else
		name = ft_get_file_name(str, vars->i + i);
	if (!name)
		return ;
	value = ft_check_key(vars->key, mem->keys);
	ft_new_str(tolken, vars->aux, vars->key, name);
	if (value != 11)
		ft_built_in(mem->built_in->function[value], mem, name, value);
	else
	{
		ft_arrow_left(name);
		ft_arrow_right(name);
	}
	free(name);
}

int	ft_check_string(char *str, int *j)
{
	t_redir	vars;

	ft_bzero(&vars, sizeof(t_redir));
	vars.i = *j;
	*j = ft_break_str(&vars, str, *j);
	if (!ft_valid_redir(vars.key, &str[*j]))
	{
		ft_free_two_to_four(vars.key, vars.aux, NULL, NULL);
		return (0);
	}
	ft_free_two_to_four(vars.key, vars.aux, NULL, NULL);
	return (1);
}

int	ft_pick_redir(t_mem *mem, t_tolken *tolken, char *str, int *j)
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

void	ft_loop_redirs(t_mem *mem, t_tolken *tolken, char *str)
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
			}
			else if (tolken->redir[i] == 1)
				ft_pick_redir(mem, tolken, str, &j);
			i++;
		}
		j++;
	}
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
			}
			else if (tolken->redir[i] == 1)
			{
				if (!ft_check_string(str, &j))
					return (-1);
			}
			i++;
		}
		j++;
	}
	ft_loop_redirs(mem, tolken, str);
	return (1);
}

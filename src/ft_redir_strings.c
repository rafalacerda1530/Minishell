/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:27:46 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/29 14:15:39 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_create_content(char *copy, char *remove, int len)
{
	int		j;
	t_redir	strings;

	j = 0;
	ft_bzero(&strings, sizeof(t_redir));
	while (copy[strings.i + j] != '\0')
	{
		if (ft_strncmp(&copy[strings.i + j], remove, len) == 0)
			j += len;
		if (copy[strings.i + j] != '\0')
		{
			ft_add_char(&strings.tmp, &strings.aux, copy[strings.i + j]);
			strings.i++;
		}
	}
	if (strings.aux)
	{
		strings.tmp = ft_strdup(strings.aux);
		free(strings.aux);
		strings.aux = ft_remove_extra_spaces(strings.tmp);
		free(strings.tmp);
	}
	return (strings.aux);
}

void	ft_new_content(t_tolken *tolken, char *aux, char *key, char *file)
{
	char	*remove;
	char	*copy;
	char	*tmp;
	size_t	len;

	remove = ft_str_remove(key, aux, file);
	copy = ft_strdup(tolken->content);
	free(tolken->content);
	len = ft_strlen(remove);
	tolken->content = ft_create_content(copy, remove, len);
	tmp = NULL;
	if (tolken->content)
	{
		free(tolken->str);
		tolken->str = ft_strdup(tolken->key);
		tmp = ft_strjoin(tolken->str, tolken->content);
		free(tolken->str);
		tolken->str = ft_strdup(tmp);
	}
	ft_free_two_to_four(tmp, copy, remove, NULL);
}

char	*ft_get_file_name(char *str, int index)
{
	char	*file;
	char	*tmp;

	file = NULL;
	tmp = NULL;
	while (str[index] != ' ' && str[index] != '\0')
	{
		ft_add_char(&tmp, &file, str[index]);
		index++;
	}
	return (file);
}

int	ft_break_str(t_redir *vars, char *str, int j)
{
	int		i;

	while (str[j] != ' ' && str[j] != '\0')
	{
		ft_add_char(&vars->tmp, &vars->aux, str[j]);
		j++;
	}
	i = 0;
	while (vars->aux[i] != '\0')
	{
		if (vars->aux[i] != '>' && vars->aux[i] != '<')
			break ;
		ft_add_char(&vars->tmp, &vars->key, vars->aux[i]);
		i++;
	}
	if (!ft_valid_redir(vars->key))
		ft_free_two_to_four(vars->key, vars->aux, NULL, NULL);
	return (j);
}

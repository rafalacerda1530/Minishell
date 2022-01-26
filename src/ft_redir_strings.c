/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:27:46 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/26 14:28:40 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_str_remove(char *key, char *aux, char *file)
{
	char	*remove;
	char	*tmp;
	int		i;

	remove = ft_strdup(key);
	if (ft_strcmp(aux, key) == 0)
		ft_add_char(&tmp, &remove, ' ');
	i = 0;
	while (file[i] != '\0')
	{
		ft_add_char(&tmp, &remove, file[i]);
		i++;
	}
	return (remove);
}

char	*ft_create_content(char *copy, char *remove, int len)
{
	int		i;
	int		j;
	char	*new_content;
	char	*tmp;

	i = 0;
	j = 0;
	new_content = NULL;
	while (copy[i + j] != '\0')
	{
		if (ft_strncmp(&copy[i + j], remove, len) == 0)
			j += len;
		if (copy[i + j] != '\0')
		{
			ft_add_char(&tmp, &new_content, copy[i + j]);
			i++;
		}
	}
	return (new_content);
}

void	ft_new_content(t_tolken *tolken, char *aux, char *key, char *file)
{
	char	*remove;
	char	*copy;
	size_t	len;

	remove = ft_str_remove(key, aux, file);
	copy = ft_strdup(tolken->content);
	free(tolken->content);
	len = ft_strlen(remove);
	tolken->content = ft_create_content(copy, remove, len);
	free(copy);
	free(remove);
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

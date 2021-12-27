/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:54:38 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/27 18:04:10 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	if (split)
		free(split);
}

int	ft_print_export(t_mem *mem, t_env_list *env_list)
{
	int			i;
	t_env_list	aux;

	i = env_list->total;
	ft_bzero(&aux, sizeof(aux));
	aux.last = env_list->last;
	while (i > 0)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(aux.last->key, 1);
		if (aux.last->content[0] != '\0')
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(aux.last->content, 1);
			ft_putchar_fd('\"', 1);
		}
		ft_putchar_fd('\n', 1);
		aux.last = aux.last->prev;
		i--;
	}
	mem->all_return = 0;
	return (0);
}

int	ft_new_env(t_mem *mem, char *key, char *content, int i)
{
	t_env_list	aux;
	int			total;

	total = mem->env_list->total;
	ft_bzero(&aux, sizeof(aux));
	aux.last = mem->env_list->last;
	while (total > 0)
	{
		if (!ft_strcmp(aux.last->key, key))
		{
			if (content[i] == '\0' || content[i + 1] == '\0')
				return (1);
			ft_free_env(mem->env_list, aux.last);
			ft_fill_env_list(mem->env_list, content, 'L');
			return (1);
		}
		aux.last = aux.last->prev;
		total--;
	}
	return (0);
}

void	ft_export_string(t_mem *mem, t_env_list *env_list, char *content)
{
	char	*key;
	int		i;
	int		added;

	i = 0;
	while (*content == ' ')
		content++;
	while (content[i] != '=' && content[i] != '\0')
		i++;
	key = (char *) malloc ((i + 1) * sizeof(char));
	ft_memcpy(key, content, i);
	key[i] = '\0';
	added = ft_new_env(mem, key, content, i);
	if (!added)
		ft_fill_env_list(env_list, content, 'L');
	free(key);
}

int	ft_invalid_key(char *str, int i, int quoted)
{
	if (ft_isalnum(str[i]) || str[i] == '_')
		return (0);
	if (str[i - 1] != '\\')
	{
		if (quoted == 0 && (str[i] == '\'' || str[i] == '"'))
			return (0);
		else if (quoted == 1 && str[i] == '\'')
			return (0);
		else if (quoted == 2 && str[i] == '"')
			return (0);
	}
	return (1);
}

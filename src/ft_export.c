/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:44 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/24 20:07:14 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_delete_export(t_mem *mem, t_env_list *env_list, char *key, int update)
{
	t_env_list	aux;
	int			i;

	i = env_list->total;
	ft_bzero(&aux, sizeof(aux));
	aux.last = env_list->last;
	while (i > 0)
	{
		if (!ft_strcmp(aux.last->key, key))
		{
			if (update == 1 || aux.last->content[0] == '\0')
			{
				ft_free_env(mem->env_list, aux.last);
				return (1);
			}
			return (0);
		}
		aux.last = aux.last->prev;
		i--;
	}
	return (1);
}

int	ft_get_export_key_size(char *content, int i)
{
	while (*content == ' ')
		content++;
	while (content[i] != '=' && content[i] != '\0')
		i++;
	return (i);
}

int	ft_export(t_mem *mem, t_env_list *env_list, char *content)
{
	char	*key;
	int		i;
	int		new;
	int		update;

	i = 0;
	update = 0;
	if (content[0] == '\0')
		ft_print_export(mem, env_list);
	else
	{
		i = ft_get_export_key_size(content, i);
		key = (char *) malloc ((i + 1) * sizeof(char));
		ft_memcpy(key, content, i);
		key[i] = '\0';
		if (content[i] != '\0' && content[i + 1] != '\0')
			update = 1;
		new = ft_delete_export(mem, env_list, key, update);
		if (update == 1 || new == 1)
			ft_fill_env_list(env_list, content, 'L');
		free(key);
	}
	mem->all_return = 0;
	return (0);
}

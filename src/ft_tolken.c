/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolken.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:00:31 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/20 13:42:08 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tolken_list	*ft_alloc_tolken_list(t_mem *mem)
{
	t_tolken_list	*tolken_list;

	tolken_list = (t_tolken_list *) malloc (sizeof(t_tolken_list));
	if (!tolken_list)
	{
		ft_memory_error();
		ft_exit(mem, 2);
	}
	tolken_list->first = NULL;
	tolken_list->last = NULL;
	tolken_list->total = 0;
	return (tolken_list);
}

t_tolken	*ft_alloc_tolken(t_mem *mem, char *input)
{
	t_tolken	*tolken;
	int			key;
	int			content;

	key = 0;
	content = 0;
	ft_get_tolken_sizes(&key, &content, input);
	tolken = (t_tolken *) malloc (sizeof(t_tolken));
	if (!tolken)
	{
		ft_memory_error();
		ft_exit(mem, 2);
	}
	ft_bzero(tolken, sizeof(t_tolken));
	ft_tolken_key(mem, tolken, key, input);
	if (content > 0)
	{
		ft_tolken_content(mem, tolken, content, &input[key + 1]);
		if (tolken->content != NULL)
			ft_tolken_string(&tolken->str, tolken->key, tolken->content);
	}
	tolken->size = key + content;
	tolken->next = tolken;
	tolken->prev = tolken;
	return (tolken);
}

void	ft_fill_tolken_list(t_mem *mem, t_tolken_list *tolken_list, char *input)
{
	t_tolken	*tolken;
	size_t		i;

	i = 0;
	while (i < ft_strlen(input))
	{
		while (input[i] == ' ')
			input++;
		tolken = ft_alloc_tolken(mem, &input[i]);
		if (tolken_list->total == 0)
			tolken_list->last = tolken;
		else
		{
			tolken->next = tolken_list->first;
			tolken_list->first->prev = tolken;
			tolken->prev = tolken_list->last;
			tolken_list->last->next = tolken;
		}
		tolken_list->first = tolken;
		tolken_list->total++;
		i = i + tolken_list->first->size + 2;
	}
}

void	ft_free_tolken(t_tolken_list *tolken_list, t_tolken *tolken)
{
	if (tolken_list->first == tolken)
	{
		if (tolken_list->last == tolken)
		{
			tolken_list->first = NULL;
			tolken_list->last = NULL;
		}
		else
		{
			tolken_list->first = tolken->next;
			tolken_list->last->next = tolken->next;
			tolken->next->prev = tolken_list->last;
		}
	}
	else
	{
		if (tolken_list->last == tolken)
			tolken_list->last = tolken->prev;
		tolken->prev->next = tolken->next;
		tolken->next->prev = tolken->prev;
	}
	tolken_list->total--;
	free(tolken);
}

void	ft_free_tolken_list(t_tolken_list *tolken_list)
{
	while (tolken_list->total != 0)
	{
		tolken_list->first->size = 0;
		if (tolken_list->first->key)
			free(tolken_list->first->key);
		if (tolken_list->first->content)
			free(tolken_list->first->content);
		if (tolken_list->first->str)
			free(tolken_list->first->str);
		if (tolken_list->first->redir)
			free(tolken_list->first->redir);
		ft_free_tolken(tolken_list, tolken_list->first);
	}
}

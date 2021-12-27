/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:44 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/27 18:35:26 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export_key(char *str, char **ret, int i, int *quote)
{
	char	*tmp;

	if (str[i] == '\\')
		i++;
	if (ft_invalid_key(str, i, *quote))
	{
		ft_key_error(str);
		return (-1);
	}
	*quote = ft_quote_check(str, &i, *quote);
	if (str[i] != '\0')
	{
		ft_add_char(&tmp, ret, str[i]);
		i++;
	}
	return (i);
}

int	ft_export_content(char *str, char **ret, int i, int *quote)
{
	char	*tmp;

	if (str[i] == '\\')
		i++;
	*quote = ft_quote_check(str, &i, *quote);
	if (str[i] == '!' && *quote != 1)
	{
		ft_content_error();
		return (-1);
	}
	if (str[i] != '\0')
	{
		ft_add_char(&tmp, ret, str[i]);
		i++;
	}
	return (i);
}

int	ft_string_check(char *str, char **ret)
{
	int	i;
	int	change;
	int	quote;

	i = 0;
	quote = 0;
	change = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=' && change == 0)
			change = 1;
		if (change == 0)
			i = ft_export_key(str, ret, i, &quote);
		else if (change == 1)
			i = ft_export_content(str, ret, i, &quote);
		if (i == -1)
		{
			free(ret);
			return (-1);
		}
	}
	return (0);
}

int	ft_invalid_string(char **str)
{
	char	*ret;
	int		check;

	ret = NULL;
	if (!ft_isalpha(str[0][0]) && str[0][0] != '_' && str[0][0] != '\\')
	{
		ft_key_error(str[0]);
		return (-1);
	}
	check = ft_string_check(*str, &ret);
	if (check == -1)
	{
		free(ret);
		return (-1);
	}
	free(*str);
	*str = ft_strdup(ret);
	free(ret);
	return (0);
}

int	ft_export(t_mem *mem, t_env_list *env_list, char *content)
{
	char	**split;
	int		i;

	i = 0;
	split = NULL;
	if (!content)
		ft_print_export(mem, env_list);
	else
	{
		split = ft_split(content, ' ');
		while (split[i])
		{
			if (ft_invalid_string(&split[i]) == -1)
			{
				ft_free_split(split);
				mem->all_return = -1;
				return (-1);
			}
			ft_export_string(mem, env_list, split[i]);
			i++;
		}
		ft_free_split(split);
	}
	mem->all_return = 0;
	return (0);
}

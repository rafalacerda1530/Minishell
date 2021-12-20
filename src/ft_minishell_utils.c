/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:27:57 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/20 12:31:16 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_first(char c)
{
	char	*add;

	add = (char *)malloc(sizeof(char) * 2);
	if (!add)
		return (NULL);
	add[0] = c;
	add[1] = '\0';
	return (add);
}

char	*ft_strjoin_char(char *s1, char const c)
{
	char	*add;
	int		i;

	if (!c)
		return (NULL);
	if (!s1)
		return (ft_strjoin_first(c));
	add = (char *)malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (!add)
	{
		free(add);
		return (NULL);
		// Free Error msg
	}
	i = -1;
	while (s1[++i])
		add[i] = s1[i];
	add[i++] = c;
	add[i] = '\0';
	return (add);
}

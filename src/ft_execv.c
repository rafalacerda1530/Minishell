/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:08:27 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/03 16:48:02 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_get_env_list(t_env_list *env_list)
{
	char		**envs;
	char		*tmp;
	int			total;
	t_env_list	aux;

	total = env_list->total;
	ft_bzero(&aux, sizeof(t_env_list));
	aux.first = env_list->first;
	tmp = NULL;
	envs = (char **) malloc (sizeof(char *) * total);
	while (total > 0)
	{
		tmp = ft_strjoin_char(aux.first->key, '=');
		envs[total - 1] = ft_strjoin(tmp, aux.first->content);
		free(tmp);
		aux.first = aux.first->next;
		total--;
	}
	envs[env_list->total] = NULL;
	return (envs);
}

char	*ft_command_check(char *split, char *command)
{
	struct stat	buffer;
	char		*begin;
	char		*full;

	begin = ft_strjoin_char(split, '/');
	full = ft_strjoin(begin, command);
	free(begin);
	if (stat(full, &buffer) != 0)
	{
		free(full);
		full = NULL;
	}
	return (full);
}

char	*ft_find_path(t_mem *mem, char *command)
{
	char	*path;
	char	**split;
	char	*ret;
	int		i;

	path = ft_get_env("PATH", mem->env_list);
	if (!path)
	{
		free(path);
		return (NULL);
	}
	split = ft_split(path, ':');
	i = 0;
	ret = NULL;
	while (split[i])
	{
		ret = ft_command_check(split[i], command);
		if (ret)
			break ;
		i++;
	}
	free(path);
	ft_free_split(split);
	return (ret);
}

int	ft_execv(t_mem *mem, t_env_list *env_list, char *command)
{
	pid_t	pid;
	char	**envs;
	char	**split;
	char	*path;
	int		result;

	envs = ft_get_env_list(env_list);
	path = ft_find_path(mem, command);
	if (mem->tolken_list->first->content)
		split = ft_split(mem->tolken_list->first->str, ' ');
	else
	{
		split = (char **) malloc (sizeof(char *));
		split[0] = ft_strdup(command);
	}
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("Failed forking child\n", 2);
	else if (pid == 0)
	{
		if (execve(path, split, envs) == -1)
			ft_putstr_fd("No command\n", 2);
	}
	if (path)
		free(path);
	if (envs)
		ft_free_split(envs);
	if (split)
		ft_free_split(split);
	waitpid(pid, &result, 0);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini- <fbonini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:08:27 by fbonini           #+#    #+#             */
/*   Updated: 2022/02/05 19:51:05 by fbonini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (split[i] && ret == NULL)
	{
		ret = ft_command_check(split[i], command);
		i++;
	}
	free(path);
	ft_free_split(split);
	if (ret == NULL)
		ft_path_error(command);
	return (ret);
}

char	**ft_cmd_split(t_tolken *tolken, char *command)
{
	char	**split;

	if (tolken->content)
		split = ft_split(tolken->str, ' ');
	else
	{
		split = (char **) malloc (sizeof(char *) * 2);
		split[0] = ft_strdup(command);
		split[1] = NULL;
	}
	return (split);
}

int	ft_execv(t_mem *mem, t_env_list *lst, char *cmd, t_tolken *tlk)
{
	t_exec				exec;

	ft_bzero(&exec, sizeof(t_exec));
	exec.path = ft_find_path(mem, cmd);
	if (exec.path == NULL)
		return (127);
	exec.envs = ft_get_env_list(lst);
	exec.split = ft_cmd_split(tlk, cmd);
	exec.pid = fork();
	ft_signals(&exec.act, ft_sigquit_exec, SIGQUIT);
	ft_signals(&exec.act, ft_sigint_exec, SIGINT);
	if (exec.pid == -1)
		ft_putstr_fd("Failed forking child\n", 2);
	else if (exec.pid == 0)
	{
		if (execve(exec.path, exec.split, exec.envs) == -1)
			ft_putendl_fd(strerror(errno), 2);
	}
	ft_free_execv(exec.envs, exec.split, exec.path);
	waitpid(exec.pid, &exec.result, 0);
	if (WIFEXITED(exec.result))
		return (WEXITSTATUS(exec.result));
	return (exec.result);
}

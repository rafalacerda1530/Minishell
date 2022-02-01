/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:21 by fbonini           #+#    #+#             */
/*   Updated: 2022/02/01 14:28:04 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_change_path(char *path, t_env_list *env_list)
{
	char	*begin;
	char	*tmp;
	char	*new_path;

	begin = ft_get_env("HOME", env_list);
	tmp = ft_strdup(&path[1]);
	new_path = ft_strjoin(begin, tmp);
	free(tmp);
	free(begin);
	return (new_path);
}

int	ft_go_to_path(char *path, t_env_list *env_list)
{
	char	*pwd;
	char	new_pwd[4096];
	char	*new;

	if (path[0] == '~')
		path = ft_change_path(path, env_list);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	new = getcwd(new_pwd, 4096);
	pwd = ft_get_env("PWD", env_list);
	ft_swap_pwd(pwd, new, env_list);
	free(pwd);
	return (0);
}

char	*ft_get_path(t_env_list *env_list, char *str)
{
	char	*path;

	if (str[0] == '~' && str[1] == '\0')
		path = ft_get_env("HOME", env_list);
	else if (str[0] == '-' && str[1] == '\0')
	{
		path = ft_get_env("OLDPWD", env_list);
		ft_putstr_fd(path, 1);
		ft_putchar_fd('\n', 1);
	}
	else
		path = ft_strdup(str);
	return (path);
}

int	ft_cd(t_mem *mem, t_env_list *env_list, char *str)
{
	char	*path;
	int		ret;

	(void)mem;
	if (str == NULL)
	{
		path = ft_get_env("HOME", env_list);
		ret = ft_go_to_path(path, env_list);
		free(path);
		return (ret);
	}
	while (*str == ' ')
		str++;
	ret = ft_check_cd_arguments(str);
	if (ret == 1)
		ft_putstr_fd("Too many arguments\n", 1);
	else
	{
		path = ft_get_path(env_list, str);
		if (path)
			ret = ft_go_to_path(path, env_list);
		free(path);
	}
	return (ret);
}

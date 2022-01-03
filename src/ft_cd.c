/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:04:21 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/03 15:47:35 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_cd_arguments(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	ft_swap_pwd(char *pwd, char *oldpwd, t_env_list *env_list)
{
	ft_search_and_change(pwd, "OLDPWD", env_list);
	ft_search_and_change(oldpwd, "PWD", env_list);
}

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

void	ft_go_to_path(char *path, t_env_list *env_list)
{
	char	*pwd;
	char	new_pwd[4096];
	char	*new;

	if (path[0] == '~')
		path = ft_change_path(path, env_list);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("Error no path\n", 2);
		return ;
	}
	new = getcwd(new_pwd, 4096);
	pwd = ft_get_env("PWD", env_list);
	ft_swap_pwd(pwd, new, env_list);
	free(pwd);
}

int	ft_cd(t_mem *mem, char *str, t_env_list *env_list)
{
	char	*path;

	(void)mem;
	while (*str == ' ')
		str++;
	if (ft_check_cd_arguments(str))
	{
		ft_putstr_fd("Too many arguments\n", 1);
		return (1);
	}
	// Need fd check
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
	if (path)
		ft_go_to_path(path, env_list);
	free(path);
	return (0);
}

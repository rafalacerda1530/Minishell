/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 01:16:58 by Rarodrig          #+#    #+#             */
/*   Updated: 2021/12/20 12:32:23 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./includes/42_libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*key;
	char			*content;
}			t_env;

typedef struct s_env_list
{
	t_env			*first;
	t_env			*last;
	unsigned int	total;
}			t_env_list;


typedef struct s_tolken
{
	struct s_tolken	*next;
	struct s_tolken	*prev;
	char			*key;
	char			*content;
	int				size;
}			t_tolken;

typedef struct s_tolken_list
{
	t_tolken			*first;
	t_tolken			*last;
	unsigned int		total;
}			t_tolken_list;

typedef struct s_mem
{
	char			*print;
	t_env_list		*env_list;
	t_tolken_list	*tolken_list;
}			t_mem;

t_tolken_list	*ft_alloc_tolken_list(void);
t_env_list		*ft_alloc_env_list(void);
void			ft_fill_env_list(t_env_list *env_list, char **envp);
void			ft_create_env_strings(t_env *env, int key, int content, char *envp);
void			ft_get_env_sizes(int *key, int *content, char *envp);

void			ft_create_shell(t_mem *mem);

void			ft_fill_tolken_list(t_tolken_list *tolken_list, char *input);
void			ft_get_tolken_sizes(int *i, int *key, int *content, char *input);
void			ft_create_tolken_strings(t_tolken *tolken, int key, int content, char *input);

void			ft_free_tolken_list(t_tolken_list *tolken_list);
void			ft_free_env_list(t_env_list *env_list);

char			*ft_strjoin_first(char c);
char			*ft_strjoin_char(char *s1, char const c);

void			ft_echo(t_mem *mem, char *str, t_env_list *env_list);
void			ft_add_char(char **tmp, char **ret, char c);
int				ft_get_key_size(char *str, int *i);
void			ft_strjoin_env(char **ret, char *content);
int				ft_true_dollar(char *str, int i, int quote);

#endif

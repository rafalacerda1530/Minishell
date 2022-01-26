/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 01:16:58 by Rarodrig          #+#    #+#             */
/*   Updated: 2022/01/26 15:54:27 by fbonini          ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# define MAX_KEYS 12

typedef int	(*t_funct)();

typedef struct s_redir
{
	int		i;
	char	*aux;
	char	*key;
	char	*tmp;
}			t_redir;

typedef struct s_parse
{
	int		index;
	int		quote;
	char	*ret;
	char	*aux;
}			t_parse;

typedef struct s_built_in
{
	t_funct	function[MAX_KEYS];
}			t_built_in;

typedef struct s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*key;
	char			*content;
	char			tag;
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
	char			*str;
	char			*key;
	char			*content;
	int				numb_redir;
	int				*redir;
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
	char			**keys;
	int				all_return;
	int				std_pipe[2];
	t_built_in		*built_in;
	t_env_list		*env_list;
	t_tolken_list	*tolken_list;
}			t_mem;

t_tolken_list	*ft_alloc_tolken_list(t_mem *mem);
t_env_list		*ft_alloc_env_list(t_mem *mem);
t_env			*ft_alloc_env(t_mem *mem, char *envp, char tag);
t_built_in		*ft_alloc_built_in(t_mem *mem);
void			ft_fill_env_list(t_mem *mem, t_env_list *env_list, char *envp, char tag);
void			ft_create_env_strings(t_env *env, int key, int content, char *envp);
void			ft_get_env_sizes(int *key, int *content, char *envp);
char			**ft_set_keys(t_mem *mem);

void			ft_create_shell(t_mem *mem);

void			ft_fill_tolken_list(t_mem *mem, t_tolken_list *tolken_list, char *input);
void			ft_get_tolken_sizes(int *i, int *j, char *input);
void			ft_tolken_key(t_mem *mem, t_tolken *tolken, int key, char *input);
void			ft_tolken_content(t_mem *mem, t_tolken *tolken, int size, char *input);
void			ft_tolken_string(char **str, char *key, char *content);
void			ft_redirect_check(char *ret, t_tolken *tolken);
void			ft_get_numb_redirect(t_tolken *tolken, t_parse parser, char *ret);

int				ft_check_key(char *str, char **keys);
int				ft_built_in(int (*funct)(), t_mem *mem, char *str, int key);

void			ft_free_tolken_list(t_tolken_list *tolken_list);
void			ft_free_env_list(t_env_list *env_list);
char			*ft_get_env(char *key, t_env_list *env_list);
void			ft_search_and_change(char *str, char *key, t_env_list *env_list);
void			ft_free_mem(t_mem *mem);
void			ft_free_env(t_env_list *env_list, t_env *env);

char			*ft_strjoin_first(char c);
char			*ft_strjoin_char(char *s1, char const c);

int				ft_quote_check(char *str, int *i, int quote);
void			ft_add_char(char **tmp, char **ret, char c);
int				ft_get_key_size(char *str, int i);
char			*ft_parse_string(char *str, t_env_list *env_list);
int				ft_space_remove(char *str, int i, int quote);
void			ft_strjoin_env(char **ret, char *content);
int				ft_true_dollar(char *str, t_parse *parser);
int				ft_true_home(char *str, t_parse *parser);
void			ft_redirect_check(char *ret, t_tolken *tolken);

int				ft_echo(t_mem *mem, t_env_list *env_list, char *str);

/*
	Built-in cd functions
*/
int				ft_cd(t_mem *mem, t_env_list *env_list, char *str);
void			ft_swap_pwd(char *pwd, char *oldpwd, t_env_list *env_list);
int				ft_check_cd_arguments(char *str);

int				ft_pwd(void);

int				ft_arrow_left(char *file);
int				ft_arrow_right(char *file);
int				ft_d_arrow_left(char **eof);
int				ft_d_arrow_right(char *file);

int				ft_env(t_mem *mem, t_env_list *env_list);
int				ft_exit(t_mem *mem, int ret);

int				ft_export(t_mem *mem, t_env_list *env_list, char *content);
int				ft_invalid_key(char *str, int i, int quoted);
void			ft_export_string(t_mem *mem, t_env_list *env_list, char *content);
int				ft_new_env(t_mem *mem, char *key, char *content, int i);
int				ft_print_export(t_mem *mem, t_env_list *env_list);

void			ft_free_split(char **split);
void			ft_free_two_to_four(char *s1, char *s2, char *s3, char *s4);

int				ft_unset(t_mem *mem, t_env_list *env_list, char *key);

void			ft_key_error(char *str);
void			ft_content_error(void);
void			ft_memory_error(void);

int				ft_execv(t_mem *mem, t_env_list *env_list, char *command, t_tolken *tolken);

void			ft_make_commands(t_mem *mem, t_tolken *tolken);

/*
	Signal Functions
*/
void			ft_signals(struct sigaction *act, void (*handler)(int), int sig, t_mem *mem);
void			sigint_handler(int sig);

/*
	Pipe Functions
*/
void			ft_copy_stds(t_mem *mem);
void			ft_reset_stds(t_mem *mem);
void			ft_close_copy_stds(t_mem *mem);
void			ft_pipe_cmd(t_mem *mem);

/*
	Redirect functions
*/
int				ft_redirects(t_mem *mem, t_tolken *tolken, char *str);
int				ft_valid_redir(char *key);
char			*ft_str_remove(char *key, char *aux, char *file);
char			*ft_create_content(char *copy, char *remove, int len);
void			ft_new_content(t_tolken *tolken, char *aux, char *key, char *file);
char			*ft_get_file_name(char *str, int index);
int				ft_break_str(t_redir *vars, char *str, int j);

#endif
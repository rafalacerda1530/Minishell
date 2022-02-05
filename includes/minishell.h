/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 01:16:58 by Rarodrig          #+#    #+#             */
/*   Updated: 2022/02/05 17:04:54 by fbonini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "42_libft/libft.h"
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
# include <errno.h>
# define MAX_KEYS 12

extern int	g_last_return;

typedef int	(*t_funct)();

typedef struct s_built_in
{
	t_funct	function[MAX_KEYS];
}			t_built_in;

typedef struct s_exec
{
	pid_t				pid;
	char				**envs;
	char				**split;
	char				*path;
	int					result;
	struct sigaction	act;
}			t_exec;

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
	int				std_pipe[2];
	t_built_in		*built_in;
	t_env_list		*env_list;
	t_tolken_list	*tolken_list;
}			t_mem;

/*
	Shell
*/
void			ft_create_shell(t_mem *mem);

/*
	Alloc functions
*/
t_tolken_list	*ft_alloc_tolken_list(t_mem *mem);
t_env_list		*ft_alloc_env_list(t_mem *mem);
t_env			*ft_alloc_env(t_mem *mem, char *envp);
t_built_in		*ft_alloc_built_in(t_mem *mem);
void			ft_fill_env_list(t_mem *mem, t_env_list *env_list, char *envp);
void			ft_create_env_str(t_env *env, int key, int content, char *envp);
void			ft_get_env_sizes(int *key, int *content, char *envp);
char			**ft_set_keys(t_mem *mem);

/*
	Tolken list functions
*/
void			ft_fill_tlkn_list(t_mem *mem, t_tolken_list *list, char *input);
void			ft_get_tolken_sizes(int *i, int *j, char *input);
void			ft_tolken_key(t_mem *mem, t_tolken *tlk, int len, char *str);
void			ft_tolken_content(t_mem *m, t_tolken *tlk, int len, char *str);
void			ft_tolken_string(char **str, char *key, char *content);
void			ft_redirect_check(char *ret, t_tolken *tolken);
void			ft_get_nb_redirect(t_tolken *tolken, t_parse parser, char *ret);

void			ft_free_tolken_list(t_tolken_list *tolken_list);
char			*ft_get_env(char *key, t_env_list *env_list);
void			ft_srch_and_change(char *str, char *key, t_env_list *env_list);

/*
	Parse functions
*/
char			*ft_strjoin_first(char c);
char			*ft_strjoin_char(char *s1, char const c);
void			ft_join_string(char **tmp, char **ret, char *str);

int				ft_quote_check(char *str, int *i, int quote);
void			ft_add_char(char **tmp, char **ret, char c);
int				ft_get_key_size(char *str, int i);
char			*ft_parse_string(t_mem *mem, char *str, t_env_list *env_list);
int				ft_space_remove(char *str, int i, int quote);
void			ft_strjoin_env(char **ret, char *content);
int				ft_true_dollar(char *str, t_parse *parser);
int				ft_true_home(char *str, t_parse *parser);
int				ft_quote_check(char *str, int *i, int quote);

/*
	Free functions
*/
void			ft_free_env(t_env_list *env_list, t_env *env);
void			ft_free_env_list(t_env_list *env_list);
void			ft_free_split(char **split);
void			ft_free_two_to_four(char *s1, char *s2, char *s3, char *s4);
void			ft_free_mem(t_mem *mem);

/*
	Execute Built-in functions
*/
int				ft_check_key(char *str, char **keys);
int				ft_built_in(int (*funct)(), t_mem *mem, char *str, int key);
void			ft_make_commands(t_mem *mem, t_tolken *tolken);

/*
	Built-in functions
*/
int				ft_echo(t_mem *mem, t_env_list *env_list, char *str);

int				ft_cd(t_mem *mem, t_env_list *env_list, char *str);
void			ft_swap_pwd(char *pwd, char *oldpwd, t_env_list *env_list);
int				ft_check_cd_arguments(char *str);

int				ft_pwd(void);

int				ft_env(t_mem *mem, t_env_list *env_list);
int				ft_exit(t_mem *mem, t_env_list *list, char *ret);

int				ft_export(t_mem *mem, t_env_list *env_list, char *content);
int				ft_invalid_key(char *str, int i, int quoted);
void			ft_export_str(t_mem *mem, t_env_list *env_list, char *content);
int				ft_new_env(t_mem *mem, char *key, char *content, int i);
int				ft_print_export(t_env_list *env_list);

int				ft_unset(t_mem *mem, t_env_list *env_list, char *key);

/*
	Execve Functions
*/

int				ft_execv(t_mem *mem, t_env_list *lst, char *cmd, t_tolken *tlk);
void			ft_free_execv(char **env, char **split, char *path);

/*
	Error Functions
*/
void			ft_key_error(char *str);
void			ft_path_error(char *cmd);
void			ft_content_error(void);
void			ft_memory_error(void);

/*
	Signal Functions
*/
void			ft_signals(struct sigaction *act, void (*hand)(int), int sig);
void			ft_sigint_heredoc(int sig);
void			ft_sigint_handler(int sig);
void			ft_sigint_exec(int sig);
void			ft_sigquit_exec(int sig);

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
int				ft_arrow_left(char *file);
int				ft_arrow_right(char *file);
int				ft_d_arrow_left(t_mem *mem, char *eof);
int				ft_d_arrow_right(char *file);

int				ft_redirects(t_mem *mem, t_tolken *tolken, char *str);
int				ft_valid_redir(char *key, char *aux);
char			*ft_str_remove(char *key, char *aux, char *file);
char			*ft_create_content(char *copy, char *remove, int len);
char			*ft_new_tmp(char *str, char *aux, char *key);
void			ft_new_str(t_tolken *tolken, char *aux, char *key, char *file);
char			*ft_get_file_name(char *str, int index);
int				ft_break_str(t_redir *vars, char *str, int j);
char			*ft_str_remove(char *key, char *aux, char *file);
char			*ft_remove_extra_spaces(char *str);

#endif
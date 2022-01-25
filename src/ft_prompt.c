/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarodrig < rarodrig@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:42:41 by fbonini           #+#    #+#             */
/*   Updated: 2022/01/25 19:54:22 by rarodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tolken(t_tolken_list *tolken_list)
{
	t_tolken	*tolken;
	int			total;

	tolken = NULL;
	total = tolken_list->total;
	tolken = tolken_list->last;
	printf("\n----------------------Tolkens Criados------------------------\n");
	while (total != 0)
	{
		printf("The Key is >%s<\nThe Command is >%s<\n", tolken->key, tolken->content);
		tolken = tolken->prev;
		total--;
	}
	printf("\n----------------------Fim------------------------\n");
}

void	ft_read_input(char **input)
{
	char	*prompt;
	char	intro[3];
	char	*msg;

	intro[0] = '$';
	intro[1] = ' ';
	intro[2] = '\0';
	prompt = NULL;
	prompt = getcwd(prompt, 0);
	msg = ft_strjoin(prompt, intro);
	*input = readline(msg);
	free(msg);
	free(prompt);
}

void	ft_create_history(char *input)
{
	int	i;

	i = 0;
	if (input && *input)
	{
		while (input[i] == ' ')
			i++;
		add_history(&input[i]);
	}
}

void	ft_make_commands(t_mem *mem, t_tolken_list *tolken_list, t_tolken *tolken)
{
	int	key;
	(void)tolken_list;
	key = ft_check_key(tolken->key, mem->keys);
	if (key < 12)
	{
		if (tolken->content)
			ft_use_built_in(mem->built_in->function[key], mem, tolken->content, key);
		else
			ft_use_built_in(mem->built_in->function[key], mem, NULL, key);
	}
	else
		ft_execv(mem, mem->env_list, tolken->key, tolken);
}

int	ft_valid_key(char *key)
{
	if (ft_strlen(key) > 2)
		return (0);
	if (key[0] == '>' && key[1] == '<')
		return (0);
	return (1);
}

void	ft_new_content(t_tolken *tolken, char *aux, char *key, char *file)
{
	int		i;
	int		j;
	size_t	len;
	char	*remove;
	char	*tmp;
	char	*copy;

	remove = ft_strdup(key);
	if (ft_strcmp(aux, key) == 0)
		ft_add_char(&tmp, &remove, ' ');
	i = 0;
	while (file[i] != '\0')
	{
		ft_add_char(&tmp, &remove, file[i]);
		i++;
	}
	// ft_add_char(&tmp, &remove, ' ');
	copy = ft_strdup(tolken->content);
	free(tolken->content);
	tolken->content = NULL;
	i = 0;
	j = 0;
	len = ft_strlen(remove);
	while (copy[i + j] != '\0')
	{
		if (ft_strncmp(&copy[i + j], remove, len) == 0)
		{
			while (remove[j] == '>' || remove[j] == '<')
				j++;
			if (remove[j] == ' ')
				j++;
			while (remove[j] != '\0')
				j++;
		}
		if (copy[i + j] != '\0')
		{
			ft_add_char(&tmp, &tolken->content, copy[i + j]);
			i++;
		}
	}
	free(copy);
	free(remove);
}

int	ft_check_string(t_mem *mem, t_tolken *tolken, char *str, int *j)
{
	char	*aux;
	char	*key;
	char	*file;
	char	*tmp;
	int		value;
	int		k;
	int		i;

	k = *j;
	key = NULL;
	aux = NULL;
	file = NULL;
	tmp = NULL;
	while(str[*j] != ' ' && str[*j] != '\0')
	{
		ft_add_char(&tmp, &aux, str[*j]);
		(*j)++;
	}
	i = 0;
	while (aux[i] != '\0')
	{
		if (aux[i] != '>' && aux[i] != '<')
			break ;
		ft_add_char(&tmp, &key, aux[i]);
		i++;
	}
	if(!ft_valid_key(key))
	{
		free(key);
		free(aux);
		return (0);
	}
	if (ft_strcmp(key, "<<") == 0)
	{
		if (ft_strlen(aux) == 2)
			ft_use_built_in(mem->built_in->function[10], mem, &str[*j + 1], 10);
		else
			ft_use_built_in(mem->built_in->function[10], mem, &str[*j], 10);
		free(tolken->content);
		tolken->content = NULL;
		free(key);
		free(aux);
		return (1);
	}
	value = ft_check_key(key, mem->keys);
	if (strcmp(aux, key) == 0)
	{
		while(str[k + i + 1] != ' ' && str[k + i + 1] != '\0')
		{
			ft_add_char(&tmp, &file, str[k + i + 1]);
			k++;
		}
	}
	else
	{
		while(str[k + i] != ' ' && str[k + i] != '\0')
		{
			ft_add_char(&tmp, &file, str[k + i + 1]);
			k++;
		}
	}
	ft_new_content(tolken, aux, key, file);
	if (value != 11)
		ft_use_built_in(mem->built_in->function[value], mem, file, value);
	else
	{
		ft_arrow_left(file);
		ft_arrow_right(file);
	}
	free(key);
	free(aux);
	free(file);
	return (1);
}

int	ft_redirects(t_mem *mem, t_tolken *tolken, char *str)
{
	int	i;
	int	j;
	int	valid;

	i = 0;
	j = 0;
	valid = 1;
	while (i < tolken->numb_redir && str[j] != '\0')
	{
		if (str[j] == '>' || str[j] == '<')
		{
			if (tolken->redir[i] == 0)
			{
				while (str[j] != ' ' && str[j + 1] != '\0')
					j++;
				i++;
			}
			if (tolken->redir[i] == 1)
			{
				valid = ft_check_string(mem, tolken, str, &j);
				if (!valid)
					return (-1);
			}
		}
		j++;
	}
	return (1);
}

void	ft_send_tolken(t_mem *mem)
{
	size_t i;
	int **fd_pipe;
	t_tolken *tolken;

	tolken = mem->tolken_list->last;
	fd_pipe = (int **) malloc ((mem->tolken_list->total - 1) * sizeof(int *));
	i = 0;
	while (i < mem->tolken_list->total - 1)
	{
		fd_pipe[i] = (int *) malloc (2 * sizeof(int));
		if (pipe(fd_pipe[i]) < 0)
			return ;
		i++;
	}
	i = 0;
	while (i < mem->tolken_list->total)
	{
		if (i > 0)
		{
			dup2(fd_pipe[i - 1][0], STDIN_FILENO);
			close(fd_pipe[i - 1][0]);
		}
		if (i != mem->tolken_list->total - 1)
		{
			dup2(fd_pipe[i][1], STDOUT_FILENO);
			close(fd_pipe[i][1]);
		} 
		else
			dup2(mem->std_pipe[1], STDOUT_FILENO);
		if (ft_redirects(mem, tolken, tolken->content) == -1)
			break ;
		ft_make_commands(mem, mem->tolken_list, tolken);
		tolken = tolken->prev;
		i++;
	}
	i = 0;
	while (i < mem->tolken_list->total - 1)
	{
		free(fd_pipe[i]);
		i++;
	}
	if (fd_pipe)
		free(fd_pipe);
}

void	ft_create_shell(t_mem *mem)
{
	char	*input;
	struct sigaction act;

	ft_bzero(&act, sizeof(struct sigaction));
	mem->std_pipe[0] = dup(STDIN_FILENO);
	mem->std_pipe[1] = dup(STDOUT_FILENO);
	while (1)
	{
		input = NULL;
		ft_signals(&act, sigint_handler, SIGINT, mem);
		ft_read_input(&input);
		ft_create_history(input);
		if (input)
		{

			ft_fill_tolken_list(mem, mem->tolken_list, input);
			// print_tolken(mem->tolken_list);
			if (mem->tolken_list->total > 1)
				ft_send_tolken(mem);
			else
			{
				if (ft_redirects(mem, mem->tolken_list->first, mem->tolken_list->first->content) != -1)
					ft_make_commands(mem, mem->tolken_list, mem->tolken_list->first);
			}
			ft_free_tolken_list(mem->tolken_list);
			free(input);
		}
		dup2(mem->std_pipe[0], STDIN_FILENO);
		dup2(mem->std_pipe[1], STDOUT_FILENO);
	}
	close(mem->std_pipe[1]);
	close(mem->std_pipe[0]);
}

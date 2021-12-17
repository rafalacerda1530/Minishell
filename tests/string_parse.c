/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:37:28 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/17 18:51:10 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
--------------------------------------------------
	List de Tolken -> Key01

	List de Função -> Key02

	key01 == Key02
	Chama a função da lista.
----------------------------------------------------


	função checkar Key
	Se for o echo
		Built in echo
	
	Echo builtin
	{
		char *str;
		int	singlequote;

		while (Conteudo == ' ' && Conteudo != '\0')
			conteudo++;
		i = 0;
		While (Conteudo[i] != '\0')
		{
			if (conteudo[i] == '$' && singlesquote == 0)
				Função $;
		}
		printa str;
	}

	(Se esta dentro de ', nao entra na função)
	Funçao $ 
		Checa proximo char
			se (" ou ')
				Não printa o $ e printa a string

			’ inhibit all interpretation of a sequence of characters.
			" inhibit all interpretation of a sequence of characters except for $.
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// #include "../includes/42_libft/libft.h"


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			cont;
	unsigned char	*n_s1;
	unsigned char	*n_s2;

	n_s1 = (unsigned char *) s1;
	n_s2 = (unsigned char *) s2;
	cont = 0;
	while ((n_s1[cont] != '\0' || n_s2[cont] != '\0') && cont < n)
	{
		if (n_s1[cont] != n_s2[cont])
		{
			return (n_s1[cont] - n_s2[cont]);
		}
		cont++;
	}
	return (0);
}


size_t	ft_strlen(const char *s)
{
	size_t	cont;

	cont = 0;
	while (*s != 0)
	{
		++s;
		cont++;
	}
	return (cont);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*nstr;
	size_t	i;
	size_t	cont;

	i = ft_strlen(s1);
	nstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	cont = 0;
	if (nstr == NULL)
		return (NULL);
	if (!s1 || !s2)
		return (NULL);
	while (s1[cont])
	{
		nstr[cont] = s1[cont];
		cont++;
	}
	i = 0;
	while (s2[i])
	{
		nstr[cont] = s2[i];
		i++;
		cont++;
	}
	nstr[cont] = '\0';
	return (nstr);
}

char	*ft_strdup(const char *string)
{
	char	*str;
	size_t	cont;

	cont = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(string) + 1);
	if (str == NULL)
	{
		return (NULL);
	}
	while (string[cont])
	{
		str[cont] = string[cont];
		cont ++;
	}
	str[cont] = '\0';
	return (str);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			cont;
	unsigned char	*n_src;
	unsigned char	*n_dest;

	if (!dest && !src)
		return (NULL);
	n_src = (unsigned char *) src;
	n_dest = (unsigned char *) dest;
	cont = 0;
	while (cont < n)
	{
		n_dest[cont] = n_src[cont];
		cont++;
	}
	return (n_dest);
}


// void	ft_echo(char *str)
// {
// 	int	i;
// 	int	j;
// 	int	quoted;
// 	char *print;
// 	char *tmp;
// 	char *tmp2;

// 	i = 0;
// 	quoted = 0;
// 	j = 0;
// 	while (*str == ' ')
// 		str++;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '"' || str[i] == '\'')
// 		{
// 			if(i != 0)
// 			{
// 				if (tmp == NULL)
// 				{
// 					print = (char *) malloc (j * sizeof(char));
// 					ft_memcpy(print, &str[i - j], j);
// 				}
// 				else
// 				{
// 					tmp2 = (char *) malloc (j * sizeof(char));
// 					

// 					printf("Tmp2:%s\n", tmp2);
// 					print = ft_strjoin(tmp,tmp2);
// 					free(tmp);
// 					free(tmp2);
// 				}
// 				tmp = ft_strdup(print);
// 				free(print);
// 				j = 0;
// 			}
// 		}
// 		i++;
// 		j++;
// 	}
// 	printf("O str eh:\n%s\n", tmp);
// 	free(tmp);
// }



// char	*ft_strjoin_first(char c)
// {
// 	char	*add;

// 	add = (char *)malloc(sizeof(char) * 2);
// 	if (!add)
// 		return (NULL);
// 	add[0] = c;
// 	add[1] = '\0';
// 	return (add);
// }

char	*ft_strjoin_char(char *s1, char const s2)
{
	char	*add;
	int		i;

	if (!s2)
		return (NULL);
	// if (!s1)
	// 	return (ft_strjoin_first(s2));
	add = (char *)malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (!add)
	{
		// free(s1);
		return (NULL);
	}
	i = -1;
	while (s1[++i])
		add[i] = s1[i];
	// free(s1);
	add[i++] = s2;
	add[i] = '\0';
	return (add);
}

/*
	while(str[i])
	{
		if (str[i] == "'")
		{
			if (quoted == 0)
				quoted = 1;
			else
				quoted = 0;
		}
			echo aBC DEF "$OLDPWD"
		if (str[i] == $ && quoted != 1)	
			função...
	}		
*/

char	*ft_check_dollar(char *str)
{
	char *ret;
	char *content;
	char *key;
	char *tmp_key;
	char *tmp; 
	int i;
	int j;
	int quoted;

	i = 0;
	j = 0;
	quoted = 0;
	ret = NULL;
	key = "TESTE";
	content = "/Desktop/Minishell/Minishell/tests";
	while(str[i] != '\0')
	{
		if (str[i] == '"' && (quoted == 0 || quoted == 2))
		{
			i++;
			if (quoted == 0)
				quoted = 2;
			else
				quoted = 0;
		}
		if (str[i] == '\'' && (quoted == 0 || quoted == 1))
		{
			i++;
			if (quoted == 0)
				quoted = 1;
			else
				quoted = 0;
		}
		if(str[i] == '$' && quoted != 1 && str[i + 1] != '\'' && str[i + 1] != '"')
		{
			i++;
			j = 0;
			while(str[i] != ' ' &&  str[i] != '\'')
			{
				if(str[i] == '\0')
					break;
				i++;
				j++;
			}
			tmp_key  = (char *) malloc (sizeof(char) * (j + 1));
			ft_memcpy(tmp_key, &str[i - j], j);
			if (ft_strncmp(tmp_key, key, j) == 0)
			{
				j = 0;
				while(content[j] != '\0')
				{
					tmp = ft_strjoin_char(ret, content[j]);
					free(ret);
					ret = ft_strdup(tmp);
					free(tmp);
					j++;
					
				}
			}
			free(tmp_key);
			// if (str[i + 1] == '\0')
			// 	break;
		}
		if (ret == NULL)
		{
			ret = (char *) malloc (sizeof(char) + 1);
			ret[0] = str[i];
			ret[1] = '\0';
			i++; 
		}
		if (str[i] != '\0')
		{
			tmp = ft_strjoin_char(ret, str[i]);
			free(ret);
			ret = ft_strdup(tmp);
			free(tmp);
			i++;
		}
	}
	
	return (ret);
}

void	ft_echo(char *str)
{
	int	i;
	int	quoted;
	char *print;
	char *tmp;
	int n;

	i = 0;
	n = 0;
	quoted = 0;
	while (*str == ' ')
		str++;
	if (str[i] == '-' && str[i + 1] ==  'n')
	{
		str++;
		str++;
		while (*str == ' ')
			str++;
		n = 1;
	}
	tmp = ft_strdup(str);
	str =  ft_check_dollar(tmp);
	free(tmp);
	print = NULL;
	tmp = NULL;
	while (str[i] != '\0')
	{
		if (print == NULL)
		{
			print = (char *) malloc (sizeof(char) + 1);
			print[0] = str[i];
			print[1] = '\0';
			i++;
		}
		tmp = ft_strjoin_char(print, str[i]);
		free(print);
		print = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	if (n == 1)
		printf("O str eh: %s", print);
	else
		printf("O str eh: %s\n", print);
	free(print);
}

int	main(void)
{
	// ft_echo("echo oi \"ab'c\" oi 'a\"aa' \"io\" \"'$TESTE'\"");
	// ft_echo("A $ABC A \"'$TESTE'\" ");
	// ft_echo("A $ABC A \"'$\"TESTE'\" ");
	// ft_echo("-n \"abcccccc\"\n");
	return 0;
}

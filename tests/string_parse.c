/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini <fbonini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:37:28 by fbonini           #+#    #+#             */
/*   Updated: 2021/12/16 17:35:24 by fbonini          ###   ########.fr       */
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


void	ft_echo(char *str)
{
	int	i;
	int	j;
	int	quoted;
	char *print;
	char *tmp;
	char *tmp2;

	i = 0;
	quoted = 0;
	while (*str == ' ')
		str++;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if(i != 0)
			{
				if (tmp == NULL)
				{
					print = (char *) malloc (j * sizeof(char));
					ft_memcpy(print, &str[i - j], j - 1);
				}
				else
				{
					tmp2 = (char *) malloc (j * sizeof(char));
					ft_memcpy(tmp2, &str[i - j], j - 1);
					print = ft_strjoin(tmp,tmp2);
					free(tmp);
					free(tmp2);
				}
				tmp = ft_strdup(print);
				if(str[i + 1] != '\0')
					free(print);
				j = 0;
			}
		}
		i++;
		j++;
	}
	printf("O str eh:\n%s\n", str);
	free(str);
}

// ["]bem  aa["] aaaa "01234"

/*
	char *str;
	char *tmp;

	print = Oi td
	tmp = Oi td
	print = Oi td + bem aa

	 aaaa - str03
	01234 - str04


*/
int	main(void)
{
	ft_echo("echo oi \"abc\" oi");
	return 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbonini- <fbonini-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 22:34:03 by fbonini-          #+#    #+#             */
/*   Updated: 2021/12/08 17:34:09 by fbonini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>
  
#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported
#define clear() printf("\033[H\033[J")

void init_shell()
{
    clear();
    printf("\n\n\n\n******************"
        "************************");
    printf("\n\n\n\t****MY SHELL****");
    printf("\n\n\t-USE AT YOUR OWN RISK-");
    printf("\n\n\n\n*******************"
        "***********************");
    char* username = getenv("USER");
    printf("\n\n\nUSER is: @%s", username);
    printf("\n");
    sleep(1);
    clear();
}

void printDir()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\nDir: %s", cwd);
}

int takeInput(char* str)
{
	char* buf;

	buf = readline("\n>>> ");
	if (strlen(buf) != 0)
	{
		add_history(buf);
		strcpy(str, buf);
		return 0;
	}
	else
	{
		return 1;
	}
}

int parsePipe(char* str, char** strpiped)
{
    int i;
    
	i = 0;
	while (i < 2)
	{
		strpiped[i] = strsep(&str, "|");
		if (strpiped[i] == NULL)
			break;
		i++;
	}
	if (strpiped[1] == NULL)
		return 0; // returns zero if no pipe is found.
	else
	{
		return 1;
	}
}

int processString(char* str, char** parsed, char** parsedpipe)
{
	char* strpiped[2];
	int piped = 0;

	piped = parsePipe(str, strpiped);
	// if (piped)
	// {
	// 	parseSpace(strpiped[0], parsed);
	// 	parseSpace(strpiped[1], parsedpipe);
	// }
	// else
	// {
	// 	parseSpace(str, parsed);
	// }
	// if (ownCmdHandler(parsed))
	// 	return 0;
	// else
		return 1 + piped;
}

int main()
{
	char	inputString[MAXCOM];
	char	*parsedArgs[MAXLIST];
	char*	parsedArgsPiped[MAXLIST];
	int		execFlag = 0;

	init_shell(); // Cria Prompt
	while (1)
	{
		printDir(); // Printa o Dir
		if (takeInput(inputString))  // Pega o input 
			continue;
		execFlag = processString(inputString, parsedArgs, parsedArgsPiped);
		printf("The flag is %d\n", execFlag);
	}
	return 0;
}

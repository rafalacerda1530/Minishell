void	print_env(t_env_list *env_list, char **envp)
{
	t_env	*env;
	int		total;

	env = NULL;
	env = env_list->last;
	printf("\n----------------------Printando variaveis de ambiente------------------------\n");
	printf("the envp is %s\n", envp[0]);
	printf("The key is: %s\nthe Env is: %s\n------\n", env->key, env->content);
	// printf("\n\n------Get PWD--------\n");
	total = env_list->total;
	env = env_list->last;
	while (total != 0)
	{
		// if (strncmp(env->key,"PWD", 3) == 0)  // Using STRING.H
		printf("The Key Env is >> %s \nThe Env is >> %s\n\n", env->key, env->content);
		env = env->prev;
		total--;
	}
	printf("\n----------------------Fim------------------------\n");
}

/* /\ Print para checkar /\ */

	// print_env(mem.env_list, envp);


/* \/ Print para checkar \/ */
void	print_tolken(t_env_list *tolken_list)
{
	t_env	*tolken;
	int			total;

	tolken = NULL;
	total = tolken_list->total;
	tolken = tolken_list->last;
	printf("\n----------------------Tolkens Criados------------------------\n");
	while (total != 0)
	{
		printf("The Key is >> %s\nThe Command is >> %s\n", tolken->key, tolken->content);
		tolken = tolken->prev;
		total--;
	}
	printf("\n----------------------Fim------------------------\n");
}
/* /\ Print para checkar /\ */


			// print_tolken(mem->env_list);
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:41:00 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/16 16:41:23 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char	**ft_tab_strcpy(char **to_copy)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	j = 0;
	while (to_copy[i])
		i++;
	copy = (char**)malloc(sizeof(copy) * i);
	while (j < i)
	{
		copy[j] = ft_strdup(to_copy[j]);
		j++;
	}
	copy[j] = NULL;
	return (copy);
}

char	**get_argv()
{
	char *line;
	char **caca;

	line = NULL;
	ft_putstr_fd("ecris sale batard : > ", 1);
	get_next_line(0, &line);
	caca = ft_strsplit(line, ' ');
	if (line)
		ft_strdel(&line);
	return (caca);
}

void	init_builtin(t_builtin *b, char **env, char **argv)
{
	b->cd = "cd";
	b->quit = "quit";
	b->exit = "exit";
	b->env = "env";
	b->setenv = "setenv";
	b->unsetenv = "unsetenv";
	b->argv = argv;
	b->envir = env;
}

void	loop_fork(char **env, t_builtin b)
{
	pid_t	parent;
	char	**argv;
	char	*path;

	argv = NULL;
	while(42)
	{
		argv = get_argv();
		init_builtin(&b, env, argv);
		path = get_command(argv[0], &b);
		parent = fork();
		if (parent > 0)
		{
			if (!path)
				exec_cd(&b);
			wait(NULL);
		}
		else if (parent == -1)
		{
			ft_printf("father = %d\n", parent);
			exit(EXIT_FAILURE);
		}
		else if (parent == 0)
		{
			if (path)
				execve(path, argv, env);
			exit(EXIT_SUCCESS);
		}
	}
}

int		main(int ac, char **av, char **env)
{
	t_builtin b;

	ft_bzero(&b, sizeof(b));
	loop_fork(ft_tab_strcpy(env), b);
	return (0);
}

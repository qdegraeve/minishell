/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:41:00 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/17 18:31:22 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

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

void	init_builtin(t_builtin *b, char **env)
{
	b->cd = "cd";
	b->quit = "quit";
	b->exit = "exit";
	b->env = "env";
	b->setenv = "setenv";
	b->unsetenv = "unsetenv";
	b->envir = env;
}

void	loop_fork(char **env, t_builtin b)
{
	pid_t	parent;
	char	**argv;
	char	*path;

	argv = NULL;
	init_builtin(&b, env);
	while(42)
	{
		b.argv = get_argv();
		path = get_command(b.argv[0], &b);
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
				execve(path, b.argv, env);
			exit(EXIT_SUCCESS);
		}
	}
}

int		main(int ac, char **av, char **env)
{
	t_builtin b;

	if (ac != 1 || av[1])
		return (0);
	ft_bzero(&b, sizeof(b));
	loop_fork(ft_tab_strcpy(env), b);
	return (0);
}
